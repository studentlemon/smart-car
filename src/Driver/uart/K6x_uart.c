/***********************************************************
 * �ļ���       ��K6x_uart.c
 * ˵��         �����ڳ�ʼ��
 * ����         ��buaa


 *��̳          ��http://www.landzo.cn
 * ��汾       ��V2.0
 *ʱ��          ��15.5.26
************************************************************/

#include "common.h"
#include "K6x_uart.h"


volatile struct UART_MemMap *UARTx[6] = {UART0_BASE_PTR, UART1_BASE_PTR, UART2_BASE_PTR, UART3_BASE_PTR, UART4_BASE_PTR, UART5_BASE_PTR}; //�������ָ�����鱣�� UARTx �ĵ�ַ

/*************************************************************************
*                             �������պ����ѧ
*
*  �������ƣ�uart_DMA_init
*  ����˵������ʼ�����ڣ����ò�����
*  ����˵����UARTn       ģ��ţ�UART0~UART5��
*            baud        �����ʣ���9600��19200��56000��115200��
*  �������أ���
*  �޸�ʱ�䣺2014-1-20
*  ��    ע���ڹٷ��������޸�
*************************************************************************/
void uart_DMA_init (UARTn uratn, uint32_t baud)
{
    register uint16_t sbr, brfa;
    uint8_t temp;
    uint32_t sysclk;     //ʱ��

    
    switch(uratn)
    {
    case UART0:
        if(UART0_RX == PTA1)
          port_alt(UART0_RX,ALT2);
        else 
          port_alt(UART0_RX,ALT3);

        if(UART0_TX == PTA2)
            port_alt(UART0_TX,ALT2);
        else 
            port_alt(UART0_TX,ALT3);

        SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;      //ʹ�� UARTn ʱ��
        break;

    case UART1:
        port_alt(UART1_RX,ALT3);
        port_alt(UART1_TX,ALT3);
        SIM_SCGC4 |= SIM_SCGC4_UART1_MASK;
        break;

    case UART2:
        port_alt(UART2_RX,ALT3);
        port_alt(UART2_TX,ALT3);
        SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;
        break;

    case UART3:
        port_alt(UART3_RX,ALT3);
        port_alt(UART3_TX,ALT3);
        SIM_SCGC4 |= SIM_SCGC4_UART3_MASK;
        break;

    case UART4:
        port_alt(UART4_RX,ALT3);
        port_alt(UART4_TX,ALT3);
        SIM_SCGC1 |= SIM_SCGC1_UART4_MASK;
        break;

    case UART5:
        port_alt(UART5_RX,ALT3);
        port_alt(UART5_TX,ALT3);

        SIM_SCGC1 |= SIM_SCGC1_UART5_MASK;
        break;
    default:
        break;
    }

    //���õ�ʱ��Ӧ�ý�ֹ���ͽ���
    UART_C2_REG(UARTx[uratn]) &= ~(UART_C2_TE_MASK  | UART_C2_RE_MASK );

    //���ó�8λ��У��ģʽ
    //���� UART ���ݸ�ʽ��У�鷽ʽ��ֹͣλλ����ͨ������ UART ģ����ƼĴ��� C1 ʵ�֣�
    UART_C1_REG(UARTx[uratn]) = 0;	// ȫ��ֱ��ʹ��Ĭ�����þ��У�����ֱ����0

    //���㲨���ʣ�����0��1ʹ���ں�ʱ�ӣ���������ʹ������ʱ��
    if ((uratn == UART0) || (uratn == UART1))
        sysclk = Gsystcl_KH * 1000;            //�ں�ʱ��
    else
        sysclk = Gbuscl_KH * 1000;  //����ʱ��

    //���� UART ����ͨѶ�����ʡ�ͨ������ UART ģ��Ĳ����ʼĴ���
    sbr = (uint16_t)(sysclk / (baud << 4));

    /* Save off the current value of the UARTx_BDH except for the SBR field */
    temp = UART_BDH_REG(UARTx[uratn]) & ~(UART_BDH_SBR(0x1F));

    UART_BDH_REG(UARTx[uratn]) = temp |  UART_BDH_SBR(((sbr & 0x1F00) >> 8));
    UART_BDL_REG(UARTx[uratn]) = (uint8_t)(sbr & UART_BDL_SBR_MASK);

    //brfa = (((sysclk*32)/(baud * 16)) - (sbr * 32));
    brfa = (((sysclk << 5) / (baud << 4)) - (sbr << 5));

    /* Save off the current value of the UARTx_C4 register except for the BRFA field */
    temp = UART_C4_REG(UARTx[uratn]) & ~(UART_C4_BRFA(0x1F));

    UART_C4_REG(UARTx[uratn]) = temp |  UART_C4_BRFA(brfa);
    
    /* ����DMA���� */
    UART_C5_REG(UARTx[uratn]) |= UART_C5_TDMAS_MASK;

    /* �����ͺͽ��� */
    UART_C2_REG(UARTx[uratn]) |= (UART_C2_TE_MASK | UART_C2_RE_MASK |UART_C2_TIE_MASK);

}


