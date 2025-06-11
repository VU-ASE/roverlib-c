#include "unity.h"
#include <string.h>
#include <pthread.h>
#include "../include/roverlib/bootinfo.h"
#include "../include/roverlib/configuration.h"


void setUp(void) {
    // This function is called before each test
}
void tearDown(void) {
    // This function is called after each test
}

// Helper function to build a service with two valid configuration entries
// "config1" -> TYPE_NUMBER, value 3.14, tunable = true
// "config2" -> TYPE_STRING, value "auto", tunable = false
static Service make_sample_service(void) {
    Service service;
    memset(&service, 0, sizeof(Service));

    // Create a list for service.configuration
    list_t *configuration_list = list_create(false, NULL);
    TEST_ASSERT_NOT_NULL(configuration_list);

    // Add "config1" as a tunable number
    Configuration *config1 = malloc(sizeof(Configuration));
    TEST_ASSERT_NOT_NULL_MESSAGE(config1, "Failed to allocate memory for config1");
    config1->name = strdup("config1");
    TEST_ASSERT_NOT_NULL_MESSAGE(config1->name, "Failed to allocate memory for config1 name");
    config1->type = malloc(sizeof(enum Type));
    TEST_ASSERT_NOT_NULL_MESSAGE(config1->type, "Failed to allocate memory for config1 type");
    *config1->type = TYPE_NUMBER;
    config1->tunable = malloc(sizeof(bool));
    TEST_ASSERT_NOT_NULL_MESSAGE(config1->tunable, "Failed to allocate memory for config1 tunable");
    *config1->tunable = true;
    config1->value = malloc(sizeof(struct Value));
    TEST_ASSERT_NOT_NULL_MESSAGE(config1->value, "Failed to allocate memory for config1 value");
    memset(config1->value, 0, sizeof(struct Value));
    config1->value->type = TYPE_NUMBER;
    config1->value->value.number = 3.14;
    list_add_tail(configuration_list, config1, sizeof(Configuration *));

    // Add "config2" as a non-tunable string
    Configuration *config2 = malloc(sizeof(Configuration));
    TEST_ASSERT_NOT_NULL_MESSAGE(config2, "Failed to allocate memory for config2");
    config2->name = strdup("config2");
    TEST_ASSERT_NOT_NULL_MESSAGE(config2->name, "Failed to allocate memory for config2 name");
    config2->type = malloc(sizeof(enum Type));
    TEST_ASSERT_NOT_NULL_MESSAGE(config2->type, "Failed to allocate memory for config2 type");
    *config2->type = TYPE_STRING;
    config2->tunable = malloc(sizeof(bool));
    TEST_ASSERT_NOT_NULL_MESSAGE(config2->tunable, "Failed to allocate memory for config2 tunable");
    *config2->tunable = false;
    config2->value = malloc(sizeof(struct Value));
    TEST_ASSERT_NOT_NULL_MESSAGE(config2->value, "Failed to allocate memory for config2 value");
    memset(config2->value, 0, sizeof(struct Value));
    config2->value->type = TYPE_STRING;
    config2->value->value.string = strdup("auto");
    list_add_tail(configuration_list, config2, sizeof(Configuration *));

    service.configuration = configuration_list;
    return service;
}

// Helper function to free service.configuration and all substructures
static void free_sample_service(Service *service) {
    // Ensure service and its configuration list are valid
    if (!service || !service->configuration) return;

    // Free each Configuration in the list
    Configuration *config = list_get_head(service->configuration);
    while (config) {
        if (config->name) free(config->name);
        if (config->type) free(config->type);
        if (config->tunable) free(config->tunable);
        if (config->value) {
            if (config->value->type == TYPE_STRING && config->value->value.string) {
                free(config->value->value.string);
            }
            free(config->value);
        }
        Configuration *next = list_get_next(service->configuration);
        free(config);
        config = next;
    }
    list_release(service->configuration);
}

