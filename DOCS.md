# Documentation Index

Complete documentation for the STM32F401RE Simple Calculator project.

## 📚 Documentation Structure

### Getting Started
1. **[QUICKSTART.md](QUICKSTART.md)** - Get running in 5 minutes
   - Prerequisites
   - Installation steps
   - First calculation
   - Common issues

2. **[README.md](README.md)** - Project overview
   - Features
   - Requirements
   - Quick build instructions
   - Project structure

### Building and Deployment
3. **[BUILD.md](BUILD.md)** - Comprehensive build guide
   - Toolchain installation
   - Build process
   - Flashing methods
   - Debugging setup
   - Troubleshooting

### Hardware Information
4. **[HARDWARE.md](HARDWARE.md)** - Hardware details
   - Board specifications
   - Pin configuration
   - Clock tree
   - Memory map
   - Serial terminal setup
   - Connection diagrams

### Software Design
5. **[DESIGN.md](DESIGN.md)** - Architecture and design
   - System architecture
   - Module descriptions
   - Data flow
   - Design decisions
   - Future enhancements
   - Performance considerations

### Usage Guide
6. **[EXAMPLES.md](EXAMPLES.md)** - Usage examples
   - Basic operations
   - Edge cases
   - Error handling
   - Practical calculations
   - Tips and tricks

## 📖 Quick Navigation

### I want to...

#### ...get started quickly
→ Read [QUICKSTART.md](QUICKSTART.md)

#### ...understand how it works
→ Read [DESIGN.md](DESIGN.md)

#### ...build from source
→ Read [BUILD.md](BUILD.md)

#### ...see usage examples
→ Read [EXAMPLES.md](EXAMPLES.md)

#### ...understand the hardware
→ Read [HARDWARE.md](HARDWARE.md)

#### ...troubleshoot issues
→ Check troubleshooting sections in:
- [QUICKSTART.md](QUICKSTART.md) - Quick fixes
- [BUILD.md](BUILD.md) - Build/flash issues
- [HARDWARE.md](HARDWARE.md) - Hardware issues

#### ...modify the code
→ Read [DESIGN.md](DESIGN.md) then check source files:
- `src/main.c` - Main application
- `src/calculator.c` - Calculator logic
- `src/uart.c` - UART driver
- `inc/*.h` - Header files

## 🔍 Documentation by Topic

