#include "common.h"
#include "include.h"
#include "K6x_delay.h"

#define   TX     PTB23_OUT
//#define   amend  1.25 

void Ultrasonic_Init(void)
{
    gpio_init(PTB23,GPO,0);  //��ʼ��TX�˿�
    gpio_Interrupt_init(PTB21, GPI_DOWN,EITHER); //���������ж�
    set_irq_priority((INT_PORTB+INC_IRQ),5);//�����ж����ȼ� 1
    setIRQadrr(INT_PORTB,PORTB_IRQHandler);  //�����жϵ�ַ���� 
}

void   Ultrasonic_Delay(uint32 n)  //��������ʱus������
{
  vuint16 i,j;
  for(i=0;i<n;i++)
  {
    for(j=0;j<13;j++);   //   13   100M   1us
                         //   28   180M   1us
                         //   32   200M   1us
  }
}

void   Ultrasonic_Trig(void)          //���������ͺ���
{
  TX=1;                      //����һ��ģ��
  delay_ms(10); //��ʱ500ms
  TX=0;
}
float  Ultrasonic_Compute(uint32 us)  //������������뺯��
{
  float Distance;
  
  Distance=(us*340.0)/80000;//*amend;
  
  return Distance;
}