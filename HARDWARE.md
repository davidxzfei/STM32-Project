# Hardware Configuration

## STM32F401RE Nucleo Board

### Board Overview
```
                    STM32 Nucleo-F401RE
    ┌───────────────────────────────────────────┐
    │                                           │
    │  ┌─────────────────────────────────┐     │
    │  │      STM32F401RET6              │     │
    │  │      ARM Cortex-M4              │     │
    │  │      84 MHz, 512KB Flash        │     │
    │  │      96KB RAM                   │     │
    │  └─────────────────────────────────┘     │
    │                                           │
    │  ST-Link V2-1 (Integrated)               │
    │  ┌────────────────┐                      │
    │  │  Debug/Program │                      │
    │  │  Virtual COM   │                      │
    │  └────────────────┘                      │
    │                                           │
    │  CN7/CN10 - Arduino Headers              │
    │  CN4 - USB User                          │
    │  CN1 - USB ST-Link                       │
    │                                           │
    └───────────────────────────────────────────┘
```

## Pin Configuration

### USART2 (Connected to ST-Link VCP)
```
Pin     Function    Connection
PA2     TX          → ST-Link → USB → Computer
PA3     RX          ← ST-Link ← USB ← Computer
```

### Pin Details
| Pin | Arduino | Function | Mode | AF |
|-----|---------|----------|------|-----|
| PA2 | D1      | USART2_TX | AF7  | Push-pull |
| PA3 | D0      | USART2_RX | AF7  | No pull |

## Connection Diagram

```
┌──────────────┐         USB Cable        ┌──────────────┐
│              │◄────────────────────────►│              │
│   Computer   │                          │ Nucleo Board │
│              │                          │              │
│  Serial      │                          │  ST-Link     │
│  Terminal    │                          │  VCP         │
│              │                          │  (USART2)    │
│              │                          │              │
└──────────────┘                          │  PA2: TX ────┤
                                          │  PA3: RX ────┤
                                          │              │
                                          │  STM32F401RE │
                                          │  @ 84 MHz    │
                                          │              │
                                          └──────────────┘
```

## Clock Tree

```
                  STM32F401RE Clock Tree
                  
External Crystal (HSE)
    8 MHz
      │
      ▼
   ┌─────┐
   │ /M  │ ÷4
   └──┬──┘
      │ 2 MHz
      ▼
   ┌─────┐
   │ ×N  │ ×168
   └──┬──┘
      │ 336 MHz
      ▼
   ┌─────┐
   │ /P  │ ÷2
   └──┬──┘
      │
      ├────► SYSCLK (84 MHz)
      │          │
      │          ├────► AHB (84 MHz)
      │          │        │
      │          │        ├────► APB2 (84 MHz)
      │          │        │        │
      │          │        │        └────► Timers
      │          │        │
      │          │        └────► APB1 (42 MHz)
      │          │                 │
      │          │                 └────► USART2 (42 MHz)
      │          │
      │          └────► Cortex System Timer
      │
      └────► /Q (84 MHz, unused)
```

## GPIO Configuration

### USART2 TX (PA2)
```
Mode:          Alternate Function
AF Number:     AF7 (USART2)
Output Type:   Push-pull
Speed:         High (50 MHz)
Pull:          No pull-up/pull-down
```

### USART2 RX (PA3)
```
Mode:          Alternate Function
AF Number:     AF7 (USART2)
Output Type:   N/A (input)
Speed:         High (50 MHz)
Pull:          No pull-up/pull-down
```

## Memory Map

```
0x0000_0000 ├──────────────────────┐
            │   Aliased to Flash   │ (Boot from Flash)
0x0800_0000 ├──────────────────────┤
            │   Flash Memory       │ 512 KB
            │   - Vector Table     │
            │   - Code (.text)     │
            │   - Constants (.ro)  │
0x0807_FFFF ├──────────────────────┤
            │   ...                │
0x2000_0000 ├──────────────────────┤
            │   SRAM               │ 96 KB
            │   - .data            │
            │   - .bss             │
            │   - Heap             │
            │   - Stack            │
0x2001_7FFF ├──────────────────────┤
            │   ...                │
0x4000_0000 ├──────────────────────┤
            │   Peripherals        │
            │   - APB1 (USART2)    │
            │   - APB2             │
            │   - AHB1 (GPIO, RCC) │
0x5FFF_FFFF ├──────────────────────┤
            │   ...                │
0xE000_0000 ├──────────────────────┤
            │   Cortex-M4 Internal │
            │   - SysTick          │
            │   - NVIC             │
            │   - SCB              │
0xFFFF_FFFF └──────────────────────┘
```

