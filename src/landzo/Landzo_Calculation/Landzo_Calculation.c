
#include "common.h"
#include "include.h"
#include "Landzo_Calculation.h"



/*********************************************************** 
函数名称：COMS_INC
函数功能：摄像头初始化
入口参数：
出口参数：无 
备 注： //DMA通道4 ，PTD0-PTD7 数据采集，ADdata数据存储位置，PTC18触发通道，DMA_BYTE1  数据存储长度，DATACOUNT  数据总个数，DMA_rising_keepon 触发方式
***********************************************************/
extern uint8  BUFF[500] ;
extern uint8  ADdata[DATALINE][DATACOUNT];

void COMS_INC (void)
{
   gpio_Interrupt_init(PTD13, GPI_UP,FALLING) ;          //场中断
   gpio_Interrupt_init(PTD14, GPI_UP,FALLING) ;          //行中断 
   DMA_PORTx2BUFF_Init (DMA_CH4, (void *)&PTE_BYTE0_INT, ADdata[0], PTD12, DMA_BYTE1, DATACOUNT, DMA_falling_keepon);
    //DMA通道4 ，PTD0-PTD7 数据采集，ADdata数据存储位置，PTC18触发通道，DMA_BYTE1  数据存储长度，DATACOUNT  数据总个数，DMA_rising_keepon 触发方式
   set_irq_priority((INT_PORTD + INC_IRQ),1) ;    //设置优先级
   setIRQadrr(INT_PORTD,PORTD_IRQHandler);  //设置中断地址函数
   set_irq_priority((INT_DMA4+INC_IRQ),6);//设置中断优先级 0 
   setIRQadrr(INT_DMA4,DMA_CH4_Handler);  //设置中断地址函数

}


/*********************************************************** 
函数名称：COMS_print
函数功能：摄像头初始化
入口参数：
出口参数：无 
修改时间：2015-12-15   已测试
备 注： //DMA通道4 ，PTD0-PTD7 数据采集，ADdata数据存储位置，PTC18触发通道，DMA_BYTE1  数据存储长度，DATACOUNT  数据总个数，DMA_rising_keepon 触发方式
***********************************************************/
void COMS_print(void)
{
  extern  uint8  frameflag ;            //采集完成标志位
  uint16 i=0,j=0;
  
  //      if(frameflag == 1)    //场采集完成标志位
 //     {
  //      DMA_Over_Flg = 0 ;       
/***********************关闭场中断，行中断，发数据，因为发送数据占用的时间太长，故刷频慢***********************/
//        gpio_Interrupt_init(PTD13,GPI_UP,DISABLED) ;          //关闭场中断
//        gpio_Interrupt_init(PTD14,GPI_DOWN,DISABLED) ;        //关闭行中断 
        
//          uart_putchar(UART0,0x01); //摄像头帧头 0x01 0xfe 0xfe 0x01
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
        
//          uart_putchar(UART0,0xfe);//摄像头帧尾 0xfe 0x01 0x01 0xfe
//          uart_putchar(UART0,0x01); 
//          uart_putchar(UART0,0x01);
//          uart_putchar(UART0,0xfe);
          
          OledPrint(DATACOUNT,DATALINE,100,(uint8 *)ADdata);
/***********************等待数据接收完，打开场中断，在场中断中打开行中断***********************/
//        gpio_Interrupt_init(PTD14, GPI_UP,FALLING) ;          //打开场中断
//       }
}


/*********************************************************** 
函数名称：key_init
函数功能：按键初始化
入口参数：
出口参数：无 
修改时间：2015-12-15   已测试
备 注： 
***********************************************************/
void key_init(void){
   gpio_Interrupt_init(PTD6, GPI_UP,FALLING) ;          //Key5
   gpio_Interrupt_init(PTD7, GPI_UP,FALLING) ;          //Key4
   gpio_Interrupt_init(PTD8, GPI_UP,FALLING) ;          //Key3
   gpio_Interrupt_init(PTD9, GPI_UP,FALLING) ;          //Key2
   gpio_Interrupt_init(PTD10, GPI_UP,FALLING) ;         //Key1
   
   setIRQadrr(INT_PORTD,PORTD_IRQHandler);  //设置中断地址函数
  
  
}