### Hardware Topics
- **Board overview**: [HARDWARE.md](HARDWARE.md#stm32f401re-nucleo-board)
- **Pin configuration**: [HARDWARE.md](HARDWARE.md#pin-configuration)
- **Clock setup**: [HARDWARE.md](HARDWARE.md#clock-tree)
- **Memory layout**: [HARDWARE.md](HARDWARE.md#memory-map)
- **Serial connection**: [HARDWARE.md](HARDWARE.md#serial-terminal-settings)

### Software Topics
- **Architecture**: [DESIGN.md](DESIGN.md#software-architecture)
- **Module structure**: [DESIGN.md](DESIGN.md#module-structure)
- **Calculator logic**: [DESIGN.md](DESIGN.md#2-calculator-module-calculatorc-h)
- **UART driver**: [DESIGN.md](DESIGN.md#3-uart-driver-uartc-h)
- **System init**: [DESIGN.md](DESIGN.md#4-system-initialization-system-stm32f4xxc)

### Build Topics
- **Toolchain setup**: [BUILD.md](BUILD.md#prerequisites)
- **Compilation**: [BUILD.md](BUILD.md#building-the-project)
- **Flashing**: [BUILD.md](BUILD.md#flashing-to-the-board)
- **Debugging**: [BUILD.md](BUILD.md#debugging)
- **Clean build**: [BUILD.md](BUILD.md#clean-build)

### Usage Topics
- **Basic operations**: [EXAMPLES.md](EXAMPLES.md#basic-arithmetic-operations)
- **Error handling**: [EXAMPLES.md](EXAMPLES.md#error-examples)
- **Edge cases**: [EXAMPLES.md](EXAMPLES.md#edge-cases)
- **Practical examples**: [EXAMPLES.md](EXAMPLES.md#practical-calculations)

## 📋 Cheat Sheet

### Quick Commands
```bash
# Build
make

# Clean
make clean

# Flash
make flash

# Serial terminal (Linux)
minicom -D /dev/ttyACM0 -b 115200
screen /dev/ttyACM0 115200

# Find USB device (Linux)
ls /dev/ttyACM*
dmesg | grep tty
```

### Serial Settings
```
Baud Rate: 115200
Data Bits: 8
Parity:    None
Stop Bits: 1
```

### Calculation Format
```
Format: operand1 operator operand2
Example: 5 + 3
Operators: + - * /
```

### Project Structure
```
src/         C source files
inc/         Header files  
startup/     Startup code
linker/      Linker script
build/       Build output (generated)
```

## 🔧 File Reference

### Source Files
| File | Description | Documentation |
|------|-------------|---------------|
| `src/main.c` | Application entry point | [DESIGN.md](DESIGN.md#1-main-application-mainc) |
| `src/calculator.c` | Calculator implementation | [DESIGN.md](DESIGN.md#2-calculator-module-calculatorc-h) |
| `src/uart.c` | UART driver | [DESIGN.md](DESIGN.md#3-uart-driver-uartc-h) |
| `src/system_stm32f4xx.c` | System initialization | [DESIGN.md](DESIGN.md#4-system-initialization-system-stm32f4xxc) |
| `startup/startup_stm32f401xe.c` | Startup code | [DESIGN.md](DESIGN.md#5-startup-code-startup-stm32f401xec) |

### Header Files
| File | Description |
|------|-------------|
| `inc/calculator.h` | Calculator API |
| `inc/uart.h` | UART driver API |
| `inc/stm32f401xe.h` | Device definitions |

### Configuration Files
| File | Description |
|------|-------------|
| `Makefile` | Build configuration |
| `linker/STM32F401RETx_FLASH.ld` | Linker script |
| `.gitignore` | Git ignore rules |

### Documentation Files
| File | Purpose |
|------|---------|
| `README.md` | Project overview |
| `QUICKSTART.md` | Quick start guide |
| `BUILD.md` | Build instructions |
| `DESIGN.md` | Design documentation |
| `HARDWARE.md` | Hardware information |
| `EXAMPLES.md` | Usage examples |
| `DOCS.md` | This file (index) |
| `LICENSE` | MIT License |

## 🎯 Learning Path

### Beginner
1. Start with [QUICKSTART.md](QUICKSTART.md)
2. Try examples from [EXAMPLES.md](EXAMPLES.md)
3. Read project overview in [README.md](README.md)

### Intermediate
1. Understand hardware in [HARDWARE.md](HARDWARE.md)
2. Learn architecture from [DESIGN.md](DESIGN.md)
3. Explore build process in [BUILD.md](BUILD.md)

### Advanced
1. Study source code in `src/` directory
2. Understand linker script
3. Modify and extend features
4. Set up debugging environment

## 🤝 Contributing

When contributing to this project:
1. Follow existing code style
2. Update relevant documentation
3. Test on actual hardware
4. Update EXAMPLES.md if adding features

## 📝 Documentation Maintenance

### When to Update Documentation

**Update QUICKSTART.md when:**
- Installation steps change
- Quick start process changes
- New common issues discovered

**Update BUILD.md when:**
- Build process changes
- New dependencies added
- Toolchain versions change

**Update DESIGN.md when:**
- Architecture changes
- New modules added
- Design decisions made

**Update HARDWARE.md when:**
- Pin configuration changes
- Clock setup modified
- New hardware features used

**Update EXAMPLES.md when:**
- New features added
- New use cases discovered
- Error handling changes

## 📞 Support

For help:
1. Check relevant documentation section above
2. Look at troubleshooting sections
3. Review examples and test your setup
4. Consult ST's official documentation:
   - [STM32F401RE Reference Manual](https://www.st.com/resource/en/reference_manual/dm00096844.pdf)
   - [Nucleo-F401RE User Manual](https://www.st.com/resource/en/user_manual/dm00105823.pdf)

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

**Last Updated**: 2024
**Project Version**: 1.0
**Target**: STM32F401RE Nucleo Board
