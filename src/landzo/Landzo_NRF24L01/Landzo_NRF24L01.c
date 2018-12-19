#include "Landzo_NRF24L01.h"

// �û����� ���ͺ� ���յ�ַ��Ƶ��
uint8 TX_ADDRESS[] = {0x5a,0x77,0x75,0xcd,0x70,0xa2,0x5a};   // ����һ����̬���͵�ַ
uint8 RX_ADDRESS[] = {0x5a,0x77,0x75,0xcd,0x70,0xa2,0x5a};

// ͨ������ ���ͺ� ���յ�ַ��Ƶ��
uint8 CO_ADDRESS[] = {0x5a,0x77,0x75,0xcd,0x70,0xa2,0x5a};



//Bank0 register initialization value
uint8_t Bank0_Reg[][2]={
{0,0x0b}, //ENCRC,CRC0,PWRUP,PRX
{1,0x01},
{2,0x01},
{3,0x03},
{4,0x0f},//500uS delay AUTO RETRANSFER
{5,0x40}, //2410M
{6,0x07},	//0x0F or 0x2F:2Mbps; 0x07:1Mbps ; 0x27:250Kbps;
{7,0x07},
{8,0x00},
{9,0x00},
{12,0xc3},
{13,0xc4},
{14,0xc5},
{15,0xc6},
{17,32},
{18,32},
{19,32},
{20,32},
{21,32},
{22,32},
{23,0x00},//FIFO STATUS
{28,0x3F},
{29,0x07}
};
uint8 CHFre[] = { 2,28,55,8,34,61,14,40,67,20,46,73,26,52,10,79} ;
//-----------------------------------------
void initNRF2401(void) 
{
  vuint8 i,j;
  uint8 WriteArr[4];
  vuint8  read[30] ;
  
  NRF24_SPI() ;
  NRF_CE = 0 ;
  
  NRF24_ms(100);//delay more than 50ms.	

//********************Write Bank0 register******************
  for(i=0;i<=20;i++) 
  { RFWriteSingle((NRF_WRITE_REG|Bank0_Reg[i][0]),Bank0_Reg[i][1]);
    NRF24_ms(1) ;
  }
  
   for(i=0;i<=20;i++)
    read[i] = RFReadSingle(Bank0_Reg[i][0]); 

 // reg 10 - Rx0 addr
  NRF24_ms(1) ;
  RFWriteMulti((NRF_WRITE_REG|10),RX_ADDRESS,5);
//  NRF24_ms(1) ;
//  RFReadMulti(10,(uint8 *)&read[0],5);
 // reg 11 - Rx0 addr
  NRF24_ms(1) ;
  RFWriteMulti((NRF_WRITE_REG|11),CO_ADDRESS,5);
//  NRF24_ms(1) ;
//  RFReadMulti(10,(uint8 *)&read[0],5); 
  //REG 16 - TX addr
  NRF24_ms(1) ;
  RFWriteMulti((NRF_WRITE_REG|16),CO_ADDRESS,5);
//  NRF24_ms(1) ;
//  RFReadMulti(16,(uint8 *)&read[0],5);


//  NRF24_ms(1) ;
//  RFWriteMulti((NRF_WRITE_REG|10),CO_ADDRESS,4);
//  NRF24_ms(1) ;
//  RFReadMulti(10,(uint8 *)&read[0],4);
//  //REG 16 - TX addr
//  NRF24_ms(1) ;
//  RFWriteMulti((NRF_WRITE_REG|16),CO_ADDRESS,4);
//  NRF24_ms(1) ;
//  RFReadMulti(16,(uint8 *)&read[0],4);
  

  for(i=21;i<=22;i++)
  {NRF24_ms(1) ;
  RFWriteSingle((NRF_WRITE_REG|Bank0_Reg[i][0]),Bank0_Reg[i][1]);}
 
//  for(i=21;i<=22;i++){
//    NRF24_ms(1) ;
//    read[i] = RFReadSingle(Bank0_Reg[i][0]); }
    RFWriteSingle((NRF_WRITE_REG|Bank0_Reg[0][0]),Bank0_Reg[0][1]);
//    NRF24_ms(1) ;
//    read[0] = RFReadSingle(Bank0_Reg[0][0]);
 // SwitchToRxMode() ;
 //  SwitchToTxMode();//switch to RX mode
   NRF_CE = 1 ;

}	


