/***********************************************************
 * �ļ���       ��K6x_gpio.c
 * ˵��         ��IO�˿�Ӧ�ú���
 


 *��̳          ��http://www.landzo.cn
 *��汾        ��V2.0
 *ʱ��          ��15.5.26
************************************************************/
/*
 * ����ͷ�ļ�
 */
#include "common.h"
#include "K6x_gpio.h"

GPIO_MemMapPtr GPIOX[5] = {PTA_BASE_PTR, PTB_BASE_PTR, PTC_BASE_PTR, PTD_BASE_PTR, PTE_BASE_PTR}; 
PORT_MemMapPtr PTX[5] = {PORTA_BASE_PTR, PORTB_BASE_PTR, PORTC_BASE_PTR, PORTD_BASE_PTR, PORTE_BASE_PTR};

/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�gpio_enable_port
*  ����˵������������GPIO�˿ڵ�ʱ�ӡ� ���߲��������á�
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2015-5-15   �Ѳ���
*  ��    ע�����ݴ�ѧ������
*************************************************************************/
void gpio_enable_port (void)
{
 	  SIM_SCGC5 |=   SIM_SCGC5_PORTA_MASK \
	               | SIM_SCGC5_PORTB_MASK \
	               | SIM_SCGC5_PORTC_MASK \
	               | SIM_SCGC5_PORTD_MASK \
	               | SIM_SCGC5_PORTE_MASK;
}
/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�gpio_Interrupt_init
*  ����˵������ʼ��GPIO�ж�Դ
*  ����˵����PTxn        �˿ں�
*            GPIO_CFG    �˿�״̬
*            mode        �ж�״̬ 
*  �������أ���
*  �޸�ʱ�䣺2015-5-15   �Ѳ���
*  ��    ע��
*************************************************************************/
void gpio_Interrupt_init(PTxn ptxn, GPIO_CFG cfg, uint32 mode) 
{
  uint8  px;
  uint32 altcfg ;
  if((cfg == GPI)||(cfg == GPI_DOWN)||(cfg == GPI_UP))
  {
    px = ptxn>> 5 ;   
    altcfg= cfg + ALT1 + mode ;
    port_init(ptxn,altcfg);
    GPIO_PDDR_REG(GPIOX[px]) &= ~(1 << (ptxn&0x1f));  //���ö˿ڷ���Ϊ���� 
    enable_irq(px+(INT_PORTA +INC_IRQ));
    
  }
}
/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�gpio_init
*  ����˵������ʼ��gpio
*  ����˵����PTxn        �˿ں�
*            GPIO_CFG    �˿�״̬
*            uint8       �������״̬ 1 ��0
*  �������أ���
*  �޸�ʱ�䣺2015-5-15   �Ѳ���
*  ��    ע��
*************************************************************************/
void gpio_init (PTxn ptxn, GPIO_CFG cfg, uint8 sata)
{ 
  vuint32 PCRcfg;
//�˿ڷ���������뻹�����
    if( (cfg  == GPI) || (cfg == GPI_UP) || (cfg == GPI_DOWN) )
    {
        PCRcfg =cfg+ALT1 ;
       // le = cfg ;
        port_init(ptxn,PCRcfg);
        GPIO_PDDR_REG(GPIOX[ptxn>> 5]) &= ~(1 << (ptxn&0x1f));  //���ö˿ڷ���Ϊ���� 
    }
    else
    {  port_alt(ptxn,ALT1) ;  
      //���ö˿ڷ���Ϊ���
        GPIO_PDDR_REG(GPIOX[ptxn>> 5]) |= (1 << (ptxn&0x1f));        // GPIO PDDR �ܽź� ��1������Ӧ�ܽ�����Ϊ�˿ڷ������
        //�˿��������/        
        if(sata == 0){     
            GPIO_PDOR_REG(GPIOX[ptxn>> 5]) &= ~(1 << (ptxn&0x1f));   // GPIO PDOR �ܽź� ��0������Ӧ�ܽ�����Ϊ�˿�����͵�ƽ
         }else{
            GPIO_PDOR_REG(GPIOX[ptxn>> 5])  |= (1 << (ptxn&0x1f));   // GPIO PDOR �ܽź� ��1������Ӧ�ܽ�����Ϊ�˿�����ߵ�ƽ
        }
    }
}



/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�gpio_set
*  ����˵������������״̬
*  ����˵����PTxn        �˿ں�
*            uint8       �������״̬ 1 ��0
*  �������أ���
*  �޸�ʱ�䣺2015-5-15   �Ѳ���
*  ��    ע��
*************************************************************************/
void gpio_set (PTxn ptxn,uint8 sata){
  if(sata) GPIO_PDOR_REG(GPIOX[ptxn>> 5])  |= (1 << (ptxn&0x1f));   // GPIO PDOR �ܽź� ��1������Ӧ�ܽ�����Ϊ�˿�����ߵ�ƽ
   else    GPIO_PDOR_REG(GPIOX[ptxn>> 5]) &= ~(1 << (ptxn&0x1f));   // GPIO PDOR �ܽź� ��0������Ӧ�ܽ�����Ϊ�˿�����͵�ƽ 
}
/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�gpio_turn
*  ����˵�������ŷ�ת
*  ����˵����PTxn        �˿ں�
*  �������أ���
*  �޸�ʱ�䣺2015-5-15   �Ѳ���
*  ��    ע��
*************************************************************************/
void gpio_turn(PTxn ptxn){
  GPIO_PTOR_REG(GPIOX[ptxn>> 5]) |= (1 << (ptxn&0x1f));   // GPIO PTOR �ܽź�  
}

/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�gpio_get
*  ����˵�������ŷ�ת
*  ����˵����PTxn        �˿ں�
*  �������أ���
*  �޸�ʱ�䣺2015-5-15   �Ѳ���
*  ��    ע��
*************************************************************************/
uint8 gpio_get (PTxn ptxn){
  return ((GPIO_PDIR_REG(GPIOX[ptxn>> 5])>>(ptxn&0x1f)) &0x01);   // GPIO PDIR �ܽź�  
}
               
