# STM32_Framework_Template
## How to use this template ?
Firstly, get the list of supported microcontroller.
If you don't find your microcontroller, don't worry !
This template is customizable and you can easily add your microcontroller.
## Prerequisites
All packages are for Ubuntu distribution.
```bash
$ sudo apt install build-essential clang-format cmake gcc gcc-arm-none-eabi gdb-multiarch lcov ninja-build openocd qemu qemu-system-arm
```
## Build project
### Build and flash embedded firmware (cross-compilation)
```bash
$ cmake -B build/<Debug or Release> -GNinja -DCMAKE_BUILD_TYPE=<Debug or Release> -DSELECTED_BOARD=<Your_Board>
$ cmake --build build/<Debug or Release> # Build sources
$ cmake --build build/<Debug or Release> --target flash # Flash the firmware
$ cmake --build build/<Debug or Release> --target clean # Clean the build
```
### Build tests (native compilation)
```bash
$ cmake -B build/Test -GNinja -DCMAKE_BUILD_TYPE=Test
$ cmake --build build/Test
$ ctest -V --test-dir build/Test # Run all tests with verbose output
$ cmake --build build/Test --target coverage # Generate code coverage report
```
## Open a debug session
## Debug
With real hardware
```bash
$ openocd -f config/openocd.cfg -c "setup <OPENOCD_TARGET_BOARD>" -c "program_debug"
```
Or with an emulator
```bash
$ qemu-system-arm -cpu cortex-m3 -machine stm32vldiscovery -gdb tcp::3333 -S -nographic -semihosting -kernel bin/<firmware_name>.elf
```
```bash
$ arm-none-eabi-gdb --tui bin/<firmware_name>.elf
(gdb) target extended-remote localhost:3333
(gdb) load
(gdb) monitor reset halt # With openocd only
```