/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�NRF24_SPI
*  ����˵������ʼ��SPIͨ����CE
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2015-5-15   �Ѳ���
*  ��    ע��
*************************************************************************/
void NRF24_SPI(void){
 // spi_init(SPI0,MASTER,500);
  IMIT_SPI_init();
  gpio_init(PTE25,GPO,1) ;
  gpio_init(PTA11,GPO,0) ;
//  gpio_Interrupt_init(PTD7,GPI_UP,FALLING); 
//  set_irq_priority((INT_PORTD+INC_IRQ),2);
//  setIRQadrr(INT_PORTD,PORTD_IRQHandler) ;
   gpio_Interrupt_init(PTC14, GPI_UP, FALLING); 
   set_irq_priority((INT_PORTC + INC_IRQ),5); //�������ȼ�     
   setIRQadrr(INT_PORTC,PORTC_IRQHandler);  //�����жϵ�ַ

    
}
/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�SwitchToRxMode
*  ����˵��������Ϊ���ģʽ
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2015-5-15   �Ѳ���
*  ��    ע��
*************************************************************************/

void SwitchToRxMode(void){
  // xdata
    vuint8 value;
    RFWriteSingle(NRF_FLUSH_RX,0);//flush Rx
    value=RFReadSingle(NRF_STATUS); // read register STATUS's value
    RFWriteSingle(NRF_WRITE_REG|NRF_STATUS,value);// clear RX_DR or TX_DS or MAX_RT interrupt flag
 //   value=RFReadSingle(STATUS); // read register STATUS's value

    NRF_CE=0;
    value=RFReadSingle(NRF_CONFIG); // read register CONFIG's value  //PRX
    value=value|0x01;//set bit 1
    RFWriteSingle(NRF_WRITE_REG | NRF_CONFIG, value); // Set PWR_UP bit, enable CRC(2 length) & Prim:RX.RX_DR enabled..
    NRF_CE=1;
   value=RFReadSingle(NRF_CONFIG); // read register CONFIG's value  //PRX
   value ++ ;
    //    B_M24G_TX=0;
//    B_M24G_RX=1;
}

/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�SwitchToRxMode
*  ����˵��������Ϊ���ģʽ
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2015-5-15   �Ѳ���
*  ��    ע��
*************************************************************************/
uint8 let2 ;
void SwitchToTxMode(void) {
  vuint8 value;
  NRF_CE=0;	
  RFWriteSingle(NRF_FLUSH_TX,00);//flush Tx
  value=RFReadSingle(NRF_STATUS); // read register STATUS's value
  RFWriteSingle(NRF_WRITE_REG|NRF_STATUS,value);// clear RX_DR or TX_DS or MAX_RT interrupt flag
  RFWriteSingle(NRF_WRITE_REG|NRF_EN_AA,01);// clear RX_DR or TX_DS or MAX_RT interrupt flag
  RFWriteSingle(NRF_WRITE_REG|NRF_EN_RXADDR,01);// clear RX_DR or TX_DS or MAX_RT interrupt flag

  
  value = RFReadSingle(NRF_CONFIG);	// read register CONFIG's value
  //PTX
  value &= ~(1<<0);//clear bit 1
  RFWriteSingle(NRF_WRITE_REG | NRF_CONFIG, value); // Set PWR_UP bit, enable CRC(2 length) & Prim:RX. RX_DR enabled.
  NRF_CE=1;
}

/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�SetChannelNum
*  ����˵��������ͨ��
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2015-5-15   �Ѳ���
*  ��    ע��
*************************************************************************/

