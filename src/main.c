#include "stm32f401xe.h"
#include "uart.h"
#include "calculator.h"

int main(void)
{
    SystemInit();
    
    UART2_Init();
    
    Calculator_Init();
    
    Calculator_PrintPrompt();
    
    while (1) {
        if (UART2_DataAvailable()) {
            char c = UART2_ReceiveChar();
            Calculator_ProcessInput(c);
        }
    }
    
    return 0;
}
