/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: debug/debug.proto */

#ifndef PROTOBUF_C_debug_2fdebug_2eproto__INCLUDED
#define PROTOBUF_C_debug_2fdebug_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003003 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _ProtobufMsgs__ServiceIdentifier ProtobufMsgs__ServiceIdentifier;
typedef struct _ProtobufMsgs__ServiceEndpoint ProtobufMsgs__ServiceEndpoint;
typedef struct _ProtobufMsgs__DebugOutput ProtobufMsgs__DebugOutput;


/* --- enums --- */


/* --- messages --- */

/*
 * Used to identify a service within the pipeline
 */
struct  _ProtobufMsgs__ServiceIdentifier
{
  ProtobufCMessage base;
  char *name;
  int32_t pid;
};
#define PROTOBUF_MSGS__SERVICE_IDENTIFIER__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&protobuf_msgs__service_identifier__descriptor) \
    , (char *)protobuf_c_empty_string, 0 }


/*
 * An endpoint that is made available by a service
 */
struct  _ProtobufMsgs__ServiceEndpoint
{
  ProtobufCMessage base;
  /*
   * the identifier to select this endpoint
   */
  char *name;
  /*
   * the zmq address to connect to
   */
  char *address;
};
#define PROTOBUF_MSGS__SERVICE_ENDPOINT__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&protobuf_msgs__service_endpoint__descriptor) \
    , (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string }


/*
 * When the transceivers picks up a SensorOutput from a service, it will wrap it in a ServiceMessage message,
 * so that the receiver can determine from which process the message originated
 */
struct  _ProtobufMsgs__DebugOutput
{
  ProtobufCMessage base;
  /*
   * The service that sent the message
   */
  ProtobufMsgs__ServiceIdentifier *service;
  /*
   * The endpoint in this service that sent the message
   */
  ProtobufMsgs__ServiceEndpoint *endpoint;
  /*
   * Time in milliseconds since epoch when the message was sent
   */
  int64_t sentat;
  ProtobufCBinaryData message;
};
#define PROTOBUF_MSGS__DEBUG_OUTPUT__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&protobuf_msgs__debug_output__descriptor) \
    , NULL, NULL, 0, {0,NULL} }


/* ProtobufMsgs__ServiceIdentifier methods */
void   protobuf_msgs__service_identifier__init
                     (ProtobufMsgs__ServiceIdentifier         *message);
size_t protobuf_msgs__service_identifier__get_packed_size
                     (const ProtobufMsgs__ServiceIdentifier   *message);
size_t protobuf_msgs__service_identifier__pack
                     (const ProtobufMsgs__ServiceIdentifier   *message,
                      uint8_t             *out);
size_t protobuf_msgs__service_identifier__pack_to_buffer
                     (const ProtobufMsgs__ServiceIdentifier   *message,
                      ProtobufCBuffer     *buffer);
ProtobufMsgs__ServiceIdentifier *
       protobuf_msgs__service_identifier__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   protobuf_msgs__service_identifier__free_unpacked
                     (ProtobufMsgs__ServiceIdentifier *message,
                      ProtobufCAllocator *allocator);
/* ProtobufMsgs__ServiceEndpoint methods */
void   protobuf_msgs__service_endpoint__init
                     (ProtobufMsgs__ServiceEndpoint         *message);
size_t protobuf_msgs__service_endpoint__get_packed_size
                     (const ProtobufMsgs__ServiceEndpoint   *message);
size_t protobuf_msgs__service_endpoint__pack
                     (const ProtobufMsgs__ServiceEndpoint   *message,
                      uint8_t             *out);
size_t protobuf_msgs__service_endpoint__pack_to_buffer
                     (const ProtobufMsgs__ServiceEndpoint   *message,
                      ProtobufCBuffer     *buffer);
ProtobufMsgs__ServiceEndpoint *
       protobuf_msgs__service_endpoint__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   protobuf_msgs__service_endpoint__free_unpacked
                     (ProtobufMsgs__ServiceEndpoint *message,
                      ProtobufCAllocator *allocator);
/* ProtobufMsgs__DebugOutput methods */
void   protobuf_msgs__debug_output__init
                     (ProtobufMsgs__DebugOutput         *message);
size_t protobuf_msgs__debug_output__get_packed_size
                     (const ProtobufMsgs__DebugOutput   *message);
size_t protobuf_msgs__debug_output__pack
                     (const ProtobufMsgs__DebugOutput   *message,
                      uint8_t             *out);
size_t protobuf_msgs__debug_output__pack_to_buffer
                     (const ProtobufMsgs__DebugOutput   *message,
                      ProtobufCBuffer     *buffer);
ProtobufMsgs__DebugOutput *
       protobuf_msgs__debug_output__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   protobuf_msgs__debug_output__free_unpacked
                     (ProtobufMsgs__DebugOutput *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*ProtobufMsgs__ServiceIdentifier_Closure)
                 (const ProtobufMsgs__ServiceIdentifier *message,
                  void *closure_data);
typedef void (*ProtobufMsgs__ServiceEndpoint_Closure)
                 (const ProtobufMsgs__ServiceEndpoint *message,
                  void *closure_data);
typedef void (*ProtobufMsgs__DebugOutput_Closure)
                 (const ProtobufMsgs__DebugOutput *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor protobuf_msgs__service_identifier__descriptor;
extern const ProtobufCMessageDescriptor protobuf_msgs__service_endpoint__descriptor;
extern const ProtobufCMessageDescriptor protobuf_msgs__debug_output__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_debug_2fdebug_2eproto__INCLUDED */
