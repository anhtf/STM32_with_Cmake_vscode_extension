#include "_h743_hal_gpio.h"

bool _h743_hal_gpio_write(GPIO_TypeDef *_gpio_port, uint16_t _gpio_pin, uint8_t _value)
{
    uint8_t ret = false;
    if (_gpio_port == NULL || _gpio_pin < 0 || _value < 0) return false;

    HAL_GPIO_WritePin(_gpio_port, _gpio_pin, _value);
    ret = _h743_hal_gpio_read(_gpio_port, _gpio_pin);
    if (ret == _value)
    return true;
    return false;
}
uint8_t _h743_hal_gpio_read(GPIO_TypeDef *_gpio_port, uint16_t _gpio_pin)
{
    return HAL_GPIO_ReadPin(_gpio_port, _gpio_pin);
}
