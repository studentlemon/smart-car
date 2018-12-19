/***********************************************************
 * 文件名       ：K6x_gpio.c
 * 说明         ：K60 看门狗驱动程序头文件
 


 *论坛          ：http://www.landzo.cn
 *库版本        ：V2.0
 *时间          ：15.5.26
************************************************************/

#ifndef __k6x_WDOG_H__
#define __k6x_WDOG_H__

#include "common.h"


void wdog_init(void);
void wdog_disable(void);
void wdog_enable(void);
void wdog_feed(void);
void wdog_enable_int(void);
void wdog_disable_int(void);

#endif 
