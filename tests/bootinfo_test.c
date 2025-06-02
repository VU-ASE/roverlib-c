#include "unity.h"
#include "../include/roverlib/bootinfo.h"



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
        "        { \"name\": \"track_data\",   \"address\": \"tcp://unix:7890\" },"
        "        { \"name\": \"debug_info\",   \"address\": \"tcp://unix:7891\" }"
        "      ]"
        "    },"
        "    {"
        "      \"service\": \"navigation\","
        "      \"streams\": ["
        "        { \"name\": \"location_data\", \"address\": \"tcp://unix:7892\" }"
        "      ]"
        "    }"
        "  ],"
        "  \"outputs\": ["
        "    { \"name\": \"motor_movement\", \"address\": \"tcp://unix:7882\" },"
        "    { \"name\": \"sensor_data\",    \"address\": \"tcp://unix:7883\" }"
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


int main (void) {
    UNITY_BEGIN();
    //RUN_TEST(test_bootinfo);
    return UNITY_END();
}