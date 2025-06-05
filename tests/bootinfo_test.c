#include "unity.h"
#include "../include/roverlib/bootinfo.h"
#include "../include/roverlib/configuration.h"
#include "../include/roverlib/run.h"


void setUp(void) {
    // This function is called before each test
}
void tearDown(void) {
    // This function is called after each test
}

static void inject_valid_service(void) {
        const char *valid_json =
        "{"
        "  \"name\": \"controller\","
        "  \"version\": \"1.0.1\","
        "  \"inputs\": ["
        "    {"
        "      \"service\": \"imaging\","
        "      \"streams\": ["
        "        { \"name\": \"track-data\",   \"address\": \"tcp://unix:7890\" },"
        "        { \"name\": \"debug-info\",   \"address\": \"tcp://unix:7891\" }"
        "      ]"
        "    },"
        "    {"
        "      \"service\": \"navigation\","
        "      \"streams\": ["
        "        { \"name\": \"location-data\", \"address\": \"tcp://unix:7892\" }"
        "      ]"
        "    }"
        "  ],"
        "  \"outputs\": ["
        "    { \"name\": \"motor-movement\", \"address\": \"tcp://unix:7882\" },"
        "    { \"name\": \"sensor-data\",    \"address\": \"tcp://unix:7883\" }"
        "  ],"
        "  \"configuration\": ["
        "    { \"name\": \"max-iterations\", \"type\": \"number\", \"tunable\": true,  \"value\": 100 },"
        "    { \"name\": \"speed\",          \"type\": \"number\", \"tunable\": false, \"value\": 1.5 },"
        "    { \"name\": \"log-level\",      \"type\": \"string\", \"tunable\": false, \"value\": \"debug\" }"
        "  ],"
        "  \"tuning\": { \"enabled\": true, \"address\": \"tcp://unix:8829\" }"
        "}";
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, setenv("ASE_SERVICE", valid_json, 1),
                                  "Failed to set ASE_SERVICE to valid JSON");
}

