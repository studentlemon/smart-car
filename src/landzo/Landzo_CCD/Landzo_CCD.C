#include "Landzo_CCD.h"

/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�CCD1_init
*  ����˵����CCD��ʼ��
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2015-12-20
*  ��    ע��
*************************************************************************/
void LandzoCCD1_init(void)
{
  gpio_init (PTB20, GPO,HIGH);
  gpio_init (PTB22, GPO,HIGH);
  adc_init(ADC0, AD23) ;
  
}
/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�CCD2_init
*  ����˵����CCD��ʼ��
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2015-12-20
*  ��    ע��
*************************************************************************/
void LandzoCCD2_init(void)
{
  gpio_init (PTB11, GPO,HIGH);
  gpio_init (PTB9, GPO,HIGH);
  adc_init(ADC1, DAD1) ;
  
}
/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�CCD3_init
*  ����˵����CCD��ʼ��
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2015-12-20
*  ��    ע��
*************************************************************************/
void LandzoCCD3_init(void)
{
  gpio_init (PTB10, GPO,HIGH);
  gpio_init (PTB16, GPO,HIGH);
  adc_init(ADC0, AD14) ;
  
}

/*************************************************************************
*                           �������պ����ѧ
*
*  �������ƣ�StartIntegration1
*  ����˵����CCD1��������
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
*************************************************************************/
void StartIntegration1(void) {

    unsigned char i;

    SI1_SetVal();            /* SI  = 1 */
    SamplingDelay();
    CLK1_SetVal();           /* CLK = 1 */
    SamplingDelay();
    SI1_ClrVal();            /* SI  = 0 */
    SamplingDelay();
    CLK1_ClrVal();           /* CLK = 0 */

    for(i=0; i<127; i++) {
        SamplingDelay();
        SamplingDelay();
        CLK1_SetVal();       /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        CLK1_ClrVal();       /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    CLK1_SetVal();           /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    CLK1_ClrVal();           /* CLK = 0 */
}

/*************************************************************************
*                           �������պ����ѧ
*
*  �������ƣ�ImageCapture1
*  ����˵����CCD1��������
*  ����˵����* ImageData   ��������
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
*ImageData =  ad_once(ADC1, AD6a, ADC_8bit);
*************************************************************************/

void ImageCapture1(uint8_t * ImageData) {

    uint8_t i;
    extern uint8_t AtemP ;

    SI1_SetVal();            /* SI  = 1 */
    SamplingDelay();
    CLK1_SetVal();           /* CLK = 1 */
    SamplingDelay();
    SI1_ClrVal();            /* SI  = 0 */
    SamplingDelay();

    //Delay 10us for sample the first pixel
    /**/
    for(i = 0; i < 250; i++) {                    //����250����CCD��ͼ����ȥ�Ƚ�ƽ����
      SamplingDelay() ;  //200ns                  //�Ѹ�ֵ�Ĵ���߸�С�ﵽ�Լ�����Ľ����
    }

    //Sampling Pixel 1

    *ImageData =  ad_once(ADC0, AD23, ADC_8bit);
    ImageData ++ ;
    CLK1_ClrVal();           /* CLK = 0 */

    for(i=0; i<127; i++) {
        SamplingDelay();
        SamplingDelay();
        CLK1_SetVal();       /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        //Sampling Pixel 2~128

       *ImageData =  ad_once(ADC0, AD23, ADC_8bit);
        ImageData ++ ;
        CLK1_ClrVal();       /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    CLK1_SetVal();           /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    CLK1_ClrVal();           /* CLK = 0 */
}


/*************************************************************************
*                           �������պ����ѧ
*
*  �������ƣ�CalculateIntegrationTime
*  ����˵���������ع�ʱ��
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
*************************************************************************/

/* �ع�ʱ�䣬��λms */
uint8_t IntegrationTime = 10;
void CalculateIntegrationTime(uint8_t * ImageData) {

/* 128�����ص��ƽ��ADֵ */
uint8_t PixelAverageValue;
/* 128�����ص��ƽ����ѹֵ��10�� */
uint8_t PixelAverageVoltage;
/* �趨Ŀ��ƽ����ѹֵ��ʵ�ʵ�ѹ��10�� */
int16_t TargetPixelAverageVoltage = 20;
/* �趨Ŀ��ƽ����ѹֵ��ʵ��ֵ��ƫ�ʵ�ʵ�ѹ��10�� */
int16_t PixelAverageVoltageError = 0;
/* �趨Ŀ��ƽ����ѹֵ������ƫ�ʵ�ʵ�ѹ��10�� */
int16_t TargetPixelAverageVoltageAllowError = 2;

    /* ����128�����ص��ƽ��ADֵ */
    PixelAverageValue = PixelAverage(128,ImageData);
    /* ����128�����ص��ƽ����ѹֵ,ʵ��ֵ��10�� */
    PixelAverageVoltage = (uint8_t)((int16_t)PixelAverageValue * 25 / 194);

    PixelAverageVoltageError = TargetPixelAverageVoltage - PixelAverageVoltage;
    if(PixelAverageVoltageError < -TargetPixelAverageVoltageAllowError)
    {
      PixelAverageVoltageError = 0- PixelAverageVoltageError ;
      PixelAverageVoltageError /= 5;
      if(PixelAverageVoltageError > 10 )
         PixelAverageVoltageError = 10 ;
       IntegrationTime -= PixelAverageVoltageError;
    }
    if(PixelAverageVoltageError > TargetPixelAverageVoltageAllowError)
    { 
        PixelAverageVoltageError /= 5;
        if(PixelAverageVoltageError > 10 )
           PixelAverageVoltageError = 10 ;
        IntegrationTime += PixelAverageVoltageError;}
 
/*    
    uart_putchar(UART0,0XAA) ;
    uart_putchar(UART0,PixelAverageVoltage) ;
    uart_putchar(UART0,PixelAverageVoltageError) ;
    uart_putchar(UART0,IntegrationTime) ;
 */   
    if(IntegrationTime <= 1)
        IntegrationTime = 1;
    if(IntegrationTime >= 100)
        IntegrationTime = 100;
}

/*************************************************************************
*                           �������պ����ѧ
*
*  �������ƣ�PixelAverage
*  ����˵����������ľ�ֵ����
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
*************************************************************************/
uint8_t PixelAverage(uint8_t len, uint8_t *data) {
  unsigned char i;
  unsigned int sum = 0;
  for(i = 0; i<len; i++) {
    sum = sum + *data++;
  }
  return ((unsigned char)(sum/len));
}
/*************************************************************************
*                           �������պ����ѧ
*
*  �������ƣ�SendHex
*  ����˵�����ɼ���������
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
*************************************************************************/
void SendHex(unsigned char hex) {
  unsigned char temp;
  temp = hex >> 4;
  if(temp < 10) {
    uart_putchar(UART0,temp + '0');
  } else {
    uart_putchar(UART0,temp - 10 + 'A');
  }
  temp = hex & 0x0F;
  if(temp < 10) {
    uart_putchar(UART0,temp + '0');
  } else {
   uart_putchar(UART0,temp - 10 + 'A');
  }
}
/*************************************************************************
*                           �������պ����ѧ
*
*  �������ƣ�SendImageData
*  ����˵����
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
*************************************************************************/
void SendImageData(unsigned char * ImageData) {

    unsigned char i;
    unsigned char crc = 0;

    /* Send Data */
    uart_putchar(UART0,'*');
    uart_putchar(UART0,'L');
    uart_putchar(UART0,'D');

    SendHex(0);
    SendHex(0);
    SendHex(0);
    SendHex(0);

    for(i=0; i<128; i++) {
      SendHex(*ImageData++);
    }

    SendHex(crc);
    uart_putchar(UART0,'#');
}
/*************************************************************************
*                           �������պ����ѧ
*
*  �������ƣ�SamplingDelay
*  ����˵����CCD��ʱ���� 200ns
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
*************************************************************************/
 void SamplingDelay(void){
   volatile uint8_t i ;
   for(i=0;i<1;i++) {
    asm("nop");
    asm("nop");}
   
}

/*************************************************************************
*                           �������պ����ѧ
*
*  �������ƣ�CCDOledPrint
*  ����˵����Һ������ʾ����
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2014-9-5
*  ��    ע��
*************************************************************************/
 void CCDOledPrint(void){
   uint8_t PCount ,CCDFAV;
   extern uint8_t Pixel[128];
     CCDFAV = 0X60 ;
     OLED_Print_Str(5,0 , "Landzo CCD Dis");
     OLED_Print_Str(5,2 , "               ");
    for(PCount = 0;PCount<128 ;PCount++){
      OLED_Set_Pos(PCount,2);
      if(Pixel[PCount]>CCDFAV){
        OLED_WrDat(0xf);
      }else
        OLED_WrDat(0xf0);
    }
   
}



/*************************************************************************
*                           �������պ����ѧ
*
*  �������ƣ�StartIntegration2
*  ����˵����CCD1��������
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
*************************************************************************/
void StartIntegration2(void) {

    unsigned char i;

    SI2_SetVal();            /* SI  = 1 */
    SamplingDelay();
    CLK2_SetVal();           /* CLK = 1 */
    SamplingDelay();
    SI2_ClrVal();            /* SI  = 0 */
    SamplingDelay();
    CLK2_ClrVal();           /* CLK = 0 */

    for(i=0; i<127; i++) {
        SamplingDelay();
        SamplingDelay();
        CLK2_SetVal();       /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        CLK2_ClrVal();       /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    CLK2_SetVal();           /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    CLK2_ClrVal();           /* CLK = 0 */
}

/*************************************************************************
*                           �������պ����ѧ
*
*  �������ƣ�ImageCapture2
*  ����˵����CCD2��������
*  ����˵����* ImageData   ��������
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
*ImageData =  ad_once(ADC1, AD6a, ADC_8bit);
*************************************************************************/

void ImageCapture2(uint8_t * ImageData) {

    uint8_t i;
    extern uint8_t AtemP ;

    SI2_SetVal();            /* SI  = 1 */
    SamplingDelay();
    CLK2_SetVal();           /* CLK = 1 */
    SamplingDelay();
    SI2_ClrVal();            /* SI  = 0 */
    SamplingDelay();

    //Delay 10us for sample the first pixel
    /**/
    for(i = 0; i < 250; i++) {                    //����250����CCD��ͼ����ȥ�Ƚ�ƽ����
      SamplingDelay() ;  //200ns                  //�Ѹ�ֵ�Ĵ���߸�С�ﵽ�Լ�����Ľ����
    }

    //Sampling Pixel 1

    *ImageData =  ad_once(ADC1, DAD1, ADC_8bit);
    ImageData ++ ;
    CLK2_ClrVal();           /* CLK = 0 */

    for(i=0; i<127; i++) {
        SamplingDelay();
        SamplingDelay();
        CLK2_SetVal();       /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        //Sampling Pixel 2~128

       *ImageData =  ad_once(ADC1, DAD1, ADC_8bit);
        ImageData ++ ;
        CLK2_ClrVal();       /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    CLK2_SetVal();           /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    CLK2_ClrVal();           /* CLK = 0 */
}


/*************************************************************************
*                           �������պ����ѧ
*
*  �������ƣ�StartIntegration3
*  ����˵����CCD3��������
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
*************************************************************************/
void StartIntegration3(void) {

    unsigned char i;

    SI3_SetVal();            /* SI  = 1 */
    SamplingDelay();
    CLK3_SetVal();           /* CLK = 1 */
    SamplingDelay();
    SI3_ClrVal();            /* SI  = 0 */
    SamplingDelay();
    CLK3_ClrVal();           /* CLK = 0 */

    for(i=0; i<127; i++) {
        SamplingDelay();
        SamplingDelay();
        CLK3_SetVal();       /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        CLK3_ClrVal();       /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    CLK3_SetVal();           /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    CLK3_ClrVal();           /* CLK = 0 */
}

/*************************************************************************
*                           �������պ����ѧ
*
*  �������ƣ�ImageCapture3
*  ����˵����CCD2��������
*  ����˵����* ImageData   ��������
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
*ImageData =  ad_once(ADC1, AD6a, ADC_8bit);
*************************************************************************/

void ImageCapture3(uint8_t * ImageData) {

    uint8_t i;
    extern uint8_t AtemP ;

    SI3_SetVal();            /* SI  = 1 */
    SamplingDelay();
    CLK3_SetVal();           /* CLK = 1 */
    SamplingDelay();
    SI3_ClrVal();            /* SI  = 0 */
    SamplingDelay();

    //Delay 10us for sample the first pixel
    /**/
    for(i = 0; i < 250; i++) {                    //����250����CCD��ͼ����ȥ�Ƚ�ƽ����
      SamplingDelay() ;  //200ns                  //�Ѹ�ֵ�Ĵ���߸�С�ﵽ�Լ�����Ľ����
    }

    //Sampling Pixel 1

    *ImageData =  ad_once(ADC0, AD14, ADC_8bit);
    ImageData ++ ;
    CLK3_ClrVal();           /* CLK = 0 */

    for(i=0; i<127; i++) {
        SamplingDelay();
        SamplingDelay();
        CLK3_SetVal();       /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        //Sampling Pixel 2~128

       *ImageData =  ad_once(ADC0, AD14, ADC_8bit);
        ImageData ++ ;
        CLK3_ClrVal();       /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    CLK3_SetVal();           /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    CLK3_ClrVal();           /* CLK = 0 */
}