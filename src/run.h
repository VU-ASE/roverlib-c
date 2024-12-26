#ifndef RUN_H
#define RUN_H

#include "../include/rovercom/control/control.pb-c.h"
#include <stdio.h>
#include <stdio.h>
#include "bootinfo.h"
#include "callbacks.h"
#include <stdlib.h>
#include "configuration.h"

// The run function takes in one argument:
// - The Main callback function, which is the user main function to run
int run(MainCallback main) {
  if (main == NULL) {
    printf("No main function to call was specified\n");
    return 1;
  }

  // 
  // Parse service configuration from ASE_SERVICE variable as injected by roverd
  // 

  char *service_env = getenv("ASE_SERVICE");
  if (service_env == NULL) {
    printf("No service definition found in environment variable ASE_SERVICE. Are you sure that this service is started by roverd?\n");
    return 1;
  }

  struct Service *service = cJSON_ParseService(service_env);
  if (service == NULL) {
    printf("Failed to parse service definition from ASE_SERVICE environment variable\n");
    return 1;
  }

  // Create test service
  Configuration configuration = {
    .name = "1.0.0",
  };

  ServiceConfiguration config = NewServiceConfiguration();

  return main(*service, configuration);
}

#endif // RUN_H