/*************************************************************************
*                             
*
*  �������ƣ�uart_init
*  ����˵������ʼ�����ڣ����ò�����
*  ����˵����UARTn       ģ��ţ�UART0~UART5��
*            baud        �����ʣ���9600��19200��56000��115200��
*  �������أ���
*  �޸�ʱ�䣺2012-1-20
*  ��    ע���ڹٷ��������޸�
*************************************************************************/
void uart_init (UARTn uratn, uint32 baud)
{
    register uint16_t sbr, brfa;
    uint8_t temp;
    uint32_t sysclk;     //ʱ��

    switch(uratn)
    {
    case UART0:
        if(UART0_RX == PTA1)
          port_alt(UART0_RX,ALT2);
        else 
          port_alt(UART0_RX,ALT3);

        if(UART0_TX == PTA2)
            port_alt(UART0_TX,ALT2);
        else 
            port_alt(UART0_TX,ALT3);

        SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;      //ʹ�� UARTn ʱ��
        break;

    case UART1:
        port_alt(UART1_RX,ALT3);
        port_alt(UART1_TX,ALT3);
        SIM_SCGC4 |= SIM_SCGC4_UART1_MASK;
        break;

    case UART2:
        port_alt(UART2_RX,ALT3);
        port_alt(UART2_TX,ALT3);
        SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;
        break;

    case UART3:
        port_alt(UART3_RX,ALT3);
        port_alt(UART3_TX,ALT3);
        SIM_SCGC4 |= SIM_SCGC4_UART3_MASK;
        break;

    case UART4:
        port_alt(UART4_RX,ALT3);
        port_alt(UART4_TX,ALT3);
        SIM_SCGC1 |= SIM_SCGC1_UART4_MASK;
        break;

    case UART5:
        port_alt(UART5_RX,ALT3);
        port_alt(UART5_TX,ALT3);

        SIM_SCGC1 |= SIM_SCGC1_UART5_MASK;
        break;
    default:
        break;
    }

    //���õ�ʱ��Ӧ�ý�ֹ���ͽ���
    UART_C2_REG(UARTx[uratn]) &= ~(UART_C2_TE_MASK  | UART_C2_RE_MASK );

    //���ó�8λ��У��ģʽ
    //���� UART ���ݸ�ʽ��У�鷽ʽ��ֹͣλλ����ͨ������ UART ģ����ƼĴ��� C1 ʵ�֣�
    UART_C1_REG(UARTx[uratn]) = 0;	// ȫ��ֱ��ʹ��Ĭ�����þ��У�����ֱ����0

    //���㲨���ʣ�����0��1ʹ���ں�ʱ�ӣ���������ʹ������ʱ��
    if ((uratn == UART0) | (uratn == UART1))
        sysclk = Gsystcl_KH * 1000;            //�ں�ʱ��
    else
        sysclk = Gbuscl_KH * 1000;  //����ʱ��

    //���� UART ����ͨѶ�����ʡ�ͨ������ UART ģ��Ĳ����ʼĴ���
    sbr = (uint16_t)(sysclk / (baud << 4));

    /* Save off the current value of the UARTx_BDH except for the SBR field */
    temp = UART_BDH_REG(UARTx[uratn]) & ~(UART_BDH_SBR(0x1F));

    UART_BDH_REG(UARTx[uratn]) = temp |  UART_BDH_SBR(((sbr & 0x1F00) >> 8));
    UART_BDL_REG(UARTx[uratn]) = (uint8_t)(sbr & UART_BDL_SBR_MASK);

    brfa = (((sysclk << 5) / (baud << 4)) - (sbr << 5));

    /* Save off the current value of the UARTx_C4 register except for the BRFA field */
    temp = UART_C4_REG(UARTx[uratn]) & ~(UART_C4_BRFA(0x1F));

    UART_C4_REG(UARTx[uratn]) = temp |  UART_C4_BRFA(brfa);

    /* �����ͺͽ��� */
    UART_C2_REG(UARTx[uratn]) |= (UART_C2_TE_MASK | UART_C2_RE_MASK );
//    enable_irq(uratn + (INT_UART0_RX_TX+INC_IRQ));
}

