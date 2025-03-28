# For Maintainers

## Requirements

Before using the roverlib, you need to have the following installed:

- libprotobuf-c-dev
- libzmq3-dev 
- libcjson-dev
- cmake

This will be installed when you use the provided devcontainer. Have a look at the devcontainer dockerfile to understand how to install the required libraries for ubuntu.

## Usage

After cloning, you can use the roverlib as described in the example of [*test/main.c*](test/main.c). We do not provide the roverlib as shared object file anymore, so you have to compile the roverlib-c headers and source files with your main program. You can find the command needed to do so in the [*test/Makefile*](test/Makefile).

The following `make` targets are available to get started quickly:

- `make build`: build main.c with roverlib-c
- `make start`: build main.c, inject boot info from *test/boot.json* and run it
- `make debug`: build main.c, inject boot info from *test/boot.json* and run it in GDB

**Note** "boot info" is the environment variable normally injected by roverd. You can find the full spec and an example [here](https://github.com/VU-ASE/rover/tree/main/spec/service-boot).

**Note 2**: you will need to install c-hashtable and c-list manually now. This can be done from both folders in the */dependencies* folder, like so:

```bash
# Example for c-hashtable, just switch name for c-list
cd dependencies/c-hashtable
mkdir build
cd build
cmake ..
make
sudo make install
```

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
