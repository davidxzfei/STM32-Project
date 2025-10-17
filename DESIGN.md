# STM32F401RE Simple Calculator - Design Document

## Overview

This project implements a simple calculator on the STM32F401RE microcontroller with UART-based user interaction. The calculator supports basic arithmetic operations and provides a command-line interface through a serial terminal.

## Hardware Platform

**Microcontroller:** STM32F401RE (ARM Cortex-M4)
- 512 KB Flash memory
- 96 KB SRAM
- Maximum CPU frequency: 84 MHz
- FPU (Floating Point Unit) for hardware-accelerated floating-point operations

**Development Board:** STM32 Nucleo-F401RE
- Integrated ST-Link debugger/programmer
- Virtual COM port for USB serial communication
- Arduino-compatible headers
- Morpho connector for full MCU access

## System Architecture

### Clock Configuration

```
HSE (8 MHz) → PLL → 84 MHz System Clock
                  ↓
            APB1: 42 MHz (for USART2)
            APB2: 84 MHz
```

The system uses the external 8 MHz crystal (HSE) with PLL to achieve 84 MHz operation:
- PLL configuration: M=4, N=168, P=2, Q=4
- System clock (SYSCLK): 84 MHz
- AHB clock (HCLK): 84 MHz
- APB1 clock: 42 MHz
- APB2 clock: 84 MHz

### Memory Layout

**Flash Memory (0x0800_0000 - 0x0807_FFFF):**
```
0x08000000: Vector Table (Interrupt vectors)
0x08000xxx: .text section (Program code)
0x080xxxxx: .rodata section (Constants)
```

**SRAM (0x2000_0000 - 0x2001_7FFF):**
```
0x20000000: .data section (Initialized variables)
0x200xxxxx: .bss section (Uninitialized variables)
0x200xxxxx: Heap
0x20017xxx: Stack (grows downward from 0x20018000)
```

## Software Architecture

### Module Structure

```
┌─────────────────┐
│   main.c        │  - Entry point, main loop
└────────┬────────┘
         │
    ┌────┴────────────────┐
    │                     │
┌───▼──────────┐   ┌─────▼──────────┐
│ calculator.c │   │   uart.c       │
│              │   │                │
│ - Init       │   │ - Init         │
│ - Parse      │   │ - Send/Receive │
│ - Calculate  │   │ - Data Check   │
└──────────────┘   └────────────────┘
         │                 │
         │                 │
    ┌────▼─────────────────▼────┐
    │  system_stm32f4xx.c       │
    │  - Clock configuration    │
    │  - System initialization  │
    └───────────────────────────┘
```

### Component Descriptions

#### 1. Main Application (main.c)
- System initialization entry point
- Main event loop
- Polls UART for incoming data
- Dispatches characters to calculator module

#### 2. Calculator Module (calculator.c/h)
- **Input Buffer Management:** Stores user input up to 64 characters
- **Command Parser:** Uses sscanf() to parse "operand1 operator operand2" format
- **Arithmetic Engine:** Performs calculations using hardware FPU
- **Result Formatting:** Custom float-to-string conversion
- **Error Handling:** Validates input and handles division by zero

Supported Operations:
- Addition: `+`
- Subtraction: `-`
- Multiplication: `*`, `x`, `X`
- Division: `/`

#### 3. UART Driver (uart.c/h)
- **USART2 Configuration:**
  - Baud rate: 115200
  - Data bits: 8
  - Parity: None
  - Stop bits: 1
  - PA2: TX (Alternate Function 7)
  - PA3: RX (Alternate Function 7)

- **Functions:**
  - Initialization with GPIO alternate function setup
  - Character transmission (blocking)
  - String transmission
  - Character reception (blocking)
  - Non-blocking data available check

#### 4. System Initialization (system_stm32f4xx.c)
- Sets up vector table relocation
- Configures PLL for 84 MHz operation
- Enables HSE and waits for stabilization
- Configures bus prescalers
- Switches system clock to PLL

#### 5. Startup Code (startup_stm32f401xe.c)
- Vector table definition with all interrupt handlers
- Reset handler implementation:
  - Copies .data from Flash to RAM
  - Zeros out .bss section
  - Calls main()
- Default interrupt handlers

### Data Flow

