#include "../include/rovercom/control/control.pb-c.h"
#include <stdio.h>
#include <stdio.h>
#include "bootinfo.h"
#include "callbacks.h"
#include "run.h"
#include "configuration.h"
#include "streams.h"

int test_main(Service service, Service_configuration *configuration) {
  printf("==== Initializing test main function =====\n");
  printf("Running service %s\n", service.name);
  printf("Running version %s\n", service.version);
  printf("That's all folks!\n");

  printf("==== Testing streams =====\n");
  // Try to set up a stream
  write_stream *stream = get_write_stream(&service, "path-no");
  if (stream == NULL) {
    printf("Could not get write stream for output path-no\n");
  }

  // Try to set up a stream
  write_stream *stream1 = get_write_stream(&service, "path");
  if (stream1 == NULL) {
    printf("Could not get write stream for output path\n");
  } else {
    printf("Got write stream for output path\n");

    // Try to write some bytes
    char *message = "Hello, world!";
    int len = write_bytes(stream1, message, strlen(message));
    if (len < 0) {
      printf("Failed to write message to stream\n");
    } else {
      printf("Wrote %d bytes to stream\n", len);
    }
  }

  return 0;
}

int main() {
  // Example main function
  return run(test_main);
}