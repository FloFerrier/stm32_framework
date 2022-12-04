# Framework-STM32F4x
## Build project
```bash

```
### Build embedded firmware (cross-compilation)
```bash
mkdir build && cd build
cmake .. -GNinja -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-arm-none-eabi.cmake -DSELECTED_BOARD=stm32f446re -DCMAKE_BUILD_TYPE=<Debug or Release>
cmake --build . --target all
cmake --build . --target clean
```
### Flash embedded firmware
```
cd ..
openocd -f config/openocd.cfg -c "program bin/stm32f446re_Debug.elf verify reset exit"
```
## Build tests (native compilation)
```bash
mkdir build && cd build
cmake .. -GNinja -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-native.cmake -DCMAKE_BUILD_TYPE=Test
cmake --build . --target all
cmake --build . --target clean
ctest
ctest -N
ctest -R <Test_Name>
ctest -T Coverage
```

## Build Test Suite
### Generate HTMP page for test coverage
```bash
mkdir test-coverage && cd test-coverage
geninfo ../build -b ../Tests -o ./coverage.info
genhtml coverage.info -o generate-html
```

## Flash after building a firmware
```bash
openocd -f config/openocd.cfg -c "setup" -c "program_release bin/stm32f446re_<Debug or Release>.elf"
```
## Open a debug session
Open a debug session with openocd :
```bash
openocd -f config/openocd.cfg -c "setup"
```
And on another terminal, launch gdb with the debug binary :
``bash
arm-none-eabi-gdb --tui --eval-command "target remote :3333" --eval-command "monitor reset halt" --eval-command "load" bin/stm32f446re_Debug.elf
```