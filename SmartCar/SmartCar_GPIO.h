/*
 * SmartCar_GPIO.h
 *
 *  Created on: 2021年1月22日
 *      Author: 孙唯
 */

#ifndef SMARTCAR_SMARTCAR_GPIO_H_
#define SMARTCAR_SMARTCAR_GPIO_H_

#include "IFXPORT.h"

//Port object
#define  P00        &MODULE_P00
#define  P02        &MODULE_P02
#define  P10        &MODULE_P10
#define  P11        &MODULE_P11
#define  P13        &MODULE_P13
#define  P14        &MODULE_P14
#define  P15        &MODULE_P15
#define  P20        &MODULE_P20
#define  P21        &MODULE_P21
#define  P22        &MODULE_P22
#define  P23        &MODULE_P23
#define  P33        &MODULE_P33


// 上下拉选项
typedef enum
{
    NO_PULL   ,     //无输入上下拉
    PULLDOWN  ,     //输入下拉
    PULLUP    ,     //输入上拉
    PUSHPULL  ,     //推挽输出
    OPENDRAIN ,     //开漏输出
}GPIOMODE_enum;


#define GET_PORT_IN_ADDR(pin)   (uint8 *)(&IfxPort_getAddress((IfxPort_Index)(pin/32))->IN + pin%32/8)

//------------------------------------------------------
//通用GPIO操作
//-------------------------------------------------------------------------------------------------------------------



//  @brief      GPIO初始化
//  @param      port        选择的端口，根据SmartCar_GPIO.h中Port object的宏定义
//  @param      pinIndex    引脚号
//  @param      pinmode     引脚配置（可设置参数由GPIOMODE_enum枚举值确定）
//  @param      dat         引脚初始化时设置的电平状态（输出时有效 ）0：低电平 1：高电平
//  @return     void
//  Sample usage:           GPIO_Init(P20,9, PUSHPULL,0);//P20_9初始化为GPIO功能、推挽输出、低电平
//  @note                   需要特别注意P20_2是不能用于输出的，仅仅只有输入的功能
//-------------------------------------------------------------------------------------------------------------------
void GPIO_Init(Ifx_P *port, uint8 pinIndex,GPIOMODE_enum pinmode,uint8 dat);
//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO输出设置
//  @param      port        选择的端口，根据SmartCar_GPIO.h中Port object的宏定义
//  @param      pinIndex    引脚号
//  @param      dat         0：低电平 1：高电平
//  @return     void
//  Sample usage:           GPIO_Set(P20,9, 1);//P20_9 输出高电平
//-------------------------------------------------------------------------------------------------------------------
void GPIO_Set(Ifx_P *port, uint8 pinIndex, uint8 dat);
//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO状态获取
//  @param      port        选择的端口，根据SmartCar_GPIO.h中Port object的宏定义
//  @param      pinIndex    引脚号
//  @return     uint8       0：低电平 1：高电平
//  Sample usage:           uint8 status = GPIO_Read(P20,9);//获取P20_9引脚电平
//-------------------------------------------------------------------------------------------------------------------
uint8 GPIO_Read(Ifx_P *port, uint8 pinIndex);
//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO 翻转
//  @param      port        选择的端口，根据SmartCar_GPIO.h中Port object的宏定义
//  @param      pinIndex    引脚号
//  @return     void
//  Sample usage:           GPIO_Toggle(P20,9);//P20_9引脚电平翻转
//-------------------------------------------------------------------------------------------------------------------
void GPIO_Toggle(Ifx_P *port, uint8 pinIndex);






#endif /* SMARTCAR_SMARTCAR_GPIO_H_ */