static void inject_invalid_service(const char *variant) {
    if (strcmp(variant, "no-fields") == 0) {
        setenv("ASE_SERVICE", "{}", 1);
    }
    else if (strcmp(variant, "no-name") == 0) {
        setenv("ASE_SERVICE", "{\"version\":\"1.0.1\"}", 1);
    }
    else if (strcmp(variant, "no-version") == 0) {
        setenv("ASE_SERVICE", "{\"name\":\"controller\"}", 1);
    }
    else if (strcmp(variant, "no-inputs") == 0) {
        setenv("ASE_SERVICE", "{\"name\":\"controller\",\"version\":\"1.0.1\"}", 1);
    }
    else if (strcmp(variant, "no-outputs") == 0) {
        setenv("ASE_SERVICE", "{\"name\":\"controller\",\"version\":\"1.0.1\",\"inputs\":[]}", 1);
    }
    else if (strcmp(variant, "no-configuration") == 0) {
        setenv("ASE_SERVICE",
               "{\"name\":\"controller\",\"version\":\"1.0.1\",\"inputs\":[],\"outputs\":[]}",
               1);
    }
    else if (strcmp(variant, "no-tuning") == 0) {
        setenv("ASE_SERVICE",
               "{\"name\":\"controller\",\"version\":\"1.0.1\",\"inputs\":[],\"outputs\":[],\"configuration\":[]}",
               1);
    }
    else if (strcmp(variant, "malformed-json") == 0) {
        setenv("ASE_SERVICE", "{\"not\":\"correct json\",}", 1);
    }
    else if (strcmp(variant, "invalid-name") == 0) {
        setenv("ASE_SERVICE",
               "{\"name\":\"Controller!\",\"version\":\"1.0.1\",\"inputs\":[],\"outputs\":[],\"configuration\":[],\"tuning\":{}}",
               1);
    }
    else if (strcmp(variant, "invalid-version") == 0) {
        setenv("ASE_SERVICE",
               "{\"name\":\"controller\",\"version\":\"v1.0\",\"inputs\":[],\"outputs\":[],\"configuration\":[],\"tuning\":{}}",
               1);
    }
    else if (strcmp(variant, "invalid-alias") == 0) {
        setenv("ASE_SERVICE",
               "{\"name\":\"controller\",\"as\":\"Controller\",\"version\":\"1.0.1\",\"inputs\":[],\"outputs\":[],\"configuration\":[],\"tuning\":{}}",
               1);
    }
    else if (strcmp(variant, "invalid-input-type") == 0) {
        setenv("ASE_SERVICE",
               "{\"name\":\"controller\",\"version\":\"1.0.1\",\"inputs\":\"not-an-array\",\"outputs\":[],\"configuration\":[],\"tuning\":{}}",
               1);
    }
    else if (strcmp(variant, "extra-field") == 0) {
        setenv("ASE_SERVICE",
               "{\"name\":\"controller\",\"version\":\"1.0.1\",\"inputs\":[],\"outputs\":[],\"configuration\":[],\"tuning\":{},\"extra\":true}",
               1);
    }
    else if (strcmp(variant, "missing-input-stream") == 0) {
        setenv("ASE_SERVICE",
               "{"
               " \"name\":\"controller\",\"version\":\"1.0.1\","
               " \"inputs\":[{\"service\":\"imaging\",\"streams\":[{}]}],"
               " \"outputs\":[],\"configuration\":[],\"tuning\":{}"
               "}",
               1);
    }
    else if (strcmp(variant, "missing-input-service") == 0) {
        setenv("ASE_SERVICE",
               "{"
               " \"name\":\"controller\",\"version\":\"1.0.1\","
               " \"inputs\":["
               "    {\"service\":\"\",\"streams\":[{\"name\":\"track_data\",\"address\":\"tcp://unix:7890\"}]}]"
               " ,\"outputs\":[],\"configuration\":[],\"tuning\":{}"
               "}",
               1);
    }
    else if (strcmp(variant, "missing-output-name") == 0) {
        setenv("ASE_SERVICE",
               "{"
               " \"name\":\"controller\",\"version\":\"1.0.1\","
               " \"inputs\":[],"
               " \"outputs\":[{\"name\":\"\",\"address\":\"tcp://unix:7882\"}],"
               " \"configuration\":[],\"tuning\":{}"
               "}",
               1);
    }
    else if (strcmp(variant, "missing-output-address") == 0) {
        setenv("ASE_SERVICE",
               "{"
               " \"name\":\"controller\",\"version\":\"1.0.1\","
               " \"inputs\":[],"
               " \"outputs\":[{\"name\":\"motor_movement\",\"address\":\"\"}],"
               " \"configuration\":[],\"tuning\":{}"
               "}",
               1);
    }
    else if (strcmp(variant, "non-boolean") == 0) {
        setenv("ASE_SERVICE",
               "{"
               " \"name\":\"controller\",\"version\":\"1.0.1\","
               " \"inputs\":[],\"outputs\":[],\"configuration\":[],"
               " \"tuning\":{\"enabled\":\"yes\",\"address\":\"tcp://unix:8829\"}"
               "}",
               1);
    }
    else if (strcmp(variant, "invalid-config-number") == 0) {
        setenv("ASE_SERVICE",
               "{"
               " \"name\":\"controller\",\"version\":\"1.0.1\",\"inputs\":[],\"outputs\":[],"
               " \"configuration\":[{\"name\":\"option\",\"type\":\"integer\",\"tunable\":true,\"value\":5}],"
               " \"tuning\":{\"enabled\":true,\"address\":\"tcp://unix:8829\"}"
               "}",
               1);
    }
    else if (strcmp(variant, "type-mismatch") == 0) {
        setenv("ASE_SERVICE",
               "{"
               " \"name\":\"controller\",\"version\":\"1.0.1\",\"inputs\":[],\"outputs\":[],"
               " \"configuration\":[{\"name\":\"option\",\"type\":\"string\",\"tunable\":true,\"value\":123}],"
               " \"tuning\":{\"enabled\":true,\"address\":\"tcp://unix:8829\"}"
               "}",
               1);
    }
}



