/***********************************************************
 * �ļ���       ��common.h
 * ˵��         �������ļ�
 


 *��̳          ��http://www.landzo.cn
 * ��汾       ��V1.0
 *ʱ��          ��15.5.26
************************************************************/
#ifndef _COMMON_H_
#define _COMMON_H_

/*
 * Include the generic CPU header file
 */
   
/**************
��Ƭ��ѡ��
**************/
//#define MK60DZ10
//#define MK64F12

#define __NVIC_PRIO_BITS          4

/*
 * Include the cpu specific header file
 */

#if defined(MK60DZ10)
#include "MK60DZ10.h"
#elif defined(MK60F15)
#include "MK60F15.h"
#elif defined(MK64F12)
#include "MK64F12.h"
#else
  #error NO MK6 defined
#endif




  
#if defined(__ICCARM__)
#define     __RAMFUN   __ramfunc
#else
#define     __RAMFUN
#endif
	
	//���ͱ����궨��
	typedef unsigned char	    uint8;  // 8 bits
	typedef unsigned short int	    uint16; // 16 bits
	typedef unsigned long int	    uint32; // 32 bits
	
	typedef char			     int8;   //  8 bits 
	typedef short int	       	     int16;  // 16 bits
	typedef int		       	     int32;  // 32 bits
	
	typedef volatile int8		     vint8;  //  8 bits
	typedef volatile int16	     vint16; // 16 bits
	typedef volatile int32	     vint32; // 32 bits
	
	typedef volatile uint8	     vuint8;  //  8 bits
	typedef volatile uint16	     vuint16; // 16 bits
	typedef volatile uint32            vuint32; // 32 bits
        
        typedef void(func)(void)            ;
//bit���Ͷ���
typedef union
{
    uint32  DU;
    uint16  W[2];
    uint8   B[4];
    struct
    {
        uint32 b0: 1;
        uint32 b1: 1;
        uint32 b2: 1;
        uint32 b3: 1;
        uint32 b4: 1;
        uint32 b5: 1;
        uint32 b6: 1;
        uint32 b7: 1;
        uint32 b8: 1;
        uint32 b9: 1;
        uint32 b10: 1;
        uint32 b11: 1;
        uint32 b12: 1;
        uint32 b13: 1;
        uint32 b14: 1;
        uint32 b15: 1;
        uint32 b16: 1;
        uint32 b17: 1;
        uint32 b18: 1;
        uint32 b19: 1;
        uint32 b20: 1;
        uint32 b21: 1;
        uint32 b22: 1;
        uint32 b23: 1;
        uint32 b24: 1;
        uint32 b25: 1;
        uint32 b26: 1;
        uint32 b27: 1;
        uint32 b28: 1;
        uint32 b29: 1;
        uint32 b30: 1;
        uint32 b31: 1;
    };
} Bittyp; 


#define  SysTick_IRQn   -1

#include "core_cm4.h"

#include "stdlib.h"	
#include "math.h"
#include <assert.h>

/***********************
ϵͳ���õ�ʱ�Ӷ���
***********************/
#include "systemclock.h"   
#include "gpio_cfg.h"
#include  "port.h"
#include  "pin_cfg.h"
 

#define enable_irq(irq)                 NVIC_EnableIRQ(irq)         //ʹ��IRQ
#define disable_irq(irq)                NVIC_DisableIRQ(irq)        //��ֹIRQ
#define set_irq_priority(irq,pri0)      NVIC_SetPriority(irq,pri0)  //�������ȼ�

#define TRUE                             (1)
#define FALSE                            (0)
#define INC_IRQ                         (-16)
#define HIGH                             (1)
#define LOW                              (0)

extern uint32   Gsystcl_KH ;    //ϵͳʱ��
extern uint32   Gbuscl_KH ;      //busʱ��



#endif 
