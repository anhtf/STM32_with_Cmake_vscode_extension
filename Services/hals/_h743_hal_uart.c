#include "_h743_hal_uart.h"
#include <string.h>
#include <stdlib.h>

#define MAX_UART_INSTANCE 10
static uint8_t g_current_uart = 1;

_h743_hal_uart_t *g_uart_obj[MAX_UART_INSTANCE] = {NULL};

static void _h743_uart_send_dma(_h743_hal_uart_t *_uart, uint16_t length)
{
    if (_uart == NULL || _uart->m_uart == NULL || length == 0)
    {
        return;
    }
    HAL_UART_Transmit_DMA(_uart->m_uart, (uint8_t *)_uart->m_tx_buffer, length);
}

static void _h743_uart_recv_dma(_h743_hal_uart_t *_uart, uint16_t length)
{
    if (_uart == NULL || _uart->m_uart == NULL || length == 0)
    {
        return;
    }
    HAL_UART_Receive_DMA(_uart->m_uart, (uint8_t *)_uart->m_rx_buffer, length);
}

_h743_hal_uart_t *_h743_hal_uart_init(UART_HandleTypeDef *_uart, uint32_t _baurate, bool _is_known_lenght)
{
    if (_uart == NULL)
    {
        return NULL;
    }

    _h743_hal_uart_t *_uart_obj = (_h743_hal_uart_t *)(malloc(sizeof(_h743_hal_uart_t)));
    if (_uart_obj == NULL)
    {
        return NULL;
    }

    _uart_obj->m_uart = _uart;
    _uart_obj->m_baurate = _baurate;
    memset(_uart_obj->m_rx_buffer, 0, H743_HAL_UART_MAX_RX_BUFFER_SIZE);
    memset(_uart_obj->m_tx_buffer, 0, H743_HAL_UART_MAX_TX_BUFFER_SIZE);
    _uart_obj->m_busy = false;

    if (_is_known_lenght)
    {
        _uart_obj->_h743_uart_send = _h743_uart_send_dma;
        _uart_obj->_h743_uart_recv = _h743_uart_recv_dma;
    }
    else
    {
        HAL_UARTEx_ReceiveToIdle_DMA(_uart_obj->m_uart, (uint8_t *)(_uart_obj->m_rx_buffer), H743_HAL_UART_MAX_RX_BUFFER_SIZE);
    }

    g_uart_obj[g_current_uart] = _uart_obj;
    g_current_uart++;
    return _uart_obj;
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    for (uint8_t i = 0; i < MAX_UART_INSTANCE; i++)
    {
        if (g_uart_obj[i] != NULL && g_uart_obj[i]->m_uart->Instance == huart->Instance)
        {
            HAL_UARTEx_ReceiveToIdle_DMA(g_uart_obj[i]->m_uart, (uint8_t *)(g_uart_obj[i]->m_rx_buffer), H743_HAL_UART_MAX_RX_BUFFER_SIZE);
            break; 
        }
    }
}