# STM32_Framework_Template
## How to use this template ?
Firstly, get the list of supported microcontroller.
If you don't find your microcontroller, don't worry !
This template is customizable and you can easily add your microcontroller.
## Prerequisites
All packages are for Ubuntu distribution.
```bash
sudo apt install build-essential clang-format cmake gcc gcc-arm-none-eabi-gcc gdb-multiarch lcov ninja-build openocd
```
## Build project
### Build and flash embedded firmware (cross-compilation)
```bash
cmake -B build/<Debug or Release> -GNinja -DCMAKE_BUILD_TYPE=<Debug or Release> -DSELECTED_BOARD=<Your_Board>
cmake --build build/<Debug or Release>
cmake flash
```
### Build tests (native compilation)
```bash
cmake -B build/Test -GNinja -DCMAKE_BUILD_TYPE=Test
cmake --build build/Test
ctest -V
ctest -N
ctest -V -R <Test_Name>
ctest -T Coverage
```
### Generate HTMP page for test coverage
```bash
mkdir test-coverage && cd test-coverage
geninfo ../build -b ../Tests -o ./coverage.info
genhtml coverage.info -o generate-html
```
## Open a debug session
## Debug
```bash
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg
```
```bash
arm-none-eabi-gdb --tui
(gdb) file bin/<firmware_name>.elf
(gdb) target extended-remote localhost:3333
(gdb) monitor reset halt
(gdb) load bin/<firmware_name>.elf
```