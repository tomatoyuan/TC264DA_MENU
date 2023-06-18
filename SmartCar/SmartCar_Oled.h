/******************************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2021,哈工大智能车创新俱乐部
 * All rights reserved.
 *
 * @file            SmartCar_Encoder
 * @company         哈工大智能车创新俱乐部
 * @author          李洋 qq:2367381108
 * @version         v1.0
 * @Software        ADS
 * @Target core     TC264
 * @date            2021-2-05
 *
 * @note：oled显示
 *      RES:P15_1    DC:P15_0   其他CS/MOSI/MISO/CLK根据具体选用QSPI模组选择

    哈尔滨工业大学智能车创新俱乐部专用，请勿泄露
***************************************************************************************************************************/



#ifndef SMARTCAR_OLED_H
#define SMARTCAR_OLED_H

#include <Qspi/SpiMaster/IfxQspi_SpiMaster.h>
#include <Port/Io/IfxPort_Io.h>
#include <stdio.h>
#include "stdarg.h"
#include "SmartCar_FONT.h"

#define IFX_INTPRIO_QSPI0_TX  1 // DMA channel 1
#define IFX_INTPRIO_QSPI0_RX  2 // DMA channel 2
#define IFX_INTPRIO_QSPI0_ER  0x30
#define IFX_INTPRIO_DMA_CH1  28
#define IFX_INTPRIO_DMA_CH2  29

//与oled初始化有关
#define OLED_QSPI_MODULE    MODULE_QSPI2//使用的QSPI模组 分别为MODULE_QSPI0,MODULE_QSPI1,MODULE_QSPI2,MODULE_QSPI3
#define OLED_BAUDRATE       10000000.0f//波特率
#define OLED_CLK_PIN        IfxQspi2_SCLK_P15_3_OUT//CLK,D0
#define OLED_MTSR_PIN       IfxQspi2_MTSR_P15_5_OUT//MOSI,D1
#define OLED_MRST_PIN       IfxQspi2_MRSTA_P15_4_IN//MISO
#define OLED_CS_PIN         IfxQspi2_SLSO0_P15_2_OUT//CS
#define OLED_RES_PIN_MODULE MODULE_P15//RES
#define OLED_RES_PIN_NUM    1//RES
#define OLED_DC_PIN_MODULE  MODULE_P15//DC
#define OLED_DC_PIN_NUM     0//DC


extern IfxQspi_SpiMaster_Channel oled_spiChannel;
extern IfxQspi_SpiMaster oled_spi;

void SmartCar_Oled_Config_Init();
void SmartCar_Oled_Init(void);

/*
 * brief 写指令到oeld
 * */
void OLED_WrtCmd(uint8 cmd);

/*
 * brief 写数据到oeld
 * */
void OLED_WrtData(uint8 data);

void SmartCar_OLED_Fill(uint8 bmp_data);
void OLED_Set_Pos(uint8 x,uint8 y);

/*
 * 设置一列8个oeld点状态
 * para x x坐标
 * para y y坐标
 * para data 对应八个点的亮灭情况
 * sample OLED_PutPixel(0, 0, 0x20);
 * */
void OLED_PutPixel(uint8 x, uint8 y, uint8 data);
void OLED_ClrPixel(uint8 x,uint8 y);

/*
 * oled打印6x8字符
 * para x x坐标
 * para y y坐标
 * para ch 字符串起始地址
 * sample SmartCar_OLED_P6x8Str(0, 0, str);
 * */
void SmartCar_OLED_P6x8Str(uint8 x, uint8 y, const char* ch);

/*
 * oled打印6x8字符(反色显示)
 * para x x坐标
 * para y y坐标
 * para ch 字符串起始地址
 * sample SmartCar_OLED_P6x8Reverse(0, 0, str);
 * */
void SmartCar_OLED_P6x8Reverse(uint8 x, uint8 y,const char* ch);

/*
 * oled打印8x16字符
 * para x x坐标
 * para y y坐标
 * para ch 字符串起始地址
 * sample SmartCar_OLED_P8x16Str(0, 0, str);
 * */
void SmartCar_OLED_P8x16Str(uint8 x, uint8 y, const char* ch);

/*
 * oled打印6x8字符
 * para x x坐标
 * para y y坐标
 * sample SmartCar_OLED_Printf6x8(0, 0, "%d", 4);
 * */
void SmartCar_OLED_Printf6x8(uint8 x, uint8 y, const char* ftm, ...);

/*
 * oled打印6x8字符
 * para x x坐标
 * para y y坐标
 * sample SmartCar_OLED_Printf8x16(0, 0, "%d", 4);
 * */
void SmartCar_OLED_Printf8x16(uint8 x,uint8 y, const char* ftm, ...);

/*
 * sample SmartCar_Buffer_Upload(&DISP_image_100thAnniversary[0][0]);
*/
void SmartCar_Buffer_Upload(const uint8 *buffer);


/**********************************************************************************************************************
*  brief      图像缩半
*  para      src         图像高度
*  para      dst        图像宽度
*  para      row           图像地址（数组）
*  para      col        二值化阀值
*  return     void
*  Sample usage:            image_size_half_forOLED((uint8_t *)image_Buffer_0,(uint8_t *)buff,ROW,COL);
**********************************************************************************************************************/
void image_size_half_forOLED(uint8 *src, uint8 *dst, const uint16 row, const uint16 col);

/**********************************************************************************************************************
*  brief      OLED显示图像
*  para      high         图像高度
*  para      width        图像宽度
*  para      *p           图像地址（数组）
*  para      value        二值化阀值
*  return     void
*  Sample usage:    dis_bmp(high,width,100)
**********************************************************************************************************************/
void dis_bmp(uint16 high, uint16 width, uint8 *p, uint8 value);
/**********************************************************************************************************************
*  brief      OLED显示IMG
*  para      high         图像高度
*  para      width        图像宽度
*  para      *p           图像地址（数组）
*  return     void
**********************************************************************************************************************/
void dis_IMG(uint16 high, uint16 width, uint8 *p);
#endif
