
#include "common.h"
#include "include.h"
#include "Landzo_Calculation.h"



/*********************************************************** 
�������ƣ�COMS_INC
�������ܣ�����ͷ��ʼ��
��ڲ�����
���ڲ������� 
�� ע�� //DMAͨ��4 ��PTD0-PTD7 ���ݲɼ���ADdata���ݴ洢λ�ã�PTC18����ͨ����DMA_BYTE1  ���ݴ洢���ȣ�DATACOUNT  �����ܸ�����DMA_rising_keepon ������ʽ
***********************************************************/
extern uint8  BUFF[500] ;
extern uint8  ADdata[DATALINE][DATACOUNT];

void COMS_INC (void)
{
   gpio_Interrupt_init(PTD13, GPI_UP,FALLING) ;          //���ж�
   gpio_Interrupt_init(PTD14, GPI_UP,FALLING) ;          //���ж� 
   DMA_PORTx2BUFF_Init (DMA_CH4, (void *)&PTE_BYTE0_INT, ADdata[0], PTD12, DMA_BYTE1, DATACOUNT, DMA_falling_keepon);
    //DMAͨ��4 ��PTD0-PTD7 ���ݲɼ���ADdata���ݴ洢λ�ã�PTC18����ͨ����DMA_BYTE1  ���ݴ洢���ȣ�DATACOUNT  �����ܸ�����DMA_rising_keepon ������ʽ
   set_irq_priority((INT_PORTD + INC_IRQ),1) ;    //�������ȼ�
   setIRQadrr(INT_PORTD,PORTD_IRQHandler);  //�����жϵ�ַ����
   set_irq_priority((INT_DMA4+INC_IRQ),6);//�����ж����ȼ� 0 
   setIRQadrr(INT_DMA4,DMA_CH4_Handler);  //�����жϵ�ַ����

}


/*********************************************************** 
�������ƣ�COMS_print
�������ܣ�����ͷ��ʼ��
��ڲ�����
���ڲ������� 
�޸�ʱ�䣺2015-12-15   �Ѳ���
�� ע�� //DMAͨ��4 ��PTD0-PTD7 ���ݲɼ���ADdata���ݴ洢λ�ã�PTC18����ͨ����DMA_BYTE1  ���ݴ洢���ȣ�DATACOUNT  �����ܸ�����DMA_rising_keepon ������ʽ
***********************************************************/
void COMS_print(void)
{
  extern  uint8  frameflag ;            //�ɼ���ɱ�־λ
  uint16 i=0,j=0;
  
  //      if(frameflag == 1)    //���ɼ���ɱ�־λ
 //     {
  //      DMA_Over_Flg = 0 ;       
/***********************�رճ��жϣ����жϣ������ݣ���Ϊ��������ռ�õ�ʱ��̫������ˢƵ��***********************/
//        gpio_Interrupt_init(PTD13,GPI_UP,DISABLED) ;          //�رճ��ж�
//        gpio_Interrupt_init(PTD14,GPI_DOWN,DISABLED) ;        //�ر����ж� 
        
//          uart_putchar(UART0,0x01); //����ͷ֡ͷ 0x01 0xfe 0xfe 0x01
//          uart_putchar(UART0,0xfe);
//          uart_putchar(UART0,0xfe);
//          uart_putchar(UART0,0x01); 
//        uart_putchar(UART0,0xff); 
//        for(i=0;i<DATALINE;i++)
//        {
//         for(j=0;j<DATACOUNT;j++)
//         {
//           if(ADdata[i][j]==0xff) ADdata[i][j]--;
////           
//           uart_putchar(UART0,ADdata[i][j]); 
////           uart_putchar(UART5,ADdata[i][j]); 
//         }
//        }
        
//          uart_putchar(UART0,0xfe);//����ͷ֡β 0xfe 0x01 0x01 0xfe
//          uart_putchar(UART0,0x01); 
//          uart_putchar(UART0,0x01);
//          uart_putchar(UART0,0xfe);
          
          OledPrint(DATACOUNT,DATALINE,100,(uint8 *)ADdata);
/***********************�ȴ����ݽ����꣬�򿪳��жϣ��ڳ��ж��д����ж�***********************/
//        gpio_Interrupt_init(PTD14, GPI_UP,FALLING) ;          //�򿪳��ж�
//       }
}


