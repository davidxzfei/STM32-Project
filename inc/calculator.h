#ifndef CALCULATOR_H
#define CALCULATOR_H

#define CALC_BUFFER_SIZE 64

typedef enum {
    CALC_OK = 0,
    CALC_ERROR_INVALID_INPUT,
    CALC_ERROR_DIVISION_BY_ZERO,
    CALC_ERROR_UNKNOWN_OPERATOR,
    CALC_ERROR_BUFFER_OVERFLOW
} CalcStatus;

void Calculator_Init(void);
void Calculator_ProcessInput(char c);
void Calculator_PrintPrompt(void);

#endif
