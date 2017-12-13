#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#include "main.h"

// USART communicate protocol
#define USART_COMM_PRO_TYPE_START_UP_DEVICE 0x00
#define USART_COMM_PRO_TYPE_KEYS 0x01

// PI-Con key usart upload protocal
// filed    bits    data
// HEADER   2       0xaa 0xaa
// TYPE     1       0x00-0xff 待定义协议类型
// LENGTH   2       两位合并为数据长度(包含头尾协议类型以及长度)
// DATA     n       任意长度数据
// FOOTER   2       0xff 0xff

// 按键数据格式定义
// 待定义

#endif
