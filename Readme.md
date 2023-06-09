# STM32_Framework_Template
## How to use this template ?
Firstly, get the list of supported microcontroller.
If you don't find your microcontroller, don't worry !
This template is customizable and you can easily add your microcontroller.
## Prerequisites
All packages are for Ubuntu distribution.
```bash
sudo apt install arm-none-eabi-gcc build_essential cmake gcc gdb-multiarch lcov ninja openocd
```
## Build project
### Build and flash embedded firmware (cross-compilation)
```bash
mkdir build_target && cd build_target
cmake .. -GNinja -DCMAKE_BUILD_TYPE=<Debug or Release> -DSELECTED_BOARD=<Your_Board>
ninja
ninja flash
```
### Build tests (native compilation)
```bash
mkdir build_test && cd build_test
cmake .. -GNinja -DCMAKE_BUILD_TYPE=Test
ninja
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