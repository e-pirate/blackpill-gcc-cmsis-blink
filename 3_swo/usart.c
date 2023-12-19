#include "usart.h"

void usart_init(USART_TypeDef *usart)
{
    /*
    Enable USART clock
    Enable GPIO clock (PA2 and PA3?)
    Set alternate GPIO function
    Optional: Enable RX interrupt (and NVIC controller)

    Set:
    baudrate
    hardware flow control
    start bit
    parity bit
    stop bit
    data word
    */

    /*
    Baud rate register - mantissa and fraction, basically fixed point 12Q4 format, check if oversampling is set to 8 or 16 bits
    115200 baud (bits/sec)

    Control register 1:
    - USART enable
    - Word length
    - Parity control enable (use parity bit)
    - Parity selection (odd/even)

    CR2:
    - STOP bits
    - CPOL (clock polarity)
    - CPHA (clock phase)
    - 
    */

    /* Enable USART2 clock */
    RCC->APB1ENR |= (1 << RCC_APB1ENR_USART2EN_Pos);
    __DSB();

    /* Enable GPIOA clock*/
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN_Msk;
    __DSB();

    /* Set PA2 and PA3 to alternate function */
    GPIOA->MODER &= ~(GPIO_MODER_MODE2_Msk | GPIO_MODER_MODE3_Msk);
    GPIOA->MODER |= ((0b10 << GPIO_MODER_MODE2_Pos) | (0b10 << GPIO_MODER_MODE3_Pos));

    /* USART2 is AF7 (found in datasheet) */
    GPIOA->AFR[0] &= ~(GPIO_AFRL_AFRL2 | GPIO_AFRL_AFRL3);
    GPIOA->AFR[0] |= (7 << GPIO_AFRL_AFSEL2_Pos) | (7 << GPIO_AFRL_AFSEL3_Pos);

    /* Configure and enable USART2 */
    USART2->BRR = 416; // 115200 baud @ 48 MHz APB1 clock and 16x oversampling
    USART2->CR1 |= USART_CR1_UE | USART_CR1_TE; // USART enable and transmitter enable

    // Dummy write, because the first byte seems to always be dropped
    usart_write(USART2, 0);
}

void usart_write(USART_TypeDef *usart, char c)
{
    usart->DR = c;
    while (!(usart->SR & USART_SR_TC));
}
