#include <stdio.h>
#include "bootinfo.h"

typedef struct {
    Service service;
} MainCallback;



// "run" function that takes in two arguments (two function pointers)
// - one "main" function 