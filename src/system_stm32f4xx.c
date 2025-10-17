#include "stm32f401xe.h"

uint32_t SystemCoreClock = 84000000;

void SystemInit(void)
{
    SCB->VTOR = FLASH_BASE;
    
    RCC->CR |= RCC_CR_HSEON;
    while (!(RCC->CR & RCC_CR_HSERDY));
    
    RCC->PLLCFGR = 0;
    RCC->PLLCFGR |= (4UL << 0);
    RCC->PLLCFGR |= (168UL << 6);
    RCC->PLLCFGR |= (0UL << 16);
    RCC->PLLCFGR |= (4UL << 24);
    
    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY));
    
    RCC->CFGR |= (0x5UL << 10);
    RCC->CFGR |= (0x4UL << 13);
    
    RCC->CFGR &= ~(0x3UL << 0);
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & (0x3UL << 2)) != RCC_CFGR_SWS_PLL);
    
    SystemCoreClock = 84000000;
}

void SystemCoreClockUpdate(void)
{
    SystemCoreClock = 84000000;
}
