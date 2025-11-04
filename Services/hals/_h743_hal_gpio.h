#pragma once

#include "stm32h7xx_hal.h"
#include "stdbool.h"

bool _h743_hal_gpio_write(GPIO_TypeDef *_gpio_port, uint16_t _gpio_pin, uint8_t _value);
uint8_t _h743_hal_gpio_read(GPIO_TypeDef *_gpio_port, uint16_t _gpio_pin);