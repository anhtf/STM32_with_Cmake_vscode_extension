#include "_h743_hal_delay.h"


void _h743_hal_delay_ms(uint32_t _ms)
{
    uint32_t current_tick = HAL_GetTick();
    while (HAL_GetTick() - current_tick <= _ms)
    {
        // do nothing
    };
}