#include <stdint.h>

#define SRAM_START (0x20000000U)
#define SRAM_SIZE (128U * 1024U)
#define SRAM_END (SRAM_START + SRAM_SIZE)
#define STACK_POINTER_INIT_ADDRESS (SRAM_END)
#define ISR_VECTOR_SIZE_WORDS 102 // Total exception count + interrupt count + 2

void default_handler(void);

// Cortex-M4 system exceptions
void Reset_exception_handler(void);
void NMI_exception_handler(void) __attribute__((weak, alias("default_handler")));
void HardFault_exception_handler(void) __attribute__((weak, alias("default_handler")));
void MemManage_exception_handler(void) __attribute__((weak, alias("default_handler")));
void BusFault_exception_handler(void) __attribute__((weak, alias("default_handler")));
void UsageFault_exception_handler(void) __attribute__((weak, alias("default_handler")));
void SVCall_exception_handler(void) __attribute__((weak, alias("default_handler")));
void DebugMonitor_exception_handler(void) __attribute__((weak, alias("default_handler")));
void PendSV_exception_handler(void) __attribute__((weak, alias("default_handler")));
void Systick_exception_handler(void) __attribute__((weak, alias("default_handler")));

// STM32F411xC/E interrupt handlers
void WWDG_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void EXTI16_PVD_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void EXTI21_TAMP_STAMP_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void EXTI22_RTC_WKUP_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void FLASH_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void RCC_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void EXTI0_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void EXTI1_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void EXTI2_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void EXTI3_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void EXTI4_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void DMA1_Stream0_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void DMA1_Stream1_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void DMA1_Stream2_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void DMA1_Stream3_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void DMA1_Stream4_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void DMA1_Stream5_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void DMA1_Stream6_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void ADC_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void EXTI9_5_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void TIM1_BRK_TIM9_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void TIM1_UP_TIM10_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void TIM1_TRG_COM_TIM11_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void TIM1_CC_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void TIM2_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void TIM3_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void TIM4_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void I2C1_EV_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void I2C1_ER_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void I2C2_EV_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void I2C2_ER_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void SPI1_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void SPI2_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void USART1_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void USART2_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void EXTI15_10_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void EXTI17_RTC_Alarm_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void EXTI18_OTG_FS_WKUP_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void DMA1_Stream7_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void SDIO_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void TIM5_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void SPI3_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void DMA2_Stream0_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void DMA2_Stream1_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void DMA2_Stream2_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void DMA2_Stream3_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void DMA2_Stream4_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void OTG_FS_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void DMA2_Stream5_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void DMA2_Stream6_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void DMA2_Stream7_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void USART6_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void I2C3_EV_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void I2C3_ER_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void FPU_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void SPI4_interrupt_handler(void) __attribute__((weak, alias("default_handler")));
void SPI5_interrupt_handler(void) __attribute__((weak, alias("default_handler")));

