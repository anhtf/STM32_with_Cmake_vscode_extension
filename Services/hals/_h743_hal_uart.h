#pragma once

#include "string.h"
#include "stm32h7xx_hal.h"
#include "stdbool.h"
#include "stdlib.h"

#define H743_HAL_UART_MAX_TX_BUFFER_SIZE  1024
#define H743_HAL_UART_MAX_RX_BUFFER_SIZE  2056
typedef struct _h743_hal_uart
{
    UART_HandleTypeDef *m_uart;
    uint16_t m_baurate;
    uint8_t  m_tx_buffer[H743_HAL_UART_MAX_TX_BUFFER_SIZE];
    uint8_t  m_rx_buffer[H743_HAL_UART_MAX_RX_BUFFER_SIZE];
    void (*_h743_uart_send)(struct _h743_hal_uart*);
    void (*_h743_uart_recv)(struct _h743_hal_uart*);
}_h743_hal_uart_t;

_h743_hal_uart_t* _h743_hal_uart_init(UART_HandleTypeDef *_uart, uint16_t _baurate, bool _is_known_lenght);
