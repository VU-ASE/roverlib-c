/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: outputs/lux.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "rovercom/outputs/lux.pb-c.h"
void   protobuf_msgs__lux_sensor_output__init
                     (ProtobufMsgs__LuxSensorOutput         *message)
{
  static const ProtobufMsgs__LuxSensorOutput init_value = PROTOBUF_MSGS__LUX_SENSOR_OUTPUT__INIT;
  *message = init_value;
}
size_t protobuf_msgs__lux_sensor_output__get_packed_size
                     (const ProtobufMsgs__LuxSensorOutput *message)
{
  assert(message->base.descriptor == &protobuf_msgs__lux_sensor_output__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t protobuf_msgs__lux_sensor_output__pack
                     (const ProtobufMsgs__LuxSensorOutput *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &protobuf_msgs__lux_sensor_output__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t protobuf_msgs__lux_sensor_output__pack_to_buffer
                     (const ProtobufMsgs__LuxSensorOutput *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &protobuf_msgs__lux_sensor_output__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
ProtobufMsgs__LuxSensorOutput *
       protobuf_msgs__lux_sensor_output__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (ProtobufMsgs__LuxSensorOutput *)
     protobuf_c_message_unpack (&protobuf_msgs__lux_sensor_output__descriptor,
                                allocator, len, data);
}
void   protobuf_msgs__lux_sensor_output__free_unpacked
                     (ProtobufMsgs__LuxSensorOutput *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &protobuf_msgs__lux_sensor_output__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor protobuf_msgs__lux_sensor_output__field_descriptors[1] =
{
  {
    "lux",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(ProtobufMsgs__LuxSensorOutput, lux),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned protobuf_msgs__lux_sensor_output__field_indices_by_name[] = {
  0,   /* field[0] = lux */
};
static const ProtobufCIntRange protobuf_msgs__lux_sensor_output__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor protobuf_msgs__lux_sensor_output__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "protobuf_msgs.LuxSensorOutput",
  "LuxSensorOutput",
  "ProtobufMsgs__LuxSensorOutput",
  "protobuf_msgs",
  sizeof(ProtobufMsgs__LuxSensorOutput),
  1,
  protobuf_msgs__lux_sensor_output__field_descriptors,
  protobuf_msgs__lux_sensor_output__field_indices_by_name,
  1,  protobuf_msgs__lux_sensor_output__number_ranges,
  (ProtobufCMessageInit) protobuf_msgs__lux_sensor_output__init,
  NULL,NULL,NULL    /* reserved[123] */
};
