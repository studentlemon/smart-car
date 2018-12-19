/***********************************************************
 * 文件名       ：systemclock.h
 * 说明         ：系统时钟源定义
 


 * 论坛         ：http://www.landzo.cn
 * 库版本       ：V2.0
 *时间          ：15.5.26
************************************************************/

#ifndef SYSTEMCLOCK_H_
#define SYSTEMCLOCK_H_                        /**< Symbol preventing repeated inclusion */






/*!< Macro to enable all interrupts. */
#define EnableInterrupts asm(" CPSIE i");

/*!< Macro to disable all interrupts. */
#define DisableInterrupts asm(" CPSID i");
/***************
外部晶振 单位 M
***************/

#define OSCCLK    50 

/**************
system频率定义
***************/

#define  SYSTEMCLOCK   PLL180


#endif  