/*********************************************************** 
�������ƣ�key_init
�������ܣ�������ʼ��
��ڲ�����
���ڲ������� 
�޸�ʱ�䣺2015-12-15   �Ѳ���
�� ע�� 
***********************************************************/
void key_init(void){
   gpio_Interrupt_init(PTD6, GPI_UP,FALLING) ;          //Key5
   gpio_Interrupt_init(PTD7, GPI_UP,FALLING) ;          //Key4
   gpio_Interrupt_init(PTD8, GPI_UP,FALLING) ;          //Key3
   gpio_Interrupt_init(PTD9, GPI_UP,FALLING) ;          //Key2
   gpio_Interrupt_init(PTD10, GPI_UP,FALLING) ;         //Key1
   
   setIRQadrr(INT_PORTD,PORTD_IRQHandler);  //�����жϵ�ַ����
  
  
}

/*********************************************************** 
�������ƣ�SD10_init
�������ܣ������ʼ��
��ڲ�����
���ڲ������� 
�޸�ʱ�䣺2015-12-15   �Ѳ���
�� ע�� 
***********************************************************/
void  SD10_init(void){
  
}
/**************************************************************
*
*               ����CCD�źź���ʶ����
*
*     �������ƣ�CCD_Black
*    ����˵��������ʶ����
*    ����˵����
*    ��������:
*    �޸�ʱ�䣺2013-03-15
*    ��    ע��
*************************************************************/  

