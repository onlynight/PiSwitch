#include "ADC.h"

void Init_ADC(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);

    //ADC1配置
    //独立工作模式
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    //扫描方式
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    //连续转换
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    //外部触发禁止
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T4_CC4; //ADC_ExternalTrigConv_T2_CC2 ADC_ExternalTrigConv_None ADC_ExternalTrigConv_T4_CC4
    //数据右对齐
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    //用于转换的通道数
    ADC_InitStructure.ADC_NbrOfChannel = NUM_CHANNEL;
    ADC_Init(ADC1, &ADC_InitStructure);

    //规则模式通道配置
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_239Cycles5);

    // ADC_ExternalTrigConvCmd(ADC1, ENABLE);
    ADC_DMACmd(ADC1, ENABLE); //使能ADC1的DMA
    ADC_Cmd(ADC1, ENABLE);    //使能ADC1

    ADC_ResetCalibration(ADC1); //使能ADC1复位校准寄存器
    //检查校准寄存器是否复位完毕
    while (ADC_GetResetCalibrationStatus(ADC1))
        ;

    //开始校准
    ADC_StartCalibration(ADC1);
    //检测是否校准完毕
    while (ADC_GetCalibrationStatus(ADC1))
        ;

    //开启ADC1的软件转换
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}
