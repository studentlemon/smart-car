/***********************************************************
 * 文件名       ：delay.c
 * 说明         ：adc初始化
 


 *论坛          ：http://www.landzo.cn
 * 库版本       ：V2.0
 *时间          ：15.5.26
************************************************************/
#include "K6x_delay.h"




/**********************************************************
*                    北京航空航天大学
*
* 函数名称：delay_ms
* 功能说明：延时函数（不准确）
* 参数说明：无
* 函数返回：无
* 备注    ：
***********************************************************/
void delay_ms(uint32 time)
{
  vuint32 i,j;
  for(i=0;i<time;i++)
  {
    for(j=Gsystcl_KH/10;j>0;j--)
    {
       asm("nop");    
    }
  }
}