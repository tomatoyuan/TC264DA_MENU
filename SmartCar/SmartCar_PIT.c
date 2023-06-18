/*
 * SmartCar_PIT.c
 *
 *  Created on: 2021年1月22日
 *      Author: 孙唯
 */
#include "SmartCar_PIT.h"




void Pit_Init(CCU6N_enum ccu6n, CCU6_CHN_enum pit_ch, uint32 time)
{
    uint8 i;
    volatile Ifx_CCU6 *module;
    uint64 timer_input_clk;
    IfxCcu6_Timer g_Ccu6Timer;
    IfxCcu6_Timer_Config timerConfig;
    uint32 timer_period;

    boolean interrupt_state = disableInterrupts();

    module = IfxCcu6_getAddress((IfxCcu6_Index)ccu6n);

    IfxCcu6_Timer_initModuleConfig(&timerConfig, module);



    timer_input_clk = IfxScuCcu_getSpbFrequency();
    i = 0;
    while(i<16)
    {
        timer_period = (uint32)(timer_input_clk * time / 1000000);
        if(timer_period < 0xffff)   break;
        timer_input_clk >>= 1;
        i++;
    }
    if(16 <= i) IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, FALSE);


    switch(ccu6n)
    {
        case CCU6_0:
        {
            if(PIT_CH0 == pit_ch)
            {
                timerConfig.interrupt1.typeOfService  = CCU6_0_CH0_INT_SERVICE;
                timerConfig.interrupt1.priority       = CCU6_0_CH0_ISR_PRIORITY;
            }
            else
            {

                timerConfig.interrupt2.typeOfService  = CCU6_0_CH1_INT_SERVICE;
                timerConfig.interrupt2.priority       = CCU6_0_CH1_ISR_PRIORITY;
            }
        }break;

        case CCU6_1:
        {
            if(PIT_CH0 == pit_ch)
            {
                timerConfig.interrupt1.typeOfService  = CCU6_1_CH0_INT_SERVICE;
                timerConfig.interrupt1.priority       = CCU6_1_CH0_ISR_PRIORITY;
            }
            else
            {
                timerConfig.interrupt2.typeOfService  = CCU6_1_CH1_INT_SERVICE;
                timerConfig.interrupt2.priority       = CCU6_1_CH1_ISR_PRIORITY;
            }
        }break;
    }

    if(PIT_CH0 == pit_ch)
    {
        timerConfig.timer = IfxCcu6_TimerId_t12;
        timerConfig.interrupt1.source         = IfxCcu6_InterruptSource_t12PeriodMatch;
        timerConfig.interrupt1.serviceRequest = IfxCcu6_ServiceRequest_1;
        timerConfig.base.t12Period            = timer_period;
        timerConfig.base.t12Frequency         = (float)timer_input_clk;
        timerConfig.clock.t12countingInputMode = IfxCcu6_CountingInputMode_internal;
    }
    else
    {
        timerConfig.timer = IfxCcu6_TimerId_t13;
        timerConfig.interrupt2.source         = IfxCcu6_InterruptSource_t13PeriodMatch;
        timerConfig.interrupt2.serviceRequest = IfxCcu6_ServiceRequest_2;
        timerConfig.base.t13Period            = timer_period;
        timerConfig.base.t13Frequency         = (float)timer_input_clk;
        timerConfig.clock.t13countingInputMode = IfxCcu6_CountingInputMode_internal;
    }
    timerConfig.timer12.counterValue = 0;
    timerConfig.timer13.counterValue = 0;
    timerConfig.trigger.t13InSyncWithT12 = FALSE;

    IfxCcu6_Timer_initModule(&g_Ccu6Timer, &timerConfig);

    restoreInterrupts(interrupt_state);

    IfxCcu6_setSuspendMode(module, IfxCcu6_SuspendMode_hard);
    IfxCcu6_Timer_start(&g_Ccu6Timer);
}


void Pit_Close(CCU6N_enum ccu6n, CCU6_CHN_enum pit_ch)
{
    volatile Ifx_CCU6 *module;
    IfxCcu6_Timer g_Ccu6Timer;

    module = IfxCcu6_getAddress((IfxCcu6_Index)ccu6n);

    g_Ccu6Timer.ccu6 = module;
    g_Ccu6Timer.timer = (IfxCcu6_TimerId)(pit_ch);

    IfxCcu6_Timer_stop(&g_Ccu6Timer);
}


void Pit_Start(CCU6N_enum ccu6n, CCU6_CHN_enum pit_ch)
{
    volatile Ifx_CCU6 *module;
    IfxCcu6_Timer g_Ccu6Timer;

    module = IfxCcu6_getAddress((IfxCcu6_Index)ccu6n);

    g_Ccu6Timer.ccu6 = module;
    g_Ccu6Timer.timer = (IfxCcu6_TimerId)(pit_ch);

    IfxCcu6_Timer_start(&g_Ccu6Timer);
}


void Pit_Disable_Interrupt(CCU6N_enum ccu6n, CCU6_CHN_enum pit_ch)
{
    volatile Ifx_CCU6 *module;
    module = IfxCcu6_getAddress((IfxCcu6_Index)ccu6n);
    IfxCcu6_disableInterrupt(module, pit_ch * 2 + 7);
}


void Pit_Enable_Interrupt(CCU6N_enum ccu6n, CCU6_CHN_enum pit_ch)
{
    volatile Ifx_CCU6 *module;
    module = IfxCcu6_getAddress((IfxCcu6_Index)ccu6n);
    IfxCcu6_enableInterrupt(module, pit_ch * 2 + 7);
}



//PIT中断函数  示例
//IFX_INTERRUPT(cc60_pit_ch0_isr, 0, CCU6_0_CH0_ISR_PRIORITY)
//{
//    enableInterrupts();//开启中断嵌套
//    PIT_CLEAR_FLAG(CCU6_0, PIT_CH0);
//
//}
//
//
//IFX_INTERRUPT(cc60_pit_ch1_isr, 0, CCU6_0_CH1_ISR_PRIORITY)
//{
//    enableInterrupts();//开启中断嵌套
//    PIT_CLEAR_FLAG(CCU6_0, PIT_CH1);
//
//}
//
//IFX_INTERRUPT(cc61_pit_ch0_isr, 0, CCU6_1_CH0_ISR_PRIORITY)
//{
//    enableInterrupts();//开启中断嵌套
//    PIT_CLEAR_FLAG(CCU6_1, PIT_CH0);
//
//}
//
//IFX_INTERRUPT(cc61_pit_ch1_isr, 0, CCU6_1_CH1_ISR_PRIORITY)
//{
//    enableInterrupts();//开启中断嵌套
//    PIT_CLEAR_FLAG(CCU6_1, PIT_CH1);
//
//}
