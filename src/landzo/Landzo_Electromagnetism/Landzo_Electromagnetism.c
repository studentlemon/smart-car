#include  "Landzo_Electromagnetism.h"


/*************************************************************************
*                           北京航空航天大学
*
*  函数名称：Electromagnetism_init
*  功能说明：电磁传感器初始化程序
*  参数说明：
*  函数返回：无
*  修改时间：2014-9-12
*  备    注：
*************************************************************************/
void Electromagnetism_init(void)
{
  adc_init(ADC0, AD15); //传感器AD初始化
  adc_init(ADC0, AD4b); //传感器AD初始化  
  adc_init(ADC0, AD14); //传感器AD初始化 
  adc_init(ADC1, DAD1); //传感器AD初始化 
  adc_init(ADC0, DAD1); //传感器AD初始化
  adc_init(ADC1, AD15); //传感器AD初始化
}

/*************************************************************************
*                           北京航空航天大学
*
*  函数名称：Electromagnetism_init
*  功能说明：电磁传感器初始化程序
*  参数说明：
*  函数返回：
*  修改时间：2014-9-12
*  备    注：
*************************************************************************/
void Electromagnetism_test(uint8_t *advalue)
{
  advalue[0] = ad_ave(ADC0, AD15, ADC_8bit, 5);   //左传感器采集信号采集5次均值滤波
  advalue[1] = ad_ave(ADC0, AD4b, ADC_8bit, 5);   //右传感器采集信号采集5次均值滤波
  advalue[2] = ad_ave(ADC0, AD14, ADC_8bit, 5);   //左传感器采集信号采集5次均值滤波
  advalue[3] = ad_ave(ADC1, DAD1, ADC_8bit, 5);   //右传感器采集信号采集5次均值滤波
  advalue[4] = ad_ave(ADC0, DAD1, ADC_8bit, 5);   //右传感器采集信号采集5次均值滤波
  advalue[5] = ad_ave(ADC1, AD16, ADC_8bit, 5);   //右传感器采集信号采集5次均值滤波
}