/*************************************************************************
*                             
*
*  �������ƣ�uart_getchar
*  ����˵��������ʱ��ȴ����ڽ���һ���ֽ�
*  ����˵����UARTn       ģ��ţ�UART0~UART5��
*  �������أ����յ����ֽ�
*  �޸�ʱ�䣺2012-1-20
*  ��    ע���ٷ�����
*************************************************************************/
char uart_getchar (UARTn uratn)
{
    /* Wait until character has been received */
    while (!(UART_S1_REG(UARTx[uratn]) & UART_S1_RDRF_MASK));

    /* Return the 8-bit data from the receiver */
    return UART_D_REG(UARTx[uratn]);
}

/*************************************************************************
*                             
*
*  �������ƣ�uart_pendchar
*  ����˵��������ʱ��ȴ����ڽ���һ���ֽ�
*  ����˵����UARTn       ģ��ţ�UART0~UART5��
*  �������أ����յ����ֽ�
*  �޸�ʱ�䣺2012-1-20
*  ��    ע��
*************************************************************************/
char uart_rechar (UARTn uratn, char *ch)
{
    uint32_t i = 0;

    while(++i < 0xffffff)                                         //ʱ������
    {
        if(UART_S1_REG(UARTx[uratn]) & UART_S1_RDRF_MASK)         //��ѯ�Ƿ���ܵ�����
        {
            *ch  =   UART_D_REG(UARTx[uratn]);                    //���ܵ�8λ������
            return  1;                                            //���� 1 ��ʾ���ճɹ�
        }
    }

    *ch = 0;                                                     //���ղ�����Ӧ������˽�����
    return 0;                                                    //����0��ʾ����ʧ��
}


/*************************************************************************
*                             
*
*  �������ƣ�uart_putchar
*  ����˵�������ڷ���һ���ֽ�
*  ����˵����UARTn       ģ��ţ�UART0~UART5��
*  �������أ���
*  �޸�ʱ�䣺2012-1-20
*  ��    ע���ٷ�����
*************************************************************************/
void uart_putchar (UARTn uratn, char ch)
{
    //�ȴ����ͻ�������
    while(!(UART_S1_REG(UARTx[uratn]) & UART_S1_TDRE_MASK));
    //��������
    UART_D_REG(UARTx[uratn]) = (uint8_t)ch;
}

/*************************************************************************
*                             
*
*  �������ƣ�uart_query
*  ����˵������ѯ�Ƿ���ܵ�һ���ֽ�
*  ����˵����UARTn       ģ��ţ�UART0~UART5��
*  �������أ�1           ���յ�һ���ֽ���
*            0           û�н��յ�
*  �޸�ʱ�䣺2012-1-20
*  ��    ע���ٷ�����
*************************************************************************/
char uart_query (UARTn uratn)
{
    return (UART_S1_REG(UARTx[uratn]) & UART_S1_RDRF_MASK);
}

/*************************************************************************
*                             
*
*  �������ƣ�uart_sendN
*  ����˵�������� ����ָ��len���ֽڳ����ַ��� ������ NULL Ҳ�ᷢ�ͣ�
*  ����˵����UARTn       ģ��ţ�UART0~UART5��
*            buff        ���ͻ�����
*            len         ���ͳ���
*  �������أ���
*  �޸�ʱ�䣺2012-1-20
*  ��    ע��
*************************************************************************/
void uart_sendN (UARTn uratn, uint8_t *buff, uint16_t len)
{
    int i;
    for(i = 0; i < len; i++)
    {
        uart_putchar(uratn, buff[i]);
    }
}
/*************************************************************************
*                             
*
*  �������ƣ�uart_sendN
*  ����˵�������� �ַ��� ������ NULL Ҳ�ᷢ�ͣ�
*  ����˵����UARTn       ģ��ţ�UART0~UART5��
*            str        �����ַ���     
*  �������أ���
*  �޸�ʱ�䣺2012-1-20
*  ��    ע��
*************************************************************************/
void uart_sendStr(UARTn uratn, const uint8_t *str)
{
  while(*str)
  {
    uart_putchar(uratn, *str++);
  }
}

