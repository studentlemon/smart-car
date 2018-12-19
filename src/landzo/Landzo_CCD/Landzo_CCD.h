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



void LandzoCCD1_init(void) ;   //CCD1��ʼ��
void StartIntegration1(void) ;   //CCD1�ع��ͷ�
void ImageCapture1(unsigned char * ImageData) ;   //CCD1�ɼ�
void LandzoCCD2_init(void) ;   //CCD2��ʼ��
void StartIntegration2(void) ;   //CCD2�ع��ͷ�
void ImageCapture2(unsigned char * ImageData) ;   //CCD2�ɼ�
void LandzoCCD3_init(void) ;   //CCD3��ʼ��
void StartIntegration3(void) ;   //CCD3�ع��ͷ�
void ImageCapture3(unsigned char * ImageData) ;   //CCD3�ɼ�
void SendHex(unsigned char hex) ;                    //������ͷ
void SamplingDelay(void) ;                           //ʱ���ӳ�
uint8_t PixelAverage(uint8_t len, uint8_t *data) ;   //��ƽ��ֵ
void SendImageData(unsigned char * ImageData) ;      //��λ����ʾ
void CCDOledPrint(void) ;                            //OLED��ʾ
void CalculateIntegrationTime(uint8_t * ImageData);   //�����ع�ʱ��

#endif /* _CCD_H_*/