// -------- VALID BOOTSPEC TESTS --------


// -------- Test 1: A valid service definition with no operations returns 0

// helper function that does nothing
static int main_no_operation(struct Service s, Service_configuration *config) {
    (void)s;
    (void)config;
    return 0;
}

// Test that a valid service with no operations returns 0
void test_valid_empty_program(void) {
    inject_valid_service();

    int result = run(main_no_operation);
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, result, "run(main_no_operation) should return 0 for valid service");
}

// -------- Test 2: Whether a valid service parses the correct configuration values

// static variables to hold the configuration values
static double got_max_iterations;
static double got_speed;
static char got_log_level[64];

// helper function that collects the configuration values and makes sure they are not NULL
static int main_config_access(struct Service s, Service_configuration *config) {
    // check max-iterations with safe access
    double *p1 = get_float_value_safe(config, "max-iterations");
    TEST_ASSERT_NOT_NULL_MESSAGE(p1, "max-iterations should be present in configuration");
    got_max_iterations = *p1;

    // check speed
    double *p2 = get_float_value(config, "speed");
    TEST_ASSERT_NOT_NULL_MESSAGE(p2, "speed should be present in configuration");
    got_speed = *p2;

    // check log-level
    char *p3 = get_string_value(config, "log-level");
    TEST_ASSERT_NOT_NULL_MESSAGE(p3, "log-level should be present in configuration");
    strncpy(got_log_level, p3, sizeof(got_log_level));

    return 0;
}

// Test that a valid service with configuration access returns the correct values
void test_valid_configuration_access(void) {
    inject_valid_service();

    int result = run(main_config_access);
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, result, "run(main_config_access) should return 0 for valid service");

    // check the values
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(100.0f, (float)got_max_iterations, "max-iterations mismatch");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(1.5f, (float)got_speed, "speed mismatch");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("debug", got_log_level, "log-level mismatch");
}


// -------- Test 3: A valid service with inputs and outputs

// static structs to hold the input and output data
static struct {
    char service[64];
    char name[64];
    char address[128];
} got_inputs[10];
static int got_input_count;

static struct {
    char name[64];
    char address[128];
} got_outputs[10];
static int got_output_count;

// helper function collects input and output data
static int main_service_access(struct Service s, Service_configuration *config) {
        // Capture inputs: for each Input in s.inputs, for each Stream in input->streams
    got_input_count = 0;
    void *inp_elem = list_get_head(s.inputs);
    while (inp_elem) {
        struct Input *inp = (struct Input *)inp_elem;
        void *str_elem = list_get_head(inp->streams);
        while (str_elem) {
            struct Stream *st = (struct Stream *)str_elem;
            // Store into captured_inputs
            strncpy(got_inputs[got_input_count].service, inp->service, sizeof(got_inputs[0].service));
            strncpy(got_inputs[got_input_count].name, st->name, sizeof(got_inputs[0].name));
            strncpy(got_inputs[got_input_count].address, st->address, sizeof(got_inputs[0].address));
            got_input_count++;
            str_elem = list_get_next(inp->streams);
        }
        inp_elem = list_get_next(s.inputs);
    }

    // Capture outputs: for each Output in s.outputs
    got_output_count = 0;
    void *out_elem = list_get_head(s.outputs);
    while (out_elem) {
        struct Output *out = (struct Output *)out_elem;
        strncpy(got_outputs[got_output_count].name, out->name, sizeof(got_outputs[0].name));
        strncpy(got_outputs[got_output_count].address, out->address, sizeof(got_outputs[0].address));
        got_output_count++;
        out_elem = list_get_next(s.outputs);
    }

    return 0;
}

