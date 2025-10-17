#include "uart.h"
#include "stm32f401xe.h"

void UART2_Init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    
    GPIOA->MODER &= ~((3UL << (2*2)) | (3UL << (2*3)));
    GPIOA->MODER |= (2UL << (2*2)) | (2UL << (2*3));
    
    GPIOA->AFR[0] &= ~((0xFUL << (4*2)) | (0xFUL << (4*3)));
    GPIOA->AFR[0] |= (7UL << (4*2)) | (7UL << (4*3));
    
    GPIOA->OSPEEDR |= (3UL << (2*2)) | (3UL << (2*3));
    
    uint32_t apb1_clock = SystemCoreClock / 2;
    uint32_t usartdiv = apb1_clock / 115200;
    USART2->BRR = usartdiv;
    
    USART2->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}

void UART2_SendChar(char c)
{
    while (!(USART2->SR & USART_SR_TXE));
    USART2->DR = c;
}

void UART2_SendString(const char *str)
{
    while (*str) {
        UART2_SendChar(*str++);
    }
}

char UART2_ReceiveChar(void)
{
    while (!(USART2->SR & USART_SR_RXNE));
    return (char)(USART2->DR & 0xFF);
}

int UART2_DataAvailable(void)
{
    return (USART2->SR & USART_SR_RXNE) ? 1 : 0;
}
