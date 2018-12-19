#include "Landzo_MeasureSpeed.h"


/*************************************************************************
*                           北京航空航天大学
*
*  函数名称：MeasureSpeed_one_init
*  功能说明：单电机测速初始化程序
*  参数说明：
*  函数返回：无
*  修改时间：2014-9-11
*  备    注：
*************************************************************************/
void MeasureSpeed_one_init(void)
{
    gpio_init (PTC4, GPO,HIGH);                            //电机使能
    
    FTM_PWM_init(FTM0 , CH1, 8000,0);       //电机占空比设置初始化    占空比 = duty /(MOD +1 ) ;FTM_CnV_REG(FTMx[ftmn], ch) = cv;
    FTM_PWM_init(FTM0 , CH2, 8000,0);  
    
    lptmr_counter_init(LPT0_ALT2, LIN_COUNT,2,LPT_Rising)  ;   //初始化脉冲计数器 ，PTC5输入捕获脚，LIN_cout =100，上升沿捕获 
  
}

/*************************************************************************
*                           北京航空航天大学
*
*  函数名称：MeasureSpeed_double_init
*  功能说明：双电机测速初始化程序
*  参数说明：
*  函数返回：无
*  修改时间：2014-9-11
*  备    注：
*************************************************************************/
void MeasureSpeed_double_init(void)
{    
    FTM_PWM_init(FTM0 , CH0, 8000,0);       //电机占空比设置初始化    占空比 = duty /(MOD +1 ) ;FTM_CnV_REG(FTMx[ftmn], ch) = cv;
    FTM_PWM_init(FTM0 , CH1, 8000,0);  
    FTM_PWM_init(FTM0 , CH2, 8000,0);       //电机占空比设置初始化    占空比 = duty /(MOD +1 ) ;FTM_CnV_REG(FTMx[ftmn], ch) = cv;
    FTM_PWM_init(FTM0 , CH3, 8000,0);
    
    lptmr_counter_init(LPT0_ALT2, LIN_COUNT,2, LPT_Rising)  ;   //初始化脉冲计数器 ，PTC5输入捕获脚，LIN_cout =100，预处理为2，上升沿捕获 
  
}

/*************************************************************************
*                           北京航空航天大学
*
*  函数名称：MeasureSpeed_one_test
*  功能说明：单电机测速程序
*  参数说明：
*  函数返回：无
*  修改时间：2014-9-11
*  备    注：
*************************************************************************/
uint16_t MeasureSpeed_one_test(void)
{
  uint16_t count=0;
  extern vuint8 LPT_INT_count;
  
  FTM_PWM_Duty(FTM0 , CH1,0);
  FTM_PWM_Duty(FTM0 , CH2,20);
  
  count = lptmr_pulse_get();                                                     //保存脉冲计数器计算值
  count = LPT_INT_count * LIN_COUNT +  count;                                     
  
  return count;
}

/*************************************************************************
*                           北京航空航天大学
*
*  函数名称：MeasureSpeed_double_test
*  功能说明：双电机测速程序
*  参数说明：
*  函数返回：无
*  修改时间：2014-9-11
*  备    注：
*************************************************************************/
void MeasureSpeed_double_test(void)
{
    FTM_PWM_Duty(FTM0 , CH0,0);
    FTM_PWM_Duty(FTM0 , CH1,20);
    FTM_PWM_Duty(FTM0 , CH2,0);
    FTM_PWM_Duty(FTM0 , CH3,20);    
}

/*************************************************************************
*                           北京航空航天大学
*
*  函数名称：speed_count_Init
*  功能说明：编码器速度采集及方向采集
*  参数说明：
*  函数返回：无
*  修改时间：2015-12-5
*  备    注：
*************************************************************************/

void speed_count_Init(void)
{

   lptmr_counter_init(LPT0_ALT2, LIN_COUNT,0, LPT_Rising)  ;   //初始化脉冲计数器 ，PTC5输入捕获脚，LIN_cout =100，预处理为2，上升沿捕获 
   DMA_count_Init(DMA_CH6,PTA19,LIN_COUNT,DMA_rising_keepon);
   
   set_irq_priority((INT_LPTimer + INC_IRQ),6) ;    //设置优先级
   setIRQadrr(INT_LPTimer,LPT_Handler);  //设置中断地址函数
   set_irq_priority((INT_DMA6+INC_IRQ),6);//设置中断优先级 0 
   setIRQadrr(INT_DMA6,DMA_CH6_Handler);  //设置中断地址函数

   
}


/*************************************************************************
*                           北京航空航天大学
*
*  函数名称：speed_count_read
*  功能说明：编码器速度采集及方向采集
*  参数说明： dmacount 速度计数溢出计数器
             lptcount 速度计数溢出计数器
            *DMAlastcout  上次dma寄存器数据
*  函数返回：*speedcount1 速度1的返回值，*speedcount2 速度2的返回值
*  修改时间：2015-12-5
*  备    注：
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
*                           北京航空航天大学
*
*  函数名称：speed_count_read
*  功能说明：编码器速度采集及方向采集
*  参数说明：*speedre1  速度1的结构体，turnre1 翻转电平计数器， dmacount 速度计数溢出计数器
            *speedre12  速度2的结构体，turnre2 翻转电平计数器， lptcount 速度计数溢出计数器
            *DMAlastcout  上次dma寄存器数据
*  函数返回：*speedcount1 速度1的返回值，*speedcount2 速度2的返回值
*  修改时间：2015-12-5
*  备    注：
*************************************************************************/

void speed_count_read(SPEEDCOUT *speedre1,uint8 *turnre1,vuint8 *dmacount  , int16 *speedcount1,    //
                      SPEEDCOUT *speedre2,uint8 *turnre2,vuint8 *lptcount,vuint16 *DMAlastcout,int16 *speedcount2)       //速度数据的读取
{
  vuint8 i ; 
  *speedcount1 = 0 ;
  *speedcount2 = 0 ;
     /*******************
      速度2的脉冲读数
     *******************/
    speedre2[*turnre2].porta = PTC12_INT ;
    speedre2[*turnre2].speedcount = lptmr_pulse_get();//保存脉冲计数器计算值
    speedre2[*turnre2].speedcount += (*lptcount) * LIN_COUNT ;
    *lptcount = 0 ;
    (*turnre2) ++ ;
    
    /*******************
      速度1的脉冲读数
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
      速度2的速度计数
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
      速度1的速度计数
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