/*********************************************************** 
函数名称：SD10_init
函数功能：舵机初始化
入口参数：
出口参数：无 
修改时间：2015-12-15   已测试
备 注： 
***********************************************************/
void  SD10_init(void){
  
}
/**************************************************************
*
*               线性CCD信号黑线识别函数
*
*     函数名称：CCD_Black
*    功能说明：黑线识别函数
*    参数说明：
*    函数返回:
*    修改时间：2013-03-15
*    备    注：
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
  
  LINEWITH=4;       //黑线宽度 
  LEFTLINEFAV=100;  //左下降沿两点电压变化值最小值
  RINGTLINFAV=100;  //右下降沿两点电压变化值最小值
  FAV=100;          //二值化阈值 
  leftcount=0;     //左黑线宽度计数值
  rightcount=0;    //右黑线宽度计数值 
  leftedge=0;      //左边界 
  rightedge=0;     //右边界
  leftavg=0;       //计算左黑线的平均值
  rightavg=0;      //计算右黑线的平均值
  leftflag=0;      //左丢线标志位
  rightflag=0;     //右丢线标志位
  
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
 
   /*查找左边沿开始，找到边沿后跳出循环*/
  for(temp0=centre_lastblack;temp0>5;temp0--)               //检测左侧边沿
  {    
    for(temp1=temp0; temp1>( temp0-LINEWITH );temp1--)      //寻找一点附近的几个点是否能构成下降沿
    {    
      if(temp1<=0) break;                                   //不满足实际条件跳出循环             
      
      temp_value1= point[temp0]-point[temp1];               //比较白点附近的几个值
      
      if(temp_value1>=LEFTLINEFAV)                          //判断是否满足要求
      {
        leftcount++;                                        //满足条件计数值加一
   //     testarry[temp0]=temp_value1;
      }
      else
      {
        leftcount=0;   
   //     testarry[temp0]=0;
      }           
    }    
    
    if(leftcount >= LINEWITH-1 )                        //判断是否满足边沿条件
    {
      leftedge = temp0 ;                                  //满足条件边沿找到
      leftflag=0;                                         //找到边沿，标志位置1 
      break;
    }
    else
    {
      leftcount=0;                                        //未找到清除计数  
      leftflag=1;                                         //标志位清除
      leftedge=5;                                         // 边沿赋值 
    }
     
    if(leftedge<5) leftedge = 5;   
  } 
  /*左边沿查找结束*/
  
  /*查找右边沿开始，找到边沿后跳出循环*/
  for(temp0=centre_lastblack;temp0< 135;temp0++)          //右边沿查找方式和查找左边沿一样
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
  /*右边沿查找结束*/
  
  
  /*判断已找到边沿的可靠性*/
  
  /*左边沿的可靠性判断*/
  if(leftflag==0)
  {
    /*计算黑线的平均值*/
    leftcount=0;
    for(temp0=leftedge;temp0>( leftedge-LINEWITH );temp0--)    
    {
      if(temp0<=0)break;
      leftcount++;
      leftavg+=point[temp0+1];
    }
    
    leftavg=leftavg/leftcount;      
    
    
    /*比较白底和黑线之间的差值*/
    leftcount=0;
    for(temp0=leftedge;temp0<( leftedge+LINEWITH );temp0++)   //判断边沿附近的白点，是否满足条件
    {
      if(temp0>=135)break;
      
      temp_value1 = point[temp0-1]-leftavg;                  //白点与黑线平均值作比较
      if( temp_value1>= LEFTLINEFAV)                         //判断是否满足要求
      { 
        leftcount++;                                         //找到边沿，标志位置1 
      }
      else
      {
        leftcount=0;                                         // 标志位清除
      }
    }
    
    if(leftcount>(LINEWITH-2))                               //判断是否满足边沿条件
    {
      *leftblackedge=leftedge;                               //两个条件都满足赋值给边沿
      leftedge=1;
    }
    else
    {
      *leftblackedge=5;
      leftcount=0;                                          //未找到清除计数 
      leftflag=0;                                           //标志位清除
    }    
  }
  else
  {
    *leftblackedge=5;
  }
  /*左边界可靠性判断结束*/
  
  
  
  /*右边界可靠性判断开始*/
  if(rightflag==0)                      // 右边界判断可靠性，和左边界判断方式一样                  
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
  
  /*右边界可靠性判断结束*/

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
函数名称：TurnPWM
函数功能：根据转向值和角度传感器计算转向值
入口参数：TurnPosition          计算黑线位置
          TurnMidPosition       黑线中点值

出口参数：无 
备 注： 
***********************************************************/
int16 TurnPWM(uint8 TurnPosition, uint8 TurnMidPosition)
{   
    int16 direction;
    int16 TurnPWM ;
    static int16 TurnKP ,TurnKD ;
    static int16 direction0 = 60;
    direction = TurnPosition - TurnMidPosition ;
    
    if((direction > -20)&&(direction<0))      //舵机左转
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
    if((direction>0)&&(direction < 20))      //舵机右转
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
   输入：speedCount采集车速，AmSpeed 目标车速  ；  
   输出 ：SpeedPWMOUT  计算车速 ；
** ===================================================================
*/

int16 SpeedControl(int16 speedCount,int16 AmSpeed,uint8 speedKP,uint8 speedKI,uint8 speedKD)
{
  
  static float Speed1_Err,SumErrSpeed;  //静态变量存储中间变量
  float Speed2_Err,Speed_EC;
  float Speed_P_Value,Speed_D_Value ;
  
  static int16  SpeedPWMOUT;
  
  Speed2_Err = Speed1_Err ;                //将上一次的偏差保存
  
  Speed1_Err = AmSpeed - speedCount  ;      //  计算新的偏差值
  
  Speed_EC = Speed1_Err - Speed2_Err ;      //  计算新的偏差变化值 
   
  Speed_P_Value =  Speed1_Err * speedKP/10.0 ;   //  增量式PID控制计算P调节量
  
  SumErrSpeed  +=  Speed1_Err * speedKI ;    //增量式PID控制计算I调节量

  Speed_D_Value =  Speed_EC   *  speedKD/100.0 ;     //  增量式PID控制计算D调节量
  
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

