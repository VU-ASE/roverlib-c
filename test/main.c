#include "../include/roverlib.h"
#include <stdio.h>
#include <sys/time.h>

long long current_time_millis() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (long long)(tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
}

int test_main(Service service, Service_configuration *configuration) {
    printf("==== Initializing test main function =====\n");
    printf("Running service %s\n", service.name);
    printf("Running version %s\n", service.version);
  
    printf("==== Testing streams =====\n");
    // Try to set up a stream
    write_stream *stream = get_write_stream(&service, "test-write");
    if (stream == NULL) {
      printf("Could not get write stream for output test-write\n");
      return -1;
    }

    // Try to write a simple rovercom message, as if we are sending RPM data
    // (see https://github.com/VU-ASE/rovercom/blob/main/definitions/outputs/wrapper.proto)
    ProtobufMsgs__SensorOutput msg = PROTOBUF_MSGS__SENSOR_OUTPUT__INIT;
    // Set the message fields
    msg.sensorid = 505;                      // let the receiver know who we are! (if you have multiple sensors in one service)
    msg.timestamp = current_time_millis();   // current time in milliseconds since epoch (useful for debugging)
    msg.status = 0;                          // we are chilling
    // Set the oneof field contents
    ProtobufMsgs__RpmSensorOutput rpm_output = PROTOBUF_MSGS__RPM_SENSOR_OUTPUT__INIT;
    rpm_output.leftrpm = 1000;
    rpm_output.rightrpm = 2400;
    // Set the oneof field (union)
    msg.rpmouput = &rpm_output;
    msg.sensor_output_case = PROTOBUF_MSGS__SENSOR_OUTPUT__SENSOR_OUTPUT_RPM_OUPUT;

    int res = write_pb(stream, &msg);
    if (res < 0) {
      printf("Could not write\n");
      return 1l;
    }
  
    return 0;
  }
  
  int main() {
    // Example main function
    return run(test_main);
  }