// -------- Test 1: Check that new_service_configuration initializes correctly
void test_new_service_configuration(void) {
    Service service = make_sample_service();
    Service_configuration config = new_service_configuration(service);

    // Check float value for "config1"
    double *float_value = get_float_value(&config, "config1");
    TEST_ASSERT_NOT_NULL_MESSAGE(float_value, "Float value for config1 should not be NULL");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(3.14f, (float)*float_value, "Float value for config1 should be 3.14");

    // Check string value for "config2"
    char *string_value = get_string_value(&config, "config2");
    TEST_ASSERT_NOT_NULL_MESSAGE(string_value, "String value for config2 should not be NULL");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("auto", string_value, "String value for config2 should be 'auto'");

    // Check that only "config1" is tunable
    TEST_ASSERT_TRUE_MESSAGE(hashtable_has_key(config.tunable, "config1"), "config1 should be tunable");
    TEST_ASSERT_FALSE_MESSAGE(hashtable_has_key(config.tunable, "config2"), "config2 should not be tunable");

    // Clean up
    free_sample_service(&service);
    hashtable_release(config.float_values);
    hashtable_release(config.string_values);
    hashtable_release(config.tunable);
    pthread_rwlock_destroy(config.rwlock);
    free(config.rwlock);
}


// -------- Test 2: Happy and sad getters for float and string values
void test_getters_happy_and_sad(void) {
    Service service = make_sample_service();
    Service_configuration config = new_service_configuration(service);

    // Happy path for float value
    double *float_value = get_float_value(&config, "config1");
    TEST_ASSERT_NOT_NULL_MESSAGE(float_value, "Float value for config1 should not be NULL");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(3.14f, (float)*float_value, "Float value for config1 should be 3.14");

    // Sad path for float value
    double *sad_float_value = get_float_value(&config, "config2");
    TEST_ASSERT_NULL_MESSAGE(sad_float_value, "Float value for config2 key should be NULL");

    // Happy path for string value
    char *string_value = get_string_value(&config, "config2");
    TEST_ASSERT_NOT_NULL_MESSAGE(string_value, "String value for config2 should not be NULL");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("auto", string_value, "String value for config2 should be 'auto'");

    // Sad path for string value
    char *sad_string_value = get_string_value(&config, "config1");
    TEST_ASSERT_NULL_MESSAGE(sad_string_value, "String value for config1 key should be NULL");

    // Clean up
    free_sample_service(&service);
    hashtable_release(config.float_values);
    hashtable_release(config.string_values);
    hashtable_release(config.tunable);
    pthread_rwlock_destroy(config.rwlock);
    free(config.rwlock);
}

// -------- Test 3: Concurrent GetFloatSafe (20 threads)
// The struct thread_arg_t is used to pass the configuration and key to the thread function
typedef struct {
    Service_configuration *config;
    char *key;
} thread_arg_t;

// This function is executed by each thread to read the float value concurrently
static void *thread_read_float(void *arg) {
    thread_arg_t *targ = (thread_arg_t *)arg;
    double *value = get_float_value_safe(targ->config, targ->key);
    if (value == NULL || *value != 3.14) {
        Unity.CurrentTestFailed = 1;
    }
    return NULL;
}

void test_get_float_safe_concurrent(void) {
    Service service = make_sample_service();
    Service_configuration config = new_service_configuration(service);

    // Create 20 threads to read the float value concurrently
    pthread_t threads[20];
    thread_arg_t ta = { .config = &config, .key = "config1" };

    for (int i = 0; i < 20; i++) {
        int result = pthread_create(&threads[i], NULL, thread_read_float, &ta);
        TEST_ASSERT_EQUAL_INT_MESSAGE(0, result, "Failed to create thread for reading float value");
    }
    for (int i = 0; i <20; i++) {
        pthread_join(threads[i], NULL);
    }

    // Clean up logic
    free_sample_service(&service);
    hashtable_release(config.float_values);
    hashtable_release(config.string_values);
    hashtable_release(config.tunable);
    pthread_rwlock_destroy(config.rwlock);
    free(config.rwlock);
}


