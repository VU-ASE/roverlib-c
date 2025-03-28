/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: outputs/battery.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "rovercom/outputs/battery.pb-c.h"
void   protobuf_msgs__battery_sensor_output__init
                     (ProtobufMsgs__BatterySensorOutput         *message)
{
  static const ProtobufMsgs__BatterySensorOutput init_value = PROTOBUF_MSGS__BATTERY_SENSOR_OUTPUT__INIT;
  *message = init_value;
}
size_t protobuf_msgs__battery_sensor_output__get_packed_size
                     (const ProtobufMsgs__BatterySensorOutput *message)
{
  assert(message->base.descriptor == &protobuf_msgs__battery_sensor_output__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t protobuf_msgs__battery_sensor_output__pack
                     (const ProtobufMsgs__BatterySensorOutput *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &protobuf_msgs__battery_sensor_output__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t protobuf_msgs__battery_sensor_output__pack_to_buffer
                     (const ProtobufMsgs__BatterySensorOutput *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &protobuf_msgs__battery_sensor_output__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
ProtobufMsgs__BatterySensorOutput *
       protobuf_msgs__battery_sensor_output__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (ProtobufMsgs__BatterySensorOutput *)
     protobuf_c_message_unpack (&protobuf_msgs__battery_sensor_output__descriptor,
                                allocator, len, data);
}
void   protobuf_msgs__battery_sensor_output__free_unpacked
                     (ProtobufMsgs__BatterySensorOutput *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &protobuf_msgs__battery_sensor_output__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor protobuf_msgs__battery_sensor_output__field_descriptors[3] =
{
  {
    "currentOutputVoltage",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_FLOAT,
    0,   /* quantifier_offset */
    offsetof(ProtobufMsgs__BatterySensorOutput, currentoutputvoltage),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "warnVoltage",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_FLOAT,
    0,   /* quantifier_offset */
    offsetof(ProtobufMsgs__BatterySensorOutput, warnvoltage),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "killVoltage",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_FLOAT,
    0,   /* quantifier_offset */
    offsetof(ProtobufMsgs__BatterySensorOutput, killvoltage),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned protobuf_msgs__battery_sensor_output__field_indices_by_name[] = {
  0,   /* field[0] = currentOutputVoltage */
  2,   /* field[2] = killVoltage */
  1,   /* field[1] = warnVoltage */
};
static const ProtobufCIntRange protobuf_msgs__battery_sensor_output__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor protobuf_msgs__battery_sensor_output__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "protobuf_msgs.BatterySensorOutput",
  "BatterySensorOutput",
  "ProtobufMsgs__BatterySensorOutput",
  "protobuf_msgs",
  sizeof(ProtobufMsgs__BatterySensorOutput),
  3,
  protobuf_msgs__battery_sensor_output__field_descriptors,
  protobuf_msgs__battery_sensor_output__field_indices_by_name,
  1,  protobuf_msgs__battery_sensor_output__number_ranges,
  (ProtobufCMessageInit) protobuf_msgs__battery_sensor_output__init,
  NULL,NULL,NULL    /* reserved[123] */
};
