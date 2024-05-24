# SENSORBOARD [Front|Rear]
This repo contains the firmware and bootloader for the SensorBoard Device v3.0

## Dependencies
- `arm-none-eabi-gdb`, `arm-none-eabi-gcc`, `arm-none-eabi-newlib`,`arm-none-eabi-binutils`: ARM toolchain necessary to compile and debug the firmware
- `make`: or similar
- `awk`, `sed`
- `openocd`: to flash the firmware on the target via a debug probe (STLINK)
- `bootcommander`, `libopenblt`, `bin2srec`: to flash the firmware via can-bus

## Build
If all the software dependencies are available through `$PATH`
```bash
make
```
otherwise specify them via:
```bash
make GCC_PATH=/<path_to_compiler>
```
This will build the firmware to be flashed via `openocd` and a debug probe (STLINK)
## Build Bootloader
All software dependencies must be available in `$PATH`
```bash
cd ./openblt_f446re
make -f STM32Make.make
cd ..
```
This will build the Bootloader firmware to be flashed via `openocd` and a debug probe (STLINK)

## Flash 
Two approaches for flashing:
- Baremetal no bootloader
- Bootloader + flash via can
### Baremetal no bootloader
Make sure the debug probe is attached to the target and they see each other. 
To verify this run this command from the project rootdir:
```bash
openocd -f openocd.cfg
```
It should look something like this:
```bash
TODO add openocd status
```

Make sure you have `openocd` dependency in `$PATH`.
```bash
make flash
```
otherwise specify the path via:
```bash
make flash OPENOCD_PATH=/<openocd_path>
```
### Bootloader + flash via can [front|left]
First flash the bootloader on the device (all dependencies must be in `$PATH`, the debugger probe must be able to talk to the target see ![before](##flash))
```bash
cd ./openblt_f446re
make -f STM32Make.make flash
cd ..
```
Then connect the sensorboard device on a CAN bus network where you can send and receive data.
```bash
# To flash the firmware to a sensorboard front device
make can_flash_front 
# To flash the firmware to a sensorboard rear device
make can_flash_rear 
```
If the dependencies of `bootcommander` and `bin2srec` are not in `$PATH` specify them like this:
```bash
# To flash the firmware to a sensorboard front device
make can_flash_front BOOTCOMMANDER_PATH=/<path_to_bootcomamnder_dir> BIN2SREC_PATH=/<path_to_bin2srec_dir>
# To flash the firmware to a sensorboard rear device
make can_flash_rear BOOTCOMMANDER_PATH=/<path_to_bootcomamnder_dir> BIN2SREC_PATH=/<path_to_bin2srec_dir>
```
