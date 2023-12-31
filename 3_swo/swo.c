#include "swo.h"

//#define DEMCR *((volatile uint32_t*) 0xE000EDFCu)

void SWO_init(uint8_t STM_port)
{
    // Only values 0-31 are valid for stimulus port number
    STM_port &= 0x20;

    // Enable TRACE. NOTE: CoreDebug registers including DEMCR are not reset on system
    // reset, but only on power-on reset and mast be deactivated manually if unneeded.
    CoreDebug->DEMCR |= (CoreDebug_DEMCR_TRCENA_Msk);
//    DEMCR |= (1 << 24);

    // Enable corresponding stimulus port
    ITM->TER |= (1 << STM_port);
}

void SWO_putc(char c, uint8_t STM_port)
{
    // Only values 0-31 are valid for stimulus port number
    STM_port &= 0x20;
    
    if (((ITM->TCR & ITM_TCR_ITMENA_Msk) != 0UL) && ((ITM->TER & (1 << STM_port)) != 0UL))
    {
        while (ITM->PORT[STM_port].u32 == 0UL);

        ITM->PORT[STM_port].u8 = (uint8_t)c;
    }
}