void SetChannelNum(uint8 ch) {
  RFWriteSingle((uint8)(NRF_WRITE_REG|5),(uint8)(ch));
}
/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�SPI_Read_Reg
*  ����˵��:��ȡ�Ĵ�����ֵ
*  ����˵����reg����Ҫ��ļĴ���
*  �������أ���������
*  �޸�ʱ�䣺2015-6-19   �Ѳ���
*  ��    ע��
*************************************************************************/
uint8 RFReadSingle(uint8 reg){
  uint8 temp ;
  NRF_SCN = 0 ;
  NRF24_delay();
  IMIT_SPI_RW(reg) ;
  NRF24_delay();
  temp=IMIT_SPI_RW(0) ;
  NRF_SCN = 1 ;
  return temp ;
}
/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�SPI_Write_Reg
*  ����˵��:��ȡ�Ĵ�����ֵ
*  ����˵����reg����Ҫ��ļĴ���
*            value д���λ��
*  �������أ���������
*  �޸�ʱ�䣺2015-6-19   �Ѳ���
*  ��    ע��
*************************************************************************/
void RFWriteSingle(uint8 reg, uint8 value)
{
    vuint8 i , j ;
    i = reg;
    j = value ;
    NRF_SCN = 0; // CSN low, init SPI transaction
    NRF24_delay();
    IMIT_SPI_RW(reg); // select register
    NRF24_delay();
    IMIT_SPI_RW(value); // ..and write value to it..
    NRF_SCN = 1; // CSN high again
}
/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�RFWriteMulti
*  ����˵��:��ȡ�Ĵ�����ֵ
*  ����˵����reg����Ҫ��ļĴ���
*            value д���λ��
*  �������أ���������
*  �޸�ʱ�䣺2015-6-19   �Ѳ���
*  ��    ע��
*************************************************************************/
void RFReadMulti(uint8 reg, uint8 *pBuf, uint8 length){
 //   uint8 rebuf[10] ;
    uint8 LetCount ;
    NRF_SCN = 0; // CSN low, init SPI transaction
    NRF24_delay();
    IMIT_SPI_RW(reg); // select register
    NRF24_delay() ;
    for(LetCount = 0 ; LetCount < length ; LetCount++){
      *pBuf = IMIT_SPI_RW(0) ;
      pBuf ++ ;
    }
 //   spi_wr_stream(SPI0,pBuf,length,pBuf) ;
    NRF_SCN = 1; // CSN high again
  }

/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�RFWriteMulti
*  ����˵��:��ȡ�Ĵ�����ֵ
*  ����˵����reg����Ҫ��ļĴ���
*            value д���λ��
*  �������أ���������
*  �޸�ʱ�䣺2015-6-19   �Ѳ���
*  ��    ע��
*************************************************************************/

void RFWriteMulti(uint8 reg, uint8 *pBuf, uint8 length){
    uint8 LetCount ;
    NRF_SCN = 0; // CSN low, init SPI transaction
    NRF24_delay();
    IMIT_SPI_RW(reg); // select register
    NRF24_delay() ;
    for(LetCount = 0 ; LetCount < length ; LetCount++){
     IMIT_SPI_RW(*pBuf) ;
      pBuf ++ ;
    }
//    spi_wr_stream(SPI0,pBuf,length,NULL) ;
    NRF_SCN = 1; // CSN high again
  }

/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�Get_Chip_ID
*  ����˵����
*  ����˵����spin��     SPIͨ���š�
*            SPI_CFG  ģʽѡ��
*            baudKH     ������
*  �������أ���
*  �޸�ʱ�䣺2015-6-19   �Ѳ���
*  ��    ע��
*************************************************************************/
uint8 Get_Chip_ID(void)
{
//  uint8 wrbuf[4] = {0},rebuf[4] = 0;
//  spi_wr_byte(SPI0,8) ;
//  NRF_SCN = 0; // CSN low, init SPI transaction
//    spi_wr_byte(SPI0,8); // select register
//    spi_wr_stream(SPI0,wrbuf,4,rebuf) ;
//    NRF_SCN = 1; // CSN high again
 
  return  RFReadSingle(8) ;
  
}

