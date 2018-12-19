
/***********************************************************
 * �ļ���       ��K6x_uart.h
 * ˵��         �����ڳ�ʼ��
 


 *��̳          ��http://www.landzo.cn
 * ��汾       ��V2.0
 *ʱ��          ��15.5.26
************************************************************/

#ifndef __K6X_UART_H__
#define __K6X_UART_H__

typedef enum  UARTn
{
    //��ʼ��Ĭ������       --TXD--      --RXD--     ���Ը�������ͨ��������<<pin_cfg.h>>�����޸� uart_init
    UART0,    //           PTD7         PTD6
    UART1,    //           PTC4         PTC3
    UART2,    //           PTD3         PTD2
    UART3,    //           PTC17        PTC16
    UART4,    //           PTE24        PTE25
    UART5     //           PTE8         PTE9
} UARTn;

extern volatile struct UART_MemMap *UARTx[6];
/********************************************************************/



void uart_init (UARTn uratn, uint32 baud);  //��ʼ��uartxģ��

char uart_getchar   (UARTn);  //���޵ȴ�����1���ֽ�

char uart_query (UARTn uratn);  //��ѯ�Ƿ���ܵ�һ���ֽ�
void uart_putchar(UARTn, char ch); //����1���ֽ�
void uart_sendN(UARTn , uint8_t *buff, uint16_t len); //����n���ֽ�
void uart_sendStr(UARTn , const uint8_t *str); //�����ַ���

void uart_irq_EN(UARTn);//�����ڽ����ж�
void uart_irq_DIS(UARTn);//�ش��ڽ����ж�

void uart_DMA_init (UARTn uratn, uint32_t baud); //��ʼ��DMAUartxģ��

#define UART_IRQ_EN(UARTn)   UART_C2_REG(UARTx[UARTn])|=UART_C2_RIE_MASK; enable_irq((UARTn<<1)+(INT_UART0_RX_TX+INC_IRQ))     //�궨�忪���ڽ����ж�
#define UART_IRQ_DIS(UARTn)  UART_C2_REG(UARTx[UARTn])&=~UART_C2_RIE_MASK; disable_irq((UARTn<<1)+(INT_UART0_RX_TX+INC_IRQ))   //�궨��ؽ������ŵ�IRQ�ж�




/********************************************************************/

#endif /* __UART_H__ */
