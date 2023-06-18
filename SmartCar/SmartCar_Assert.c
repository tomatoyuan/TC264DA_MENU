/******************************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2021,哈工大智能车创新俱乐部
 * All rights reserved.
 *
 * @file            SmartCar_Assert
 * @company         哈工大智能车创新俱乐部
 * @author          李洋 qq:2367381108
 * @version         v1.0
 * @Software        ADS
 * @Target core     TC264
 * @date            2021-2-05
 *
 * @note：

    哈尔滨工业大学智能车创新俱乐部专用，请勿泄露
***************************************************************************************************************************/

#include <SmartCar_Assert.h>
#include "stdio.h"

void assert(pchar __file, unsigned int __line, pchar __function)
{
    //输出断言错误 所在文件目录 所在文件行 调用函数名称
#if(DEBUG_PRINTF)
    printf("ASSERTION: %s %d %s\n",__file, __line, __function);
#endif
#pragma warning 507
    while(TRUE)
    {
        //等待程序员解决 断言错误

    }
#pragma warning default
}
