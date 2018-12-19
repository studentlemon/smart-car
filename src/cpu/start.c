/*
 * File:	start.c
 * Purpose:	Kinetis start up routines.
 *
 * Notes:
 */
#include "common.h"
#include "start.h"
#include "k6x_wdog.h" 
#include "system.h"
#include "startup.h"
#include "K6x_gpio.h"

uint32  Gsystcl_KH ;    //系统时钟
uint32  Gbuscl_KH ;      //bus时钟
/********************************************************************/
/*!
 * \brief   Kinetis Start
 * \return  None
 *
 * This function calls all of the needed starup routines and then
 * branches to the main process.
 */
void start(void)
{
#if defined(MK64F12)
    SCB_CPACR |= (3<<20)|(3<<22); //配置M4内核寄存器CPACR，打开对FPU的访问权限
#endif
    /* 关闭看门狗 */
    wdog_disable();
    /* 复制中断向量表、初始化数据、以__ramfunc声明的子函数复制到RAM区 */
    common_startup();
    gpio_enable_port() ;
    Gsystcl_KH = system_init(SYSTEMCLOCK) ;
    Gbuscl_KH = Gsystcl_KH /(((SIM_CLKDIV1&SIM_CLKDIV1_OUTDIV2_MASK)>>SIM_CLKDIV1_OUTDIV2_SHIFT)+1) ;
    
   /* 跳进main函数 */
    main();
    /* 保证CPU不会停止执行 */
    while(1);
}

