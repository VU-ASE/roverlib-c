# roverlib-c
Building a service that runs on the rover? Then you'll need the roverlib. This is the variant for C

**WIP**. Full docs on ase website

# Requirements
Before installing/using the roverlib, you need to have the following installed:

- libprotobuf-c-dev
- libzmq3-dev 
- libcjson-dev
- cmake

This will be installed when you use the provided devcontainer. Have a look at the devcontainer dockerfile to understand how to install the required libraries for ubuntu.

# Installation

Clone the repo first, then enter its directory. 
```bash
mkdir build
cmake ..
make 
sudo make install
```

This will build the shared object and install it with its header files.

# Usage

After installation, you can use roverlib as follows:

```c
#include <roverlib.h>

int test_main(Service service, Service_configuration *configuration) {
  printf("==== Initializing test main function =====\n");
  printf("Running service %s\n", service.name);
  printf("Running version %s\n", service.version);

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
```

Compile this with:

```bash
gcc -I/usr/include/cjson -o main main.c -lroverlib-c
```

# Attributions

Some code is generated using quicktype, which relies on joelguittet/c-list and joelguittet/c-hashtable. 
These libraries are redistributed in this repository and modified slightly to allow for compilation to static libraries which are included in the roverlib.so file, so that there is no need to install them manually. 