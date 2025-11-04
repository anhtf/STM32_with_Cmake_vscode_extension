#include "_h743_hal_uart.h"

#define MAX_UART_INSTANCE  10
static uint8_t g_current_uart = 1;

_h743_hal_uart_t *g_uart_obj[MAX_UART_INSTANCE] = {NULL};

static void _h743_uart_send_dma(_h743_hal_uart_t * _uart)
{
    HAL_UART_Transmit_DMA(_uart->m_uart, (uint8_t*)&_uart->m_tx_buffer, sizeof(_uart->m_tx_buffer));
}

static void _h743_uart_recv_dma(_h743_hal_uart_t * _uart)
{
    HAL_UART_Receive_DMA(_uart->m_uart, (uint8_t*)&_uart->m_rx_buffer, sizeof(_uart->m_rx_buffer));
}

_h743_hal_uart_t* _h743_hal_uart_init(UART_HandleTypeDef *_uart, uint16_t _baurate, bool _is_known_lenght)
{
    if (_uart == NULL || _baurate < 0)
    {
        return NULL;
    }

    _h743_hal_uart_t *_uart_obj = (_h743_hal_uart_t *)(malloc(sizeof(_h743_hal_uart_t)));
    if (_uart_obj == NULL)
    {
        return NULL;
    }

    _uart_obj->m_baurate = _baurate;

    if (_is_known_lenght)
    {
        _uart_obj->_h743_uart_send = _h743_uart_send_dma;
        _uart_obj->_h743_uart_recv = _h743_uart_recv_dma;
    }
    else
    {
        HAL_UARTEx_ReceiveToIdle_DMA(_uart_obj->m_uart, (uint8_t*)&(_uart_obj->m_rx_buffer), sizeof(_uart_obj->m_rx_buffer));
    }

    g_uart_obj[g_current_uart] = _uart_obj;
    g_current_uart++;
    return _uart_obj;
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    for (uint8_t i = 0; i < MAX_UART_INSTANCE; i++)
    {
        HAL_UARTEx_ReceiveToIdle_DMA(g_uart_obj[i]->m_uart, (uint8_t*)&(g_uart_obj[i]->m_rx_buffer), sizeof(g_uart_obj[i]->m_rx_buffer));
    }
}