#include "Joystick.h"

static void GPIO_Config(void);
static void TIM_Config(void);
static void ADC_Config(void);
static void DMA_Config(void);

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

void Joystick_Config(void)
{
    GPIO_Config();
    TIM_Config();
    ADC_Config();
    DMA_Config();
}

static void GPIO_Config(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_PinRemapConfig(GPIO_Remap_ADC1_ETRGREG, ENABLE);
}

static void TIM_Config(void)
{
    TIM_OCInitTypeDef TIM_OCInitStructure;

    // adc采样外部触发tim4只能用通道4 ADC_ExternalTrigConv_T4_CC4
    // Time Channel 4 pwm config
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 500;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);
}

static void ADC_Config(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);

    ADC_InitTypeDef ADC_InitStructure;

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
    ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 2, ADC_SampleTime_239Cycles5);

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

static void DMA_Config(void)
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