uint32_t isr_vector[ISR_VECTOR_SIZE_WORDS] __attribute__((section(".isr_vector"))) = {
    STACK_POINTER_INIT_ADDRESS,
    // Cortex-M4 system exceptions
    (uint32_t)&Reset_exception_handler,                 // 0x0000 0004
    (uint32_t)&NMI_exception_handler,                   // 0x0000 0008
    (uint32_t)&HardFault_exception_handler,             // 0x0000 000C
    (uint32_t)&MemManage_exception_handler,             // 0x0000 0010
    (uint32_t)&BusFault_exception_handler,              // 0x0000 0014
    (uint32_t)&UsageFault_exception_handler,            // 0x0000 0018
    0,                                                  // 0x0000 001C
    0,                                                  // 0x0000 0020
    0,                                                  // 0x0000 0024
    0,                                                  // 0x0000 0028
    (uint32_t)&SVCall_exception_handler,                // 0x0000 002C
    (uint32_t)&DebugMonitor_exception_handler,          // 0x0000 0030
    0,                                                  // 0x0000 0034
    (uint32_t)&PendSV_exception_handler,                // 0x0000 0038
    (uint32_t)&Systick_exception_handler,               // 0x0000 003C
    /* STM32F411xC/E interrupt handlers, see chapter 10.1.3 Interrupt and exception vector table 37 of Reference manual */
    (uint32_t)&WWDG_interrupt_handler,                  // 0x0000 0040
    (uint32_t)&EXTI16_PVD_interrupt_handler,            // 0x0000 0044
    (uint32_t)&EXTI21_TAMP_STAMP_interrupt_handler,     // 0x0000 0048
    (uint32_t)&EXTI22_RTC_WKUP_interrupt_handler,       // 0x0000 004C
    (uint32_t)&FLASH_interrupt_handler,                 // 0x0000 0050
    (uint32_t)&RCC_interrupt_handler,                   // 0x0000 0054
    (uint32_t)&EXTI0_interrupt_handler,                 // 0x0000 0058
    (uint32_t)&EXTI1_interrupt_handler,                 // 0x0000 005C
    (uint32_t)&EXTI2_interrupt_handler,                 // 0x0000 0060
    (uint32_t)&EXTI3_interrupt_handler,                 // 0x0000 0064
    (uint32_t)&EXTI4_interrupt_handler,                 // 0x0000 0068
    (uint32_t)&DMA1_Stream0_interrupt_handler,          // 0x0000 006C
    (uint32_t)&DMA1_Stream1_interrupt_handler,          // 0x0000 0070
    (uint32_t)&DMA1_Stream2_interrupt_handler,          // 0x0000 0074
    (uint32_t)&DMA1_Stream3_interrupt_handler,          // 0x0000 0078
    (uint32_t)&DMA1_Stream4_interrupt_handler,          // 0x0000 007C
    (uint32_t)&DMA1_Stream5_interrupt_handler,          // 0x0000 0080
    (uint32_t)&DMA1_Stream6_interrupt_handler,          // 0x0000 0084
    (uint32_t)&ADC_interrupt_handler,                   // 0x0000 0088
    0,                                                  // 0x0000 008C
    0,                                                  // 0x0000 0090
    0,                                                  // 0x0000 0094
    0,                                                  // 0x0000 0098
    (uint32_t)&EXTI9_5_interrupt_handler,               // 0x0000 009C
    (uint32_t)&TIM1_BRK_TIM9_interrupt_handler,         // 0x0000 00A0
    (uint32_t)&TIM1_UP_TIM10_interrupt_handler,         // 0x0000 00A4
    (uint32_t)&TIM1_TRG_COM_TIM11_interrupt_handler,    // 0x0000 00A8
    (uint32_t)&TIM1_CC_interrupt_handler,               // 0x0000 00AC
    (uint32_t)&TIM2_interrupt_handler,                  // 0x0000 00B0
    (uint32_t)&TIM3_interrupt_handler,                  // 0x0000 00B4
    (uint32_t)&TIM4_interrupt_handler,                  // 0x0000 00B8
    (uint32_t)&I2C1_EV_interrupt_handler,               // 0x0000 00BC
    (uint32_t)&I2C1_ER_interrupt_handler,               // 0x0000 00C0
    (uint32_t)&I2C2_EV_interrupt_handler,               // 0x0000 00C4
    (uint32_t)&I2C2_ER_interrupt_handler,               // 0x0000 00C8
    (uint32_t)&SPI1_interrupt_handler,                  // 0x0000 00CC
    (uint32_t)&SPI2_interrupt_handler,                  // 0x0000 00D0
    (uint32_t)&USART1_interrupt_handler,                // 0x0000 00D4
    (uint32_t)&USART2_interrupt_handler,                // 0x0000 00D8
    0,                                                  // 0x0000 00DC
    (uint32_t)&EXTI15_10_interrupt_handler,             // 0x0000 00E0
    (uint32_t)&EXTI17_RTC_Alarm_interrupt_handler,      // 0x0000 00E4
    (uint32_t)&EXTI18_OTG_FS_WKUP_interrupt_handler,    // 0x0000 00E8
    0,                                                  // 0x0000 00EC
    0,                                                  // 0x0000 00F0
    0,                                                  // 0x0000 00F4
    0,                                                  // 0x0000 00F8
    (uint32_t)&DMA1_Stream7_interrupt_handler,          // 0x0000 00FC
    0,                                                  // 0x0000 0100
    (uint32_t)&SDIO_interrupt_handler,                  // 0x0000 0104
    (uint32_t)&TIM5_interrupt_handler,                  // 0x0000 0108
    (uint32_t)&SPI3_interrupt_handler,                  // 0x0000 010C
    0,                                                  // 0x0000 0110
    0,                                                  // 0x0000 0114
    0,                                                  // 0x0000 0118
    0,                                                  // 0x0000 011C
    (uint32_t)&DMA2_Stream0_interrupt_handler,          // 0x0000 0120
    (uint32_t)&DMA2_Stream1_interrupt_handler,          // 0x0000 0124
    (uint32_t)&DMA2_Stream2_interrupt_handler,          // 0x0000 0128
    (uint32_t)&DMA2_Stream3_interrupt_handler,          // 0x0000 012C
    (uint32_t)&DMA2_Stream4_interrupt_handler,          // 0x0000 0130
    0,                                                  // 0x0000 0134
    0,                                                  // 0x0000 0138
    0,                                                  // 0x0000 013C
    0,                                                  // 0x0000 0140
    0,                                                  // 0x0000 0144
    0,                                                  // 0x0000 0148
    (uint32_t)&OTG_FS_interrupt_handler,                // 0x0000 014C
    (uint32_t)&DMA2_Stream5_interrupt_handler,          // 0x0000 0150
    (uint32_t)&DMA2_Stream6_interrupt_handler,          // 0x0000 0154
    (uint32_t)&DMA2_Stream7_interrupt_handler,          // 0x0000 0158
    (uint32_t)&USART6_interrupt_handler,                // 0x0000 015C
    (uint32_t)&I2C3_EV_interrupt_handler,               // 0x0000 0160
    (uint32_t)&I2C3_ER_interrupt_handler,               // 0x0000 0164
    0,                                                  // 0x0000 0168
    0,                                                  // 0x0000 016C
    0,                                                  // 0x0000 0170
    0,                                                  // 0x0000 0174
    0,                                                  // 0x0000 0178
    0,                                                  // 0x0000 017C
    0,                                                  // 0x0000 0180
    (uint32_t)&FPU_interrupt_handler,                   // 0x0000 0184
    0,                                                  // 0x0000 0188
    0,                                                  // 0x0000 018C
    (uint32_t)&SPI4_interrupt_handler,                  // 0x0000 0190
    (uint32_t)&SPI5_interrupt_handler                   // 0x0000 0194
};

extern uint32_t _etext, _sdata, _edata, _sbss, _ebss;
void main(void);

void Reset_exception_handler(void)
{
    // Copy .data from FLASH to SRAM
    uint32_t data_size = (uint32_t)&_edata - (uint32_t)&_sdata;
    uint8_t *flash_data = (uint8_t*) &_etext;
    uint8_t *sram_data = (uint8_t*) &_sdata;
  
    for (uint32_t i = 0; i < data_size; i++)
    {
        sram_data[i] = flash_data[i];
    }

    // Zero-fill .bss section in SRAM
    uint32_t bss_size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    uint8_t *bss = (uint8_t*) &_sbss;

    for (uint32_t i = 0; i < bss_size; i++)
    {
        bss[i] = 0;
    }
  
    main();
}

void default_handler(void)
{
    while(1);
}
