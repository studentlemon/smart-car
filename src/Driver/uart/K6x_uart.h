
/***********************************************************
 * 文件名       ：K6x_uart.h
 * 说明         ：串口初始化
 


 *论坛          ：http://www.landzo.cn
 * 库版本       ：V2.0
 *时间          ：15.5.26
************************************************************/

#ifndef __K6X_UART_H__
#define __K6X_UART_H__

typedef enum  UARTn
{
    //初始化默认配置       --TXD--      --RXD--     可以复用其他通道，请在<<pin_cfg.h>>自行修改 uart_init
    UART0,    //           PTD7         PTD6
    UART1,    //           PTC4         PTC3
    UART2,    //           PTD3         PTD2
    UART3,    //           PTC17        PTC16
    UART4,    //           PTE24        PTE25
    UART5     //           PTE8         PTE9
} UARTn;

extern volatile struct UART_MemMap *UARTx[6];
/********************************************************************/



void uart_init (UARTn uratn, uint32 baud);  //初始化uartx模块

char uart_getchar   (UARTn);  //无限等待接受1个字节

char uart_query (UARTn uratn);  //查询是否接受到一个字节
void uart_putchar(UARTn, char ch); //发送1个字节
void uart_sendN(UARTn , uint8_t *buff, uint16_t len); //发送n个字节
void uart_sendStr(UARTn , const uint8_t *str); //发送字符串

void uart_irq_EN(UARTn);//开串口接收中断
void uart_irq_DIS(UARTn);//关串口接收中断

void uart_DMA_init (UARTn uratn, uint32_t baud); //初始化DMAUartx模块

#define UART_IRQ_EN(UARTn)   UART_C2_REG(UARTx[UARTn])|=UART_C2_RIE_MASK; enable_irq((UARTn<<1)+(INT_UART0_RX_TX+INC_IRQ))     //宏定义开串口接收中断
#define UART_IRQ_DIS(UARTn)  UART_C2_REG(UARTx[UARTn])&=~UART_C2_RIE_MASK; disable_irq((UARTn<<1)+(INT_UART0_RX_TX+INC_IRQ))   //宏定义关接收引脚的IRQ中断




/********************************************************************/

#endif /* __UART_H__ */
