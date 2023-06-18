/*
 * common.c
 *
 *  Created on: 2021年1月22日
 *      Author: 孙唯
 */

#include "common.h"

IFX_ALIGN(4) IfxCpu_syncEvent g_cpuSyncEvent = 0;//事件同步变量

App_Cpu0 g_AppCpu0; //频率信息变量
void get_clk(void)
{

    //禁用看门狗
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());


    //获取时钟频率，便于查看当前系统运行频率
    g_AppCpu0.info.pllFreq = IfxScuCcu_getPllFrequency();//锁相环
    g_AppCpu0.info.cpuFreq = IfxScuCcu_getCpuFrequency(IfxCpu_getCoreIndex());//处理器
    g_AppCpu0.info.sysFreq = IfxScuCcu_getSpbFrequency();//系统
    g_AppCpu0.info.stmFreq = IfxStm_getFrequency(&MODULE_STM0);

}