// Test that a valid service with inputs and outputs returns the correct values
void test_valid_service_access(void) {
    inject_valid_service();

    int result = run(main_service_access);
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, result, "run(main_service_access) should return 0 for valid service");

    // Expected inputs: 3 entries
    struct {
        const char *service;
        const char *name;
        const char *address;
    } want_inputs[] = {
        { "imaging",    "track-data",    "tcp://unix:7890" },
        { "imaging",    "debug-info",    "tcp://unix:7891" },
        { "navigation", "location-data", "tcp://unix:7892" }
    };
    TEST_ASSERT_EQUAL_INT_MESSAGE(3, got_input_count, "Input count mismatch");
    for (int i = 0; i < 3; i++) {
        TEST_ASSERT_EQUAL_STRING_MESSAGE(want_inputs[i].service, got_inputs[i].service, "Input.service mismatch");
        TEST_ASSERT_EQUAL_STRING_MESSAGE(want_inputs[i].name,    got_inputs[i].name,    "Input.name mismatch");
        TEST_ASSERT_EQUAL_STRING_MESSAGE(want_inputs[i].address, got_inputs[i].address, "Input.address mismatch");
    }

    // Expected outputs: 2 entries
    struct {
        const char *name;
        const char *address;
    } want_outputs[] = {
        { "motor-movement", "tcp://unix:7882" },
        { "sensor-data",    "tcp://unix:7883" }
    };
    TEST_ASSERT_EQUAL_INT_MESSAGE(2, got_output_count, "Output count mismatch");
    for (int i = 0; i < 2; i++) {
        TEST_ASSERT_EQUAL_STRING_MESSAGE(want_outputs[i].name,    got_outputs[i].name,    "Output.name mismatch");
        TEST_ASSERT_EQUAL_STRING_MESSAGE(want_outputs[i].address, got_outputs[i].address, "Output.address mismatch");
    }
}



// -------- INVALID BOOTSPEC TESTS --------

// -------- Test 4: inavlid bootspecs cause run to return != 0

// helper function that does nothing
static int main_invalid(struct Service s, Service_configuration *config) {
    (void)s;
    (void)config;
    return 0; // This should never be called
}

// Test that an invalid service definition returns != 0
void test_invalid_bootspecs(void) {
        const char *invalids[] = {
        "no-name",
        "no-version",
        "no-inputs",
        "no-outputs",
        "no-configuration",
        "no-tuning",
        "malformed-json",
        "invalid-name",
        "invalid-version",
        "invalid-alias",
        "invalid-input-type",
        "extra-field",
        "missing-input-stream",
        "missing-input-service",
        "missing-output-name",
        "missing-output-address",
        "non-boolean",
        "invalid-config-number", 
        "type-mismatch"
    };
    const int n_invalid = sizeof(invalids)/sizeof(invalids[0]);

    for (int i = 0; i < n_invalid; i++) {
        inject_invalid_service(invalids[i]);
        int result = run(main_invalid);
        char msgbuf[128];
        snprintf(msgbuf, sizeof(msgbuf), "Variant \"%s\" should cause run(...) != 0, but got 0", invalids[i]);
        TEST_ASSERT_NOT_EQUAL_MESSAGE(0, result, msgbuf);
    }
}

int main (void) {
    printf("CODE: Starting bootinfo tests...\n");
    UNITY_BEGIN();
    // Valid service tests
    printf("BEFORE RUNNING TESTS\n");
    RUN_TEST(test_valid_empty_program);
    printf("AFTER FIRST TEST\n");
    printf("BEFORE RUNNING CONFIGURATION TESTS\n");
    RUN_TEST(test_valid_configuration_access);
    printf("AFTER SECOND TEST\n");
    RUN_TEST(test_valid_service_access);
    printf("AFTER THIRD TEST\n");
    // Invalid service tests
    RUN_TEST(test_invalid_bootspecs);
    printf("AFTER INVALID TESTS\n");
    return UNITY_END();
}