#include <stdint.h>

#define SRAM_START (0x20000000U)
#define SRAM_SIZE (128U * 1024U)
#define SRAM_END (SRAM_START + SRAM_SIZE)
#define STACK_POINTER_INIT_ADDRESS (SRAM_END)
#define ISR_VECTOR_SIZE_WORDS 102 // Total exception count + interrupt count + 2

void reset_handler(void);
void default_handler(void);

// Cortex-M4 system exceptions
void nmi_handler(void) __attribute__((weak, alias("default_handler")));
void hard_fault_handler(void) __attribute__((weak, alias("default_handler")));
void mem_manage_handler(void) __attribute__((weak, alias("default_handler")));
void bus_fault_handler(void) __attribute__((weak, alias("default_handler")));
void usage_fault_handler(void) __attribute__((weak, alias("default_handler")));
void svcall_handler(void) __attribute__((weak, alias("default_handler")));
void debug_monitor_handler(void) __attribute__((weak, alias("default_handler")));
void pendsv_handler(void) __attribute__((weak, alias("default_handler")));
void systick_handler(void) __attribute__((weak, alias("default_handler")));

// STM32F411xC/E interrupt handlers
void wwdg_handler(void) __attribute__((weak, alias("default_handler")));
void exti16_pvd_handler(void) __attribute__((weak, alias("default_handler")));
void exti21_tamp_stamp_handler(void) __attribute__((weak, alias("default_handler")));
void exti22_rtc_wkup_handler(void) __attribute__((weak, alias("default_handler")));
void flash_handler(void) __attribute__((weak, alias("default_handler")));
void rcc_handler(void) __attribute__((weak, alias("default_handler")));
void exti0_handler(void) __attribute__((weak, alias("default_handler")));
void exti1_handler(void) __attribute__((weak, alias("default_handler")));
void exti2_handler(void) __attribute__((weak, alias("default_handler")));
void exti3_handler(void) __attribute__((weak, alias("default_handler")));
void exti4_handler(void) __attribute__((weak, alias("default_handler")));
void dma1_stream0_handler(void) __attribute__((weak, alias("default_handler")));
void dma1_stream1_handler(void) __attribute__((weak, alias("default_handler")));
void dma1_stream2_handler(void) __attribute__((weak, alias("default_handler")));
void dma1_stream3_handler(void) __attribute__((weak, alias("default_handler")));
void dma1_stream4_handler(void) __attribute__((weak, alias("default_handler")));
void dma1_stream5_handler(void) __attribute__((weak, alias("default_handler")));
void dma1_stream6_handler(void) __attribute__((weak, alias("default_handler")));
void adc_handler(void) __attribute__((weak, alias("default_handler")));
void exti9_5_handler(void) __attribute__((weak, alias("default_handler")));
void tim1_brk_tim9_handler(void) __attribute__((weak, alias("default_handler")));
void tim1_up_tim10_handler(void) __attribute__((weak, alias("default_handler")));
void tim1_trg_com_tim11_handler(void) __attribute__((weak, alias("default_handler")));
void tim1_cc_handler(void) __attribute__((weak, alias("default_handler")));
void tim2_handler(void) __attribute__((weak, alias("default_handler")));
void tim3_handler(void) __attribute__((weak, alias("default_handler")));
void tim4_handler(void) __attribute__((weak, alias("default_handler")));
void i2c1_ev_handler(void) __attribute__((weak, alias("default_handler")));
void i2c1_er_handler(void) __attribute__((weak, alias("default_handler")));
void i2c2_ev_handler(void) __attribute__((weak, alias("default_handler")));
void i2c2_er_handler(void) __attribute__((weak, alias("default_handler")));
void spi1_handler(void) __attribute__((weak, alias("default_handler")));
void spi2_handler(void) __attribute__((weak, alias("default_handler")));
void usart1_handler(void) __attribute__((weak, alias("default_handler")));
void usart2_handler(void) __attribute__((weak, alias("default_handler")));
void exti15_10_handler(void) __attribute__((weak, alias("default_handler")));
void exti17_rtc_alarm_handler(void) __attribute__((weak, alias("default_handler")));
void exti18_otg_fs_wkup_handler(void) __attribute__((weak, alias("default_handler")));
void dma1_stream7_handler(void) __attribute__((weak, alias("default_handler")));
void sdio_handler(void) __attribute__((weak, alias("default_handler")));
void tim5_handler(void) __attribute__((weak, alias("default_handler")));
void spi3_handler(void) __attribute__((weak, alias("default_handler")));
void dma2_stream0_handler(void) __attribute__((weak, alias("default_handler")));
void dma2_stream1_handler(void) __attribute__((weak, alias("default_handler")));
void dma2_stream2_handler(void) __attribute__((weak, alias("default_handler")));
void dma2_stream3_handler(void) __attribute__((weak, alias("default_handler")));
void dma2_stream4_handler(void) __attribute__((weak, alias("default_handler")));
void otg_fs_handler(void) __attribute__((weak, alias("default_handler")));
void dma2_stream5_handler(void) __attribute__((weak, alias("default_handler")));
void dma2_stream6_handler(void) __attribute__((weak, alias("default_handler")));
void dma2_stream7_handler(void) __attribute__((weak, alias("default_handler")));
void usart6_handler(void) __attribute__((weak, alias("default_handler")));
void i2c3_ev_handler(void) __attribute__((weak, alias("default_handler")));
void i2c3_er_handler(void) __attribute__((weak, alias("default_handler")));
void fpu_handler(void) __attribute__((weak, alias("default_handler")));
void spi4_handler(void) __attribute__((weak, alias("default_handler")));
void spi5_handler(void) __attribute__((weak, alias("default_handler")));

