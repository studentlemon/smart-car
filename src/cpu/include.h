/***********************************************************
 * 文件名       ：include.h
 * 说明         ：驱动模块包含文件
 


 *论坛          ：http://www.landzo.cn
 * 库版本       ：V1.0
 *时间          ：15.5.26
************************************************************/

#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include  "common.h"

/*
 * Include 用户自定义的头文件
 */

#include  "port.h"
#include  "K6x_gpio.h"
#include  "isr.h"



#include  "K6x_adc.h"       //ADC模块
#include  "K6x_can.h" 
#include  "K6x_delay.h"
#include  "K6x_dma.h"       //DMA模块
#include  "K6x_flash.h" 
#include  "K6x_FTM.h"       //FTM模块（FTM0：电机控制 / 通用 /PWM     FTM1、2：正交解码 / 通用 /PWM ）
#include  "K6x_i2c.h"
#include  "K6x_lptmr.h"     //低功耗定时器(延时)
#include  "K6x_PIT.h"       //周期中断计时器
#include  "K6x_spi.h"
#include  "K6x_uart.h"      //串口 

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
#include  "Landzo_1.44TFT.h" //1.44寸串口TFT
#include  "Landzo_NRF24L01.h"
#include  "Landzo_TFTLCD.h"//1.44寸并行TFT
#define USART_REC_LEN  			200  	//定义最大接收字节数 200

#endif  //__INCLUDE_H__
