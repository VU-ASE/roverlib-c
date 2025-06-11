#ifndef VALIDATE_H
#define VALIDATE_H

#include <stdbool.h>
#include <cJSON.h>

// The function returns true if the name is valid according to the schema defined in the roverlib documentation.
// A valid name consists of lowercase letters and hyphens, and must not be empty.
// The function is used to validate the name of a service, input, output, or configuration option.
bool is_valid_name(const char *name);

// The function returns true if the version is valid according to the schema defined in the roverlib documentation.
// A valid version consists of a major version, a minor version, and a patch version, separated by dots.
bool is_valid_version(const char *version);

// The function returns true if the address is valid according to the schema defined in the roverlib documentation.
// A valid address is a non-empty string that starts with "tcp://".
bool is_valid_address(const char *address);

// The function checks the following things:
// 1. Exactly the allowed fields are pressent in the schema “name”, optional “as”,
//      “version”, “inputs”, “outputs”, “configuration”, “tuning”.  Nothing extra.
//
// 2. Every required key is present and of the correct JSON type:
//        - “name”    : string matching is_valid_name(…)
//        - “as”      : (optional) string matching is_valid_name(…)
//        - “version” : string matching is_valid_version(…)
//        - “inputs”  : array of objects, each with
//                        • “service”: string matching is_valid_name(…)
//                        • “streams”: array of objects, each with
//                              – “name”   : string matching is_valid_name(…)
//                              – “address”: string satisfying is_valid_address(…)
//        - “outputs” : array of objects, each with
//                        • “name”   : string matching is_valid_name(…)
//                        • “address”: string satisfying is_valid_address(…)
//        - “configuration”: array of objects, each with
//                        • “name”   : string matching is_valid_name(…)
//                        • “type”   : string equal to “number” or “string”
//                        • “tunable”: boolean
//                        • “value”  : JSON number if type=“number”, or JSON string if type=“string”
//        - “tuning”  : object containing
//                        • “enabled”: boolean
//                        • “address”: string satisfying is_valid_address(…)
//
// 3. If anything is missing or from the wrong type, the function returns false.
bool is_valid_schema(const cJSON *schema);

#endif // VALIDATE_H