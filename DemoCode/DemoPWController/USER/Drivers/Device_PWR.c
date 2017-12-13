#include "Device_PWR.h"

void PWR_Config(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    // PWR_WakeUpPinCmd(ENABLE); //使能唤醒管脚功能
}

void Device_Enter_Stop_Mode(void)
{
    // RCC_APB2PeriphResetCmd(0X01FC, DISABLE); //复位所有IO口
    // PWR_EnterSTANDBYMode();                  //进入待命（STANDBY）模式
    PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFE);

    // when device resume, it will start here
    SystemInit();
    LED_ON;
}
