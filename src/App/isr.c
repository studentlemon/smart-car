/***********************************************************
 * �ļ���       ��isr.c
 * ˵��         ���жϹ���ģ��
 


 *��̳          ��http://www.landzo.cn
 * ��汾       ��V1.0
 *ʱ��          ��15.5.26
************************************************************/

//#include "isr.h"
#include  "include.h"
#include  "Landzo_Calculation.h"
extern uint8 TIME0flag_5ms   ;
extern uint8 TIME0flag_10ms  ;
extern uint8 TIME0flag_20ms  ;
extern uint8 TIME0flag_50ms  ;
extern uint8 TIME0flag_80ms  ;
extern uint8 TIME0flag_100ms ;
extern uint8 TIME1flag_20ms  ;
extern uint8 TIME0flag_1s;
uint16  TimeCount = 0 ;
/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�setIRQadrr
*  ����˵���������жϵ�ַ����
*  ����˵����IRQInterruptIndex �ж���������оƬ��.H�ļ�������K60 ��"MK60DZ10.h"
*            void IRQAdrr(void)  �жϺ���
*  �������أ���
*  �޸�ʱ�䣺2015-5-15    �Ѳ���
*  ��    ע��
*************************************************************************/

__RAMFUN void setIRQadrr(IRQInterruptIndex IRQnum,void IRQAdrr(void) ){
  extern uint32 __VECTOR_TABLE[];
  extern uint32 __VECTOR_RAM[];
  vuint32  *Vector_TABl ,Vector_TAB;
  vuint16 temp0 ,temp1;
  vuint32 buf[512];
  Vector_TAB = SCB_VTOR ;
  Vector_TABl = (vuint32  *)Vector_TAB ;
  /**************
  �ж���������ram���򣬿��Խ���ֱ�Ӳ���
  **************/
  if(Vector_TAB == (uint32)&__VECTOR_RAM){   
    Vector_TABl[IRQnum] = (uint32)(IRQAdrr) ;
   }
  else{
    /*****************************
    ��������flash��
    *****************************/
    for(temp0 = 0 ; temp0 < 512 ; temp0++){
      buf[temp0] = Vector_TABl[temp0];
    }
    buf[IRQnum]  = (uint32)(IRQAdrr) ;  
    hw_flash_init() ;
    flash_erase_sector(0) ;
    flash_write(0,0,2048,(uint8 *)buf) ;
  }
  }



/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�USART0_IRQHandler
*  ����˵��������0 �ж� ���� ������
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2014-8-28    �Ѳ���
*  ��    ע��
*************************************************************************/
uint8 USART_RX_BUF[USART_REC_LEN];//���ջ���,���USART_REC_LEN���ֽ�.
uint16 USART_RX_STA=0;    //����״̬���
uint8 UART_receive = 0;   //1 ������ɱ��

void USART0_IRQHandler(void)
{
  uint8 Res;
  DisableInterrupts; //�����ж�
  if(uart_query(UART0) != 0)  //�����ж�(���յ������ݱ�����0x0a��β)
   {
      Res = uart_getchar (UART0);//(USART1->DR);//��ȡ���յ�������
      USART_RX_BUF[USART_RX_STA]=Res;
      USART_RX_STA++;
      if(Res == 0x0a) //���յ�0x0a��β
      {
        UART_receive = 1; //�������
      }
   }
  EnableInterrupts;		  //�����ж�
}
/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�USART1_IRQHandler
*  ����˵��������1 �ж� ���� ������
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-14    �Ѳ���
*  ��    ע��
*************************************************************************/


void USART1_IRQHandler(void)
{
    uint8 ch;

    DisableInterrupts;		    //�����ж�

    //����һ���ֽ����ݲ��ط�
    ch = uart_getchar (UART1);      //���յ�һ������
    uart_sendStr  (UART1, "\n�㷢�͵�����Ϊ��");
    uart_putchar (UART1, ch);       //�ͷ��ͳ�ȥ

    EnableInterrupts;		    //�����ж�
}
/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�PIT1_IRQHandler
*  ����˵����PIT1��ʱ�жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-9-18    �Ѳ���
*  ��    ע��
*************************************************************************/

void PIT1_IRQHandler(void)
{
  PIT_Flag_Clear(PIT1);       //���жϱ�־λ
   
}

/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�PIT0_IRQHandler
*  ����˵����PIT0 ��ʱ�жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-18    �Ѳ���
*  ��    ע��
*************************************************************************/
uint16 ultrturn ;


void PIT0_IRQHandler(void)
{
  PIT_Flag_Clear(PIT0);       //���жϱ�־λ
  ultrturn ++ ;   //������
  
  TimeCount ++ ;
  
  if(TimeCount%1 == 0 )
  {
    TIME0flag_5ms = 1;
  } 
  if(TimeCount%2 == 0 )
  {
    TIME0flag_10ms = 1;    
  }   
  if(TimeCount%4 == 0 )
  {
    TIME0flag_20ms = 1;
  }
  if(TimeCount%10 == 0 )
  {
    TIME0flag_50ms = 1;
  }
  if(TimeCount%16 == 0 )
  {
    TIME0flag_80ms = 1;
  }  
  if(TimeCount%20 == 0 )
  {
    TIME0flag_100ms = 1;
  //  TimeCount = 0 ;
  }  
  if(TimeCount%200 == 0 )
  {
    TIME0flag_1s = 1;
    TimeCount = 0 ;
  } 
}

