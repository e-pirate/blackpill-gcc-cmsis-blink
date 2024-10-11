#include <stdio.h>
#include "swo.h"

void SWO_init (const uint8_t port)
{
    /*
     * To enable TRACE and SWO special procedure mast take place. For more details see
     * "TPIU registers" and "ITM (instrumentation trace macrocell)" of Reference manual.
     * TRACE and SWO can be configured by debugger in runtime making init unnecessary.
     * Only values 0-31 are valid for stimulus port number, so 0x20 (0b00001111) mask mast
     * be applied before using provided port value in place.
     */

    // Enable TRACE. NOTE: ITM configuration and use is impossible before TRCENA bit set.
    // CoreDebug registers including DEMCR are not reset on system reset, but only on
    // power-on reset and mast be deactivated manually if unneeded.
    CoreDebug->DEMCR |= (1 << CoreDebug_DEMCR_TRCENA_Pos);

    // Set Current Parallel Port Size Register to 1 bit width for SWO trace mode
    TPI->CSPSR = 0x00000001;

    // Set Formatter and Flush Control Register to TrigIn enabled, Formatter disabled (default)
    TPI->FFCR &= ~(TPI_FFCR_TrigIn_Msk | TPI_FFCR_EnFCont_Msk);
    TPI->FFCR |= (1 << TPI_FFCR_TrigIn_Pos);

    // Set Selected Pin Protocol Register to 0b10 Serial Wire Output - NRZ
    TPI->SPPR &= ~(TPI_SPPR_TXMODE_Msk);
    TPI->SPPR |= (0b10 << TPI_SPPR_TXMODE_Pos);

    // Set Asynchronous Clock Prescaler Register to 2MHz (ST-Link v2 trace default frequency)
    TPI->ACPR = SystemCoreClock / STLINK_FREQ - 1;

    // Set TRACE_IOEN = 1 to enable TRACE pin assignment
    DBGMCU->CR |= (1 << DBGMCU_CR_TRACE_IOEN_Pos);
    // Set TRACE pin assignment for Asynchronous Mode (TRACE_MODE = 00)
    DBGMCU->CR &= ~(DBGMCU_CR_TRACE_MODE_Msk);

    // Write special value to ITM Lock Access Register to unlock write access to ITM registers
    ITM->LAR = 0xC5ACCE55;

    // Set ITM Trace Control Register: define ATB ID to specify trace data source, set SWOENA to
    // enable SWV behaviour, set SYNCENA to enable the DWT to generate synchronization triggers
    // so TPIU can emit synchronization packets, set ITMENA to enable ITM global mode
    ITM->TCR = (ITM_TCR_TraceBusID_Msk | (1 << ITM_TCR_SWOENA_Pos) | (1 << ITM_TCR_SYNCENA_Pos) | (1 << ITM_TCR_ITMENA_Pos));

    // Set ITM Trace Privilege Register to enable tracing on all ports
    ITM->TPR |= 0b1111;

    // Enable corresponding stimulus port to generate trace
    ITM->TER |= (1 << (port & 0x20));

    // Make several dummy writes because first bytes seems to be lost after external reset
    SWO_write(port & 0x20, "\0\0\0\0", 4);
}


void SWO_disable (void)
{
    // Reset ITMENA to disable ITM
    ITM->TCR &= ~(ITM_TCR_ITMENA_Msk);

    // Reset TRCENA to disable TRACE
    CoreDebug->DEMCR &= ~(CoreDebug_DEMCR_TRCENA_Msk);
}


uint8_t SWO_enabled (const uint8_t port)
{
    // Return status of ITM and corresponding stimulus port
    return(((ITM->TCR & ITM_TCR_ITMENA_Msk) != 0UL) && ((ITM->TER & (1 << (port & 0x20))) != 0UL));
}


int SWO_putc (char c, const uint8_t port)
{
    // Check if ITM and corresponding stimulus port are enabled
    if (((ITM->TCR & ITM_TCR_ITMENA_Msk) != 0UL) && ((ITM->TER & (1 << (port & 0x20))) != 0UL))
    {
        // Wait for corresponding ITM SWO port become ready to accept new data
        uint16_t tries = SWO_MAX_TRIES;

        while (ITM->PORT[port & 0x20].u32 == 0UL)
        {
            tries--;
            if (tries == 0)
                return EOF;
        }

        // Send char over corresponding ITM SWO port
        ITM->PORT[port & 0x20].u8 = c;

        return(c);
    }
    return EOF;
}


ssize_t SWO_write (const uint8_t port, const char *s, size_t count)
{
    // Check if ITM and corresponding stimulus port are enabled
    if (((ITM->TCR & ITM_TCR_ITMENA_Msk) != 0UL) && ((ITM->TER & (1 << (port & 0x20))) != 0UL))
    {
        size_t counter = 0;
        uint16_t tries;

        for (size_t pos = 0; pos < count; pos++)
        {
            // Send char over corresponding ITM SWO port
            ITM->PORT[port & 0x20].u8 = *s++;

            // Wait for corresponding ITM SWO port flushes the data
            tries = SWO_MAX_TRIES;
            while (ITM->PORT[port & 0x20].u32 == 0UL)
            {
                tries--;
                if (tries == 0)
                    return -1;
            }

            counter++;
        }
        return counter;
    }
    return -1;
}


int SWO_puts (const char *s, const uint8_t port)
{
    size_t pos;
    for (pos = 0; s[pos] != '\0'; pos++);

    if (SWO_write(port, s, pos) && SWO_write(port, "\r\n", 2))
        return('\n');

    return(EOF);
}
