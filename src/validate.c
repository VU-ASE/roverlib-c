#include "../include/roverlib/validate.h"
#include "string.h"
#include <ctype.h> 

// Helper where we parse an unsigned intiger without any leading zeros
static bool parse_unsigned_int(const char **p) {
    const char *start = *p;
    
    if (!isdigit((unsigned char) *start)) {
        return false; // Must start with a digit
    }

    if (*start == '0' && isdigit((unsigned char) *(start + 1))) {
        return false; // Leading zero is not allowed unless it's the only digit
    }

    while (isdigit((unsigned char) *start)) {
        start++;
    }
    *p = start; // Update the pointer to the next character

    return true;
}

// ------- enforce ^[a-z]+(-[a-z]+)*$
bool is_valid_name(const char *name) {
    if (name == NULL || name[0] == '\0') {
        return false; // Empty string is invalid
    }

    // Check the first character is a lowercase letter
    if (name[0] < 'a' || name[0] > 'z') {
        return false; // First character must be a lowercase letter
    }

    // Check the rest of the string, that it contains only lowercase letters and hyphens
    for (const char *p = name + 1; *p; p++) {
        if (*p == '-') {
            if (!*(p + 1) || !(*(p + 1) >= 'a' && *(p + 1) <= 'z')) {
                return false; // hyphen must be followed by a lowercase letter
            }
        }
        else if (!(*p >= 'a' && *p <= 'z')) {
            return false; // Must be a lowercase letter
        }
    }

    return true; // Placeholder, actual validation logic should be implemented
}

// ------- check: X.Y.Z with optional suffix
bool is_valid_version(const char *version) {
    if (version == NULL || version[0] == '\0') {
        return false; // Empty string is invalid
    }

    // check the major version
    if (!parse_unsigned_int(&version)) {
        return false; // Major version must be a valid unsigned integer
    }
    if (*version != '.') {
        return false; // Major version must be followed by a dot
    }
    version++; // Move past the dot

    // check the minor version
    if (!parse_unsigned_int(&version)) {
        return false; // Minor version must be a valid unsigned integer
    }
    if (*version != '.') {
        return false; // Minor version must be followed by a dot
    }
    version++; // Move past the dot

    // check the patch version
    if (!parse_unsigned_int(&version)) {
        return false; // Patch version must be a valid unsigned integer
    }

    // Check for optional suffix, either end‐of‐string, or '-' (prerelease), or '+' (build metadata)
    if (*version == '\0') {
        return true; // Valid version with no suffix
    }
    
    if (*version == '-' || *version == '+') {
        version++; // Move past the hyphen or plus sign
        if (!*version) {
            return false; // Suffix cannot be empty
        }

        // The suffix must be alphanumeric, hyphen or dots
        while (*version) {
            if (!(( *version >= '0' && *version <= '9') ||
                  ( *version >= 'A' && *version <= 'Z') ||
                  ( *version >= 'a' && *version <= 'z') ||
                   *version == '-' || *version == '.')) 
            {
                return false;
            }
            version++;
        }
        return true;
    }

    return false; 
}

// ------- ensure a non-empty string that starts with "tcp://"
bool is_valid_address(const char *address) {
    const char *prefix = "tcp://";
    size_t prefix_len = strlen(prefix);

    if (address == NULL || strlen(address) < prefix_len) {
        return false; // Address must be at least as long as the prefix
    }

    if (strncmp(address, prefix, prefix_len) != 0) {
        return false; // Address must start with "tcp://"
    }

    // Check the rest of the address is non-empty
    if (address[prefix_len] == '\0') {
        return false; // Address must not be empty after the prefix
    }

    return true; 
}

