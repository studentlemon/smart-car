#ifndef _CCD_H_
#define _CCD_H_

#include "include.h"

//#define TRUE        1
#define SI1_SetVal()   PTB22_OUT = 1 ;
#define SI1_ClrVal()   PTB22_OUT = 0 ;
#define CLK1_ClrVal()  PTB20_OUT = 0 ;
#define CLK1_SetVal()  PTB20_OUT = 1 ;

#define SI2_SetVal()   PTB11_OUT = 1 ;
#define SI2_ClrVal()   PTB11_OUT = 0 ;
#define CLK2_ClrVal()  PTB9_OUT = 0 ;
#define CLK2_SetVal()  PTB9_OUT = 1 ;

#define SI3_SetVal()   PTB10_OUT = 1 ;
#define SI3_ClrVal()   PTB10_OUT = 0 ;
#define CLK3_ClrVal()  PTB16_OUT = 0 ;
#define CLK3_SetVal()  PTB16_OUT = 1 ;



void LandzoCCD1_init(void) ;   //CCD1初始化
void StartIntegration1(void) ;   //CCD1曝光释放
void ImageCapture1(unsigned char * ImageData) ;   //CCD1采集
void LandzoCCD2_init(void) ;   //CCD2初始化
void StartIntegration2(void) ;   //CCD2曝光释放
void ImageCapture2(unsigned char * ImageData) ;   //CCD2采集
void LandzoCCD3_init(void) ;   //CCD3初始化
void StartIntegration3(void) ;   //CCD3曝光释放
void ImageCapture3(unsigned char * ImageData) ;   //CCD3采集
void SendHex(unsigned char hex) ;                    //发送行头
void SamplingDelay(void) ;                           //时间延迟
uint8_t PixelAverage(uint8_t len, uint8_t *data) ;   //求平均值
void SendImageData(unsigned char * ImageData) ;      //上位机显示
void CCDOledPrint(void) ;                            //OLED显示
void CalculateIntegrationTime(uint8_t * ImageData);   //计数曝光时间

#endif /* _CCD_H_*/