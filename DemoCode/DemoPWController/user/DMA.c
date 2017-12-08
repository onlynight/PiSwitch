#include "DMA.h"

void DMA1_Channel1_IRQHandler(void)
{
    if (DMA_GetITStatus(DMA1_IT_TC1) != RESET)
    {
        //自己的中断处理代码 但是记住程序不要太复杂  最好不要超过中断时间
        UART_SendInt16(USART1, get_ChannelValue(ADC_Channel_0));
        UART_SendInt16(USART1, get_ChannelValue(ADC_Channel_1));
        DMA_ClearITPendingBit(DMA1_IT_TC1);
    }
}

void Init_DMA(void)
{
    // 开启dma1通道时钟
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    // DMA1通道1配置
    DMA_DeInit(DMA1_Channel1);

    DMA_InitTypeDef DMA_InitStructure;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) & (ADC1->DR);         //外设地址 (uint32_t) & (ADC1->DR)
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ad_value;                 //内存地址
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                          //dma传输方向单向
    DMA_InitStructure.DMA_BufferSize = NUM_CHANNEL;                             //设置DMA在传输时缓冲区的长度
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;            //设置DMA的外设递增模式，一个外设
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                     //设置DMA的内存递增模式
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //外设数据字长
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;         //内存数据字长
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                             //设置DMA的传输模式：连续不断的循环模式 DMA_Mode_Circular DMA_Mode_Normal
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;                         //设置DMA的优先级别
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                                //设置DMA的2个memory中的变量互相访问
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);

    DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);
    DMA_Cmd(DMA1_Channel1, ENABLE);
}

uint16_t get_ChannelValue(uint8_t ADC_Channel)
{
    uint16_t ret = 0;
    switch (ADC_Channel)
    {
    case ADC_Channel_0:
        ret = ad_value[0];
        break;
    case ADC_Channel_1:
        ret = ad_value[1];
        break;
    default:
        break;
    }
    return ret;
}
