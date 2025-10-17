# Build Instructions

## Prerequisites

### Install ARM GCC Toolchain

#### Ubuntu/Debian:
```bash
sudo apt-get update
sudo apt-get install gcc-arm-none-eabi binutils-arm-none-eabi gdb-arm-none-eabi
```

#### macOS (using Homebrew):
```bash
brew install --cask gcc-arm-embedded
```

#### Windows:
Download and install the ARM GNU Toolchain from:
https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm

### Install STLink Utilities (for flashing)

#### Ubuntu/Debian:
```bash
sudo apt-get install stlink-tools
```

#### macOS:
```bash
brew install stlink
```

## Building the Project

1. Clone the repository and navigate to the project directory:
```bash
cd /path/to/stm32f401re-calculator
```

2. Build the project:
```bash
make
```

This will create the following files in the `build/` directory:
- `calculator.elf` - ELF executable with debug symbols
- `calculator.bin` - Binary image for flashing
- `calculator.hex` - Intel HEX format
- `calculator.map` - Memory map file

## Flashing to the Board

### Using st-flash:
```bash
make flash
```

Or manually:
```bash
st-flash write build/calculator.bin 0x8000000
```

### Using OpenOCD:
```bash
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg \
  -c "program build/calculator.elf verify reset exit"
```

## Debugging

### Using GDB with OpenOCD:

Terminal 1 (start OpenOCD server):
```bash
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg
```

Terminal 2 (start GDB):
```bash
arm-none-eabi-gdb build/calculator.elf
(gdb) target remote localhost:3333
(gdb) monitor reset halt
(gdb) load
(gdb) continue
```

## Testing

1. Connect the Nucleo board to your computer via USB
2. Open a serial terminal (e.g., minicom, screen, PuTTY) with settings:
   - Port: /dev/ttyACM0 (Linux) or COM port (Windows)
   - Baud rate: 115200
   - Data bits: 8
   - Parity: None
   - Stop bits: 1

3. Reset the board and you should see the calculator welcome message

4. Test with sample calculations:
```
calc> 5 + 3
Result: 8.0000

calc> 12.5 * 2
Result: 25.0000

calc> 100 / 4
Result: 25.0000
```

## Troubleshooting

### Build Errors

**Error: "arm-none-eabi-gcc: command not found"**
- Install the ARM GCC toolchain as described in Prerequisites

**Linker errors:**
- Check that all source files are listed in the Makefile
- Verify the linker script path is correct

### Flash Errors

**Error: "Cannot connect to target"**
- Check USB connection
- Install ST-Link drivers
- Try unplugging and replugging the board

**Error: "Verification failed"**
- Try erasing the flash first: `st-flash erase`
- Then flash again: `make flash`

### Runtime Issues

**No output on serial terminal:**
- Verify correct COM port selection
- Check baud rate is set to 115200
- Press the reset button on the board
- Try different terminal software

**Incorrect calculations:**
- Check input format: `operand1 operator operand2`
- Ensure spaces between operands and operator
- Verify supported operators: +, -, *, /

## Clean Build

To remove all build artifacts:
```bash
make clean
```

## Project Size

Typical build size:
- Flash usage: ~10-15 KB
- RAM usage: ~2-3 KB

This leaves plenty of space for additional features on the STM32F401RE (512KB Flash, 96KB RAM).
