/***********************************************************
 * �ļ���       ��main.c
 * ˵��         ���û�Ӧ�ó���
 


 *��̳          ��http://www.landzo.cn
 * ��汾       ��V1.0
 *ʱ��          ��15.6.24
************************************************************/

#include "include.h"  // Include.h �����û��Զ����ͷ�ļ� ��ֵ
#include  "Landzo_Calculation.h"

/***********************�������***************************/
uint8 TIME0flag_5ms=0;
uint8 TIME0flag_10ms=0;
uint8 TIME0flag_20ms=0;
uint8 TIME0flag_50ms=0;
uint8 TIME0flag_80ms=0;
uint8 TIME0flag_100ms=0;
uint8 TIME0flag_1s =0;
uint8 TIME1flag_20ms=0;


extern uint8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
extern uint16 USART_RX_STA;    


extern  uint8  DMA_Over_Flg ;            //�ɼ���ɱ�־λ
extern  uint8  LinADCout ;
extern  uint8_t  LandzoRAM[ ];
extern  vuint8 key5,key4,key3,key2,key1 ;


uint16 TurnPWM_Value ;
uint16 LinCout =0;
uint8 Atem8B0 = 0 ;
int8  Station ;
uint8 ALineOverCout = 0 ;                 //�ɼ������������
uint8 ALineCal = 0 ;    
uint8  MIDSTATION = 71 ;                 //CCD��������ʾ�ĺ��ߵ��м�λ��
uint16 Sum_Station = 0 ;
uint8  Rightblackedge[DATALINE]={0};
uint8  Leftblackedge[DATALINE]={0};
uint8  CameraStation[DATALINE]={0};
uint8 ADdata[DATALINE][DATACOUNT] ={0} ;        //����AD����洢
uint16 Atemp0 ;
uint8  checkflg = 0 ;     
uint16 i=0,j=0;
uint8  ii ;
/*********************NRFģ�����******************/
uint8  bksartflag = 1 ;
uint8  reflag = 0 ;
uint8  rebufer[32] ={36};
uint16 trnbufer[8] ;
uint8  releth;

extern uint8 frameflag ;
/****************�ٶȱ���****************/
int16 speedcout1,speedcount2 ;
uint16 Set_Speed=0 ;                                  //Ŀ���ٶ�
uint16 Speed_Count =0 ;                          //���������
uint16 SpeedPWM_Value=0 ;                          //PID�����PWM 

uint8 Speed_P;
uint8 Speed_I;
uint8 Speed_D;

extern vuint8 LPT_INT_count ;  //�ٶ�2��count
extern vuint8 DMA_count_Flg  ; //�ٶ�1��count



/***********************�������***************************/

/************************������***************************/
void main(void)
{    
  DisableInterrupts;   //��ֹ���ж� 
  gpio_init(PTA28,GPO,1) ;  //LED GPIO���ų�ʼ������ ������� ���Ϊ�ߵ�ƽ
  gpio_init(PTC13,GPO,0) ;  //Buzzer ,�ߵ�ƽ�� 
  uart_init (UART0 , 115200);//���ڳ�ʼ�� ���ڣ�UART0 �����ʣ�115200
  uart_init (UART5 , 115200);//���ڳ�ʼ�� ���ڣ�UART0 �����ʣ�115200
  pit_init_ms(PIT0,5); //�����ж϶�ʱ��PIT0 ��ʱ5ms  
  set_irq_priority((INT_PIT0+INC_IRQ),2);//�����ж����ȼ� 2
  setIRQadrr(INT_PIT0,PIT0_IRQHandler);  //����PIT1��ʱ���жϵ�ַ����
  
  IICWriteGpio_inint();
//  while(LandzoIICEEROM_INIT()!= 1);
/***********************��ʼ������ͷ����***************************/
  COMS_INC ();    //���ж�Ϊ  14�����ж�Ϊ13������ΪPTE0-PTE7��DMA����ΪPTD12���ɼ����ݵ�����Ϊ160 X100��
//                   //��ʹ�ó����ʱ����Ҫ�鿴 calculation.h �еľ��嶨�� 
//                  /* #define  DATALINE   100     //��������
//                     #define  DATACOUNT  160 //�������� */ 
  
   OLED_Init();    //OELD��ʾ
   Servo_motor_SD5_init();   //�����ʼ
   Servo_motor_SD5_centre();
   Motor_double_PWM_init();   //�����ʼ��

   speed_count_Init();

  for(i = 0;i < DATALINE;i ++) //ADdata[i][j] ��ʼ����ֵ
   {
     for(j = 0;j < DATACOUNT;j ++)
     {
       ADdata[i][j] = 0;     
     }
   } 

  ///�ٶȱ�����ʼ��
    Set_Speed = 80 ;  //64
    Speed_P=5;
    Speed_I=0;
    Speed_D=0;
  
  EnableInterrupts;   //�������ж�  
  while(1)
  {
    if(TIME0flag_5ms){
      TIME0flag_5ms = 0 ;
//      uart_putchar(UART0,0xff);
//      uart_putchar(UART0,0xff);
//      uart_putchar(UART5,0xff);
//      uart_putchar(UART0,0xff);
      
    }
    if(TIME0flag_20ms){
      TIME0flag_20ms = 0 ;
      
      speed1_count_read(&DMA_count_Flg,&speedcout1,&LPT_INT_count,&speedcount2) ;
      Speed_Count = (speedcout1+speedcount2)/2 ;
      SpeedPWM_Value =SpeedControl(Speed_Count,Set_Speed,Speed_P,Speed_I,Speed_D) ;    //PID��������PWMֵ      
      //SpeedPWM_Value = 0 ;
        FTM_PWM_Duty(FTM0 , CH0,0);                                           //FTM0 CH0 PWM��� ���������
        FTM_PWM_Duty(FTM0 , CH1,SpeedPWM_Value);                              //FTM0 CH1 PWM��� ���������  
        FTM_PWM_Duty(FTM0 , CH2,0);                                           //FTM0 CH2 PWM��� ���������
        FTM_PWM_Duty(FTM0 , CH3,SpeedPWM_Value);                              //FTM0 CH3 PWM��� ���������  

     //  PTA28_OUT = ~PTA28_OUT ;
    }
    
    if(DMA_Over_Flg==1)
    {
      DMA_Over_Flg=0;
      if(ALineOverCout < LinADCout){
        Camera_Black(&ADdata[ALineOverCout][0],&Rightblackedge[ALineOverCout],
                  &Leftblackedge[ALineOverCout],&CameraStation[ALineOverCout]);
        ALineOverCout ++ ;
      }
      
    }
    
    if((frameflag)&&(ALineOverCout == DATALINE)){
       frameflag = 0;
       ALineOverCout = 0 ;
       for(int i=0;i<DATALINE;i++)
       {
             Sum_Station+= CameraStation[i];
       }       
       Station=(int8)(Sum_Station/DATALINE);
       Sum_Station=0;
      TurnPWM_Value = TurnPWM(Station, MIDSTATION) ;                        //����CCDλ��ֵ����ת��PWMֵ����
      //TurnPWM_Value = MIDSTRING2 ;
      FTM_CnV_REG(FTMx[FTM1], CH1) = TurnPWM_Value ;                            //ת��ֵ   ���2   
       
      COMS_print();   //���ڷ�������ʾ
    }
      
      if(TIME0flag_100ms)   //LEDָʾ����˸��ʾ����������
     {
       TIME0flag_100ms=0;


     }

  
 }
}


