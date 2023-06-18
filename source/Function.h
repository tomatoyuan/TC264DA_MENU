/*
 * Function.h
 *
 *  Created on: 2021年10月15日
 *      Author: awellfrog
 */

#ifndef SOURCE_FUNCTION_H_
#define SOURCE_FUNCTION_H_


#include "SmartCar_GPIO.h"
#include "Menu.h"
#include "stdio.h"

/** 获取五项按键的操作
 * 返回 key 代表操作 “上” “下” “ok” “左” “右”
 * */
uint32 Get_Operation();

/** 返回 a, b 中的最小值 */
uint32 Get_Min(uint32 a, uint32 b);

/** 图像显示函数 */
void show_male();
void show_female();
void fun1();

/** 档位选择 */
void Gear_1_Para();
void Gear_2_Para();
void Gear_3_Para();


/** 参数修改 ******************************************************************************/
/** float型修改 */
void trial(float num, int8 output_format[], float *P);
/** uint32型修改 */
void tiral_uint32(uint32 num, int8 output_format[], uint32 *P);

/** float类型的修改
 * 需要加入参数限制
 * 需要加入输出格式
 * */
float Resize_Number_Float(float num, uint32 len_size, uint32 len_after_point, int8 output_format[]);

/** Uint32类型的修改
 * 需要加入参数限制
 * 需要加入输出格式
 * */
uint32 Resize_Number_Uint32(uint32 num, uint32 len_size, int8 output_format[]);
/* -------------------------------------------------------------------------------------*/



/****** Flash ****************************************************************************/
/** 写入Flash */
void FIVEMENU_writeFlash(void);

/** 读入Flash */
/** 三个档位的参数分别存在1 2 3扇区中 */
void FIVEMENU_readFlash(void);

/** 保存档位到Flash */
void Save_Gear(void);



#endif /* SOURCE_FUNCTION_H_ */
