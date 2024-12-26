#include "../include/rovercom/control/control.pb-c.h"
#include <stdio.h>
#include <stdio.h>
#include "bootinfo.h"
#include "callbacks.h"

// The run function takes in two arguments:
// - The Main callback function, which is the user main function to run
// - The Termination callback function, which is the termination callback function
int run(MainCallback main, TerminationCallback termination) {
  printf("Hello, roverlib run func\n");

  if (main == NULL) {
    printf("Main callback is NULL\n");
    return 1;
  }
  if (termination == NULL) {
    printf("Termination callback is NULL\n");
    return 1;
  }

  // Create test service
  Service service = {
    .version = "1.0.0",
  };
  Configuration configuration = {
    .name = "1.0.0",
  };

  return main(service, configuration);
}

int test_main(Service service, Configuration configuration) {
  printf("Hello, roverlib test_main func\n");
  return 0;
}

int test_terminate(int signal) {
  printf("Hello, roverlib test_terminate func\n");
  return 0;
}

int main() {
  printf("Hello, roverlib\n");

  run(test_main, test_terminate);

  return 0;
}