/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�Receive_Packet
*  ����˵����read FIFO to read a packet,RX���յ�״̬λ
*  ����˵����RFRxBuff  ���յ�����ָ��
*  �������أ���
*  �޸�ʱ�䣺2015-5-15   �Ѳ���
*  ��    ע��
*************************************************************************/
uint8 Receive_Packet(uint8 *RFRxBuff){
  uint8 len,sta,fifo_sta;
	
  len = 0;
  sta = RFReadSingle(NRF_STATUS);	// read register STATUS's value
  if(sta & NRF_STATUS_RX_DR_MASK)// if receive data ready (RX_DR) interrupt
  {
    do
    {
      len = MAX_PACKET_LEN ;//RFReadSingle(NRF_R_RX_PL_WID);// read len

      if(len <= MAX_PACKET_LEN)
        RFReadMulti(NRF_RD_RX_PLOAD,RFRxBuff,len);// read receive payload from RX_FIFO buffer
      else
	RFWriteSingle(NRF_FLUSH_RX,0);//flush Rx
      fifo_sta = RFReadSingle(NRF_FIFO_STATUS);	// read register FIFO_STATUS's value
    }while((fifo_sta & NRF_FIFO_STATUS_RX_EMPTY) == 0); //while not empty
    RFWriteSingle(NRF_WRITE_REG|NRF_STATUS,sta);// clear RX_DR or TX_DS or MAX_RT interrupt flag
  }
  return len;
}

/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�CodePPMpacket
*  ����˵������������
*  ����˵����	Txbuff:packet ���������
*  	        len: packet length
*  �������أ���
*  �޸�ʱ�䣺2015-5-15   �Ѳ���
*  ��    ע��
*************************************************************************/

void CodePPMpacket(uint8 * Txbuff)
{
  uint8_t checksum = 0,j;
  
//  Txbuff[0] = 8;
//  checksum ^= Txbuff[0];
  for(j=0;j<4;j++)
  {
    Txbuff[j] = RX_ADDRESS[j];
    checksum ^= Txbuff[j];
  }
  for(j=4;j<6;j++)
  {
    Txbuff[j] = 00;
    checksum ^= Txbuff[j];
  }
  Txbuff[6] = 0x5a;
  checksum ^= Txbuff[6];
  Txbuff[7] = checksum;
}
/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�Send_Packet
*  ����˵����fill FIFO to send a packet,TX���͵�״̬λ
*  ����˵����	type: WR_TX_PLOAD or  W_TX_PAYLOAD_NOACK_CMD
*  	        pbuf: a buffer pointer
*       	len: packet length
*  �������أ���
*  �޸�ʱ�䣺2015-5-15   �Ѳ���
*  ��    ע��
*************************************************************************/

void Send_Packet(uint8 type,uint8 *pbuf,uint8 len){
  uint8 fifo_sta;

  fifo_sta = RFReadSingle(NRF_FIFO_STATUS);	// read register FIFO_STATUS's value

  if((fifo_sta&NRF_FIFO_STATUS_TX_FULL)==0)//if not full, send data 
 { 
   RFWriteSingle(NRF_FLUSH_TX,0);//flush Tx 
    NRF24_ms(1);
   RFWriteMulti(type, pbuf, len); // Writes data to buffer
 }
}


/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�newPPMsend
*  ����˵���� ��������
*  ����˵����	
*  �������أ���
*  �޸�ʱ�䣺2015-5-15   �Ѳ���
*  ��    ע��
*************************************************************************/
void newPPMsend(uint8 * Txbuffer,uint8 len)
{
  vuint8 sta;

  sta = RFReadSingle(NRF_STATUS);	// read register FIFO_STATUS's value
  if((sta&NRF_STATUS_TX_DS_MASK) || (sta&NRF_STATUS_MAX_RT_MASK))
  {
     let2 = sta ;
    RFWriteSingle(NRF_WRITE_REG|NRF_STATUS,sta);
    RFWriteSingle(NRF_FLUSH_TX,00);//flush Tx
  }
  //���͵�ǰ����
 // assemblePPMpacket();
  sta = RFReadSingle(NRF_FIFO_STATUS);
  sta ++ ;
 // Send_Packet(NRF_W_TX_PAYLOAD_NOACK,Txbuffer,len);  
  Send_Packet(NRF_WR_TX_PLOAD,Txbuffer,len); 
  sta = RFReadSingle(NRF_FIFO_STATUS);
  sta ++ ;
}

