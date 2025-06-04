#include "unity.h"
#include <string.h>
#include <list.h>
#include "../include/roverlib/bootinfo.h"
#include "../include/roverlib/streams.h"

void setUp(void) {
    // This function is called before each test
}
void tearDown(void) {
    // This function is called after each test
}

// Helper function to create a sample service with valid output and input streams
// It has a output ("testOutput", "tcp://unix:5555")
// and an input ("testService", "testInput", "tcp://unix:6666") stream
static Service make_sample_service(void) {
    Service service;
    memset(&service, 0, sizeof(Service));

    // Create a list for service.outputs
    list_t *outputs = list_create(false, NULL);
    TEST_ASSERT_NOT_NULL_MESSAGE(outputs, "Failed to create outputs list");

    Output *output = malloc(sizeof(Output));
    TEST_ASSERT_NOT_NULL_MESSAGE(output, "Failed to allocate memory for output");
    output->name = strdup("testOutput");
    TEST_ASSERT_NOT_NULL_MESSAGE(output->name, "Failed to allocate memory for output name");
    output->address = strdup("tcp://localhost:5555");
    TEST_ASSERT_NOT_NULL_MESSAGE(output->address, "Failed to allocate memory for output address");
    list_add_tail(outputs, output, sizeof(Output *));

    service.outputs = outputs;

    // Create a list for service.inputs
    list_t *inputs = list_create(false, NULL);
    TEST_ASSERT_NOT_NULL_MESSAGE(inputs, "Failed to create inputs list");
    
    Input *input = malloc(sizeof(Input));
    TEST_ASSERT_NOT_NULL_MESSAGE(input, "Failed to allocate memory for input");
    input->service = strdup("testService");
    TEST_ASSERT_NOT_NULL_MESSAGE(input->service, "Failed to allocate memory for input service name");

    // Create a list for input streams
    list_t *streams = list_create(false, NULL);
    TEST_ASSERT_NOT_NULL_MESSAGE(streams, "Failed to create streams list");
    Stream *stream = malloc(sizeof(Stream));
    TEST_ASSERT_NOT_NULL_MESSAGE(stream, "Failed to allocate memory for stream");
    stream->name = strdup("testInput");
    TEST_ASSERT_NOT_NULL_MESSAGE(stream->name, "Failed to allocate memory for stream name");
    stream->address = strdup("tcp://unix:6666");
    TEST_ASSERT_NOT_NULL_MESSAGE(stream->address, "Failed to allocate memory for stream address");
    list_add_tail(streams, stream, sizeof(Stream *));

    input->streams = streams;
    list_add_tail(inputs, input, sizeof(Input *));
    service.inputs = inputs;

    return service;
}

// Helper function to free the sample service
static void free_sample_service(Service *service) {
    if (!service) return;

    // Free outputs
    if (service->outputs) {
        Output *output = list_get_head(service->outputs);
        while (output) {
            if (output->name) free(output->name);
            if (output->address) free(output->address);
            Output *next_output = list_get_next(service->outputs);
            free(output);
            output = next_output;
        }
        list_release(service->outputs);
    }

    // Free inputs
    if (service->inputs) {
        Input *input = list_get_head(service->inputs);
        while (input) {
            if (input->service) free(input->service);

            // Free each stream in input
            if (input->streams) {
                Stream *stream = list_get_head(input->streams);
                while (stream) {
                    if (stream->name) free(stream->name);
                    if (stream->address) free(stream->address);
                    Stream *next_stream = list_get_next(input->streams);
                    free(stream);
                    stream = next_stream;
                }
                list_release(input->streams);
            }
            Input *next_input = list_get_next(service->inputs);
            free(input);
            input = next_input;
        }
        list_release(service->inputs);
    }
}

// -------- Test 1: get_write_stream happy path
void test_get_write_stream(void) {
    Service service = make_sample_service();

    // Try to get the write stream for the output "testOutput"
    write_stream *stream1 = get_write_stream(&service, "testOutput");
    TEST_ASSERT_NOT_NULL_MESSAGE(stream1, "get_write_stream should return a valid stream");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("tcp://localhost:5555", stream1->address, "Stream address should match output address");

    // Call again does not store singletons, so we expect a fresh malloc
    write_stream *stream2 = get_write_stream(&service, "testOutput");
    TEST_ASSERT_NOT_NULL_MESSAGE(stream2, "get_write_stream should return a valid stream on second call");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("tcp://localhost:5555", stream2->address, "Stream address should match output address");
    TEST_ASSERT_EQUAL_INT64(0, stream2->bytes);

    // Pointers should differ
    TEST_ASSERT_NOT_EQUAL_MESSAGE(stream1, stream2, "get_write_stream should return different pointers on each call");

    // Clean up
    free(stream1);
    free(stream2);
    free_sample_service(&service);
}

// -------- Test 2: get_read_stream happy path
void test_get_read_stream(void) {
    Service service = make_sample_service();

    // Try to get the read stream for the input "testService" and stream "testInput"
    read_stream *stream1 = get_read_stream(&service, "testService", "testInput");
    TEST_ASSERT_NOT_NULL_MESSAGE(stream1, "get_read_stream should return a valid stream");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("tcp://unix:6666", stream1->address, "Stream address should match input stream address");

    // Call again does not store singletons, so we expect a fresh malloc
    read_stream *stream2 = get_read_stream(&service, "testService", "testInput");
    TEST_ASSERT_NOT_NULL_MESSAGE(stream2, "get_read_stream should return a valid stream on second call");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("tcp://unix:6666", stream2->address, "Stream address should match input stream address");
    TEST_ASSERT_EQUAL_INT64(0, stream2->bytes);

    // Pointers should differ
    TEST_ASSERT_NOT_EQUAL_MESSAGE(stream1, stream2, "get_read_stream should return different pointers on each call");

    // Clean up
    free(stream1);
    free(stream2);
    free_sample_service(&service);
}

// -------- Test 3: get_write_stream on a non-existent output must return NULL
void test_get_write_stream_missing(void) {
    Service service = make_sample_service();

    // Try to get a write stream for a non-existent output
    write_stream *stream = get_write_stream(&service, "nonExistentOutput");
    TEST_ASSERT_NULL_MESSAGE(stream, "get_write_stream should return NULL for non-existent output");

    // Clean up
    free_sample_service(&service);
}

// -------- Test 4: get_read_stream on a non-existent input must return NULL
void test_get_read_stream_missing(void) {
    Service service = make_sample_service();

    // Try to get a read stream for a non-existent input
    read_stream *stream = get_read_stream(&service, "nonExistentService", "nonExistentInput");
    TEST_ASSERT_NULL_MESSAGE(stream, "get_read_stream should return NULL for non-existent input");

    // Clean up
    free_sample_service(&service);
}

int main (void) {
    UNITY_BEGIN();
    RUN_TEST(test_get_write_stream);
    RUN_TEST(test_get_read_stream);
    RUN_TEST(test_get_write_stream_missing);
    RUN_TEST(test_get_read_stream_missing);
    return UNITY_END();
}