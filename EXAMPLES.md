# Usage Examples

## Basic Arithmetic Operations

### Addition
```
calc> 5 + 3
Result: 8.0000

calc> 123.45 + 67.89
Result: 191.3400

calc> -10 + 5
Result: -5.0000
```

### Subtraction
```
calc> 10 - 3
Result: 7.0000

calc> 5.5 - 2.3
Result: 3.2000

calc> 0 - 15
Result: -15.0000
```

### Multiplication
```
calc> 6 * 7
Result: 42.0000

calc> 2.5 * 4
Result: 10.0000

calc> -3 * 5
Result: -15.0000

calc> 0.1 * 0.1
Result: 0.0100
```

### Division
```
calc> 20 / 4
Result: 5.0000

calc> 15 / 2
Result: 7.5000

calc> 1 / 3
Result: 0.3333

calc> 100 / 25
Result: 4.0000
```

## Edge Cases

### Division by Zero
```
calc> 5 / 0
Error: Division by zero
calc>
```

### Very Large Numbers
```
calc> 99999 * 99999
Result: 9999800001.0000

calc> 1000000 + 1000000
Result: 2000000.0000
```

### Very Small Numbers
```
calc> 0.001 * 0.001
Result: 0.0000

calc> 0.1 + 0.1
Result: 0.2000
```

### Negative Numbers
```
calc> -5 + -3
Result: -8.0000

calc> -10 * -2
Result: 20.0000

calc> -15 / 3
Result: -5.0000
```

## Error Examples

### Invalid Input Format

Missing operator:
```
calc> 5 3
Error: Invalid input format
calc>
```

Missing operand:
```
calc> 5 +
Error: Invalid input format
calc>
```

No spaces:
```
calc> 5+3
Error: Invalid input format
calc>
```

### Unknown Operator
```
calc> 5 % 3
Error: Unknown operator
calc>

calc> 10 ^ 2
Error: Unknown operator
calc>
```

### Invalid Characters
```
calc> five + three
Error: Invalid input format
calc>

calc> 5 + three
Error: Invalid input format
calc>
```

## Special Input Handling

### Backspace/Delete
```
calc> 5 + 333[BACKSPACE][BACKSPACE]3
Result: 8.0000
```

### Empty Input
```
calc> [ENTER]
calc>
```
(Returns to prompt without error)

### Alternative Multiplication Symbol
```
calc> 5 x 3
Result: 15.0000

calc> 5 X 3
Result: 15.0000

calc> 5 * 3
Result: 15.0000
```
(All three forms work for multiplication)

## Practical Calculations

### Temperature Conversion (Celsius to Fahrenheit formula: F = C * 1.8 + 32)

Step 1: Multiply by 1.8
```
calc> 25 * 1.8
Result: 45.0000
```

Step 2: Add 32
```
calc> 45 + 32
Result: 77.0000
```

### Voltage Divider Calculation
For R1=10k, R2=5k, Vin=5V
Vout = Vin * R2 / (R1 + R2)

Step 1: Add resistors
```
calc> 10 + 5
Result: 15.0000
```

Step 2: Calculate ratio
```
calc> 5 / 15
Result: 0.3333
```

Step 3: Multiply by input voltage
```
calc> 5 * 0.3333
Result: 1.6665
```

### Power Calculation (P = V² / R)
For V=12V, R=4Ω

Step 1: Square voltage
```
calc> 12 * 12
Result: 144.0000
```

Step 2: Divide by resistance
```
calc> 144 / 4
Result: 36.0000
```
Power = 36 Watts

### Percentage Calculation
Calculate 15% of 200

Step 1: Convert percentage to decimal
```
calc> 15 / 100
Result: 0.1500
```

Step 2: Multiply by base number
```
calc> 0.15 * 200
Result: 30.0000
```

### Speed Calculation (Distance/Time)
Distance = 120 km, Time = 2.5 hours

```
calc> 120 / 2.5
Result: 48.0000
```
Speed = 48 km/h

### Area Calculation
Rectangle: length = 12.5, width = 8.3

```
calc> 12.5 * 8.3
Result: 103.7500
```
Area = 103.75 square units

### Unit Conversion
Inches to centimeters (1 inch = 2.54 cm)
Convert 10 inches to cm:

```
calc> 10 * 2.54
Result: 25.4000
```

## Session Example

Complete calculation session:
```
=====================================
  STM32F401RE Simple Calculator
=====================================
Supported operations: +, -, *, /
Format: operand1 operator operand2
Example: 5 + 3
         12.5 * 2.4
=====================================

calc> 10 + 5
Result: 15.0000
calc> 20 - 8
Result: 12.0000
calc> 6 * 7
Result: 42.0000
calc> 100 / 4
Result: 25.0000
calc> 5 / 0
Error: Division by zero
calc> 3.14 * 2
Result: 6.2800
calc> hello
Error: Invalid input format
calc>
```

## Tips for Best Results

1. **Always use spaces:** Place spaces between operands and operators
   - ✓ Correct: `5 + 3`
   - ✗ Incorrect: `5+3`

2. **Decimal precision:** Results are displayed with 4 decimal places
   - Input: `1 / 3`
   - Output: `0.3333`

3. **Negative numbers:** Use minus sign directly before the number
   - ✓ Correct: `-5 + 3`
   - ✓ Correct: `5 + -3`

4. **Floating-point limitations:** Very large or very small numbers may lose precision
   - This is inherent to 32-bit floating-point representation

5. **Buffer limit:** Input is limited to 63 characters
   - Typical expressions are well within this limit

6. **Use backspace:** Correct mistakes before pressing Enter
   - Backspace key removes the last character

7. **Calculator state:** Each calculation is independent
   - No memory or variable storage (yet!)
