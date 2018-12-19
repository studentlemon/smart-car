#ifndef  Landzo_Calculation_H
#define  Landzo_Calculation_H  


void COMS_INC (void) ;        //摄像头初始化
void COMS_print(void) ;       //摄像头串口发送
void key_init(void) ;         //按键初始化
int16 TurnPWM(uint8 TurnPosition, uint8 TurnMidPosition) ;     //计算转向位置
void Camera_Black(uint8 *point1,uint8 *rightblackedge,uint8 *leftblackedge,uint8 *centre_black) ;

int16 SpeedControl(int16 speedCount,int16 AmSpeed,uint8 speedKP,uint8 speedKI,uint8 speedKD) ;
/*********************************************************************************************************
* Description: define
*********************************************************************************************************
*/
#define  DATALINE   3    //采样行数
#define  DATACOUNT   160 //采样点数

 /**********************
 * 舵机偏移最值
 *********************/
#define  TURNPWMMAX     (600)
#define  TURNPWMMIN     (-600)


 /**********************
 * 电机偏移最值
 *********************/
#define  SPEED_PWM_MIN    -350
#define  SPEED_PWM_MAX    350


#endif