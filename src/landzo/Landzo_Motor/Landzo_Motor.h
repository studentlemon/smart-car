#ifndef _LANDZOmotor_H
#define _LANDZOmotor_H

#include "include.h"

/************************
#define  ����
************************/
#define  LPTMRCOUNT    65535 
#define  TXSTPWM       80


/***************************************************/
/************************
��������
************************/
void Motor_one_PWM_init(void);
void Motor_double_PWM_init(void);
void Motor_one_test(void);
void Motor_double_test(void);

#endif
//end