void Camera_Black(uint8 *point1,uint8 *rightblackedge,uint8 *leftblackedge,uint8 *centre_black)
{
  uint8 point[150]={0};
  int16 temp0,temp1;  
  int16 temp_value1,temp_value2;
  uint16 leftedge,rightedge;
  uint16 leftavg,rightavg;
  uint8 leftflag,rightflag;
  uint8 leftcount,rightcount;
  uint8 LINEWITH, LEFTLINEFAV, RINGTLINFAV, FAV;
  static uint8 centre_lastblack =71; 
  
  LINEWITH=4;       //���߿�� 
  LEFTLINEFAV=100;  //���½��������ѹ�仯ֵ��Сֵ
  RINGTLINFAV=100;  //���½��������ѹ�仯ֵ��Сֵ
  FAV=100;          //��ֵ����ֵ 
  leftcount=0;     //����߿�ȼ���ֵ
  rightcount=0;    //�Һ��߿�ȼ���ֵ 
  leftedge=0;      //��߽� 
  rightedge=0;     //�ұ߽�
  leftavg=0;       //��������ߵ�ƽ��ֵ
  rightavg=0;      //�����Һ��ߵ�ƽ��ֵ
  leftflag=0;      //���߱�־λ
  rightflag=0;     //�Ҷ��߱�־λ
  
  for(int i=0;i<140;i++)
  {
    if( *point1++ > FAV)
    {
      point[i]=0xA0;    
    }
    else
    {
      point[i]=0;
    }   
  } 
 
   /*��������ؿ�ʼ���ҵ����غ�����ѭ��*/
  for(temp0=centre_lastblack;temp0>5;temp0--)               //���������
  {    
    for(temp1=temp0; temp1>( temp0-LINEWITH );temp1--)      //Ѱ��һ�㸽���ļ������Ƿ��ܹ����½���
    {    
      if(temp1<=0) break;                                   //������ʵ����������ѭ��             
      
      temp_value1= point[temp0]-point[temp1];               //�Ƚϰ׵㸽���ļ���ֵ
      
      if(temp_value1>=LEFTLINEFAV)                          //�ж��Ƿ�����Ҫ��
      {
        leftcount++;                                        //������������ֵ��һ
   //     testarry[temp0]=temp_value1;
      }
      else
      {
        leftcount=0;   
   //     testarry[temp0]=0;
      }           
    }    
    
    if(leftcount >= LINEWITH-1 )                        //�ж��Ƿ������������
    {
      leftedge = temp0 ;                                  //�������������ҵ�
      leftflag=0;                                         //�ҵ����أ���־λ��1 
      break;
    }
    else
    {
      leftcount=0;                                        //δ�ҵ��������  
      leftflag=1;                                         //��־λ���
      leftedge=5;                                         // ���ظ�ֵ 
    }
     
    if(leftedge<5) leftedge = 5;   
  } 
  /*����ز��ҽ���*/
  
  /*�����ұ��ؿ�ʼ���ҵ����غ�����ѭ��*/
  for(temp0=centre_lastblack;temp0< 135;temp0++)          //�ұ��ز��ҷ�ʽ�Ͳ��������һ��
  {    
    for(temp1=temp0; temp1< ( temp0+LINEWITH );temp1++)
    {
      if(temp1>=135) break;
      
      temp_value2 = point[temp0]-point[temp1];
      
      if(temp_value2 >=RINGTLINFAV)
      {      
        rightcount++;
      }
      else
      {
        rightcount=0;
      }          
      
    }
    
    if( rightcount >= LINEWITH-1 )
    {
      rightedge = temp0;
      rightflag=0;
      break;
    }
    else
    {
      rightcount=0;  
      rightflag=1;
      rightedge=135;
    }
    
    if( rightedge > 135) rightedge=135;
    
  }    
  /*�ұ��ز��ҽ���*/
  
  
  /*�ж����ҵ����صĿɿ���*/
  
  /*����صĿɿ����ж�*/
  if(leftflag==0)
  {
    /*������ߵ�ƽ��ֵ*/
    leftcount=0;
    for(temp0=leftedge;temp0>( leftedge-LINEWITH );temp0--)    
    {
      if(temp0<=0)break;
      leftcount++;
      leftavg+=point[temp0+1];
    }
    
    leftavg=leftavg/leftcount;      
    
    
    /*�Ƚϰ׵׺ͺ���֮��Ĳ�ֵ*/
    leftcount=0;
    for(temp0=leftedge;temp0<( leftedge+LINEWITH );temp0++)   //�жϱ��ظ����İ׵㣬�Ƿ���������
    {
      if(temp0>=135)break;
      
      temp_value1 = point[temp0-1]-leftavg;                  //�׵������ƽ��ֵ���Ƚ�
      if( temp_value1>= LEFTLINEFAV)                         //�ж��Ƿ�����Ҫ��
      { 
        leftcount++;                                         //�ҵ����أ���־λ��1 
      }
      else
      {
        leftcount=0;                                         // ��־λ���
      }
    }
    
    if(leftcount>(LINEWITH-2))                               //�ж��Ƿ������������
    {
      *leftblackedge=leftedge;                               //�������������㸳ֵ������
      leftedge=1;
    }
    else
    {
      *leftblackedge=5;
      leftcount=0;                                          //δ�ҵ�������� 
      leftflag=0;                                           //��־λ���
    }    
  }
  else
  {
    *leftblackedge=5;
  }
  /*��߽�ɿ����жϽ���*/
  
  
  
  /*�ұ߽�ɿ����жϿ�ʼ*/
  if(rightflag==0)                      // �ұ߽��жϿɿ��ԣ�����߽��жϷ�ʽһ��                  
  {
    rightcount=0;
    for(temp0=rightedge;temp0<( rightedge+LINEWITH );temp0++)
    {
      if(temp0>=135)break;
      rightcount++;
      rightavg+=point[temp0-1];
    }
    
    rightavg=rightavg/rightcount;
    
    rightcount=0;
    for(temp0=rightedge;temp0>( rightedge-LINEWITH );temp0--)
    {
      if(temp0<=0)break;
      
      temp_value2 = point[temp0] - rightavg;
      if(temp_value2>= RINGTLINFAV)
      {
        rightcount++;
      }
      else
      {
        rightcount=0;
      }      
    }
    
    if(rightcount>(LINEWITH-2))
    {
      *rightblackedge=rightedge;
      rightedge=1;
    }
    else
    {
      *rightblackedge=135;
      rightcount=0;
      rightflag=0;
    }
    
  }
  else
  {
    *rightblackedge=135;
  }
  
  /*�ұ߽�ɿ����жϽ���*/

  if( ( leftflag==0 )&&( rightflag==0 ) )
  {
  *centre_black = (uint8)(( leftedge + rightedge )/2);
  centre_lastblack = *centre_black;
  }
  else if( ( leftflag==0 )&&( rightflag==1 ) )
  {
   *centre_black = (uint8)(( leftedge + rightedge )/2);
   centre_lastblack = *centre_black;
  }
  else if( ( leftflag==1 )&&( rightflag==0 ) )
  {
   *centre_black = (uint8)(( leftedge + rightedge )/2);
   centre_lastblack = *centre_black;
  }
  else if( ( leftflag==1 )&&( rightflag==1 ) )
  {
   *centre_black= centre_lastblack;
  }   
  
   *leftblackedge=leftedge;
  *rightblackedge=rightedge;
  
}

