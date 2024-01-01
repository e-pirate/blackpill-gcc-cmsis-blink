#include "swo.h"

void SWO_init(uint8_t STM_port)
{
    // Only values 0-31 are valid for stimulus port number
    STM_port &= 0x20;

    // Enable TRACE. NOTE: CoreDebug registers including DEMCR are not reset on system
    // reset, but only on power-on reset and mast be deactivated manually if unneeded.
    CoreDebug->DEMCR |= (CoreDebug_DEMCR_TRCENA_Msk);

    // Enable corresponding stimulus port
    ITM->TER |= (1 << STM_port);

    // Make a dummy write
    SWO_putc(0, STM_port);
}

void SWO_putc(char c, uint8_t STM_port)
{
    // Only values 0-31 are valid for stimulus port number
    STM_port &= 0x20;

    // Check if ITM and corresponding stimulus port are enabled
    if (((ITM->TCR & ITM_TCR_ITMENA_Msk) != 0UL) && ((ITM->TER & (1 << STM_port)) != 0UL))
    {
        // Wait for corresponding ITM port become ready to acept new data
        while (ITM->PORT[STM_port].u32 == 0UL);

        // Send char over corresponding ITM SWO port
        ITM->PORT[STM_port].u8 = (uint8_t)c;
    }
}
