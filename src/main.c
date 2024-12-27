#include "../include/rovercom/control/control.pb-c.h"
#include <stdio.h>
#include <stdio.h>
#include "bootinfo.h"
#include "callbacks.h"
#include "run.h"
#include "configuration.h"

int test_main(Service service, Service_configuration *configuration) {
  printf("==== Initializing test main function =====\n");
  printf("Running service %s\n", service.name);
  printf("Running version %s\n", service.version);
  printf("That's all folks!\n");


  return 0;
}

int main() {
  // Example main function
  return run(test_main);
}