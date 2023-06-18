/*
 * common.h
 *
 *  Created on: 2021年1月22日
 *      Author: 孙唯
 */

#ifndef SMARTCAR_COMMON_H_
#define SMARTCAR_COMMON_H_

#include "PLATFORM_TYPES.H"
#include <math.h>
#include "Cpu0_Main.h"
#include <string.h>
#include "IfxCpu.h"
#include "IfxScuEru.h"
#include "SysSe/Bsp/Bsp.h"
#include <stdint.h>
//声明数据类型
typedef char                int8;    //  8 bits
typedef short int           int16;   // 16 bits
typedef long  int           int32;   // 32 bits
typedef long  long          int64;   // 64 bits

typedef volatile int8       vint8;   //  8 bits
typedef volatile int16      vint16;  // 16 bits
typedef volatile int32      vint32;  // 32 bits
typedef volatile int64      vint64;  // 64 bits

typedef volatile uint8      vuint8;  //  8 bits
typedef volatile uint16     vuint16; // 16 bits
typedef volatile uint32     vuint32; // 32 bits
typedef volatile uint64     vuint64; // 64 bits

extern IfxCpu_syncEvent g_cpuSyncEvent;

#define AURIX_MCU_FREQUENCY         200*1000*1000//设置单片机频率为200M 200M(默认频率)

void get_clk(void);

#endif /* SMARTCAR_COMMON_H_ */
