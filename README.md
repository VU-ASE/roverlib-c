# roverlib-c

Building a service that runs on the rover? Then you'll need the roverlib. This is the variant for C.

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
cd build
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

# Maintenance 

This library contains some auto-generated code. If the underlying specs are updated, you can do the following to generate again:

**`bootinfo.h` and `bootinfo.c`:** 
copy the roverd bootspec JSON schema from https://github.com/VU-ASE/roverd/blob/main/roverd/spec/bootspec.json. Then use the quicktype cJSON generator to generate the C code at https://app.quicktype.io/. Use the following settings: 
- hashtable size 64
- naming style types: pascal case
- naming style members: underscore case
- naming style enumerators: upper underscore case
- source code generation: multi source
- integer code: int 64 T
- add typedef
- print formatted
Make sure to split up the generated file, put the declarations in `include/bootinfo.h` and the implementations in `src/bootinfo.c`.

**rovercom**:
copy the generated rovercom package from https://github.com/VU-ASE/rovercom/tree/main/packages/c/gen. You only need `output` and `tuning`. Make sure to put all header files in the `include/rovercom` directory (keep the file structure!) and all c source files in the `src/rovercom` directory (keep the file structure!)

# Testing and building from source

Sometimes you might want to build a program with the "raw" source files directly, for example to build with debug symbols. This is very easy using the devcontainer. Open vscode in the container and enter the *test* directory, you can then build and simulate roverd by injecting a bootspec. An example bootspec and the full spec can be found [here](https://github.com/VU-ASE/rover/tree/main/spec/service-boot).

Note that you will need to install c-hashtable and c-list manually now. This can be done from both folders in the */dependencies* folder, like so:

```bash
# Example for c-hashtable, just switch name for c-list
cd dependencies/c-hashtable
mkdir build
cd build
cmake ..
make
sudo make install
```
