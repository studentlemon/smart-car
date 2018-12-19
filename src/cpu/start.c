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

uint32  Gsystcl_KH ;    //ϵͳʱ��
uint32  Gbuscl_KH ;      //busʱ��
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
    SCB_CPACR |= (3<<20)|(3<<22); //����M4�ں˼Ĵ���CPACR���򿪶�FPU�ķ���Ȩ��
#endif
    /* �رտ��Ź� */
    wdog_disable();
    /* �����ж���������ʼ�����ݡ���__ramfunc�������Ӻ������Ƶ�RAM�� */
    common_startup();
    gpio_enable_port() ;
    Gsystcl_KH = system_init(SYSTEMCLOCK) ;
    Gbuscl_KH = Gsystcl_KH /(((SIM_CLKDIV1&SIM_CLKDIV1_OUTDIV2_MASK)>>SIM_CLKDIV1_OUTDIV2_SHIFT)+1) ;
    
   /* ����main���� */
    main();
    /* ��֤CPU����ִֹͣ�� */
    while(1);
}

