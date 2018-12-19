#include  "Landzo_GyroAccelerate.h"

//==========MMA8451 �Ĵ�����ַ==================//
#define MMA8451_DSR   0x00   // Data Status Register
#define MMA8451_XOUT  0x01   // 14-bit output value X 
#define MMA8451_YOUT  0x03   // 14-bit output value Y 
#define MMA8451_ZOUT  0x05   // 14-bit output value Z
#define MMA8451_CFG   0x0E   //  XYZ_DATA_CFG Register   [1:0]scale value range 
#define MMA8451_SR    0x29   // Auto-Wake/Sleep and 
#define MMA8451_CR1   0x2A   // System Control 1 Registe
//[5:3]bits select the Output Data Rate (ODR) for acceleration samples 

//=========MMA8451 ���ܲ���==================//
#define MMA8451_MODE    0x11     // DR = 50 Hz  F_READ=0   ACTIVE=1
#define MMA8451_SCAL    0x00    // 0x00 2g   0x01  4g   0x10  8g
#define MMA8451_WADDR   0X38    //write address   [7:1]=0x1c   [0]=0   [7:0]=0x38
#define MMA8451_RADDR   0X39    //read address    [7:1]=0x1c   [0]=1    [7:0]=0x39

/*-----------------------------------------------------------------------
delay_1ns         : ��ʱ����
��д����          ��2013-12-15 
����޸�����      ��2013-12-15  
-----------------------------------------------------------------------*/

void IIC_MMA8451_Delay_ms(uint8_t ms)
{
  volatile uint16_t ii,jj,n;
  if (ms<1) ms=1;
  for(ii=0;ii<ms;ii++)
    //  for(jj=0;jj<1335;jj++);     //16MHz--1ms
    //for(jj=0;jj<4005;jj++);    //48MHz--1ms  
    //for(jj=0;jj<5341;jj++);    //64MHz--1ms  
    for(jj=0;jj<18200;jj++);     //200MHz--1ms  
} 


/*-----------------------------------------------------------------------
IIC_MMA8451_Delay_1us         : ��ʱ����
��д����          ��2013-12-15  
����޸�����      ��2013-12-15   
-----------------------------------------------------------------------*/

void IIC_MMA8451_Delay_1us(uint8_t us)                 //1us��ʱ����
{
  volatile uint8_t i ,j ;
  if(us < 1 )  us = 1 ;
  for(i=0;i<us;i++) 
  {
    for(j = 0 ;j < 15 ;j ++);
    
  }
  
}



