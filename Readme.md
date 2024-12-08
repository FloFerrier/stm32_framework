# STM32_Framework_Template
## How to use this template ?
Firstly, get the list of supported microcontroller.
If you don't find your microcontroller, don't worry !
This template is customizable and you can easily add your microcontroller.
## Prerequisites
This framework is cross-platform, it is supported by Linux and Windows (other OS have not been tested but should work).
Download all tools listed in the following table.

| Name                     | Version   | URL                                                               |
|--------------------------|-----------|-------------------------------------------------------------------|
| CMake                    | 3.31.2    | https://cmake.org/download/                                       |
| Ninja                    | 1.12.1    | https://github.com/ninja-build/ninja/releases                     |
| Arm-none-eabi-toolchain  | 13.3.Rel1 | https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads |
| Openocd                  | 0.12.0    | https://openocd.org/pages/getting-openocd.html                    |

Once downloaded, install the tools and add the path to the toll binaries to the PATH environment variable.
After that, check that the tools are available by opening a console (Git Bash or Powershell on Windows, Bash on Linux).

```bash
$ cmake --version
cmake version 3.31.2
#####################
$ ninja --version
1.12.1
#####################
$ arm-none-eabi-gcc --version
arm-none-eabi-gcc.exe (Arm GNU Toolchain 13.3.Rel1(Build arm-13.24))
#####################
$ openocd --version
xPack Open On-Chip Debugger 0.12.0+dev-01685-gb9224c0c0-dirty
```

Nucleo board from ST, need install drivers on the host :
https://www.st.com/en/development-tools/stsw-link009.html

## Using CMake to manage build system
CMake allows to be cross-platform and manage the build system on 2 steps :
1. Configure : Detect the architecture and toolchains, find dependencies and write build tool files.
2. Build : Compile and link binaries, run tests.

### Configure step
At the top of project, enter the following command depending on your context for configuring.
Three context are available :
- Debug : Build cross-compiling firmware on debug mode.
- Release : Build cross-compiling firmware on release mode.
- Test : Build native test suite binaries.

#### Configure on Debug mode
```bash
$ cmake -G Ninja -B build/debug -DCMAKE_BUILD_TYPE=Debug -DSELECTED_BOARD=<Your_Board> --toolchain "cmake/toolchain-arm-none-eabi.cmake"
```
Notes:
- ```--toolchain <TOOLCHAIN_FILE>``` is equivalent to ```-DCMAKE_TOOLCHAIN_FILE=<TOOLCHAIN_FILE>```
- Add ```--fresh``` to configure a fresh build tree, removing any existing cache file

#### Configure on Release mode
```bash
$ cmake -G Ninja -B build/release -DCMAKE_BUILD_TYPE=Release -DSELECTED_BOARD=<Your_Board> --toolchain "cmake/toolchain-arm-none-eabi.cmake"
```

#### Configure on Test mode
```bash
$ cmake -G Ninja -B build/test -DCMAKE_BUILD_TYPE=Test --toolchain "cmake/toolchain-native.cmake"
```

### Build step
At root of project and after configuring, build binaries with the following command :
```bash
cmake --build <build_folder>
```
The <build_folder> is depending of your context :
- For Debug mode = <build_folder>=build/debug
- For Release mode = <build_folder>=build/release
- For Test mode = <build_folder>=build/test

It is possible to build directly on the <build_folder>, follows the commands at the root of the project :
```bash
$ cd <build_folder>
$ cmake --build .
```

### Flash on the target
After building the cross-compiling firmware in Debug or Release mode, flash it on the board with the following command :
```bash
$ cmake --build <build_folder> --target flash
```
Need to plug the nucleo-board !

### Debug on the target
After building the firmware in Debug mode, debug it on the board with the following command :
```bash
$ cmake --build build/debug --target debug
```

### Other commands
After configuring and at build time, available commands can be display with this command :
```bash
$ cmake --build <build_folder> --target help
```

No-exhaustive list :
```bash
$ cmake --build <build_folder> --target clean # Clean the build folder
```

### Build tests (native compilation)
```bash
cmake -B build/Test -GNinja -DCMAKE_BUILD_TYPE=Test
cmake --build build/Test
ctest -V --test-dir build/Test # Run all tests with verbose output
cmake --build build/Test --target coverage # Generate code coverage report
```
## Open a debug session
## Debug
```bash
openocd -f config/openocd.cfg -c "setup <OPENOCD_TARGET_BOARD>" -c "program_debug"
```
```bash
arm-none-eabi-gdb --tui bin/<firmware_name>.elf
(gdb) target extended-remote localhost:3333
(gdb) load
(gdb) monitor reset halt
```