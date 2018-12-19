#include "Landzo_CCD.h"

/*************************************************************************
*                             北京航空航天大学
*
*  函数名称：CCD1_init
*  功能说明：CCD初始化
*  参数说明：
*  函数返回：无
*  修改时间：2015-12-20
*  备    注：
*************************************************************************/
void LandzoCCD1_init(void)
{
  gpio_init (PTB20, GPO,HIGH);
  gpio_init (PTB22, GPO,HIGH);
  adc_init(ADC0, AD23) ;
  
}
/*************************************************************************
*                             北京航空航天大学
*
*  函数名称：CCD2_init
*  功能说明：CCD初始化
*  参数说明：
*  函数返回：无
*  修改时间：2015-12-20
*  备    注：
*************************************************************************/
void LandzoCCD2_init(void)
{
  gpio_init (PTB11, GPO,HIGH);
  gpio_init (PTB9, GPO,HIGH);
  adc_init(ADC1, DAD1) ;
  
}
/*************************************************************************
*                             北京航空航天大学
*
*  函数名称：CCD3_init
*  功能说明：CCD初始化
*  参数说明：
*  函数返回：无
*  修改时间：2015-12-20
*  备    注：
*************************************************************************/
void LandzoCCD3_init(void)
{
  gpio_init (PTB10, GPO,HIGH);
  gpio_init (PTB16, GPO,HIGH);
  adc_init(ADC0, AD14) ;
  
}

/*************************************************************************
*                           北京航空航天大学
*
*  函数名称：StartIntegration1
*  功能说明：CCD1启动程序
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
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
*                           北京航空航天大学
*
*  函数名称：ImageCapture1
*  功能说明：CCD1采样程序
*  参数说明：* ImageData   采样数组
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
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
    for(i = 0; i < 250; i++) {                    //更改250，让CCD的图像看上去比较平滑，
      SamplingDelay() ;  //200ns                  //把该值改大或者改小达到自己满意的结果。
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
*                           北京航空航天大学
*
*  函数名称：CalculateIntegrationTime
*  功能说明：计算曝光时间
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
*************************************************************************/

/* 曝光时间，单位ms */
uint8_t IntegrationTime = 10;
void CalculateIntegrationTime(uint8_t * ImageData) {

/* 128个像素点的平均AD值 */
uint8_t PixelAverageValue;
/* 128个像素点的平均电压值的10倍 */
uint8_t PixelAverageVoltage;
/* 设定目标平均电压值，实际电压的10倍 */
int16_t TargetPixelAverageVoltage = 20;
/* 设定目标平均电压值与实际值的偏差，实际电压的10倍 */
int16_t PixelAverageVoltageError = 0;
/* 设定目标平均电压值允许的偏差，实际电压的10倍 */
int16_t TargetPixelAverageVoltageAllowError = 2;

    /* 计算128个像素点的平均AD值 */
    PixelAverageValue = PixelAverage(128,ImageData);
    /* 计算128个像素点的平均电压值,实际值的10倍 */
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
*                           北京航空航天大学
*
*  函数名称：PixelAverage
*  功能说明：求数组的均值程序
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
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
*                           北京航空航天大学
*
*  函数名称：SendHex
*  功能说明：采集发数程序
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
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
*                           北京航空航天大学
*
*  函数名称：SendImageData
*  功能说明：
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
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
*                           北京航空航天大学
*
*  函数名称：SamplingDelay
*  功能说明：CCD延时程序 200ns
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
*************************************************************************/
 void SamplingDelay(void){
   volatile uint8_t i ;
   for(i=0;i<1;i++) {
    asm("nop");
    asm("nop");}
   
}

/*************************************************************************
*                           北京航空航天大学
*
*  函数名称：CCDOledPrint
*  功能说明：液晶屏显示程序
*  参数说明：
*  函数返回：无
*  修改时间：2014-9-5
*  备    注：
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
*                           北京航空航天大学
*
*  函数名称：StartIntegration2
*  功能说明：CCD1启动程序
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
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
*                           北京航空航天大学
*
*  函数名称：ImageCapture2
*  功能说明：CCD2采样程序
*  参数说明：* ImageData   采样数组
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
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
    for(i = 0; i < 250; i++) {                    //更改250，让CCD的图像看上去比较平滑，
      SamplingDelay() ;  //200ns                  //把该值改大或者改小达到自己满意的结果。
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
*                           北京航空航天大学
*
*  函数名称：StartIntegration3
*  功能说明：CCD3启动程序
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
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
*                           北京航空航天大学
*
*  函数名称：ImageCapture3
*  功能说明：CCD2采样程序
*  参数说明：* ImageData   采样数组
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
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
    for(i = 0; i < 250; i++) {                    //更改250，让CCD的图像看上去比较平滑，
      SamplingDelay() ;  //200ns                  //把该值改大或者改小达到自己满意的结果。
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