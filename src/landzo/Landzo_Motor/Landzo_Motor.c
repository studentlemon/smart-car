#include  "Landzo_motor.h"

/*************************************************************************
*                           北京航空航天大学
*
*  函数名称：Motor_one_PWM_Init
*  功能说明：电机驱动初始化程序
*  参数说明：
*  函数返回：无
*  修改时间：2014-9-11
*  备    注：
*************************************************************************/

void Motor_one_PWM_init(void)
{    
  gpio_init (PTC4, GPO,HIGH);                             //电机使能
  FTM_PWM_init(FTM0 , CH1, 80000,0);                        //电机占空比设置初始化   MOD =313 ;  占空比 = duty /(MOD +1 ) ;FTM_CnV_REG(FTMx[ftmn], ch) = cv;
  FTM_PWM_init(FTM0 , CH2, 80000,0);                        //电机占空比设置初始化   MOD =313 ;  占空比 = duty /(MOD +1 ) ;FTM_CnV_REG(FTMx[ftmn], ch) = cv;
  
}

/*************************************************************************
*                           北京航空航天大学
*
*  函数名称：Motor_double_PWM_Init
*  功能说明：电机驱动初始化程序
*  参数说明：
*  函数返回：无
*  修改时间：2014-9-5
*  备    注：
*************************************************************************/

void Motor_double_PWM_init(void)
{    
  FTM_PWM_init(FTM0 , CH0, 80000,0);                        //电机占空比设置初始化   MOD =313 ;  占空比 = duty /(MOD +1 ) ;FTM_CnV_REG(FTMx[ftmn], ch) = cv;
  FTM_PWM_init(FTM0 , CH1, 80000,0);                        //电机占空比设置初始化   MOD =313 ;  占空比 = duty /(MOD +1 ) ;FTM_CnV_REG(FTMx[ftmn], ch) = cv;
  FTM_PWM_init(FTM0 , CH2, 80000,0);                        //电机占空比设置初始化   MOD =313 ;  占空比 = duty /(MOD +1 ) ;FTM_CnV_REG(FTMx[ftmn], ch) = cv;
  FTM_PWM_init(FTM0 , CH3, 80000,0);                        //电机占空比设置初始化   MOD =313 ;  占空比 = duty /(MOD +1 ) ;FTM_CnV_REG(FTMx[ftmn], ch) = cv;
}

/*************************************************************************
*                           北京航空航天大学
*
*  函数名称：Motor_one_test
*  功能说明：电机驱动初始化程序
*  参数说明：
*  函数返回：无
*  修改时间：2014-9-11
*  备    注：
*************************************************************************/

void Motor_one_test(void)
{
  uint8_t count=0;
  if( count == 3 )
  {
    count = 2 ;
    FTM_PWM_Duty(FTM0 , CH1,TXSTPWM);
    FTM_PWM_Duty(FTM0 , CH2,0);
  }
  else if(count == 2)
  {
    
    count = 1 ;
    FTM_PWM_Duty(FTM0 , CH1,0);
    FTM_PWM_Duty(FTM0 , CH2,0);
    
  }
  else if(count == 1)
  {
    
    count = 0 ;
    
    FTM_PWM_Duty(FTM0 , CH1,0);
    FTM_PWM_Duty(FTM0 , CH2,TXSTPWM);
    
  }
  else if(count == 0)
  {    
    count = 3 ;
    FTM_PWM_Duty(FTM0 , CH1,0);
    FTM_PWM_Duty(FTM0 , CH2,0);
    
  }
}
/*************************************************************************
*                           北京航空航天大学
*
*  函数名称：Motor_double_test
*  功能说明：电机驱动初始化程序
*  参数说明：
*  函数返回：无
*  修改时间：2014-9-11
*  备    注：
*************************************************************************/
void Motor_double_test(void)
{
  static uint8_t count=0;
  if( count == 3 )
  {
    count = 2 ;
    FTM_PWM_Duty(FTM2 , CH0,TXSTPWM);
    FTM_PWM_Duty(FTM2 , CH1,0);
    FTM_PWM_Duty(FTM0 , CH2,TXSTPWM);
    FTM_PWM_Duty(FTM0 , CH3,0);
  } 
  else if(count == 2)
  {
    
    count = 1 ;
    FTM_PWM_Duty(FTM2 , CH0,0);
    FTM_PWM_Duty(FTM2 , CH1,0);
    FTM_PWM_Duty(FTM0 , CH2,0);
    FTM_PWM_Duty(FTM0 , CH3,0);
    
  }
  else if(count == 1)
  {
    
    count = 0 ;
    
    FTM_PWM_Duty(FTM2 , CH0,0);
    FTM_PWM_Duty(FTM2 , CH1,TXSTPWM);
    FTM_PWM_Duty(FTM0 , CH2,0);
    FTM_PWM_Duty(FTM0 , CH3,TXSTPWM);
    
  } 
  else if(count == 0)
  {
    
    count = 3 ;
    FTM_PWM_Duty(FTM2 , CH0,0);
    FTM_PWM_Duty(FTM2,  CH1,0);
    FTM_PWM_Duty(FTM0 , CH2,0);
    FTM_PWM_Duty(FTM0 , CH3,0);
    
  }
}


