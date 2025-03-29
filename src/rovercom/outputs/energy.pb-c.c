/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: outputs/energy.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "rovercom/outputs/energy.pb-c.h"
void   protobuf_msgs__energy_sensor_output__init
                     (ProtobufMsgs__EnergySensorOutput         *message)
{
  static const ProtobufMsgs__EnergySensorOutput init_value = PROTOBUF_MSGS__ENERGY_SENSOR_OUTPUT__INIT;
  *message = init_value;
}
size_t protobuf_msgs__energy_sensor_output__get_packed_size
                     (const ProtobufMsgs__EnergySensorOutput *message)
{
  assert(message->base.descriptor == &protobuf_msgs__energy_sensor_output__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t protobuf_msgs__energy_sensor_output__pack
                     (const ProtobufMsgs__EnergySensorOutput *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &protobuf_msgs__energy_sensor_output__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t protobuf_msgs__energy_sensor_output__pack_to_buffer
                     (const ProtobufMsgs__EnergySensorOutput *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &protobuf_msgs__energy_sensor_output__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
ProtobufMsgs__EnergySensorOutput *
       protobuf_msgs__energy_sensor_output__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (ProtobufMsgs__EnergySensorOutput *)
     protobuf_c_message_unpack (&protobuf_msgs__energy_sensor_output__descriptor,
                                allocator, len, data);
}
void   protobuf_msgs__energy_sensor_output__free_unpacked
                     (ProtobufMsgs__EnergySensorOutput *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &protobuf_msgs__energy_sensor_output__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor protobuf_msgs__energy_sensor_output__field_descriptors[3] =
{
  {
    "supplyVoltage",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_FLOAT,
    0,   /* quantifier_offset */
    offsetof(ProtobufMsgs__EnergySensorOutput, supplyvoltage),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "currentAmps",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_FLOAT,
    0,   /* quantifier_offset */
    offsetof(ProtobufMsgs__EnergySensorOutput, currentamps),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "powerWatts",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_FLOAT,
    0,   /* quantifier_offset */
    offsetof(ProtobufMsgs__EnergySensorOutput, powerwatts),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned protobuf_msgs__energy_sensor_output__field_indices_by_name[] = {
  1,   /* field[1] = currentAmps */
  2,   /* field[2] = powerWatts */
  0,   /* field[0] = supplyVoltage */
};
static const ProtobufCIntRange protobuf_msgs__energy_sensor_output__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor protobuf_msgs__energy_sensor_output__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "protobuf_msgs.EnergySensorOutput",
  "EnergySensorOutput",
  "ProtobufMsgs__EnergySensorOutput",
  "protobuf_msgs",
  sizeof(ProtobufMsgs__EnergySensorOutput),
  3,
  protobuf_msgs__energy_sensor_output__field_descriptors,
  protobuf_msgs__energy_sensor_output__field_indices_by_name,
  1,  protobuf_msgs__energy_sensor_output__number_ranges,
  (ProtobufCMessageInit) protobuf_msgs__energy_sensor_output__init,
  NULL,NULL,NULL    /* reserved[123] */
};
