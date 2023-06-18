/*
 * SmartCar_Flash.h
 *
 *  Created on: 2021年2月3日
 *      Author: 孙唯
 */

#ifndef SMARTCAR_SMARTCAR_FLASH_H_
#define SMARTCAR_SMARTCAR_FLASH_H_

#include "common.h"
#include "IfxFlash_cfg.h"
#include "IfxScuWdt.h"
#include "IfxFlash.h"


#define EEPROM_BASE_ADDR             IFXFLASH_DFLASH_START
#define EEPROM_SIZE                  IFXFLASH_DFLASH_SIZE                   //一共有96KB
#define EEPROM_SECTOR_SIZE           (EEPROM_SIZE / IFXFLASH_DFLASH_NUM_LOG_SECTORS)
#define EEPROM_SECTOR_NUM            (IFXFLASH_DFLASH_NUM_LOG_SECTORS)      //一共有12个扇区

#define EEPROM_PAGE_SIZE             IFXFLASH_DFLASH_PAGE_LENGTH
#define EEPROM_SECTOR_PAGE_NUM       (EEPROM_SECTOR_SIZE/EEPROM_PAGE_SIZE)  //每个扇区有1024页


//-------------------------------------------------------------------------------------------------------------------
//  @brief      使用宏定义对flash进行数据读取
//  @param      sector_num      需要写入的扇区编号
//  @param      page_num        需要读取的页
//  @param      type            读取的数据类型uint32 uint16 uint8 int32 float等
//  @return                     返回给定地址的数据
//  @since      v1.0
//  Sample usage:               Page_Read(0,0,uint32);//读取0号扇区  第0页数据 类型为uint32
//-------------------------------------------------------------------------------------------------------------------
#define     Page_Read(sector_num,page_num,type)    (*(type *)((uint32)((EEPROM_BASE_ADDR + (sector_num)*EEPROM_SECTOR_SIZE) + ((page_num)*8))))

#define     float_conversion_uint32(float_data)     (*(uint32 *)&float_data)




//-------------------------------------------------------------------------------------------------------------------
//  @brief      擦除扇区
//  @param      sector_num      需要写入的扇区编号   参数范围0-11
//  @return     void
//  @since      v1.0
//  Sample usage:               Sector_Erase(0);
//-------------------------------------------------------------------------------------------------------------------
void Sector_Erase(uint32 sector_num);
//-------------------------------------------------------------------------------------------------------------------
//  @brief      编程一页（写）
//  @param      sector_num      需要写入的扇区编号   参数范围0-11
//  @param      page_num        需要写入的页编号     参数范围0-1023
//  @param      buf             需要写入的数据地址   传入的数组类型必须为uint32
//  @return     void
//  @since      v1.0
//  Sample usage:               Page_Program(0,0, &buf);
//-------------------------------------------------------------------------------------------------------------------
void Page_Program(uint32 sector_num, uint32 page_num, uint32 *buf);
//-------------------------------------------------------------------------------------------------------------------
//  @brief      编程一扇区（写）   将buf起1024个数据写入扇区
//  @param      sector_num      需要写入的扇区编号   参数范围0-11
//  @param      buf             需要写入的数据地址   传入的数组类型必须为uint32
//  @return     void
//  @since      v1.0
//  Sample usage:               Sector_Program(0,0, &buf[0]);
//-------------------------------------------------------------------------------------------------------------------
void Sector_Program(uint32 sector_num, uint32* buf);


#endif /* SMARTCAR_SMARTCAR_FLASH_H_ */