uint32_t isr_vector[ISR_VECTOR_SIZE_WORDS] __attribute__((section(".isr_vector"))) = {
    STACK_POINTER_INIT_ADDRESS,
    // Cortex-M4 system exceptions
    (uint32_t)&reset_handler,                     // 0x0000 0004
    (uint32_t)&nmi_handler,                       // 0x0000 0008
    (uint32_t)&hard_fault_handler,                // 0x0000 000C
    (uint32_t)&mem_manage_handler,                // 0x0000 0010
    (uint32_t)&bus_fault_handler,                 // 0x0000 0014
    (uint32_t)&usage_fault_handler,               // 0x0000 0018
    0,                                            // 0x0000 001C
    0,                                            // 0x0000 0020
    0,                                            // 0x0000 0024
    0,                                            // 0x0000 0028
    (uint32_t)&svcall_handler,                    // 0x0000 002C
    (uint32_t)&debug_monitor_handler,             // 0x0000 0030
    0,                                            // 0x0000 0034
    (uint32_t)&pendsv_handler,                    // 0x0000 0038
    (uint32_t)&systick_handler,                   // 0x0000 003C
    /* STM32F411xC/E interrupt handlers, see chapter 10.1.3 Interrupt and exception vector table 37 of Reference manual */
    (uint32_t)&wwdg_handler,                      // 0x0000 0040
    (uint32_t)&exti16_pvd_handler,                // 0x0000 0044
    (uint32_t)&exti21_tamp_stamp_handler,         // 0x0000 0048
    (uint32_t)&exti22_rtc_wkup_handler,           // 0x0000 004C
    (uint32_t)&flash_handler,                     // 0x0000 0050
    (uint32_t)&rcc_handler,                       // 0x0000 0054
    (uint32_t)&exti0_handler,                     // 0x0000 0058
    (uint32_t)&exti1_handler,                     // 0x0000 005C
    (uint32_t)&exti2_handler,                     // 0x0000 0060
    (uint32_t)&exti3_handler,                     // 0x0000 0064
    (uint32_t)&exti4_handler,                     // 0x0000 0068
    (uint32_t)&dma1_stream0_handler,              // 0x0000 006C
    (uint32_t)&dma1_stream1_handler,              // 0x0000 0070
    (uint32_t)&dma1_stream2_handler,              // 0x0000 0074
    (uint32_t)&dma1_stream3_handler,              // 0x0000 0078
    (uint32_t)&dma1_stream4_handler,              // 0x0000 007C
    (uint32_t)&dma1_stream5_handler,              // 0x0000 0080
    (uint32_t)&dma1_stream6_handler,              // 0x0000 0084
    (uint32_t)&adc_handler,                       // 0x0000 0088
    0,                                            // 0x0000 008C
    0,                                            // 0x0000 0090
    0,                                            // 0x0000 0094
    0,                                            // 0x0000 0098
    (uint32_t)&exti9_5_handler,                   // 0x0000 009C
    (uint32_t)&tim1_brk_tim9_handler,             // 0x0000 00A0
    (uint32_t)&tim1_up_tim10_handler,             // 0x0000 00A4
    (uint32_t)&tim1_trg_com_tim11_handler,        // 0x0000 00A8
    (uint32_t)&tim1_cc_handler,                   // 0x0000 00AC
    (uint32_t)&tim2_handler,                      // 0x0000 00B0
    (uint32_t)&tim3_handler,                      // 0x0000 00B4
    (uint32_t)&tim4_handler,                      // 0x0000 00B8
    (uint32_t)&i2c1_ev_handler,                   // 0x0000 00BC
    (uint32_t)&i2c1_er_handler,                   // 0x0000 00C0
    (uint32_t)&i2c2_ev_handler,                   // 0x0000 00C4
    (uint32_t)&i2c2_er_handler,                   // 0x0000 00C8
    (uint32_t)&spi1_handler,                      // 0x0000 00CC
    (uint32_t)&spi2_handler,                      // 0x0000 00D0
    (uint32_t)&usart1_handler,                    // 0x0000 00D4
    (uint32_t)&usart2_handler,                    // 0x0000 00D8
    0,                                            // 0x0000 00DC
    (uint32_t)&exti15_10_handler,                 // 0x0000 00E0
    (uint32_t)&exti17_rtc_alarm_handler,          // 0x0000 00E4
    (uint32_t)&exti18_otg_fs_wkup_handler,        // 0x0000 00E8
    0,                                            // 0x0000 00EC
    0,                                            // 0x0000 00F0
    0,                                            // 0x0000 00F4
    0,                                            // 0x0000 00F8
    (uint32_t)&dma1_stream7_handler,              // 0x0000 00FC
    0,                                            // 0x0000 0100
    (uint32_t)&sdio_handler,                      // 0x0000 0104
    (uint32_t)&tim5_handler,                      // 0x0000 0108
    (uint32_t)&spi3_handler,                      // 0x0000 010C
    0,                                            // 0x0000 0110
    0,                                            // 0x0000 0114
    0,                                            // 0x0000 0118
    0,                                            // 0x0000 011C
    (uint32_t)&dma2_stream0_handler,              // 0x0000 0120
    (uint32_t)&dma2_stream1_handler,              // 0x0000 0124
    (uint32_t)&dma2_stream2_handler,              // 0x0000 0128
    (uint32_t)&dma2_stream3_handler,              // 0x0000 012C
    (uint32_t)&dma2_stream4_handler,              // 0x0000 0130
    0,                                            // 0x0000 0134
    0,                                            // 0x0000 0138
    0,                                            // 0x0000 013C
    0,                                            // 0x0000 0140
    0,                                            // 0x0000 0144
    0,                                            // 0x0000 0148
    (uint32_t)&otg_fs_handler,                    // 0x0000 014C
    (uint32_t)&dma2_stream5_handler,              // 0x0000 0150
    (uint32_t)&dma2_stream6_handler,              // 0x0000 0154
    (uint32_t)&dma2_stream7_handler,              // 0x0000 0158
    (uint32_t)&usart6_handler,                    // 0x0000 015C
    (uint32_t)&i2c3_ev_handler,                   // 0x0000 0160
    (uint32_t)&i2c3_er_handler,                   // 0x0000 0164
    0,                                            // 0x0000 0168
    0,                                            // 0x0000 016C
    0,                                            // 0x0000 0170
    0,                                            // 0x0000 0174
    0,                                            // 0x0000 0178
    0,                                            // 0x0000 017C
    0,                                            // 0x0000 0180
    (uint32_t)&fpu_handler,                       // 0x0000 0184
    0,                                            // 0x0000 0188
    0,                                            // 0x0000 018C
    (uint32_t)&spi4_handler,                      // 0x0000 0190
    (uint32_t)&spi5_handler                       // 0x0000 0194
};

extern uint32_t _etext, _sdata, _edata, _sbss, _ebss;
void main(void);

void reset_handler(void)
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
