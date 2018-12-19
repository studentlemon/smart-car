#include "Landzo_MeasureSpeed.h"


/*************************************************************************
*                           �������պ����ѧ
*
*  �������ƣ�MeasureSpeed_one_init
*  ����˵������������ٳ�ʼ������
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2014-9-11
*  ��    ע��
*************************************************************************/
void MeasureSpeed_one_init(void)
{
    gpio_init (PTC4, GPO,HIGH);                            //���ʹ��
    
    FTM_PWM_init(FTM0 , CH1, 8000,0);       //���ռ�ձ����ó�ʼ��    ռ�ձ� = duty /(MOD +1 ) ;FTM_CnV_REG(FTMx[ftmn], ch) = cv;
    FTM_PWM_init(FTM0 , CH2, 8000,0);  
    
    lptmr_counter_init(LPT0_ALT2, LIN_COUNT,2,LPT_Rising)  ;   //��ʼ����������� ��PTC5���벶��ţ�LIN_cout =100�������ز��� 
  
}

/*************************************************************************
*                           �������պ����ѧ
*
*  �������ƣ�MeasureSpeed_double_init
*  ����˵����˫������ٳ�ʼ������
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2014-9-11
*  ��    ע��
*************************************************************************/
void MeasureSpeed_double_init(void)
{    
    FTM_PWM_init(FTM0 , CH0, 8000,0);       //���ռ�ձ����ó�ʼ��    ռ�ձ� = duty /(MOD +1 ) ;FTM_CnV_REG(FTMx[ftmn], ch) = cv;
    FTM_PWM_init(FTM0 , CH1, 8000,0);  
    FTM_PWM_init(FTM0 , CH2, 8000,0);       //���ռ�ձ����ó�ʼ��    ռ�ձ� = duty /(MOD +1 ) ;FTM_CnV_REG(FTMx[ftmn], ch) = cv;
    FTM_PWM_init(FTM0 , CH3, 8000,0);
    
    lptmr_counter_init(LPT0_ALT2, LIN_COUNT,2, LPT_Rising)  ;   //��ʼ����������� ��PTC5���벶��ţ�LIN_cout =100��Ԥ����Ϊ2�������ز��� 
  
}

/*************************************************************************
*                           �������պ����ѧ
*
*  �������ƣ�MeasureSpeed_one_test
*  ����˵������������ٳ���
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2014-9-11
*  ��    ע��
*************************************************************************/
uint16_t MeasureSpeed_one_test(void)
{
  uint16_t count=0;
  extern vuint8 LPT_INT_count;
  
  FTM_PWM_Duty(FTM0 , CH1,0);
  FTM_PWM_Duty(FTM0 , CH2,20);
  
  count = lptmr_pulse_get();                                                     //�����������������ֵ
  count = LPT_INT_count * LIN_COUNT +  count;                                     
  
  return count;
}

/*************************************************************************
*                           �������պ����ѧ
*
*  �������ƣ�MeasureSpeed_double_test
*  ����˵����˫������ٳ���
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2014-9-11
*  ��    ע��
*************************************************************************/
void MeasureSpeed_double_test(void)
{
    FTM_PWM_Duty(FTM0 , CH0,0);
    FTM_PWM_Duty(FTM0 , CH1,20);
    FTM_PWM_Duty(FTM0 , CH2,0);
    FTM_PWM_Duty(FTM0 , CH3,20);    
}

/*************************************************************************
*                           �������պ����ѧ
*
*  �������ƣ�speed_count_Init
*  ����˵�����������ٶȲɼ�������ɼ�
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2015-12-5
*  ��    ע��
*************************************************************************/

void speed_count_Init(void)
{

   lptmr_counter_init(LPT0_ALT2, LIN_COUNT,0, LPT_Rising)  ;   //��ʼ����������� ��PTC5���벶��ţ�LIN_cout =100��Ԥ����Ϊ2�������ز��� 
   DMA_count_Init(DMA_CH6,PTA19,LIN_COUNT,DMA_rising_keepon);
   
   set_irq_priority((INT_LPTimer + INC_IRQ),6) ;    //�������ȼ�
   setIRQadrr(INT_LPTimer,LPT_Handler);  //�����жϵ�ַ����
   set_irq_priority((INT_DMA6+INC_IRQ),6);//�����ж����ȼ� 0 
   setIRQadrr(INT_DMA6,DMA_CH6_Handler);  //�����жϵ�ַ����

   
}


