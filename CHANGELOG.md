# Changelog

All notable changes to the STM32F401RE Simple Calculator project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.0] - 2024-10-17

### Added
- Initial release of STM32F401RE Simple Calculator
- Basic arithmetic operations: addition, subtraction, multiplication, division
- UART-based command-line interface at 115200 baud
- Support for floating-point calculations using hardware FPU
- Input buffer with 64-character capacity
- Backspace/delete support for input correction
- Comprehensive error handling:
  - Invalid input format detection
  - Division by zero protection
  - Unknown operator detection
- Custom float-to-string conversion (4 decimal places)
- Simple expression parser (operand1 operator operand2 format)
- Welcome screen with usage instructions
- Real-time character echo for user feedback

### Hardware Support
- STM32F401RE microcontroller (ARM Cortex-M4 @ 84 MHz)
- STM32 Nucleo-F401RE development board
- USART2 communication (PA2: TX, PA3: RX)
- HSE clock source with PLL configuration
- Hardware FPU enabled

### Documentation
- README.md - Project overview and quick start
- QUICKSTART.md - 5-minute setup guide
- BUILD.md - Comprehensive build instructions
- DESIGN.md - Architecture and design documentation
- HARDWARE.md - Hardware configuration and connections
- EXAMPLES.md - Usage examples and test cases
- DOCS.md - Documentation index
- CHANGELOG.md - This file
- LICENSE - MIT License

### Build System
- Makefile for ARM GCC toolchain
- Linker script for STM32F401RE (512KB Flash, 96KB RAM)
- Startup code with vector table
- System initialization with clock configuration
- Build artifacts: .elf, .bin, .hex, .map files

### Code Structure
- Modular architecture with separate UART and calculator modules
- Bare-metal implementation (no RTOS)
- Clean separation of concerns
- Hardware abstraction for peripherals
- Custom CMSIS-style device headers

### Development Tools Support
- GCC ARM embedded toolchain
- ST-Link flashing support
- OpenOCD debugging support
- GDB debugging ready

## [Unreleased]

### Planned Features
- Multi-operation expressions (e.g., "5 + 3 * 2")
- Parentheses support for operation precedence
- Additional operators: power (^), square root, modulo (%)
- Trigonometric functions (sin, cos, tan)
- Memory functions (store, recall, clear)
- Command history with up/down arrow keys
- Different display modes (decimal, hexadecimal, binary)
- Scientific notation for very large/small numbers
- Configurable precision for results
- LCD display support (I2C or SPI)
- Physical keypad input support
- Result history buffer
- Statistics functions (mean, median, etc.)
- Unit conversion features
- Low-power sleep mode when idle
- DMA for UART transfers
- Interrupt-driven I/O
- Configuration via commands
- Save settings to Flash memory

### Future Hardware Support
- Support for other STM32F4 variants
- Support for STM32F0/F3/F7 families
- Optional external display
- Optional keypad matrix
- Battery operation support

## Version History

### Version 1.0.0 (2024-10-17)
- Initial public release
- Core calculator functionality
- Complete documentation
- Tested on STM32F401RE Nucleo board

## Notes

### Breaking Changes
None yet - this is the initial release.

### Compatibility
- Requires ARM GCC toolchain (arm-none-eabi-gcc)
- Tested with STM32F401RE Nucleo board
- Compatible with any STM32F401xE device
- Serial terminal at 115200 baud, 8N1

### Known Issues
- Very large numbers may lose precision (inherent to 32-bit float)
- No support for multi-operation expressions yet
- No command history yet
- Buffer limited to 63 characters

### Contributors
- Initial design and implementation: STM32F401RE Calculator Team

## How to Contribute

See individual documentation files for guidelines on:
- Code style: DESIGN.md
- Build process: BUILD.md
- Testing: EXAMPLES.md

Please ensure:
1. Code compiles without warnings
2. Tested on actual hardware
3. Documentation updated
4. CHANGELOG.md updated with your changes

## Links

- [Repository](https://github.com/yourusername/stm32f401re-calculator)
- [Issue Tracker](https://github.com/yourusername/stm32f401re-calculator/issues)
- [STM32F401RE Datasheet](https://www.st.com/resource/en/datasheet/stm32f401re.pdf)
- [ARM GCC Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm)
