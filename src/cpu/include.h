/***********************************************************
 * �ļ���       ��include.h
 * ˵��         ������ģ������ļ�
 


 *��̳          ��http://www.landzo.cn
 * ��汾       ��V1.0
 *ʱ��          ��15.5.26
************************************************************/

#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include  "common.h"

/*
 * Include �û��Զ����ͷ�ļ�
 */

#include  "port.h"
#include  "K6x_gpio.h"
#include  "isr.h"



#include  "K6x_adc.h"       //ADCģ��
#include  "K6x_can.h" 
#include  "K6x_delay.h"
#include  "K6x_dma.h"       //DMAģ��
#include  "K6x_flash.h" 
#include  "K6x_FTM.h"       //FTMģ�飨FTM0��������� / ͨ�� /PWM     FTM1��2���������� / ͨ�� /PWM ��
#include  "K6x_i2c.h"
#include  "K6x_lptmr.h"     //�͹��Ķ�ʱ��(��ʱ)
#include  "K6x_PIT.h"       //�����жϼ�ʱ��
#include  "K6x_spi.h"
#include  "K6x_uart.h"      //���� 

#include  "landzo_sd.h"  
#include  "Landzo_CCD.h"
#include  "Landzo_Electromagnetism.h"
#include  "Landzo_GyroAccelerate.h"
#include  "Landzo_Key.h"
#include  "Landzo_MeasureSpeed.h"
#include  "Landzo_motor.h"
#include  "Landzo_OLED.h"
#include  "Landzo_Predator.h"
#include  "Landzo_servomotor.h"
#include  "Landzo_Ultrasonic.h"
#include  "Landzo_1.44TFT.h" //1.44�紮��TFT
#include  "Landzo_NRF24L01.h"
#include  "Landzo_TFTLCD.h"//1.44�粢��TFT
#define USART_REC_LEN  			200  	//�����������ֽ��� 200

#endif  //__INCLUDE_H__
