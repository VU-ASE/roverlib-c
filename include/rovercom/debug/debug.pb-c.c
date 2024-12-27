/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: debug/debug.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "debug/debug.pb-c.h"
void   protobuf_msgs__service_identifier__init
                     (ProtobufMsgs__ServiceIdentifier         *message)
{
  static const ProtobufMsgs__ServiceIdentifier init_value = PROTOBUF_MSGS__SERVICE_IDENTIFIER__INIT;
  *message = init_value;
}
size_t protobuf_msgs__service_identifier__get_packed_size
                     (const ProtobufMsgs__ServiceIdentifier *message)
{
  assert(message->base.descriptor == &protobuf_msgs__service_identifier__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t protobuf_msgs__service_identifier__pack
                     (const ProtobufMsgs__ServiceIdentifier *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &protobuf_msgs__service_identifier__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t protobuf_msgs__service_identifier__pack_to_buffer
                     (const ProtobufMsgs__ServiceIdentifier *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &protobuf_msgs__service_identifier__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
ProtobufMsgs__ServiceIdentifier *
       protobuf_msgs__service_identifier__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (ProtobufMsgs__ServiceIdentifier *)
     protobuf_c_message_unpack (&protobuf_msgs__service_identifier__descriptor,
                                allocator, len, data);
}
void   protobuf_msgs__service_identifier__free_unpacked
                     (ProtobufMsgs__ServiceIdentifier *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &protobuf_msgs__service_identifier__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   protobuf_msgs__service_endpoint__init
                     (ProtobufMsgs__ServiceEndpoint         *message)
{
  static const ProtobufMsgs__ServiceEndpoint init_value = PROTOBUF_MSGS__SERVICE_ENDPOINT__INIT;
  *message = init_value;
}
size_t protobuf_msgs__service_endpoint__get_packed_size
                     (const ProtobufMsgs__ServiceEndpoint *message)
{
  assert(message->base.descriptor == &protobuf_msgs__service_endpoint__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t protobuf_msgs__service_endpoint__pack
                     (const ProtobufMsgs__ServiceEndpoint *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &protobuf_msgs__service_endpoint__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t protobuf_msgs__service_endpoint__pack_to_buffer
                     (const ProtobufMsgs__ServiceEndpoint *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &protobuf_msgs__service_endpoint__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
ProtobufMsgs__ServiceEndpoint *
       protobuf_msgs__service_endpoint__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (ProtobufMsgs__ServiceEndpoint *)
     protobuf_c_message_unpack (&protobuf_msgs__service_endpoint__descriptor,
                                allocator, len, data);
}
void   protobuf_msgs__service_endpoint__free_unpacked
                     (ProtobufMsgs__ServiceEndpoint *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &protobuf_msgs__service_endpoint__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   protobuf_msgs__debug_output__init
                     (ProtobufMsgs__DebugOutput         *message)
{
  static const ProtobufMsgs__DebugOutput init_value = PROTOBUF_MSGS__DEBUG_OUTPUT__INIT;
  *message = init_value;
}
size_t protobuf_msgs__debug_output__get_packed_size
                     (const ProtobufMsgs__DebugOutput *message)
{
  assert(message->base.descriptor == &protobuf_msgs__debug_output__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t protobuf_msgs__debug_output__pack
                     (const ProtobufMsgs__DebugOutput *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &protobuf_msgs__debug_output__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t protobuf_msgs__debug_output__pack_to_buffer
                     (const ProtobufMsgs__DebugOutput *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &protobuf_msgs__debug_output__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
ProtobufMsgs__DebugOutput *
       protobuf_msgs__debug_output__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (ProtobufMsgs__DebugOutput *)
     protobuf_c_message_unpack (&protobuf_msgs__debug_output__descriptor,
                                allocator, len, data);
}
void   protobuf_msgs__debug_output__free_unpacked
                     (ProtobufMsgs__DebugOutput *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &protobuf_msgs__debug_output__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor protobuf_msgs__service_identifier__field_descriptors[2] =
{
  {
    "name",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(ProtobufMsgs__ServiceIdentifier, name),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "pid",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(ProtobufMsgs__ServiceIdentifier, pid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned protobuf_msgs__service_identifier__field_indices_by_name[] = {
  0,   /* field[0] = name */
  1,   /* field[1] = pid */
};
static const ProtobufCIntRange protobuf_msgs__service_identifier__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor protobuf_msgs__service_identifier__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "protobuf_msgs.ServiceIdentifier",
  "ServiceIdentifier",
  "ProtobufMsgs__ServiceIdentifier",
  "protobuf_msgs",
  sizeof(ProtobufMsgs__ServiceIdentifier),
  2,
  protobuf_msgs__service_identifier__field_descriptors,
  protobuf_msgs__service_identifier__field_indices_by_name,
  1,  protobuf_msgs__service_identifier__number_ranges,
  (ProtobufCMessageInit) protobuf_msgs__service_identifier__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor protobuf_msgs__service_endpoint__field_descriptors[2] =
{
  {
    "name",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(ProtobufMsgs__ServiceEndpoint, name),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "address",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(ProtobufMsgs__ServiceEndpoint, address),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned protobuf_msgs__service_endpoint__field_indices_by_name[] = {
  1,   /* field[1] = address */
  0,   /* field[0] = name */
};
static const ProtobufCIntRange protobuf_msgs__service_endpoint__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor protobuf_msgs__service_endpoint__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "protobuf_msgs.ServiceEndpoint",
  "ServiceEndpoint",
  "ProtobufMsgs__ServiceEndpoint",
  "protobuf_msgs",
  sizeof(ProtobufMsgs__ServiceEndpoint),
  2,
  protobuf_msgs__service_endpoint__field_descriptors,
  protobuf_msgs__service_endpoint__field_indices_by_name,
  1,  protobuf_msgs__service_endpoint__number_ranges,
  (ProtobufCMessageInit) protobuf_msgs__service_endpoint__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor protobuf_msgs__debug_output__field_descriptors[4] =
{
  {
    "service",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(ProtobufMsgs__DebugOutput, service),
    &protobuf_msgs__service_identifier__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "endpoint",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(ProtobufMsgs__DebugOutput, endpoint),
    &protobuf_msgs__service_endpoint__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "message",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_BYTES,
    0,   /* quantifier_offset */
    offsetof(ProtobufMsgs__DebugOutput, message),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "sentAt",
    4,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT64,
    0,   /* quantifier_offset */
    offsetof(ProtobufMsgs__DebugOutput, sentat),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned protobuf_msgs__debug_output__field_indices_by_name[] = {
  1,   /* field[1] = endpoint */
  2,   /* field[2] = message */
  3,   /* field[3] = sentAt */
  0,   /* field[0] = service */
};
static const ProtobufCIntRange protobuf_msgs__debug_output__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 4 }
};
const ProtobufCMessageDescriptor protobuf_msgs__debug_output__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "protobuf_msgs.DebugOutput",
  "DebugOutput",
  "ProtobufMsgs__DebugOutput",
  "protobuf_msgs",
  sizeof(ProtobufMsgs__DebugOutput),
  4,
  protobuf_msgs__debug_output__field_descriptors,
  protobuf_msgs__debug_output__field_indices_by_name,
  1,  protobuf_msgs__debug_output__number_ranges,
  (ProtobufCMessageInit) protobuf_msgs__debug_output__init,
  NULL,NULL,NULL    /* reserved[123] */
};