/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�HardFault_Handler
*  ����˵����Ӳ���Ϸ��жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-4    �Ѳ���
*  ��    ע��������LED��˸��ָʾ������Ӳ���Ϸ�
*************************************************************************/
void HardFault_Handler(void)
{
  while (1)
  {
    //printf("\n****Ӳ���Ϸô���!!!*****\r\n\n");
  }
}

/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�PORTD_IRQHandler
*  ����˵����PORTD�˿��жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-1-25    �Ѳ���
*  ��    ע�����ź���Ҫ�Լ���ʼ�������
*************************************************************************/
void dlay(void){
  volatile uint16_t  dlaycount ;
   
  for(dlaycount = 0 ; dlaycount < 120 ; dlaycount ++){
  }
}

extern uint8  rebufer[12] ;
extern uint8  releth;
extern uint8 reflag ;
extern uint8 bksartflag ;
uint8 stat ;
/************************��������******************************/
vuint8 key5,key4,key3,key2,key1 ;

/*********************�ٶ�ģ��********************************/
SPEEDCOUT speed1[10],speed2[10];
uint8  turncount1 = 0,turncount2 = 0 ;
vuint8 LPT_INT_count = 0;  //�ٶ�2��count
vuint8 DMA_count_Flg = 0;  //�ٶ�1��count
vint16 DMALastValue;


/**************************����ͷ���ñ���***************************/
uint8  DMA_Over_Flg = 0 ;     //���ɼ���ɱ�־λ

extern uint16 LinCout;
uint8 frameflag = 0 ;
uint8 LinADCout =0;
uint8 AcqFlg =0 ;
uint16 *linarrycot = 0;
uint16 AcqAryy[] = {0X110 ,0X115,0X120,0XFFFF ,0XFFFF};
uint16 makcout = 0 ;
uint8 Sample_Flag=0;
extern uint8  ADdata[DATALINE][DATACOUNT];
void PORTD_IRQHandler()
{
   if(PORTD_ISFR & 0x2000)            //PTC13�����жϣ��ɼ������ж�
   { 
     PORTD_ISFR  |= 0x2000;         //д1���жϱ�־λ                           
     if((Sample_Flag)&&(LinADCout<DATALINE))
     {
        Sample_Flag = 0; 
        dlay() ;      //����ͷ���жϸ�Ϊ�½��ش�������Ч��ǰ����һ����������������Ҫһ����ʱ�������ĵ����ô���ʱ�䣬�����������Ҫ���ݵ�Ƭ������Ƶ������
        DMA_DADDR(DMA_CH4) = (uint32_t)ADdata[LinADCout] ;   //���ݴ洢��ַ�仯
        DMA_EN(DMA_CH4);                                    //ʹ��ͨ��CHn Ӳ������      (�������ܼ�������DMA����) 
        DMA_IRQ_EN(DMA_CH4) ;                             //����DMAͨ������
        LinADCout ++ ;
     }
      LinCout++;  
      if(LinCout == *linarrycot)
      {
        Sample_Flag = 1 ;
        if(*linarrycot != 0xFFFF )
        {
          linarrycot ++ ;
        }
      }
  }
  
  
  
  if(PORTD_ISFR & 0x4000)         //PTC14�����ж�,�ɼ��ĳ��жϡ�
  {
      PORTD_ISFR  |= 0x4000;        //д1���жϱ�־λ
      LinCout = 0 ;
      LinADCout=0;
      Sample_Flag=0;
      linarrycot = &AcqAryy[0] ;    //��ʼ��Ҫ�ɼ�������
      LinCout = 0 ;                         //�������ͷ����
      frameflag = 1 ;
   //   gpio_Interrupt_init(PTD13, GPI_UP, FALLING) ;          //�������ж�    
   //   PORTD_ISFR  |= 0x6000;         //д1���жϱ�־λ


  }
  
  


  
    
  if(PORTD_ISFR & 0x400) {
      PORTD_ISFR  |= 0x400;        //д1���жϱ�־λ
      key1 = 1 ;
  }
  if(PORTD_ISFR & 0x200) {
      PORTD_ISFR  |= 0x200;        //д1���жϱ�־λ
      key2 = 1 ;
  }
  if(PORTD_ISFR & 0x100) {
      PORTD_ISFR  |= 0x100;        //д1���жϱ�־λ
      key3 = 1 ;
  }
  if(PORTD_ISFR & 0x80) {
      PORTD_ISFR  |= 0x80;        //д1���жϱ�־λ
      key4 = 1 ;
  }
  if(PORTD_ISFR & 0x40) {
      PORTD_ISFR  |= 0x40;        //д1���жϱ�־λ
      key5 = 1 ;
  }
   
}

/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�PORTA_IRQHandler
*  ����˵����PORTA�˿��жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-1-25    �Ѳ���
*  ��    ע�����ź���Ҫ�����Լ���ʼ�����޸�
*************************************************************************/

