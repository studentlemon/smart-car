/******************** (C) COPYRIGHT 2011 北京航空航天大学 ********************
 * 文件名       ：isr.h
 * 描述         ：工程模版实验
 *
 * 实验平台     ：landzo电子开发版
 * 库版本       ：
 * 嵌入系统     ：
 *
 


**********************************************************************************/



#ifndef __ISR_H
#define __ISR_H 1
#include  "common.h"

typedef struct  speedcount
{
    uint8   porta;
    vint16  speedcount;
    
} SPEEDCOUT;


void HardFault_Handler(void);      //发生硬件上访（程序跑飞）
void USART0_IRQHandler(void);
void USART1_IRQHandler(void);
void PIT0_IRQHandler(void);            //PIT0 定时中断服务函数
void PIT1_IRQHandler(void);            //PIT1 定时中断服务函数
void PORTA_IRQHandler(void);           //PORTA中断服务函数
void PORTB_IRQHandler(void);           //PORTB中断服务函数
void PORTC_IRQHandler(void);           //PORTC中断服务函数
void PORTD_IRQHandler(void);           //PORTD中断服务函数
void FTM0_IRQHandler(void);            //FTM0输入捕捉中断
void FTM1_IRQHandler(void);            //FTM0输入捕捉中断
void LPT_Handler(void);           //LPT脉冲中断
void DMA_CH6_Handler(void);
void DMA_CH4_Handler(void);              //DMA通道4的中断服务函数

__RAMFUN void setIRQadrr(IRQInterruptIndex IRQnum,void IRQAdrr(void) ) ;

#endif  //__ISR_H

/* End of "isr.h" */
