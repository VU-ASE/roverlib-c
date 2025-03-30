# Installation

:::info[Recommended approach]

It is not recommended to install this library manually. Instead, you can initialize a C service using `roverctl` using [this command](https://ase.vu.nl/docs/framework/Software/rover/roverctl/usage/#initialize-a-service).

:::

This library cannot be installed using any package manager. Instead, you can download the source code from the [latest release](https://github.com/VU-ASE/roverlib-c/releases/latest) and integrate it in your C project. Take a look at the provided [Devcontainer](https://github.com/VU-ASE/roverlib-c/tree/main/.devcontainer) to understand which libraries need to be installed.

You will need to install joelguittet/c-hashtable and joelguittet/c-list manually. This can be done from both folders in the [*/dependencies*](https://github.com/VU-ASE/roverlib-c/tree/main/dependencies) folder, like so:

```bash
# Example for c-hashtable, just switch name for c-list
cd dependencies/c-hashtable
mkdir build
cd build
cmake ..
make
sudo make install
```