//--------------------------------------------------------------------------------------------------
// �������ƣ� IIC_MMA8451_Start()
// �������ܣ� ����I2C�����ӳ���
//--------------------------------------------------------------------------------------------------
void IIC_MMA8451_Start(void)
{ 
  MMA8451_SDAO = 1;  
  IIC_MMA8451_Delay_1us(MMA8451_DELAY);      // ��ʱ1us 
  MMA8451_CLK = 1;
  IIC_MMA8451_Delay_1us(MMA8451_DELAY);      // ��ʱ5us 
  MMA8451_SDAO = 0;
  IIC_MMA8451_Delay_1us(MMA8451_DELAY);  
  MMA8451_CLK = 0;
  IIC_MMA8451_Delay_1us(MMA8451_DELAY);
}
//--------------------------------------------------------------------------------------------------
// �������ƣ� IIC_MMA8451_Stop()
// �������ܣ� ֹͣI2C�������ݴ����ӳ���
//--------------------------------------------------------------------------------------------------
void IIC_MMA8451_Stop(void)
{ 
  MMA8451_SDAO = 0;   	   //ʱ�ӱ��ָߣ������ߴӵ͵���һ�����䣬I2Cͨ��ֹͣ
  IIC_MMA8451_Delay_1us(MMA8451_DELAY);      // ��ʱ1us 
  MMA8451_CLK = 1;
  IIC_MMA8451_Delay_1us(MMA8451_DELAY);
  MMA8451_SDAO = 1;
  IIC_MMA8451_Delay_1us(MMA8451_DELAY);
  MMA8451_CLK = 0;
  IIC_MMA8451_Delay_1us(MMA8451_DELAY);
}
//--------------------------------------------------------------------------------------------------
// �������ƣ� slave_ACK
// �������ܣ� �ӻ�����Ӧ��λ�ӳ���
//�޸�ʱ�䣺  2014-09-09   18:48
//�޸��� ��   yu
//--------------------------------------------------------------------------------------------------
void IIC_MMA8451_Slave_ACK(void)
{
  MMA8451_SDAO = 0; 
  IIC_MMA8451_Delay_1us(MMA8451_DELAY);      // ��ʱ5us 
  MMA8451_CLK = 1;
  IIC_MMA8451_Delay_1us(MMA8451_DELAY);			
  MMA8451_CLK = 0;
  IIC_MMA8451_Delay_1us(MMA8451_DELAY);      // ��ʱ5us 
  MMA8451_SDAO = 1;
  IIC_MMA8451_Delay_1us(MMA8451_DELAY);
}
//--------------------------------------------------------------------------------------------------
// �������ƣ� IIC_MMA8451_Slave_NOACK
// �������ܣ� �ӻ����ͷ�Ӧ��λ�ӳ�����ʹ���ݴ�����̽���
//�޸�ʱ�䣺  2014-09-09   18:48
//�޸��� ��   yu
//--------------------------------------------------------------------------------------------------
void IIC_MMA8451_Slave_NOACK(void)
{ 
  MMA8451_SDAO = 1;  
  IIC_MMA8451_Delay_1us(MMA8451_DELAY);      // ��ʱ5us 
  MMA8451_CLK = 1;
  IIC_MMA8451_Delay_1us(MMA8451_DELAY);
  MMA8451_CLK = 0;
  IIC_MMA8451_Delay_1us(MMA8451_DELAY);      // ��ʱ5us 
  MMA8451_SDAO = 0;
  IIC_MMA8451_Delay_1us(MMA8451_DELAY);      // ��ʱ5us 
}
//--------------------------------------------------------------------------------------------------
// �������ƣ� IIC_MMA8451_Check_ACK
// �������ܣ� ����Ӧ��λ����ӳ�����ʹ���ݴ�����̽���
//--------------------------------------------------------------------------------------------------
uint8_t IIC_MMA8451_Check_ACK(void)
{ 
  uint8_t check ;
  
  MMA8451_SDAO = 1; 
  MMA8451_DDRA = 0 ;
  MMA8451_SDAI = 1 ;
  
  IIC_MMA8451_Delay_1us(MMA8451_DELAY);      // ��ʱ5us 
  MMA8451_CLK = 1;
  check = 0;
  if(MMA8451_SDAI == 1)    // ��BFSDA=1 ������Ӧ����λ��Ӧ���־F0
    check = 1;
  IIC_MMA8451_Delay_1us(MMA8451_DELAY);      // ��ʱ1us 
  MMA8451_CLK = 0;     
  MMA8451_DDRA = 1 ;
  MMA8451_SDAO = 1 ;
  return  check ;
}

