/***********************************************************
 * 文件名       ：isr.c
 * 说明         ：中断功能模块
 


 *论坛          ：http://www.landzo.cn
 * 库版本       ：V1.0
 *时间          ：15.5.26
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
*                             北京航空航天大学
*
*  函数名称：setIRQadrr
*  功能说明：设置中断地址函数
*  参数说明：IRQInterruptIndex 中断向量表，在芯片的.H文件，比如K60 在"MK60DZ10.h"
*            void IRQAdrr(void)  中断函数
*  函数返回：无
*  修改时间：2015-5-15    已测试
*  备    注：
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
  中断向量表在ram区域，可以进行直接擦除
  **************/
  if(Vector_TAB == (uint32)&__VECTOR_RAM){   
    Vector_TABl[IRQnum] = (uint32)(IRQAdrr) ;
   }
  else{
    /*****************************
    向量表在flash中
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
*                             北京航空航天大学
*
*  函数名称：USART0_IRQHandler
*  功能说明：串口0 中断 接收 服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2014-8-28    已测试
*  备    注：
*************************************************************************/
uint8 USART_RX_BUF[USART_REC_LEN];//接收缓冲,最大USART_REC_LEN个字节.
uint16 USART_RX_STA=0;    //接收状态标记
uint8 UART_receive = 0;   //1 接收完成标记

void USART0_IRQHandler(void)
{
  uint8 Res;
  DisableInterrupts; //关总中断
  if(uart_query(UART0) != 0)  //接收中断(接收到的数据必须是0x0a结尾)
   {
      Res = uart_getchar (UART0);//(USART1->DR);//读取接收到的数据
      USART_RX_BUF[USART_RX_STA]=Res;
      USART_RX_STA++;
      if(Res == 0x0a) //接收到0x0a结尾
      {
        UART_receive = 1; //接收完成
      }
   }
  EnableInterrupts;		  //开总中断
}
/*************************************************************************
*                             北京航空航天大学
*
*  函数名称：USART1_IRQHandler
*  功能说明：串口1 中断 接收 服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-14    已测试
*  备    注：
*************************************************************************/


void USART1_IRQHandler(void)
{
    uint8 ch;

    DisableInterrupts;		    //关总中断

    //接收一个字节数据并回发
    ch = uart_getchar (UART1);      //接收到一个数据
    uart_sendStr  (UART1, "\n你发送的数据为：");
    uart_putchar (UART1, ch);       //就发送出去

    EnableInterrupts;		    //开总中断
}
/*************************************************************************
*                             北京航空航天大学
*
*  函数名称：PIT1_IRQHandler
*  功能说明：PIT1定时中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-9-18    已测试
*  备    注：
*************************************************************************/

void PIT1_IRQHandler(void)
{
  PIT_Flag_Clear(PIT1);       //清中断标志位
   
}

/*************************************************************************
*                             北京航空航天大学
*
*  函数名称：PIT0_IRQHandler
*  功能说明：PIT0 定时中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-18    已测试
*  备    注：
*************************************************************************/
uint16 ultrturn ;


void PIT0_IRQHandler(void)
{
  PIT_Flag_Clear(PIT0);       //清中断标志位
  ultrturn ++ ;   //超声波
  
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
*                             北京航空航天大学
*
*  函数名称：HardFault_Handler
*  功能说明：硬件上访中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-4    已测试
*  备    注：可以用LED闪烁来指示发生了硬件上访
*************************************************************************/
void HardFault_Handler(void)
{
  while (1)
  {
    //printf("\n****硬件上访错误!!!*****\r\n\n");
  }
}

/*************************************************************************
*                             北京航空航天大学
*
*  函数名称：PORTD_IRQHandler
*  功能说明：PORTD端口中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-1-25    已测试
*  备    注：引脚号需要自己初始化来清除
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
/************************按键定义******************************/
vuint8 key5,key4,key3,key2,key1 ;

/*********************速度模块********************************/
SPEEDCOUT speed1[10],speed2[10];
uint8  turncount1 = 0,turncount2 = 0 ;
vuint8 LPT_INT_count = 0;  //速度2的count
vuint8 DMA_count_Flg = 0;  //速度1的count
vint16 DMALastValue;


/**************************摄像头采用变量***************************/
uint8  DMA_Over_Flg = 0 ;     //场采集完成标志位

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
   if(PORTD_ISFR & 0x2000)            //PTC13触发中断，采集的行中断
   { 
     PORTD_ISFR  |= 0x2000;         //写1清中断标志位                           
     if((Sample_Flag)&&(LinADCout<DATALINE))
     {
        Sample_Flag = 0; 
        dlay() ;      //摄像头行中断改为下降沿触发，有效点前面有一段行消隐区，故需要一段延时消除消耗掉，该处的时间，程序里面的需要根据单片机的主频调整。
        DMA_DADDR(DMA_CH4) = (uint32_t)ADdata[LinADCout] ;   //数据存储地址变化
        DMA_EN(DMA_CH4);                                    //使能通道CHn 硬件请求      (这样才能继续触发DMA传输) 
        DMA_IRQ_EN(DMA_CH4) ;                             //允许DMA通道传输
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
  
  
  
  if(PORTD_ISFR & 0x4000)         //PTC14触发中断,采集的场中断。
  {
      PORTD_ISFR  |= 0x4000;        //写1清中断标志位
      LinCout = 0 ;
      LinADCout=0;
      Sample_Flag=0;
      linarrycot = &AcqAryy[0] ;    //初始化要采集的行数
      LinCout = 0 ;                         //清除摄像头行数
      frameflag = 1 ;
   //   gpio_Interrupt_init(PTD13, GPI_UP, FALLING) ;          //开启行中断    
   //   PORTD_ISFR  |= 0x6000;         //写1清中断标志位


  }
  
  


  
    
  if(PORTD_ISFR & 0x400) {
      PORTD_ISFR  |= 0x400;        //写1清中断标志位
      key1 = 1 ;
  }
  if(PORTD_ISFR & 0x200) {
      PORTD_ISFR  |= 0x200;        //写1清中断标志位
      key2 = 1 ;
  }
  if(PORTD_ISFR & 0x100) {
      PORTD_ISFR  |= 0x100;        //写1清中断标志位
      key3 = 1 ;
  }
  if(PORTD_ISFR & 0x80) {
      PORTD_ISFR  |= 0x80;        //写1清中断标志位
      key4 = 1 ;
  }
  if(PORTD_ISFR & 0x40) {
      PORTD_ISFR  |= 0x40;        //写1清中断标志位
      key5 = 1 ;
  }
   
}

/*************************************************************************
*                             北京航空航天大学
*
*  函数名称：PORTA_IRQHandler
*  功能说明：PORTA端口中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-1-25    已测试
*  备    注：引脚号需要根据自己初始化来修改
*************************************************************************/

void PORTA_IRQHandler()
{
  if(PORTA_ISFR & 0x08)         //PTB0触发中断
  {
     
    PORTA_ISFR  |= 0x08;        //写1清中断标志位
    
 
  }
  
  
}

/*************************************************************************
*                             北京航空航天大学
*
*  函数名称：PORTD_IRQHandler
*  功能说明：PORTD端口中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-1-25    已测试
*  备    注：引脚号需要自己初始化来清除
*************************************************************************/
void PORTC_IRQHandler(void)
{
    if(PORTC_ISFR & 0x2000)          //PTD13触发中断
  { 
      PORTC_ISFR  |= 0x2000;         //写1清中断标志位
      
  }
   
}

/*************************************************************************
*                             北京航空航天大学
*
*  函数名称：FTM0_IRQHandler
*  功能说明：FTM0输入捕捉中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-25
*  备    注：引脚号需要根据自己初始化来修改，参考现有的代码添加自己的功能
*************************************************************************/
void FTM0_IRQHandler()
{
  
  
}

/*************************************************************************
*                             北京航空航天大学
*
*  函数名称：FTM1_IRQHandler
*  功能说明：FTM1输入捕捉中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-25
*  备    注：引脚号需要根据自己初始化来修改，参考现有的代码添加自己的功能
*************************************************************************/
void FTM1_IRQHandler()
{
  uint8_t s = FTM1_STATUS;             //读取捕捉和比较状态  All CHnF bits can be checked using only one read of STATUS.
  uint8_t n;
  FTM1_STATUS = 0x00;               //清中断标志位
 
  n = 1;
  if( s & (1 << n) )
  {
    FTM_CnSC_REG(FTM1_BASE_PTR, n) &= ~FTM_CnSC_CHIE_MASK; //禁止输入捕捉中断
    /*     用户任务       */
    /*********************/
    //不建议在这里开启输入捕捉中断
    //FTM_CnSC_REG(FTM1_BASE_PTR,n) |= FTM_CnSC_CHIE_MASK;  //开启输入捕捉中断
  }
  
}


/*************************************************************************
*                             北京航空航天大学
*
*  函数名称：DMA_CH4_Handler
*  功能说明：DMA通道4的中断服务函数
*  参数说明：是采集摄像头数据，本数据位摄像头AD数据，可以采集到300个点。
设置标志位能够及时搬移。
*  函数返回：无
*  修改时间：2012-3-18    已测试
*  备    注：
*************************************************************************/
void DMA_CH4_Handler(void)
{
  DMA_IRQ_CLEAN(DMA_CH4) ;
  DMA_IRQ_DIS(DMA_CH4);
  DMA_DIS(DMA_CH4);
  DMA_Over_Flg =  1 ;
}



/*************************************************************************
*                             北京航空航天大学
*
*  函数名称：PORTB_IRQHandler
*  功能说明：PORTB端口中断服务函数
*  参数说明：用于速度1、2的速度及方向计算
*  函数返回：无
*  修改时间：2015-12-25    已测试
*  备    注：引脚号需要根据自己初始化来修改
*************************************************************************/

/*************************超声波变量***************************/
 uint32 ultrdata ;
 int32 ultrtime;

void PORTB_IRQHandler()
{
//  uint8_t  n = 0;    //引脚号
//  n = 21;
 
  if(PORTB_ISFR & 0x200000) {
      PORTB_ISFR  |= 0x200000;        //写1清中断标志位 
      if(PTB21_INT == 0){
        ultrtime = ultrdata - PIT_CVAL0 ;
        ultrtime = ultrtime*1000/Gbuscl_KH + ultrturn * 5*1000 ;  //时间单位为1us
      }
      else{
        ultrdata = PIT_CVAL0 ;
        ultrturn = 0 ;
      }

  }
  
}

/*************************************************************************
*                             北京航空航天大学
*
*  函数名称：DMA_CH4_Handler
*  功能说明：DMA通道4的中断服务函数
*  参数说明：速度通道2的采集
*  函数返回：无
*  修改时间：2015-3-18    已测试
*  备    注：
*************************************************************************/

void DMA_CH6_Handler(void)
{
//  printf("DMA_CH0_Handler\n");
  DMA_IRQ_CLEAN(DMA_CH6);                             //清除通道传输中断标志位    (这样才能再次进入中断)
  DMA_EN(DMA_CH6);                                    //使能通道CHn 硬件请求      (这样才能继续触发DMA传输)
  DMA_count_Flg ++ ;
}

/*************************************************************************
*                             北京航空航天大学
*
*  函数名称：LPT_Handler
*  功能说明：LPT_Handler 中断采集
*  参数说明：速度通道1的采集
*  函数返回：无
*  修改时间：2015-3-18    已测试
*  备    注：
*************************************************************************/



void  LPT_Handler(void)
{
  LPTMR0_CSR |= LPTMR_CSR_TCF_MASK;   //清除LPTMR比较标志
  LPT_INT_count++;                    //中断溢出加1
}