/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�CodeCheck
*  ����˵���� ����
*  ����˵����	
*  �������أ���
*  �޸�ʱ�䣺2015-5-15   �Ѳ���
*  ��    ע��
*************************************************************************/
void CodeCheck(void)
{
  static uint8 ch = 0;
  vuint8 TX_buffer[32] ;
  
  NRF24_ms(1) ;
  SwitchCFG(0);
//  NRF24_ms(1) ;
//  RFWriteMulti((NRF_WRITE_REG|16),CO_ADDRESS,4);
//  NRF24_ms(1) ;
//  RFWriteMulti((NRF_WRITE_REG|10),CO_ADDRESS,4);
//  NRF24_ms(1) ;
  RFWriteSingle((NRF_WRITE_REG|5),CHFre[ch]);
  TX_buffer[0] = RFReadSingle(5);
  ch++ ;
  if(ch> 16) ch= 0 ;
  NRF24_ms(1) ;
  TX_buffer[0] =RFReadSingle(NRF_FIFO_STATUS);
////  SwitchToTxMode() ;
//  NRF24_ms(1) ;
//  NRF_CE=0;
//  CodePPMpacket(TX_buffer);
  newPPMsend(TX_ADDRESS,7) ;
//  NRF_CE=1;
//  NRF24_ms(1) ;
//  RFWriteMulti((WRITE_REG|16),TX_ADDRESS,4);
//  SwitchToRxMode();
}
/*-----------------------------------------------------------------------
delay_1ns         : ��ʱ����
��д����          ��2013-12-15 
����޸�����      ��2013-12-15  
-----------------------------------------------------------------------*/

void NRF24_ms(uint8_t us)
{
   volatile uint16_t ii,jj,n;
   if (us<1) us=1;
   for(ii=0;ii<us;ii++) 
      for(jj=0;jj<2000;jj++);     
} 

/*-----------------------------------------------------------------------
delay_1ns         : ��ʱ����
��д����          ��2013-12-15 
����޸�����      ��2013-12-15  
-----------------------------------------------------------------------*/

void NRF24_delay(void)
{
   volatile uint16_t ii;
   for(ii=0;ii<100;ii++) 
      asm("nop");   
} 


/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�IMIT_SPI_init
*  ����˵���� ģ��SPI��ʼ��
*  ����˵����	
*  �������أ���
*  �޸�ʱ�䣺2015-5-15   �Ѳ���
*  ��    ע��
*************************************************************************/
void IMIT_SPI_init(void)
{
  gpio_init(PTE24,GPO,1) ;
  gpio_init(PTE26,GPI_UP,0) ;
  gpio_init(PTA5 ,GPO,1);
}
/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�IMIT_SPI_RW
*  ����˵���� SPI��д�����
*  ����˵����	
*  �������أ���
*  �޸�ʱ�䣺2015-5-15   �Ѳ���
*  ��    ע��
*************************************************************************/

void SPI_delay(void)
{
   volatile uint16_t ii;
   for(ii=0;ii<2;ii++) 
      asm("nop");   
}

uint8 IMIT_SPI_RW(uint8 value)
{
    uint8 bit_ctr,REvalue = 0;
    NRF_SCK = 0; // ..then set SCK low again
    SPI_delay() ;
    for(bit_ctr=0;bit_ctr<8;bit_ctr++) // output 8-bit
    {
      if(value & 0x80)
      { NRF_MOSI =1;}
      else
      { NRF_MOSI=0;}
      value = (value << 1); // shift next bit into MSB.
      NRF_SCK = 1;
      
      // if(MISO){ value =value| 0X01; } else {
  //    REvalue =REvalue& 0XFE; 
      // Set SCK high..
      REvalue <<= 1 ;
      REvalue |= NRF_MISO; // capture current MISO bit
      SPI_delay() ;
      NRF_SCK = 0; // ..then set SCK low again
      SPI_delay() ;
    }
    return REvalue ; // return read uint8
}




