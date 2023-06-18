/******************************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,哈工大智能车创新俱乐部
 * All rights reserved.
 *
 * @file            SmartCar_Assert
 * @company         哈工大智能车创新俱乐部
 * @author          李洋 qq:2367381108
 * @version         v1.0
 * @Software        ADS
 * @Target core     TC264
 * @date            2020-2-05
 *
 * @note：

    哈尔滨工业大学智能车创新俱乐部专用，请勿泄露
***************************************************************************************************************************/

#ifndef SMARTCAR_ASSERT_H
#define SMARTCAR_ASSERT_H


#include "Ifx_Types.h"

void assert(pchar __file, unsigned int __line, pchar __function);



#define SMARTCAR_ASSERT(expr)   ((expr) ? ((void)0) : assert(__FILE__, __LINE__, __func__))

#endif
