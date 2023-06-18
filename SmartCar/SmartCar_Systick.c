/*
 * SmartCar_Systick.c
 *
 *  Created on: 2021年1月25日
 *      Author: 孙唯
 */
#include "SmartCar_Systick.h"

static uint32 systick_count[2];

//-------------------------------------------------------------------------------------------------------------------
//  @brief      systick延时函数
//  @param      time            需要延时的时间
//  @return     void
//  Sample usage:               无需调用，请使用h文件中的宏定义
//-------------------------------------------------------------------------------------------------------------------
void Systick_Delay(STMN_enum stmn, uint32 time)
{
    uint32 stm_clk;
    stm_clk = IfxStm_getFrequency(IfxStm_getAddress((IfxStm_Index)stmn));
    IfxStm_waitTicks(IfxStm_getAddress((IfxStm_Index)stmn), (uint32)((uint64)stm_clk*time/1000000000));
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      systick定时器启动
//  @param      stmn            选择使用的模块
//  @return     void
//  Sample usage:               Systick_Start(STM0);//记录下当前的时间
//-------------------------------------------------------------------------------------------------------------------
void Systick_Start(STMN_enum stmn)
{

    systick_count[stmn] = IfxStm_getLower(IfxStm_getAddress((IfxStm_Index)stmn));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief     获得当前System tick timer的值
//  @param     stmn             选择使用的模块
//  @return    uint32           返回从开始到现在的时间(单位10ns)
//  Sample usage:               uint32 tim = Systick_Get(STM0);
//-------------------------------------------------------------------------------------------------------------------
uint32 Systick_Get(STMN_enum stmn)
{
    uint32 time;
    uint32 stm_clk;

    stm_clk = IfxStm_getFrequency(IfxStm_getAddress((IfxStm_Index)stmn));

    time = IfxStm_getLower(IfxStm_getAddress((IfxStm_Index)stmn)) - systick_count[stmn];
    time = (uint32)((uint64)time * 100000000 / stm_clk);
    return time;
}