//--------------------------------------------------------------------------------------------------
// �������ƣ� IIC_MMA8451_SendByte
// ��ڲ����� ch
// �������ܣ� ����һ���ֽ�
//--------------------------------------------------------------------------------------------------
void IIC_MMA8451_SendByte(uint8_t ch)
{ 
  uint8_t n=8;     // ��BFSDA�Ϸ���һλ�����ֽڣ�����λ
  MMA8451_DDRA=1;
  while(n--)
  { 
    if((ch&0x80) == 0x80)    // ��Ҫ���͵��������λΪ1����λ1
    {
      MMA8451_SDAO = 1;    // ����λ1
      IIC_MMA8451_Delay_1us(MMA8451_DELAY);
      MMA8451_CLK = 1;
      IIC_MMA8451_Delay_1us(MMA8451_DELAY);
      MMA8451_CLK = 0;  
      IIC_MMA8451_Delay_1us(MMA8451_DELAY);
      
    }
    else
    {  
      MMA8451_SDAO = 0;    // ������λ0
      IIC_MMA8451_Delay_1us(MMA8451_DELAY);
      MMA8451_CLK = 1;
      IIC_MMA8451_Delay_1us(MMA8451_DELAY);
      MMA8451_CLK = 0;  
      IIC_MMA8451_Delay_1us(MMA8451_DELAY);
    }
    ch = ch<<1;    // ��������һλ
  }
}
//--------------------------------------------------------------------------------------------------
// �������ƣ� IIC_MMA8451_ReceiveByte
// ���ؽ��յ�����
// �������ܣ� ����һ�ֽ��ӳ���
//--------------------------------------------------------------------------------------------------
uint8_t IIC_MMA8451_ReceiveByte(void)
{
  uint8_t n=8;    // ��BFSDA���϶�ȡһ�������ֽڣ�����λ
  uint8_t tdata = 0;
  MMA8451_DDRA = 0 ;
  while(n--)
  {                
    MMA8451_SDAI = 1;
    IIC_MMA8451_Delay_1us(MMA8451_DELAY);
    MMA8451_CLK=0;
    IIC_MMA8451_Delay_1us(MMA8451_DELAY);
    MMA8451_CLK = 1;
    IIC_MMA8451_Delay_1us(MMA8451_DELAY);
    tdata = tdata<<1;    // ����һλ����_crol_(temp,1)
    if(MMA8451_SDAI == 1)
      tdata = tdata|0x01;    // �����յ���λΪ1�������ݵ����һλ��1
    else 
      tdata = tdata&0xfe;    // �������ݵ����һλ��0      
  }
  MMA8451_CLK=0;  
  MMA8451_DDRA = 1;
  return(tdata);
}

/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�IIC_WriteAddr
*  ����˵����д��һ���ֽ����ݵ�I2C�豸ָ���Ĵ�����ַ
*  ����˵����SlaveID     7λ�ӻ���ַ
*            Addr        �ӻ��ļĴ�����ַ
*            Data        ����
*  �������أ���
*  �޸�ʱ�䣺2012-1-20
*  ��    ע��
*************************************************************************/

uint8_t IIC_MMA8451_WriteAddr(uint8 slave_add, uint8 Addr, uint8 Data)
{
  uint8_t check = 1;
  
  IIC_MMA8451_Start();                // ����I2C
  
  IIC_MMA8451_SendByte(slave_add);     // ���͵�ַλ
  check = IIC_MMA8451_Check_ACK();                // ���Ӧ��λ  
  //uart_putchar(UART0,check);
  if(check == 1)
  { 
    return IICEorr;    // ����Ӧ���������������ѻ����ô����־λSystemError
  }
  
  IIC_MMA8451_SendByte(Addr);     
  check= IIC_MMA8451_Check_ACK();    // ���Ӧ��λ
  if (check == 1)
  {
    return IICEorr;    // ����Ӧ���������������ѻ����ô����־λSystemError
  }
  
  IIC_MMA8451_SendByte(Data);     
  check= IIC_MMA8451_Check_ACK();    // ���Ӧ��λ
  if (check == 1)
  {
    return IICEorr;    // ����Ӧ���������������ѻ����ô����־λSystemError
  }
  
  IIC_MMA8451_Stop();         // ȫ��������ֹͣ 
  
  return IICOK;
}

