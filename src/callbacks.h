#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "bootinfo.h"

// The user main function to run
// Takes in two arguments:
// - The service object, which contains information about the service being run
// - The configuration object, which contains the configuration options for this service (can be tuned ota)
// Returns an integer, which is the exit code of the service (0 for success, anything else for failure)
typedef int (*MainCallback)(Service, Configuration);

// The termination callback function
// Takes in one argument:
// - The signal that caused the termination
// Returns an integer, which is the exit code of the cleanup process (0 for success, anything else for failure)
typedef int (*TerminationCallback)(int);

#endif // CALLBACKS_H