// ------- enforce the whole schema at once
bool is_valid_schema(const cJSON *schema) {
    if (schema == NULL) {
        return false; // Schema cannot be NULL
    }

    // 1. ------- Check for any extra top-level fields
    // The only allowed fields are "name", "as", "version", "inputs", "outputs", "configuration", and "tuning"
    const char *allowed_fields[] = {
        "name", "as", "version", "inputs", "outputs", "configuration", "tuning"
    };

    for (cJSON *child = schema->child; child; child = child->next) {
        const char *key = child->string;
        bool found_extra_field = false;
        for (size_t i = 0; i < sizeof(allowed_fields) / sizeof(allowed_fields[0]); i++) {
            if (strcmp(key, allowed_fields[i]) == 0) {
                found_extra_field = true;
                break;
            }
        }
        if (!found_extra_field) {
            return false; // Found an extra field that is not allowed
        }
    }

    // 2. ------- Check that name exists and is a valid name using is_valid_name
    cJSON *name_item = cJSON_GetObjectItemCaseSensitive(schema, "name");
    if (!cJSON_IsString(name_item) || !is_valid_name(name_item->valuestring)) {
        return false; // "name" must be a string and valid according to is_valid_name
    }

    // 3. ------- check if "as" exists and is a valid name if present
    cJSON *as_item = cJSON_GetObjectItemCaseSensitive(schema, "as");
    if (as_item) {
        if (!cJSON_IsString(as_item) || !is_valid_name(as_item->valuestring)) {
            return false; // "as" must be a string and valid according to is_valid_name
        }
    }

    // 4. ------- Check that version exists and is a valid version using is_valid_version
    cJSON *version_item = cJSON_GetObjectItemCaseSensitive(schema, "version");
    if (!cJSON_IsString(version_item) || !is_valid_version(version_item->valuestring)) {
        return false; // "version" must be a string and valid according to is_valid_version
    }

    // 5. ------- check that inputs is an array of objects
    cJSON *inputs = cJSON_GetObjectItemCaseSensitive(schema, "inputs");
    if (!cJSON_IsArray(inputs)) {
        return false; // "inputs" must be an array
    }
    {
        cJSON * input_object = NULL;
        cJSON_ArrayForEach(input_object, inputs) {

            // Each element in the inputs array must be an object with "service" (valid name) and "streams" fields (array)
            if (!cJSON_IsObject(input_object)) {
                return false; 
            }
            cJSON *service_item = cJSON_GetObjectItemCaseSensitive(input_object, "service");
            cJSON *streams_item = cJSON_GetObjectItemCaseSensitive(input_object, "streams");
            if (!cJSON_IsString(service_item) || !is_valid_name(service_item->valuestring)) {
                return false; // "service" must be a string and valid according to is_valid_name
            }
            if (!cJSON_IsArray(streams_item)) {
                return false; // "streams" must be an array
            }

            // Each element in the streams array must be an object with "name" (valid name) and "address" (valid address)
            cJSON *stream_object = NULL;
            cJSON_ArrayForEach(stream_object, streams_item) {
                if (!cJSON_IsObject(stream_object)) {
                    return false;
                }

                cJSON *stream_name_item = cJSON_GetObjectItemCaseSensitive(stream_object, "name");
                cJSON *stream_address_item = cJSON_GetObjectItemCaseSensitive(stream_object, "address");
                if (!cJSON_IsString(stream_name_item) || !is_valid_name(stream_name_item->valuestring)) {
                    return false; // "name" must be a string and valid according to is_valid_name
                }
                if (!cJSON_IsString(stream_address_item) || !is_valid_address(stream_address_item->valuestring)) {
                    return false; // "address" must be a string and valid according to is_valid_address
                }

            }
            
        }

        // 6. ------- Check that outputs exists and is an array of object
        cJSON *outputs = cJSON_GetObjectItemCaseSensitive(schema, "outputs");
        if (!cJSON_IsArray(outputs)) {
            return false; // "outputs" must be an array
        }
        {
            cJSON *output_object = NULL;
            cJSON_ArrayForEach(output_object, outputs) {
                if (!cJSON_IsObject(output_object)) {
                    return false; // Each output must be an object
                }

                cJSON *output_name_item = cJSON_GetObjectItemCaseSensitive(output_object, "name");
                cJSON *output_address_item = cJSON_GetObjectItemCaseSensitive(output_object, "address");
                if (!cJSON_IsString(output_name_item) || !is_valid_name(output_name_item->valuestring)) {
                    return false; // "name" must be a string and valid according to is_valid_name
                }
                if (!cJSON_IsString(output_address_item) || !is_valid_address(output_address_item->valuestring)) {
                    return false; // "address" must be a string and valid according to is_valid_address
                }
            }
        }

        // 7. ------- Check that configuration exists and is an array of objects
        cJSON *configuration = cJSON_GetObjectItemCaseSensitive(schema, "configuration");
        if (!cJSON_IsArray(configuration)) {
            return false; // "configuration" must be an array
        }
        {
            cJSON *config_object = NULL;
            cJSON_ArrayForEach(config_object, configuration) {
                if (!cJSON_IsObject(config_object)) {
                    return false; // Each configuration must be an object
                }

                cJSON *config_name_item = cJSON_GetObjectItemCaseSensitive(config_object, "name");
                cJSON *config_type_item = cJSON_GetObjectItemCaseSensitive(config_object, "type");
                cJSON *config_tunable_item = cJSON_GetObjectItemCaseSensitive(config_object, "tunable");
                cJSON *config_value_item = cJSON_GetObjectItemCaseSensitive(config_object, "value");

                if (!cJSON_IsString(config_name_item) || !is_valid_name(config_name_item->valuestring)) {
                    return false; // "name" must be a string and valid according to is_valid_name
                }
                
                if (!cJSON_IsString(config_type_item)) {
                    return false; // "type" must be a string
                }

                int is_number_type = strcmp(config_type_item->valuestring, "number") == 0;
                int is_string_type = strcmp(config_type_item->valuestring, "string") == 0;
                if (!is_number_type && !is_string_type) {
                    return false; // "type" must be either "number" or "string"
                }

                if (!cJSON_IsBool(config_tunable_item)) {
                    return false; // "tunable" must be a boolean
                }
                if (is_number_type) {
                    if (!cJSON_IsNumber(config_value_item)) {
                        return false; // "value" must be a number if type is "number"
                    }
                } else {
                    if (!cJSON_IsString(config_value_item)) {
                        return false; // "value" must be a string if type is "string"
                    }
                }
            }
        }

        // 8. ------- Check that tuning exists and is an object with "enabled" (boolean) and "address" (valid address)
        cJSON *tuning = cJSON_GetObjectItemCaseSensitive(schema, "tuning");
        if (!cJSON_IsObject(tuning)) {
            return false; // "tuning" must be an object
        }
        {
            cJSON *tuning_enabled_item = cJSON_GetObjectItemCaseSensitive(tuning, "enabled");
            cJSON *tuning_address_item = cJSON_GetObjectItemCaseSensitive(tuning, "address");

            if (!cJSON_IsBool(tuning_enabled_item)) {
                return false; // "enabled" must be a boolean
            }
            if (!cJSON_IsString(tuning_address_item) || !is_valid_address(tuning_address_item->valuestring)) {
                return false; // "address" must be a string and valid according to is_valid_address
            }
        }
    }

    return true; 
}