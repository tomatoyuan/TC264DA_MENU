/*
 * SmartCar_PIT.h
 *
 *  Created on: 2021年1月22日
 *      Author: 孙唯
 */

#ifndef SMARTCAR_SMARTCAR_PIT_H_
#define SMARTCAR_SMARTCAR_PIT_H_

#include "common.h"
#include "IfxCcu6_Timer.h"
#include "SysSe/Bsp/Bsp.h"
#include "SmartCar_GPIO.h"
//模块号
typedef enum
{
    CCU6_0,
    CCU6_1,
}CCU6N_enum;

//通道号
typedef enum
{
    PIT_CH0,
    PIT_CH1,
}CCU6_CHN_enum;

//------------PIT中断参数相关定义------------
#define CCU6_0_CH0_INT_SERVICE  IfxSrc_Tos_cpu0 //定义CCU6_0 PIT通道0中断服务类型，即中断是由谁响应处理 0:CPU0 1:CPU1 3:DMA  不可设置为其他值
#define CCU6_0_CH0_ISR_PRIORITY 210  //定义CCU6_0 PIT通道0中断优先级 优先级范围1-255 越大优先级越高 与平时使用的单片机不一样

#define CCU6_0_CH1_INT_SERVICE  IfxSrc_Tos_cpu0
#define CCU6_0_CH1_ISR_PRIORITY 200

#define CCU6_1_CH0_INT_SERVICE  IfxSrc_Tos_cpu0
#define CCU6_1_CH0_ISR_PRIORITY 32

#define CCU6_1_CH1_INT_SERVICE  IfxSrc_Tos_cpu0
#define CCU6_1_CH1_ISR_PRIORITY 33


#define PIT_CLEAR_FLAG(ccu6n,pit_ch) IfxCcu6_clearInterruptStatusFlag(IfxCcu6_getAddress((IfxCcu6_Index)ccu6n), (IfxCcu6_InterruptSource)(7+(pit_ch*2)))

//-------------------------------------------------------------------------------------------------------------------
//  @brief      pit初始化
//  @param      ccu6n           选择CCU6模块(CCU6_0、CCU6_1)
//  @param      pit_ch          选择通道(PIT_CH0、PIT_CH1)
//  @param      time            周期时间
//  @return     void
//  @note                       请使用.h文件中 带时间单位的宏定义函数
//  Sample usage:               Pit_Init_ms(CCU6_0, PIT_CH0, 5000);    //设置周期中断5000ms
//                              Pit_Init_us(CCU6_0, PIT_CH0, 5000);    //设置周期中断5000us
//-------------------------------------------------------------------------------------------------------------------
void Pit_Init(CCU6N_enum ccu6n, CCU6_CHN_enum pit_ch, uint32 time);

//------------------------------------PIT中断时间单位可选------------------------------------
#define Pit_Init_ms(ccu6n, pit_ch, time)  Pit_Init(ccu6n, pit_ch, time*1000)   //(单位为 毫秒)
#define Pit_Init_us(ccu6n, pit_ch, time)  Pit_Init(ccu6n, pit_ch, time)        //(单位为 微秒)



//-------------------------------------------------------------------------------------------------------------------
//  @brief      pit关闭
//  @param      ccu6n           选择CCU6模块(CCU6_0、CCU6_1)
//  @param      pit_ch          选择通道(PIT_CH0、PIT_CH1)
//  @return     void
//  @note
//  Sample usage:               Pit_Close(CCU6_0, PIT_CH0); //关闭CCU60 通道0的计时器
//-------------------------------------------------------------------------------------------------------------------
void Pit_Close(CCU6N_enum ccu6n, CCU6_CHN_enum pit_ch);
//-------------------------------------------------------------------------------------------------------------------
//  @brief      pit开始
//  @param      ccu6n           选择CCU6模块(CCU6_0、CCU6_1)
//  @param      pit_ch          选择通道(PIT_CH0、PIT_CH1)
//  @return     void
//  @note
//  Sample usage:               Pit_Start(CCU6_0, PIT_CH0); //打开CCU60 通道0的计时器
//-------------------------------------------------------------------------------------------------------------------
void Pit_Start(CCU6N_enum ccu6n, CCU6_CHN_enum pit_ch);
//-------------------------------------------------------------------------------------------------------------------
//  @brief      禁止pit中断
//  @param      ccu6n           选择CCU6模块(CCU6_0、CCU6_1)
//  @param      pit_ch          选择通道(PIT_CH0、PIT_CH1)
//  @return     void
//  @note
//  Sample usage:               Pit_Disable_Interrupt(CCU6_0, PIT_CH0); //禁止CCU60 通道0的中断
//-------------------------------------------------------------------------------------------------------------------
void Pit_Disable_Interrupt(CCU6N_enum ccu6n, CCU6_CHN_enum pit_ch);
//-------------------------------------------------------------------------------------------------------------------
//  @brief      使能pit中断
//  @param      ccu6n           选择CCU6模块(CCU6_0、CCU6_1)
//  @param      pit_ch          选择通道(PIT_CH0、PIT_CH1)
//  @return     void
//  @note
//  Sample usage:               Pit_Enable_Interrupt(CCU6_0, PIT_CH0);  //开启CCU60 通道0的中断
//-------------------------------------------------------------------------------------------------------------------
void Pit_Enable_Interrupt(CCU6N_enum ccu6n, CCU6_CHN_enum pit_ch);







#endif /* SMARTCAR_SMARTCAR_PIT_H_ */
