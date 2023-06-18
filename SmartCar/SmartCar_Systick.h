/*
 * SmartCar_Systick.h
 *
 *  Created on: 2021年1月25日
 *      Author: 孙唯
 */

#ifndef SMARTCAR_SMARTCAR_SYSTICK_H_
#define SMARTCAR_SMARTCAR_SYSTICK_H_

#include "IfxStm.h"
#include "IFXSTM_CFG.h"
#include "common.h"

typedef enum  // 枚举STM模块号
{
    STM0,
    STM1,
}STMN_enum;


void Systick_Delay(STMN_enum stmn, uint32 time);
void Systick_Start(STMN_enum stmn);
uint32 Systick_Get(STMN_enum stmn);

//------------------------------------以下宏定义用于延时------------------------------------
#define Delay_ms(stmn, time)    Systick_Delay(stmn, time*1000000)   //设置延时时间  单位ms
#define Delay_us(stmn, time)    Systick_Delay(stmn, time*1000)      //设置延时时间  单位us
#define Delay_ns(stmn, time)    Systick_Delay(stmn, time)           //设置延时时间  单位ns

//------------------------------------以下宏定义用于获取当前时间------------------------------------
#define GetTime_ms(stmn)        Systick_Get(stmn)/100000            //获取当前计时时间  单位ms
#define GetTime_us(stmn)        Systick_Get(stmn)/100               //获取当前计时时间  单位us
#define GetTime_ns(stmn)        Systick_Get(stmn)*10                //获取当前计时时间  单位ns




#endif /* SMARTCAR_SMARTCAR_SYSTICK_H_ */