/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�I2C_ReadAddr
*  ����˵������ȡI2C�豸ָ����ַ�Ĵ���������
*  ����˵����SlaveID     7λ�ӻ���ַ
*            Addr        �ӻ��ļĴ�����ַ
*  �������أ��ӻ��Ĵ���������
*  �޸�ʱ�䣺2012-1-20
*  ��    ע��
*************************************************************************/
uint8_t IIC_MMA8451_ReadAddr_byte(uint8_t slave_add, uint8_t Addr, uint8_t *rece_data)
{
  uint8_t check;
  
  IIC_MMA8451_Start();                                       //ST
  IIC_MMA8451_SendByte(MMA8451_WADDR);                        // MMA8451_WADDR  
  IIC_MMA8451_Delay_1us(MMA8451_DELAY);      // ��ʱ5us 
  check =IIC_MMA8451_Check_ACK();
  //uart_putchar(UART0,check);
  if(check == 1)
  {
    return IICEorr ;
  }  
  
  IIC_MMA8451_SendByte(Addr);                                 //REGISTER ADDR             
  IIC_MMA8451_Delay_1us(MMA8451_DELAY);      // ��ʱ5us 
  check =IIC_MMA8451_Check_ACK();
  if(check == 1)
  {
    return IICEorr ;
  }
  
  IIC_MMA8451_Start();  
  
  IIC_MMA8451_SendByte(slave_add);
  IIC_MMA8451_Delay_1us(MMA8451_DELAY);      // ��ʱ1us 
  check =IIC_MMA8451_Check_ACK();
  if(check == 1)
  {
    return IICEorr ;
  } 
  
  *rece_data=IIC_MMA8451_ReceiveByte();
  
  IIC_MMA8451_Slave_NOACK();    // �յ����һ���ֽں���һ����Ӧ��λ
  
  IIC_MMA8451_Stop();
  return IICOK;
  
}

/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�I2C_ReadAddr
*  ����˵������ȡI2C�豸ָ����ַ�Ĵ���������
*  ����˵����SlaveID     7λ�ӻ���ַ
*            Addr        �ӻ��ļĴ�����ַ
*  �������أ��ӻ��Ĵ���������
*  �޸�ʱ�䣺2012-1-20
*  ��    ע��
*************************************************************************/
uint8_t IIC_MMA8451_ReadAddr(uint8_t slave_add, uint8_t Addr, uint8_t *rece_data, uint16_t n)
{
  uint8_t receive_da,check;
  uint16_t i=0;
  uint8_t *rece_data_buff ;
  rece_data_buff = rece_data ;
  
  IIC_MMA8451_Start();                                       //ST
  IIC_MMA8451_SendByte(MMA8451_WADDR);                        // MMA8451_WADDR  
  IIC_MMA8451_Delay_1us(MMA8451_DELAY);      // ��ʱ1us 
  check =IIC_MMA8451_Check_ACK();
  if(check == 1)
  {
    return IICEorr ;
  }  
  
  IIC_MMA8451_SendByte(Addr);                                 //REGISTER ADDR             
  IIC_MMA8451_Delay_1us(MMA8451_DELAY);      // ��ʱ1us 
  check =IIC_MMA8451_Check_ACK();
  if(check == 1)
  {
    return IICEorr ;
  }
  
  IIC_MMA8451_Start();  
  
  IIC_MMA8451_SendByte(slave_add);
  IIC_MMA8451_Delay_1us(MMA8451_DELAY);      // ��ʱ1us 
  check =IIC_MMA8451_Check_ACK();
  if(check == 1)
  {
    return IICEorr ;
  } 
  
  for(;n > 1;n--)
  { 
    receive_da=IIC_MMA8451_ReceiveByte();
    rece_data_buff[i++]=receive_da;
    IIC_MMA8451_Slave_ACK();    // �յ�һ���ֽں���һ��Ӧ��λ    
  }
  
  receive_da=IIC_MMA8451_ReceiveByte();
  rece_data_buff[i++]=receive_da;
  IIC_MMA8451_Slave_NOACK();    // �յ����һ���ֽں���һ����Ӧ��λ
  
  IIC_MMA8451_Stop();
  return IICOK;
  
}

