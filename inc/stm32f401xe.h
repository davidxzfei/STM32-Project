#ifndef STM32F401XE_H
#define STM32F401XE_H

#include <stdint.h>

/* Memory Base Addresses */
#define FLASH_BASE            0x08000000UL
#define SRAM_BASE             0x20000000UL
#define PERIPH_BASE           0x40000000UL

/* APB1 Peripherals */
#define APB1PERIPH_BASE       PERIPH_BASE
#define USART2_BASE           (APB1PERIPH_BASE + 0x4400UL)

/* APB2 Peripherals */
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000UL)

/* AHB1 Peripherals */
#define AHB1PERIPH_BASE       (PERIPH_BASE + 0x00020000UL)
#define GPIOA_BASE            (AHB1PERIPH_BASE + 0x0000UL)
#define RCC_BASE              (AHB1PERIPH_BASE + 0x3800UL)

/* System Control Block */
#define SCS_BASE              0xE000E000UL
#define SCB_BASE              (SCS_BASE + 0x0D00UL)

/* GPIO Register Structure */
typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
} GPIO_TypeDef;

/* USART Register Structure */
typedef struct {
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
} USART_TypeDef;

/* RCC Register Structure */
typedef struct {
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    uint32_t RESERVED0[2];
    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;
    uint32_t RESERVED1[2];
    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;
    uint32_t RESERVED2[2];
    volatile uint32_t APB1ENR;
    volatile uint32_t APB2ENR;
} RCC_TypeDef;

/* SCB Register Structure */
typedef struct {
    volatile uint32_t CPUID;
    volatile uint32_t ICSR;
    volatile uint32_t VTOR;
    volatile uint32_t AIRCR;
    volatile uint32_t SCR;
    volatile uint32_t CCR;
    volatile uint32_t SHPR[3];
    volatile uint32_t SHCSR;
    volatile uint32_t CFSR;
    volatile uint32_t HFSR;
    volatile uint32_t DFSR;
    volatile uint32_t MMFAR;
    volatile uint32_t BFAR;
    volatile uint32_t AFSR;
} SCB_TypeDef;

/* Peripheral Definitions */
#define GPIOA                 ((GPIO_TypeDef *) GPIOA_BASE)
#define USART2                ((USART_TypeDef *) USART2_BASE)
#define RCC                   ((RCC_TypeDef *) RCC_BASE)
#define SCB                   ((SCB_TypeDef *) SCB_BASE)

/* RCC Bit Definitions */
#define RCC_AHB1ENR_GPIOAEN   (1UL << 0)
#define RCC_APB1ENR_USART2EN  (1UL << 17)
#define RCC_CR_HSEON          (1UL << 16)
#define RCC_CR_HSERDY         (1UL << 17)
#define RCC_CR_PLLON          (1UL << 24)
#define RCC_CR_PLLRDY         (1UL << 25)
#define RCC_CFGR_SW_PLL       (0x2UL << 0)
#define RCC_CFGR_SWS_PLL      (0x2UL << 2)

/* USART Bit Definitions */
#define USART_SR_TXE          (1UL << 7)
#define USART_SR_RXNE         (1UL << 5)
#define USART_CR1_UE          (1UL << 13)
#define USART_CR1_TE          (1UL << 3)
#define USART_CR1_RE          (1UL << 2)

/* System Constants */
#define HSE_VALUE             8000000UL
#define HSI_VALUE             16000000UL

/* External declarations */
extern uint32_t SystemCoreClock;

void SystemInit(void);
void SystemCoreClockUpdate(void);

#endif
