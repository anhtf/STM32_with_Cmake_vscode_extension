#pragma once
#include "_h743_hals.h"

#pragma pack(1)
typedef struct
{
    uint8_t m_header;
    uint32_t m_count;
    uint16_t m_adc_raw;
    uint8_t m_cs;
} packet_to_pc_t;

typedef struct u_comm
{
    _h743_hal_uart_t *_m_uart;
    packet_to_pc_t *_m_packet;
} u_comm_t;

#pragma pack()

u_comm_t *u_comm_init(UART_HandleTypeDef *_uart, uint32_t _baurate, bool _known);
uint8_t checksum(uint8_t *_buffer, uint16_t lenght);