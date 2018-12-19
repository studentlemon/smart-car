
#ifndef _NRF24L21_H
#define _NRF24L21_H

#include "include.h"


/*******
�Ĵ������ƶ���
********/
#define  NRF_SCN                   PTE25_OUT
#define  NRF_CE                    PTA11_OUT
#define  NRF_SCK                   PTE24_OUT
#define  NRF_MISO                  PTE26_INT        //NRF OUT  MCU INPUT
#define  NRF_MOSI                  PTA5_OUT        //NRF INPUT MCU OUTPUT

#define MAX_PACKET_LEN            32              // max value is 32
/*******
�Ĵ������ƶ���
********/
/* STATUS Bit Fields */
#define NRF_STATUS_RX_DR_MASK           0x40u 
#define NRF_STATUS_TX_DS_MASK           0x20u
#define NRF_STATUS_MAX_RT_MASK          0x10u
#define NRF_STATUS_RX_P_NO_SHIFT        1
#define NRF_STATUS_RX_P_NO_MASK         0x0Eu
#define NRF_STATUS_RX_P_NO(x)           (((uint8_t)(((uint32_t)(x))<<STATUS_RX_P_NO_SHIFT))&STATUS_RX_P_NO_MASK)
#define NRF_STATUS_TX_FULL              0x01u
/* CONFIG bit Fields */
#define NRF_CONFIG_PRIM_RX_MASK         0x01u
#define NRF_CONFIG_PWR_UP_MASK          0x02u
#define NRF_CONFIG_CRCO_MASK            0x04u
#define NRF_CONFIG_EN_CRC_MASK          0x08u
#define NRF_CONFIG_MASK_MAX_RT_MASK     0x10u
#define NRF_CONFIG_MASK_TX_DS_MASK      0x20u
#define NRF_CONFIG_MASK_RX_DS_MASK      0x40u
/* OBSERVE_TX bit Fields */
#define NRF_OBSERVE_TX_ARC_CNT_MASK     0x0Fu
#define NRF_OBSERVE_TX_ARC_CNT_SHIFT    0
#define NRF_OBSERVE_TX_PLOS_CNT_MASK    0xF0u
#define NRF_OBSERVE_TX_PLOS_CNT_SHIFT   4
  //FIFO_STATUS
#define NRF_FIFO_STATUS_TX_REUSE        0x40
#define NRF_FIFO_STATUS_TX_FULL         0x20
#define NRF_FIFO_STATUS_TX_EMPTY        0x10

#define NRF_FIFO_STATUS_RX_FULL         0x02
#define NRF_FIFO_STATUS_RX_EMPTY        0x01
//********************************************************************************************************************// 
/* SPI(NRFF24L01) ָ�� */
#define NRF_READ_REG                    0x00   // �����üĴ���
#define NRF_WRITE_REG                   0x20   // д���üĴ���
#define NRF_RD_RX_PLOAD                 0x61   // ��ȡRX FIFO�е�����
#define NRF_WR_TX_PLOAD                 0xA0   // ��TX FIFO��д������
#define NRF_FLUSH_TX                    0xE1   // ���TX FIFO�е����� Ӧ���ڷ���ģʽ��
#define NRF_FLUSH_RX                    0xE2   // ���RX FIFO�е����� Ӧ���ڽ���ģʽ��
#define NRF_REUSE_TX_PL                 0xE3   // ����ʹ����һ����Ч����
#define NRF_NOP                         0xFF   // ����
//********************************************************************************************************************// 
/* register define */
#define NRF_CONFIG              0x00  //���÷���״̬��CRCУ��ģʽ�Լ����շ�״̬��Ӧ��ʽ
#define NRF_EN_AA               0x01  //�Զ�Ӧ��������
#define NRF_EN_RXADDR           0x02  //�����ŵ�����
#define NRF_SETUP_AW            0x03  //�շ���ַ�������
#define NRF_SETUP_RETR          0x04  //�Զ��ط�����������
#define NRF_RF_CH               0x05  //����Ƶ���趨
#define NRF_RF_SETUP            0x06
#define NRF_STATUS              0x07
#define NRF_OBSERVE_TX          0x08 //���ͼ��Ĵ���
#define NRF_CD                  0x09
#define NRF_RX_ADDR_P0          0x0A
#define NRF_RX_ADDR_P1          0x0B
#define NRF_RX_ADDR_P2          0x0C
#define NRF_RX_ADDR_P3          0x0D
#define NRF_RX_ADDR_P4          0x0E
#define NRF_RX_ADDR_P5          0x0F
#define NRF_TX_ADDR             0x10
#define NRF_RX_PW_P0            0x11
#define NRF_RX_PW_P1            0x12
#define NRF_RX_PW_P2            0x13
#define NRF_RX_PW_P3            0x14
#define NRF_RX_PW_P4            0x15
#define NRF_RX_PW_P5            0x16
#define NRF_FIFO_STATUS         0x17





void NRF24_delay(void) ;
void initNRF2401(void) ;     //��ʼ��BK24
uint8 Get_Chip_ID(void) ;
void NRF24_SPI(void) ;          //SPI����
void NRF24_ms(uint8_t ms) ;      //��ʱ����
void SwitchCFG(uint8 blank) ;   //blankģ���л�
uint8 RFReadSingle(uint8 reg) ;  //���Ĵ���ֵ
void RFWriteSingle(uint8 reg, uint8 value) ;  //�Ĵ���ֵд�뵥���ֽ�
void RFWriteMulti(uint8 reg, uint8 *pBuf, uint8 length) ;   //�Ĵ���д�����ֽ�
void SwitchToRxMode(void); 
void RFReadMulti(uint8 reg, uint8 *pBuf, uint8 length) ;
void Send_Packet(uint8 type,uint8 *pbuf,uint8 len) ;
uint8 Receive_Packet(uint8 *RFRxBuff) ;

void CodeCheck(void) ;
uint8 IMIT_SPI_RW(uint8 value) ;
void IMIT_SPI_init(void);
void SwitchToTxMode(void) ;

void Datacheck(uint8 *rebuff ,uint16 * txbuff) ;   //���ݽ���
void newPPMsend(uint8 * Txbuffer,uint8 len) ;
#endif

