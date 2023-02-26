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
cmake .. -GNinja -DCMAKE_BUILD_TYPE=<Debug or Release>
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
Open a debug session with openocd :
```bash
openocd -f config/openocd.cfg -c "setup stm32l1"
```
And on another terminal, launch gdb with the debug binary :
``bash
arm-none-eabi-gdb --tui --eval-command "target remote :3333" --eval-command "monitor reset halt" --eval-command "load" bin/<Your board>_Debug.elf
```