//--------------------------------------------------------------------------------------------------
// �������ƣ� LandzoIICEEROM
// ��ڲ����� 
// �������ܣ� ͨ��IIC����landzo03ʹ����ͷ��������ź� ,read address :11011101b 0XDD, 
//             writre address : 11011100b,OXDC��
//--------------------------------------------------------------------------------------------------
uint8_t LandzoMMA8451_init(void)
{
  uint8_t LandzoOK ;
  
  gpio_init (PTB7, GPO,HIGH);
  gpio_init (PTB10, GPO,HIGH);
  
  LandzoOK = IIC_MMA8451_WriteAddr(MMA8451_WADDR, MMA8451_CFG, MMA8451_SCAL);
  IIC_MMA8451_Delay_ms(10) ;                    //�ӳ�100us
  if(!LandzoOK)  return IICEorr; 
  
  LandzoOK = IIC_MMA8451_WriteAddr(MMA8451_WADDR, MMA8451_CR1, MMA8451_MODE);
  IIC_MMA8451_Delay_ms(10) ;                    //�ӳ�100us
  if(!LandzoOK)  return IICEorr; 
  
  return  IICOK ;  
  
}

/*********************************************************** 
�������ƣ�AngleAcceleration_init   
�������ܣ����ٶȽǶȴ�������ʼ������
��ڲ�����
���ڲ������� 
�� ע�� 
***********************************************************/
void AngleAcceleration_init(void)
{
     adc_init(ADC0, AD8) ;     //PTB0
     adc_init(ADC0, AD9) ;     //PTB1
     adc_init(ADC0, AD12) ;     //PTB2
     adc_init(ADC0, AD13) ;     //PTB3
//     adc_init(ADC1, AD14) ;     //PTB10
//     adc_init(ADC1, AD15) ;     //PTB11  
}

/*********************************************************** 
�������ƣ�AngleAcceleration_AD   
�������ܣ����ٶȽǶȴ�����AD�ɼ�
��ڲ�����
���ڲ������� 
�� ע�� 
***********************************************************/
uint8 AngleAcceleration_AD(uint16_t *AdColle,uint8_t Count)
{
   uint8  BCount ;
   BCount = Count ;      
     AdColle[0] += ad_sum(ADC0,AD9, ADC_12bit, ADCOUT) ;  //AR2
     AdColle[1] += ad_sum(ADC0, AD8, ADC_12bit, ADCOUT) ;  //AR1
  //   AdColle[5] += ad_sum(ADC1, AD12, ADC_12bit, ADCOUT) ;  //AR3
  //   AdColle[0] += ad_sum(ADC1,AD13, ADC_12bit, ADCOUT) ;  //ZGԴ����
     AdColle[2] += ad_sum(ADC0, AD12, ADC_12bit, ADCOUT) ;  //YGԴ����
     AdColle[3] += ad_sum(ADC0, AD13, ADC_12bit, ADCOUT) ;  //xGԴ���� 
     
     return (BCount+ADCOUT) ;//ADCOUT==5;  
   
}

/*********************************************************** 
�������ƣ�AAnglePrintUart 
�������ܣ�
��ڲ�����
���ڲ������� 
�� ע�� 
***********************************************************/
void AAnglePrintUart(uint16 * angleprint,uint8 *count){
  uint8 i;
  uint8 uartCRC = 0;
  uint16 uartAD ;
  for(i = 0 ; i < 4 ;i ++){
    uartAD = angleprint[i]/(*count) ;
    uart_putchar (UART0, uartAD) ;
    uart_putchar (UART0, uartAD>>8) ;
    uartCRC += (uint8)uartAD + (uint8)(uartAD>>8);
    angleprint[i] = 0 ;
  }
  *count = 0 ;
  uart_putchar (UART0, uartCRC) ;
}