/*************************************************************************
*                           �������պ����ѧ
*
*  �������ƣ�speed_count_read
*  ����˵�����������ٶȲɼ�������ɼ�
*  ����˵���� dmacount �ٶȼ������������
             lptcount �ٶȼ������������
            *DMAlastcout  �ϴ�dma�Ĵ�������
*  �������أ�*speedcount1 �ٶ�1�ķ���ֵ��*speedcount2 �ٶ�2�ķ���ֵ
*  �޸�ʱ�䣺2015-12-5
*  ��    ע��
*************************************************************************/
void speed1_count_read(vuint8 *dmacount , int16 *speedcount1, vuint8 *lptcount,int16 *speedcount2)
{
  static uint16 DMAlastcount ;
  *speedcount1 = lptmr_pulse_get()+ (*lptcount) * LIN_COUNT ;
  *speedcount2 = (*dmacount) *LIN_COUNT + DMAlastcount - (DMA_CITER_ELINKNO(DMA_CH6)&DMA_CITER_ELINKNO_CITER_MASK) ;
  DMAlastcount = DMA_CITER_ELINKNO(DMA_CH6)&DMA_CITER_ELINKNO_CITER_MASK;
  *dmacount = 0 ;
  *lptcount = 0 ;
    
  
  
}




/*************************************************************************
*                           �������պ����ѧ
*
*  �������ƣ�speed_count_read
*  ����˵�����������ٶȲɼ�������ɼ�
*  ����˵����*speedre1  �ٶ�1�Ľṹ�壬turnre1 ��ת��ƽ�������� dmacount �ٶȼ������������
            *speedre12  �ٶ�2�Ľṹ�壬turnre2 ��ת��ƽ�������� lptcount �ٶȼ������������
            *DMAlastcout  �ϴ�dma�Ĵ�������
*  �������أ�*speedcount1 �ٶ�1�ķ���ֵ��*speedcount2 �ٶ�2�ķ���ֵ
*  �޸�ʱ�䣺2015-12-5
*  ��    ע��
*************************************************************************/

void speed_count_read(SPEEDCOUT *speedre1,uint8 *turnre1,vuint8 *dmacount  , int16 *speedcount1,    //
                      SPEEDCOUT *speedre2,uint8 *turnre2,vuint8 *lptcount,vuint16 *DMAlastcout,int16 *speedcount2)       //�ٶ����ݵĶ�ȡ
{
  vuint8 i ; 
  *speedcount1 = 0 ;
  *speedcount2 = 0 ;
     /*******************
      �ٶ�2���������
     *******************/
    speedre2[*turnre2].porta = PTC12_INT ;
    speedre2[*turnre2].speedcount = lptmr_pulse_get();//�����������������ֵ
    speedre2[*turnre2].speedcount += (*lptcount) * LIN_COUNT ;
    *lptcount = 0 ;
    (*turnre2) ++ ;
    
    /*******************
      �ٶ�1���������
     *******************/
    speedre1[*turnre1].porta = PTC11_INT ;
    speedre1[*turnre1].speedcount = *DMAlastcout - (DMA_CITER_ELINKNO(DMA_CH6)&DMA_CITER_ELINKNO_CITER_MASK) ;    
    if(*dmacount) {
      i ++ ;
    }
    *DMAlastcout = DMA_CITER_ELINKNO(DMA_CH6)&DMA_CITER_ELINKNO_CITER_MASK;
    speedre1[*turnre1].speedcount += (*dmacount) *LIN_COUNT ;
    *dmacount = 0 ;
    (*turnre1) ++ ;
    
    /*******************
      �ٶ�2���ٶȼ���
     *******************/
    for(i = 0 ;i < *turnre2 ;i++){
      if(speedre2[i].porta == 0 ){
        *speedcount2 -= speedre2[i].speedcount ; 
      }
      else {
        *speedcount2 += speedre2[i].speedcount ;
      }
       speedre2[i].speedcount = 0 ; 
    }
    *turnre2 = 0 ;
     
    /*******************
      �ٶ�1���ٶȼ���
     *******************/
    for(i = 0 ;i < *turnre1 ;i++){
      if(speedre1[i].porta == 0 ){
        
        *speedcount1 -= speedre1[i].speedcount ; 
      }
      else {
        *speedcount1 += speedre1[i].speedcount ;
      }
       if(( *speedcount1 >= 400)||( *speedcount1 <= -400))
               i ++ ;
       speedre1[i].speedcount = 0 ; 
    }
        
 
   *turnre1 = 0 ;
   
}
