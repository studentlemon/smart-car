#include "common.h"
#include "include.h"
#include "K6x_delay.h"

#define   TX     PTB23_OUT
//#define   amend  1.25 

void Ultrasonic_Init(void)
{
    gpio_init(PTB23,GPO,0);  //初始化TX端口
    gpio_Interrupt_init(PTB21, GPI_DOWN,EITHER); //开启接收中断
    set_irq_priority((INT_PORTB+INC_IRQ),5);//设置中断优先级 1
    setIRQadrr(INT_PORTB,PORTB_IRQHandler);  //设置中断地址函数 
}

void   Ultrasonic_Delay(uint32 n)  //超声波延时us级函数
{
  vuint16 i,j;
  for(i=0;i<n;i++)
  {
    for(j=0;j<13;j++);   //   13   100M   1us
                         //   28   180M   1us
                         //   32   200M   1us
  }
}

void   Ultrasonic_Trig(void)          //超声波发送函数
{
  TX=1;                      //启动一次模块
  delay_ms(10); //延时500ms
  TX=0;
}
float  Ultrasonic_Compute(uint32 us)  //超声波计算距离函数
{
  float Distance;
  
  Distance=(us*340.0)/80000;//*amend;
  
  return Distance;
}