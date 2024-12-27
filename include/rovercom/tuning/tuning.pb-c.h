/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: tuning/tuning.proto */

#ifndef PROTOBUF_C_tuning_2ftuning_2eproto__INCLUDED
#define PROTOBUF_C_tuning_2ftuning_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003003 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _ProtobufMsgs__TuningState ProtobufMsgs__TuningState;
typedef struct _ProtobufMsgs__TuningState__Parameter ProtobufMsgs__TuningState__Parameter;
typedef struct _ProtobufMsgs__TuningState__Parameter__NumberParameter ProtobufMsgs__TuningState__Parameter__NumberParameter;
typedef struct _ProtobufMsgs__TuningState__Parameter__StringParameter ProtobufMsgs__TuningState__Parameter__StringParameter;


/* --- enums --- */


/* --- messages --- */

/*
 * note: it may seem weird to not extract the key from the oneof, but this is so that the parser can easily determine the type of the parameter
 * extracting it to a separate field on the same level as oneof would make it ambiguous
 */
struct  _ProtobufMsgs__TuningState__Parameter__NumberParameter
{
  ProtobufCMessage base;
  char *key;
  float value;
};
#define PROTOBUF_MSGS__TUNING_STATE__PARAMETER__NUMBER_PARAMETER__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&protobuf_msgs__tuning_state__parameter__number_parameter__descriptor) \
    , (char *)protobuf_c_empty_string, 0 }


struct  _ProtobufMsgs__TuningState__Parameter__StringParameter
{
  ProtobufCMessage base;
  char *key;
  char *value;
};
#define PROTOBUF_MSGS__TUNING_STATE__PARAMETER__STRING_PARAMETER__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&protobuf_msgs__tuning_state__parameter__string_parameter__descriptor) \
    , (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string }


typedef enum {
  PROTOBUF_MSGS__TUNING_STATE__PARAMETER__PARAMETER__NOT_SET = 0,
  PROTOBUF_MSGS__TUNING_STATE__PARAMETER__PARAMETER_NUMBER = 1,
  PROTOBUF_MSGS__TUNING_STATE__PARAMETER__PARAMETER_STRING = 3
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(PROTOBUF_MSGS__TUNING_STATE__PARAMETER__PARAMETER)
} ProtobufMsgs__TuningState__Parameter__ParameterCase;

struct  _ProtobufMsgs__TuningState__Parameter
{
  ProtobufCMessage base;
  ProtobufMsgs__TuningState__Parameter__ParameterCase parameter_case;
  union {
    ProtobufMsgs__TuningState__Parameter__NumberParameter *number;
    ProtobufMsgs__TuningState__Parameter__StringParameter *string;
  };
};
#define PROTOBUF_MSGS__TUNING_STATE__PARAMETER__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&protobuf_msgs__tuning_state__parameter__descriptor) \
    , PROTOBUF_MSGS__TUNING_STATE__PARAMETER__PARAMETER__NOT_SET, {0} }


struct  _ProtobufMsgs__TuningState
{
  ProtobufCMessage base;
  /*
   * increased when the state changes, used to prevent unnecessary updates (so *not* in milliseconds since epoch)
   */
  uint64_t timestamp;
  size_t n_dynamicparameters;
  ProtobufMsgs__TuningState__Parameter **dynamicparameters;
};
#define PROTOBUF_MSGS__TUNING_STATE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&protobuf_msgs__tuning_state__descriptor) \
    , 0, 0,NULL }


/* ProtobufMsgs__TuningState__Parameter__NumberParameter methods */
void   protobuf_msgs__tuning_state__parameter__number_parameter__init
                     (ProtobufMsgs__TuningState__Parameter__NumberParameter         *message);
/* ProtobufMsgs__TuningState__Parameter__StringParameter methods */
void   protobuf_msgs__tuning_state__parameter__string_parameter__init
                     (ProtobufMsgs__TuningState__Parameter__StringParameter         *message);
/* ProtobufMsgs__TuningState__Parameter methods */
void   protobuf_msgs__tuning_state__parameter__init
                     (ProtobufMsgs__TuningState__Parameter         *message);
/* ProtobufMsgs__TuningState methods */
void   protobuf_msgs__tuning_state__init
                     (ProtobufMsgs__TuningState         *message);
size_t protobuf_msgs__tuning_state__get_packed_size
                     (const ProtobufMsgs__TuningState   *message);
size_t protobuf_msgs__tuning_state__pack
                     (const ProtobufMsgs__TuningState   *message,
                      uint8_t             *out);
size_t protobuf_msgs__tuning_state__pack_to_buffer
                     (const ProtobufMsgs__TuningState   *message,
                      ProtobufCBuffer     *buffer);
ProtobufMsgs__TuningState *
       protobuf_msgs__tuning_state__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   protobuf_msgs__tuning_state__free_unpacked
                     (ProtobufMsgs__TuningState *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*ProtobufMsgs__TuningState__Parameter__NumberParameter_Closure)
                 (const ProtobufMsgs__TuningState__Parameter__NumberParameter *message,
                  void *closure_data);
typedef void (*ProtobufMsgs__TuningState__Parameter__StringParameter_Closure)
                 (const ProtobufMsgs__TuningState__Parameter__StringParameter *message,
                  void *closure_data);
typedef void (*ProtobufMsgs__TuningState__Parameter_Closure)
                 (const ProtobufMsgs__TuningState__Parameter *message,
                  void *closure_data);
typedef void (*ProtobufMsgs__TuningState_Closure)
                 (const ProtobufMsgs__TuningState *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor protobuf_msgs__tuning_state__descriptor;
extern const ProtobufCMessageDescriptor protobuf_msgs__tuning_state__parameter__descriptor;
extern const ProtobufCMessageDescriptor protobuf_msgs__tuning_state__parameter__number_parameter__descriptor;
extern const ProtobufCMessageDescriptor protobuf_msgs__tuning_state__parameter__string_parameter__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_tuning_2ftuning_2eproto__INCLUDED */