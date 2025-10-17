# Quick Start Guide

Get your STM32F401RE calculator running in 5 minutes!

## Prerequisites Check

Before you begin, ensure you have:
- [ ] STM32 Nucleo-F401RE board
- [ ] USB Mini-B cable
- [ ] Computer with USB port
- [ ] ARM GCC toolchain installed
- [ ] Serial terminal software (PuTTY, minicom, screen, etc.)

## Step-by-Step Setup

### 1. Install Required Software

#### On Ubuntu/Debian:
```bash
sudo apt-get update
sudo apt-get install gcc-arm-none-eabi binutils-arm-none-eabi
sudo apt-get install stlink-tools
sudo apt-get install minicom
```

#### On macOS:
```bash
brew install --cask gcc-arm-embedded
brew install stlink
brew install minicom
```

#### On Windows:
1. Download ARM GCC from [ARM Developer](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm)
2. Download ST-Link utility from [ST Website](https://www.st.com/en/development-tools/stsw-link004.html)
3. Download PuTTY from [PuTTY Download](https://www.putty.org/)

### 2. Clone and Build

```bash
# Clone the repository
git clone <your-repo-url>
cd stm32f401re-calculator

# Build the project
make
```

Expected output:
```
arm-none-eabi-gcc -c ... src/main.c -o build/main.o
...
Build complete!
   text    data     bss     dec     hex filename
  12345     100    1024   13469    349d build/calculator.elf
```

### 3. Connect the Hardware

1. Connect the Nucleo board to your computer using the USB cable
2. The board should power up (LD3 red LED should light up)
3. Wait for the ST-Link driver to install (first time only on Windows)

### 4. Flash the Firmware

```bash
make flash
```

Expected output:
```
st-flash write build/calculator.bin 0x8000000
st-flash 1.7.0
2024-10-17T12:00:00 INFO common.c: F4xx: 96 KiB SRAM, 512 KiB flash...
2024-10-17T12:00:00 INFO common.c: Attempting to write ...
2024-10-17T12:00:01 INFO common.c: Flash written and verified! jolly good!
```

### 5. Open Serial Terminal

#### Linux:
```bash
minicom -D /dev/ttyACM0 -b 115200
```

Or using screen:
```bash
screen /dev/ttyACM0 115200
```

#### macOS:
```bash
# Find the port
ls /dev/cu.*

# Connect (replace XXX with your port)
screen /dev/cu.usbmodemXXX 115200
```

#### Windows:
1. Open PuTTY
2. Select "Serial" connection type
3. Set Serial line to your COM port (e.g., COM3)
4. Set Speed to 115200
5. Click "Open"

### 6. Reset the Board

Press the black RESET button on the Nucleo board.

You should see:
```
=====================================
  STM32F401RE Simple Calculator
=====================================
Supported operations: +, -, *, /
Format: operand1 operator operand2
Example: 5 + 3
         12.5 * 2.4
=====================================

calc>
```

### 7. Try Your First Calculation

Type and press Enter:
```
calc> 5 + 3
Result: 8.0000
calc>
```

🎉 **Congratulations!** Your calculator is working!

## Common Issues and Solutions

### Issue: "arm-none-eabi-gcc: command not found"
**Solution:** Install the ARM GCC toolchain (see Step 1)

### Issue: "make: command not found"
**Solution:** 
- Linux/macOS: `sudo apt-get install make` or `brew install make`
- Windows: Install MinGW or use WSL

### Issue: "Cannot open /dev/ttyACM0"
**Solution:** 
- Check if the device exists: `ls /dev/ttyACM*`
- Add yourself to dialout group: `sudo usermod -a -G dialout $USER`
- Log out and log back in

### Issue: "st-flash: command not found"
**Solution:** Install stlink-tools (see Step 1)

### Issue: "Cannot connect to target"
**Solution:**
- Check USB cable connection
- Try a different USB port
- Press the RESET button on the board
- Try: `st-flash erase` then `make flash` again

### Issue: No output on serial terminal
**Solution:**
- Verify correct baud rate (115200)
- Press RESET button on the board
- Check correct COM port / device
- Try different terminal software
- On Linux, check: `dmesg | grep tty` after plugging in

### Issue: Garbage characters on terminal
**Solution:**
- Double-check baud rate is 115200
- Ensure 8N1 settings (8 data bits, No parity, 1 stop bit)

### Issue: "Error: Invalid input format"
**Solution:**
- Ensure spaces between operands and operator
- Format: `operand1 operator operand2`
- Correct: `5 + 3`
- Incorrect: `5+3`

## Next Steps

Now that your calculator is running, you can:

1. **Try more calculations** - See [EXAMPLES.md](EXAMPLES.md) for more examples
2. **Understand the design** - Read [DESIGN.md](DESIGN.md) for architecture details
3. **Modify the code** - Add new features like:
   - More operators (power, square root, modulo)
   - Expression history
   - Multiple operations in one line
   - LCD display support

4. **Learn debugging** - Set up GDB debugging:
   ```bash
   # Terminal 1
   openocd -f interface/stlink.cfg -f target/stm32f4x.cfg
   
   # Terminal 2
   arm-none-eabi-gdb build/calculator.elf
   (gdb) target remote localhost:3333
   (gdb) load
   (gdb) break main
   (gdb) continue
   ```

## Project Files Overview

- **README.md** - Project overview and features
- **BUILD.md** - Detailed build instructions
- **DESIGN.md** - Architecture and design decisions
- **EXAMPLES.md** - Usage examples and test cases
- **HARDWARE.md** - Hardware configuration and connections
- **QUICKSTART.md** - This file!

## Getting Help

If you encounter issues not covered here:

1. Check the full documentation in BUILD.md and DESIGN.md
2. Review the hardware connections in HARDWARE.md
3. Verify your setup matches the requirements
4. Check ST's official documentation for the Nucleo-F401RE

## Test Commands

Quick test suite to verify everything works:

```
calc> 5 + 3
Result: 8.0000

calc> 10 - 7
Result: 3.0000

calc> 6 * 7
Result: 42.0000

calc> 100 / 4
Result: 25.0000

calc> 5 / 0
Error: Division by zero

calc> hello
Error: Invalid input format
```

If all these work correctly, your calculator is fully functional! 🚀

## Making Changes

To modify the code:

1. Edit source files in `src/` or `inc/`
2. Rebuild: `make clean && make`
3. Flash: `make flash`
4. Reset board and test

Example modification - Change welcome message:
```c
// Edit src/calculator.c
// Find the Calculator_Init() function
// Modify the UART2_SendString() calls
```

Happy calculating! 🧮