// -------- Test 4: Concurrent GetStringSafe (20 threads)
static void *thread_read_string(void *arg) {
    thread_arg_t *targ = (thread_arg_t *)arg;
    char *value = get_string_value_safe(targ->config, targ->key);
    if (value == NULL || strcmp(value, "auto") != 0) {
        Unity.CurrentTestFailed = 1;
    }
    return NULL;
}

void test_get_string_safe_concurrent(void) {
    Service service = make_sample_service();
    Service_configuration config = new_service_configuration(service);

    // Create 20 threads to read the string value concurrently
    pthread_t threads[20];
    thread_arg_t ta = { .config = &config, .key = "config2" };

    for (int i = 0; i < 20; i++) {
        int result = pthread_create(&threads[i], NULL, thread_read_string, &ta);
        TEST_ASSERT_EQUAL_INT_MESSAGE(0, result, "Failed to create thread for reading string value");
    }
    for (int i = 0; i < 20; i++) {
        pthread_join(threads[i], NULL);
    }

    // Clean up logic
    free_sample_service(&service);
    hashtable_release(config.float_values);
    hashtable_release(config.string_values);
    hashtable_release(config.tunable);
    pthread_rwlock_destroy(config.rwlock);
    free(config.rwlock);
}

// -------- Test 5: Setting floats on tunable and non-tunable keys
void test_set_float_value(void) {
    Service service = make_sample_service();
    Service_configuration config = new_service_configuration(service);

    // "config1" is tunable, so we should be able to update it to 6.28
    set_float_value(&config, "config1", 6.28);
    double *updated_float_value = get_float_value(&config, "config1");
    TEST_ASSERT_NOT_NULL_MESSAGE(updated_float_value, "Updated float value for config1 should not be NULL");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(6.28f, (float)*updated_float_value, "Updated float value for config1 should be 6.28");

    // "config2" is not tunable, so setting it should not change the value
    set_float_value(&config, "config2", 9.81);
    double *non_tunable_float_value = get_float_value(&config, "config2");
    TEST_ASSERT_NULL_MESSAGE(non_tunable_float_value, "Float value for non-tunable config2 should be NULL");

    // Clean up
    free_sample_service(&service);
    hashtable_release(config.float_values);
    hashtable_release(config.string_values);
    hashtable_release(config.tunable);
    pthread_rwlock_destroy(config.rwlock);
    free(config.rwlock);
}

// -------- Test 6: Getters for missing keys should return NULL
void test_get_missing_keys(void) {
    Service service = make_sample_service();
    Service_configuration config = new_service_configuration(service);

    // Try to get a float value for a missing key
    double *missing_float_value = get_float_value(&config, "missing_key");
    TEST_ASSERT_NULL_MESSAGE(missing_float_value, "Float value for missing key should be NULL");

    // Try to get a string value for a missing key
    char *missing_string_value = get_string_value(&config, "missing_key");
    TEST_ASSERT_NULL_MESSAGE(missing_string_value, "String value for missing key should be NULL");

    // Clean up
    free_sample_service(&service);
    hashtable_release(config.float_values);
    hashtable_release(config.string_values);
    hashtable_release(config.tunable);
    pthread_rwlock_destroy(config.rwlock);
    free(config.rwlock);
}

int main (void) {
    UNITY_BEGIN();
    RUN_TEST(test_new_service_configuration);
    RUN_TEST(test_getters_happy_and_sad);
    RUN_TEST(test_get_float_safe_concurrent);
    RUN_TEST(test_get_string_safe_concurrent);
    RUN_TEST(test_set_float_value);
    RUN_TEST(test_get_missing_keys);
    return UNITY_END();
}