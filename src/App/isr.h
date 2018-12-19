/******************** (C) COPYRIGHT 2011 �������պ����ѧ ********************
 * �ļ���       ��isr.h
 * ����         ������ģ��ʵ��
 *
 * ʵ��ƽ̨     ��landzo���ӿ�����
 * ��汾       ��
 * Ƕ��ϵͳ     ��
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


void HardFault_Handler(void);      //����Ӳ���Ϸã������ܷɣ�
void USART0_IRQHandler(void);
void USART1_IRQHandler(void);
void PIT0_IRQHandler(void);            //PIT0 ��ʱ�жϷ�����
void PIT1_IRQHandler(void);            //PIT1 ��ʱ�жϷ�����
void PORTA_IRQHandler(void);           //PORTA�жϷ�����
void PORTB_IRQHandler(void);           //PORTB�жϷ�����
void PORTC_IRQHandler(void);           //PORTC�жϷ�����
void PORTD_IRQHandler(void);           //PORTD�жϷ�����
void FTM0_IRQHandler(void);            //FTM0���벶׽�ж�
void FTM1_IRQHandler(void);            //FTM0���벶׽�ж�
void LPT_Handler(void);           //LPT�����ж�
void DMA_CH6_Handler(void);
void DMA_CH4_Handler(void);              //DMAͨ��4���жϷ�����

__RAMFUN void setIRQadrr(IRQInterruptIndex IRQnum,void IRQAdrr(void) ) ;

#endif  //__ISR_H

/* End of "isr.h" */