## Power Supply

### Options
1. **USB ST-Link (Default)** - Powers from CN1 USB connector
2. **USB User** - Powers from CN4 (5V_USB_VBUS)
3. **External 5V** - E5V pin (requires VIN/E5V solder bridge)
4. **External 3.3V** - +3V3 pin

### Current Consumption
- Active @ 84 MHz: ~25 mA
- USART active: +2 mA
- Total typical: ~30 mA

## LED Indicators

| LED | Color | Connection | Function |
|-----|-------|------------|----------|
| LD1 | Tri-color | ST-Link | ST-Link communication |
| LD2 | Green | PA5 | User LED (not used in this project) |
| LD3 | Red | Power | Power indicator |

## Reset and Boot Configuration

### Reset Sources
1. **NRST Pin** - External reset (button B1)
2. **Power-on Reset** - VDD rise
3. **Software Reset** - NVIC system reset

### Boot Mode (STM32F401RE)
```
BOOT0 pin = 0 (default)
BOOT1 = X (don't care)
→ Boot from Flash (0x0800_0000)
```

## Serial Terminal Settings

### Configuration
```
Parameter       Value
─────────────────────────
Baud Rate:      115200
Data Bits:      8
Parity:         None
Stop Bits:      1
Flow Control:   None
```

### Connection
- **Linux/macOS:** `/dev/ttyACM0` (or `/dev/cu.usbmodem*` on macOS)
- **Windows:** `COMx` (check Device Manager)

### Terminal Commands

#### Using screen (Linux/macOS):
```bash
screen /dev/ttyACM0 115200
```

#### Using minicom (Linux):
```bash
minicom -D /dev/ttyACM0 -b 115200
```

#### Using PuTTY (Windows):
1. Connection Type: Serial
2. Serial Line: COM3 (or appropriate port)
3. Speed: 115200

## Hardware Requirements

### Minimum Requirements
- STM32 Nucleo-F401RE board
- USB Type-A to Mini-B cable (for ST-Link)
- Computer with USB port
- Serial terminal software

### Optional Additions
- Logic analyzer for debugging
- Oscilloscope for clock verification
- ST-Link/V2 external debugger (board has integrated)

## Troubleshooting Hardware Issues

### LED States

**LD1 (ST-Link):**
- Blinking red: Communication error
- Red/green: Flashing in progress
- Green: Successful connection

**LD3 (Power):**
- Off: No power supply
- On: Board powered correctly

### Common Issues

**No serial output:**
1. Check USB connection
2. Verify correct COM port selection
3. Confirm baud rate (115200)
4. Check ST-Link driver installation
5. Try different USB port

**Cannot flash:**
1. Check ST-Link connection (LD1)
2. Verify st-flash or OpenOCD installation
3. Try: `st-flash erase` then reflash
4. Check USB cable (some are charge-only)

**Erratic behavior:**
1. Check power supply (USB cable quality)
2. Verify clock configuration
3. Check for solder bridges
4. Try different USB port (avoid hubs)

## Development Tools

### Required Software
- ARM GCC toolchain (`arm-none-eabi-gcc`)
- Make
- ST-Link utilities (`st-flash`, `st-info`)

### Optional Tools
- OpenOCD (debugging)
- GDB (`arm-none-eabi-gdb`)
- STM32CubeIDE
- System Workbench for STM32

## Schematic References

For complete board schematics, refer to:
- [Nucleo-F401RE Schematic (ST)](https://www.st.com/resource/en/schematic_pack/nucleo_64pins_sch.zip)
- [STM32F401RE Datasheet](https://www.st.com/resource/en/datasheet/stm32f401re.pdf)

## Pin Compatibility

This project uses only USART2 (PA2/PA3), so all other pins remain available for expansion:
- 50 I/O pins available
- 3 I2C interfaces
- 3 SPI interfaces
- 3 additional USARTs
- 12-bit ADC (16 channels)
- Multiple timers
- USB OTG Full Speed

## Safety Notes

1. Do not exceed 3.3V on any GPIO pin
2. Maximum current per I/O pin: 25 mA
3. Do not apply voltage to pins before powering the board
4. Disconnect external circuits before flashing
5. Use proper ESD precautions when handling the board
