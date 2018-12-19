#ifndef _SERVOMOTOR_H_
#define _SERVOMOTOR_H_

#include "include.h"

#define MIDSTRING1  4600        //S3010�����ֵ
#define MIDSTRING2  4600        //SD5  �����ֵ

void Servo_motor_S3010_init(void);
void Servo_motor_SD5_init(void);
void Servo_motor_S3010_centre(void);
void Servo_motor_SD5_centre(void);
void Servo_motor_S3010_test(void);
void Servo_motor_SD5_test(void);


#endif