#include "calculator.h"
#include "uart.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static char input_buffer[CALC_BUFFER_SIZE];
static uint32_t buffer_index = 0;

static void float_to_string(float value, char *buffer, int precision)
{
    int int_part = (int)value;
    float frac_part = value - (float)int_part;
    
    if (value < 0) {
        *buffer++ = '-';
        int_part = -int_part;
        frac_part = -frac_part;
    }
    
    char temp[20];
    int i = 0;
    
    if (int_part == 0) {
        temp[i++] = '0';
    } else {
        while (int_part > 0) {
            temp[i++] = '0' + (int_part % 10);
            int_part /= 10;
        }
    }
    
    for (int j = i - 1; j >= 0; j--) {
        *buffer++ = temp[j];
    }
    
    *buffer++ = '.';
    
    for (int j = 0; j < precision; j++) {
        frac_part *= 10;
        int digit = (int)frac_part;
        *buffer++ = '0' + digit;
        frac_part -= digit;
    }
    
    *buffer = '\0';
}

static CalcStatus parse_and_calculate(const char *input, float *result)
{
    float operand1, operand2;
    char operator;
    int parsed;
    
    parsed = sscanf(input, "%f %c %f", &operand1, &operator, &operand2);
    
    if (parsed != 3) {
        return CALC_ERROR_INVALID_INPUT;
    }
    
    switch (operator) {
        case '+':
            *result = operand1 + operand2;
            break;
        case '-':
            *result = operand1 - operand2;
            break;
        case '*':
        case 'x':
        case 'X':
            *result = operand1 * operand2;
            break;
        case '/':
            if (operand2 == 0.0f) {
                return CALC_ERROR_DIVISION_BY_ZERO;
            }
            *result = operand1 / operand2;
            break;
        default:
            return CALC_ERROR_UNKNOWN_OPERATOR;
    }
    
    return CALC_OK;
}

void Calculator_Init(void)
{
    buffer_index = 0;
    memset(input_buffer, 0, CALC_BUFFER_SIZE);
    
    UART2_SendString("\r\n");
    UART2_SendString("=====================================\r\n");
    UART2_SendString("  STM32F401RE Simple Calculator\r\n");
    UART2_SendString("=====================================\r\n");
    UART2_SendString("Supported operations: +, -, *, /\r\n");
    UART2_SendString("Format: operand1 operator operand2\r\n");
    UART2_SendString("Example: 5 + 3\r\n");
    UART2_SendString("         12.5 * 2.4\r\n");
    UART2_SendString("=====================================\r\n\r\n");
}

void Calculator_PrintPrompt(void)
{
    UART2_SendString("calc> ");
}

void Calculator_ProcessInput(char c)
{
    if (c == '\r' || c == '\n') {
        UART2_SendString("\r\n");
        
        if (buffer_index > 0) {
            input_buffer[buffer_index] = '\0';
            
            float result = 0;
            CalcStatus status = parse_and_calculate(input_buffer, &result);
            
            switch (status) {
                case CALC_OK: {
                    char result_str[32];
                    float_to_string(result, result_str, 4);
                    UART2_SendString("Result: ");
                    UART2_SendString(result_str);
                    UART2_SendString("\r\n");
                    break;
                }
                case CALC_ERROR_INVALID_INPUT:
                    UART2_SendString("Error: Invalid input format\r\n");
                    break;
                case CALC_ERROR_DIVISION_BY_ZERO:
                    UART2_SendString("Error: Division by zero\r\n");
                    break;
                case CALC_ERROR_UNKNOWN_OPERATOR:
                    UART2_SendString("Error: Unknown operator\r\n");
                    break;
                default:
                    UART2_SendString("Error: Unknown error\r\n");
                    break;
            }
            
            buffer_index = 0;
            memset(input_buffer, 0, CALC_BUFFER_SIZE);
        }
        
        Calculator_PrintPrompt();
    } else if (c == 127 || c == 8) {
        if (buffer_index > 0) {
            buffer_index--;
            input_buffer[buffer_index] = '\0';
            UART2_SendString("\b \b");
        }
    } else if (buffer_index < CALC_BUFFER_SIZE - 1) {
        input_buffer[buffer_index++] = c;
        UART2_SendChar(c);
    }
}