/*********************************************************** 
�������ƣ�TurnPWM
�������ܣ�����ת��ֵ�ͽǶȴ���������ת��ֵ
��ڲ�����TurnPosition          �������λ��
          TurnMidPosition       �����е�ֵ

���ڲ������� 
�� ע�� 
***********************************************************/
int16 TurnPWM(uint8 TurnPosition, uint8 TurnMidPosition)
{   
    int16 direction;
    int16 TurnPWM ;
    static int16 TurnKP ,TurnKD ;
    static int16 direction0 = 60;
    direction = TurnPosition - TurnMidPosition ;
    
    if((direction > -20)&&(direction<0))      //�����ת
    {
      TurnKP = -10 ;
      TurnKD = 0 ;
    }
    else if((direction>-35)&&(direction < -20))
    { 
      TurnKP = -15 ;
      TurnKD = 0 ;
    }
    else if((direction<-35))
    {
      TurnKP = -20 ;
      TurnKD = 0 ;
    }
    if((direction>0)&&(direction < 20))      //�����ת
    { 
      TurnKP = -15 ;
      TurnKD = 0 ;
    }
    else if((direction>20)&&(direction <35))
    { 
      TurnKP = -20 ;
      TurnKD = 0 ;
    }
    else if((direction>30))
    {
      TurnKP = -20 ;
      TurnKD = 0 ;
    }
    
    
    TurnPWM =  TurnKP * direction + TurnKD * (direction - direction0);
    if(TurnPWM > TURNPWMMAX) {TurnPWM = TURNPWMMAX ;}
    else if (TurnPWM < TURNPWMMIN ) {TurnPWM = TURNPWMMIN ;}
    
    direction0 = direction ;
    TurnPWM += MIDSTRING2 ;
    
    return TurnPWM ;
    
} 


/*
** ===================================================================
** SpeedPID
   ���룺speedCount�ɼ����٣�AmSpeed Ŀ�공��  ��  
   ��� ��SpeedPWMOUT  ���㳵�� ��
** ===================================================================
*/

int16 SpeedControl(int16 speedCount,int16 AmSpeed,uint8 speedKP,uint8 speedKI,uint8 speedKD)
{
  
  static float Speed1_Err,SumErrSpeed;  //��̬�����洢�м����
  float Speed2_Err,Speed_EC;
  float Speed_P_Value,Speed_D_Value ;
  
  static int16  SpeedPWMOUT;
  
  Speed2_Err = Speed1_Err ;                //����һ�ε�ƫ���
  
  Speed1_Err = AmSpeed - speedCount  ;      //  �����µ�ƫ��ֵ
  
  Speed_EC = Speed1_Err - Speed2_Err ;      //  �����µ�ƫ��仯ֵ 
   
  Speed_P_Value =  Speed1_Err * speedKP/10.0 ;   //  ����ʽPID���Ƽ���P������
  
  SumErrSpeed  +=  Speed1_Err * speedKI ;    //����ʽPID���Ƽ���I������

  Speed_D_Value =  Speed_EC   *  speedKD/100.0 ;     //  ����ʽPID���Ƽ���D������
  
  SpeedPWMOUT  += (int16)(Speed_P_Value + SumErrSpeed + Speed_D_Value);
  if(SpeedPWMOUT < SPEED_PWM_MIN )
  {
   SpeedPWMOUT = SPEED_PWM_MIN ;
  }
  else if(SpeedPWMOUT > SPEED_PWM_MAX)
  {
    SpeedPWMOUT = SPEED_PWM_MAX ;
         
  }
  if(SpeedPWMOUT<=0)SpeedPWMOUT=0;
          
   return  SpeedPWMOUT ;  
}