```
User Input (Serial Terminal)
    ↓
UART2 Receive (Hardware)
    ↓
UART2_ReceiveChar() - uart.c
    ↓
Calculator_ProcessInput() - calculator.c
    ↓ [Accumulate in buffer]
    ↓ [On Enter key]
parse_and_calculate() - calculator.c
    ↓ [Parse operands and operator]
    ↓
Arithmetic Operation (Hardware FPU)
    ↓
float_to_string() - calculator.c
    ↓
UART2_SendString() - uart.c
    ↓
UART2 Transmit (Hardware)
    ↓
Display Result (Serial Terminal)
```

## User Interface

### Welcome Screen
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

### Input Processing
- Characters are echoed back for visual feedback
- Backspace (ASCII 127 or 8) removes last character
- Enter (CR/LF) processes the expression
- Buffer overflow protection (64 character limit)

### Output Format
```
calc> 5 + 3
Result: 8.0000
calc>
```

### Error Messages
- `Error: Invalid input format` - Parsing failed
- `Error: Division by zero` - Divide by zero attempted
- `Error: Unknown operator` - Unsupported operator used

## Design Decisions

### 1. Bare-Metal vs RTOS
**Choice:** Bare-metal implementation

**Rationale:**
- Simple application with minimal concurrency requirements
- Lower memory footprint
- Easier to understand and debug
- Direct hardware control

### 2. Polling vs Interrupts for UART
**Choice:** Polling in main loop

**Rationale:**
- Simpler implementation for a single-threaded application
- No interrupt priority concerns
- Adequate responsiveness for human typing speed
- Easy to extend if needed

### 3. Floating-Point Support
**Choice:** Use hardware FPU

**Rationale:**
- STM32F401RE has hardware FPU (fpv4-sp-d16)
- Enables float calculations without software emulation
- Better performance and code size
- Natural for calculator application

### 4. String Formatting
**Choice:** Custom float-to-string function

**Rationale:**
- Standard printf requires significant memory (heap)
- Custom implementation is lightweight
- Fixed precision (4 decimal places) is sufficient
- Avoids newlib nano dependencies

### 5. Error Handling
**Choice:** Return status codes + user-friendly messages

**Rationale:**
- Clear feedback to user
- Graceful degradation
- No system crashes on invalid input
- Educational value (explains errors)

## Performance Considerations

### Timing
- UART transmission at 115200 baud: ~86 μs per character
- Calculation time: < 1 μs (hardware FPU)
- Overall responsiveness: Limited by human typing speed

### Memory Usage
- Code size: ~10-15 KB
- Static data: ~100 bytes
- Stack: 1 KB reserved
- Heap: 512 bytes reserved (though not used in current implementation)

### Power Consumption
- Active mode at 84 MHz: ~25 mA
- Can be optimized with:
  - Lower clock frequency
  - Sleep mode when idle
  - Dynamic voltage scaling

## Future Enhancements

### Potential Features
1. **Extended Operations:**
   - Power, square root, modulo
   - Trigonometric functions
   - Parentheses support

2. **Expression Parser:**
   - Multi-operation expressions (e.g., "5 + 3 * 2")
   - Order of operations (PEMDAS)
   - Variable storage (memory)

3. **User Interface:**
   - Command history (up/down arrows)
   - Display mode (decimal, hex, binary)
   - Scientific notation

4. **Hardware Integration:**
   - LCD display (I2C/SPI)
   - Keypad input (GPIO)
   - LED indicators

5. **Optimization:**
   - DMA for UART transfers
   - Interrupt-driven I/O
   - Low-power sleep modes

## Testing Strategy

### Unit Testing
- Parser validation with various input formats
- Arithmetic operation correctness
- Edge cases (division by zero, very large/small numbers)
- Buffer overflow protection

### Integration Testing
- UART communication reliability
- Complete input-to-output flow
- Error handling paths
- System stability over extended operation

### Hardware Testing
- Verify on actual STM32F401RE board
- Test with different terminal applications
- Verify clock configuration with oscilloscope
- Temperature stability testing

## References

- [STM32F401xE Reference Manual](https://www.st.com/resource/en/reference_manual/dm00096844.pdf)
- [STM32F401RE Datasheet](https://www.st.com/resource/en/datasheet/stm32f401re.pdf)
- [ARM Cortex-M4 Technical Reference Manual](https://developer.arm.com/documentation/100166/0001)
- [Nucleo-F401RE User Manual](https://www.st.com/resource/en/user_manual/dm00105823.pdf)
