# STM32F401RE Simple Calculator

A bare-metal calculator implementation for the STM32F401RE microcontroller (Nucleo-F401RE board).

## Features

- Basic arithmetic operations: addition (+), subtraction (-), multiplication (*), division (/)
- UART communication for input/output via serial terminal
- Simple command-line interface
- Support for floating-point calculations
- Error handling for division by zero and invalid input

## Hardware Requirements

- STM32F401RE Nucleo board
- USB cable for programming and serial communication

## Software Requirements

- ARM GCC toolchain (`arm-none-eabi-gcc`)
- Make
- Serial terminal (e.g., PuTTY, minicom, screen)

## Building the Project

```bash
make
```

This will generate `calculator.elf`, `calculator.bin`, and `calculator.hex` files in the `build/` directory.

## Flashing the Firmware

### Using st-flash (STLink utility):
```bash
make flash
```

### Using OpenOCD:
```bash
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program build/calculator.elf verify reset exit"
```

## Usage

1. Connect the Nucleo board to your computer via USB
2. Open a serial terminal with the following settings:
   - Baud rate: 115200
   - Data bits: 8
   - Parity: None
   - Stop bits: 1
3. Reset the board or power cycle it
4. You should see the calculator welcome message
5. Enter calculations in the format: `operand1 operator operand2`
   - Example: `5 + 3`
   - Example: `10.5 * 2.3`
   - Example: `100 / 4`

## Project Structure

```
.
├── src/
│   ├── main.c              # Main application
│   ├── calculator.c        # Calculator logic
│   ├── uart.c              # UART driver
│   └── system_stm32f4xx.c  # System initialization
├── inc/
│   ├── calculator.h        # Calculator header
│   ├── uart.h              # UART driver header
│   └── stm32f401xe.h       # Device header (CMSIS)
├── startup/
│   └── startup_stm32f401xe.c  # Startup code
├── linker/
│   └── STM32F401RETx_FLASH.ld # Linker script
├── Makefile                # Build configuration
└── README.md              # This file
```

## Technical Details

- **MCU**: STM32F401RE (ARM Cortex-M4)
- **Clock**: 84 MHz (PLL from 8 MHz HSE)
- **UART**: USART2 (PA2: TX, PA3: RX) - Connected to ST-Link VCP
- **Flash**: 512 KB
- **RAM**: 96 KB

## Clean Build

```bash
make clean
```

## License

This project is provided as-is for educational purposes.
