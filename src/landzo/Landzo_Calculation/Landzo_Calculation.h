#ifndef  Landzo_Calculation_H
#define  Landzo_Calculation_H  


void COMS_INC (void) ;        //����ͷ��ʼ��
void COMS_print(void) ;       //����ͷ���ڷ���
void key_init(void) ;         //������ʼ��
int16 TurnPWM(uint8 TurnPosition, uint8 TurnMidPosition) ;     //����ת��λ��
void Camera_Black(uint8 *point1,uint8 *rightblackedge,uint8 *leftblackedge,uint8 *centre_black) ;

int16 SpeedControl(int16 speedCount,int16 AmSpeed,uint8 speedKP,uint8 speedKI,uint8 speedKD) ;
/*********************************************************************************************************
* Description: define
*********************************************************************************************************
*/
#define  DATALINE   3    //��������
#define  DATACOUNT   160 //��������

 /**********************
 * ���ƫ����ֵ
 *********************/
#define  TURNPWMMAX     (600)
#define  TURNPWMMIN     (-600)


 /**********************
 * ���ƫ����ֵ
 *********************/
#define  SPEED_PWM_MIN    -350
#define  SPEED_PWM_MAX    350


#endif