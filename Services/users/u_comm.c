#include "u_comm.h"
#include <stdlib.h>

uint8_t checksum(uint8_t *_buffer, uint16_t lenght)
{
    uint8_t ret = 0;
    for (int i = 0; i < lenght; i++)
    {
        ret += _buffer[i];
    }
    return (ret & 0xFF);
}

u_comm_t *u_comm_init(UART_HandleTypeDef *_uart, uint32_t _baurate, bool _known)
{
    if (_uart == NULL)
    {
        return NULL;
    }
    u_comm_t *u_comm_obj = (u_comm_t *)(malloc(sizeof(u_comm_t)));

    if (u_comm_obj == NULL)
    {
        return NULL;
    }

    u_comm_obj->_m_packet = (packet_to_pc_t *)malloc(sizeof(packet_to_pc_t));
    if (u_comm_obj->_m_packet == NULL)
    {
        free(u_comm_obj);
        return NULL;
    }
    u_comm_obj->_m_packet->m_header = 0xAA;
    u_comm_obj->_m_packet->m_count = 0;

    u_comm_obj->_m_uart = _h743_hal_uart_init(_uart, _baurate, _known);
    if (u_comm_obj->_m_uart == NULL)
    {
        free(u_comm_obj->_m_packet);
        free(u_comm_obj);
        return NULL;
    }

    return u_comm_obj;
}