void PORTA_IRQHandler()
{
  if(PORTA_ISFR & 0x08)         //PTB0�����ж�
  {
     
    PORTA_ISFR  |= 0x08;        //д1���жϱ�־λ
    
 
  }
  
  
}

/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�PORTD_IRQHandler
*  ����˵����PORTD�˿��жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-1-25    �Ѳ���
*  ��    ע�����ź���Ҫ�Լ���ʼ�������
*************************************************************************/
void PORTC_IRQHandler(void)
{
    if(PORTC_ISFR & 0x2000)          //PTD13�����ж�
  { 
      PORTC_ISFR  |= 0x2000;         //д1���жϱ�־λ
      
  }
   
}

/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�FTM0_IRQHandler
*  ����˵����FTM0���벶׽�жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-25
*  ��    ע�����ź���Ҫ�����Լ���ʼ�����޸ģ��ο����еĴ�������Լ��Ĺ���
*************************************************************************/
void FTM0_IRQHandler()
{
  
  
}

/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�FTM1_IRQHandler
*  ����˵����FTM1���벶׽�жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-25
*  ��    ע�����ź���Ҫ�����Լ���ʼ�����޸ģ��ο����еĴ�������Լ��Ĺ���
*************************************************************************/
void FTM1_IRQHandler()
{
  uint8_t s = FTM1_STATUS;             //��ȡ��׽�ͱȽ�״̬  All CHnF bits can be checked using only one read of STATUS.
  uint8_t n;
  FTM1_STATUS = 0x00;               //���жϱ�־λ
 
  n = 1;
  if( s & (1 << n) )
  {
    FTM_CnSC_REG(FTM1_BASE_PTR, n) &= ~FTM_CnSC_CHIE_MASK; //��ֹ���벶׽�ж�
    /*     �û�����       */
    /*********************/
    //�����������￪�����벶׽�ж�
    //FTM_CnSC_REG(FTM1_BASE_PTR,n) |= FTM_CnSC_CHIE_MASK;  //�������벶׽�ж�
  }
  
}


/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�DMA_CH4_Handler
*  ����˵����DMAͨ��4���жϷ�����
*  ����˵�����ǲɼ�����ͷ���ݣ�������λ����ͷAD���ݣ����Բɼ���300���㡣
���ñ�־λ�ܹ���ʱ���ơ�
*  �������أ���
*  �޸�ʱ�䣺2012-3-18    �Ѳ���
*  ��    ע��
*************************************************************************/
void DMA_CH4_Handler(void)
{
  DMA_IRQ_CLEAN(DMA_CH4) ;
  DMA_IRQ_DIS(DMA_CH4);
  DMA_DIS(DMA_CH4);
  DMA_Over_Flg =  1 ;
}



/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�PORTB_IRQHandler
*  ����˵����PORTB�˿��жϷ�����
*  ����˵���������ٶ�1��2���ٶȼ��������
*  �������أ���
*  �޸�ʱ�䣺2015-12-25    �Ѳ���
*  ��    ע�����ź���Ҫ�����Լ���ʼ�����޸�
*************************************************************************/

/*************************����������***************************/
 uint32 ultrdata ;
 int32 ultrtime;

void PORTB_IRQHandler()
{
//  uint8_t  n = 0;    //���ź�
//  n = 21;
 
  if(PORTB_ISFR & 0x200000) {
      PORTB_ISFR  |= 0x200000;        //д1���жϱ�־λ 
      if(PTB21_INT == 0){
        ultrtime = ultrdata - PIT_CVAL0 ;
        ultrtime = ultrtime*1000/Gbuscl_KH + ultrturn * 5*1000 ;  //ʱ�䵥λΪ1us
      }
      else{
        ultrdata = PIT_CVAL0 ;
        ultrturn = 0 ;
      }

  }
  
}

/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�DMA_CH4_Handler
*  ����˵����DMAͨ��4���жϷ�����
*  ����˵�����ٶ�ͨ��2�Ĳɼ�
*  �������أ���
*  �޸�ʱ�䣺2015-3-18    �Ѳ���
*  ��    ע��
*************************************************************************/

void DMA_CH6_Handler(void)
{
//  printf("DMA_CH0_Handler\n");
  DMA_IRQ_CLEAN(DMA_CH6);                             //���ͨ�������жϱ�־λ    (���������ٴν����ж�)
  DMA_EN(DMA_CH6);                                    //ʹ��ͨ��CHn Ӳ������      (�������ܼ�������DMA����)
  DMA_count_Flg ++ ;
}

/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�LPT_Handler
*  ����˵����LPT_Handler �жϲɼ�
*  ����˵�����ٶ�ͨ��1�Ĳɼ�
*  �������أ���
*  �޸�ʱ�䣺2015-3-18    �Ѳ���
*  ��    ע��
*************************************************************************/



void  LPT_Handler(void)
{
  LPTMR0_CSR |= LPTMR_CSR_TCF_MASK;   //���LPTMR�Ƚϱ�־
  LPT_INT_count++;                    //�ж������1
}