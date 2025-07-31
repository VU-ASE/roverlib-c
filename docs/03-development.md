# For Maintainers

This library contains some auto-generated code. If the underlying specs are updated, you can do the following to generate again:


## If the boot spec changes:

**`bootinfo.h` and `bootinfo.c`:** 
copy the roverd bootspec JSON schema from https://github.com/VU-ASE/rover/blob/main/spec/service-boot/schema.json. Then use the quicktype cJSON generator to generate the C code at https://app.quicktype.io/. Use the following settings: 
- hashtable size 64
- naming style types: pascal case
- naming style members: underscore case
- naming style enumerators: upper underscore case
- source code generation: multi source
- integer code: int 64 T
- add typedef
- print formatted
- single source
- Make sure to specify:
    - Name = Service
    - Source type = JSON Schema

Make sure to split up the generated file, put the declarations in `include/bootinfo.h` and the implementations in `src/bootinfo.c`.


## If the rovercom definitions change:

**rovercom**:
copy the generated rovercom package from https://github.com/VU-ASE/rovercom/tree/main/packages/c/gen. You only need `output` and `tuning`. Make sure to put all header files in the `include/rovercom` directory (keep the file structure!) and all c source files in the `src/rovercom` directory (keep the file structure!)

- If compilation fails, look into the /output and /tuning .c files and change `#include "output/...h"` to `#include "rovercom/output/...h"`. You can do a find and replace all for this!
