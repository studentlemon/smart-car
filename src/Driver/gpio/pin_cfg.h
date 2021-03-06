/***********************************************************
 * 文件名       ：pin_cfg.h
 * 说明         ：端口配置文件
 * 作者         ：buaa


 *论坛          ：http://www.landzo.cn
 * 库版本       ：V2.0
 *时间          ：15.5.26
************************************************************/


#ifndef _PIN_CFG_H_
#define _PIN_CFG_H_

#include "gpio_cfg.h"


/**********************************  UART   ***************************************/

//      模块通道    端口          可选范围                          建议
#define UART0_RX    PTA15        //PTA1、PTA15、PTB16、PTD6          PTA1不要用（与Jtag冲突）
#define UART0_TX    PTA14        //PTA2、PTA14、PTB17、PTD7          PTA2不要用（与Jtag冲突）

#define UART1_RX    PTC3        //PTC3、PTE1
#define UART1_TX    PTC4        //PTC4、PTE0

#define UART2_RX    PTD2        //PTD2
#define UART2_TX    PTD3        //PTD3

#define UART3_RX    PTC16       //PTB10、PTC16、PTE5
#define UART3_TX    PTC17       //PTB11、PTC17、PTE4

#define UART4_RX    PTE25       //PTC14、PTE25
#define UART4_TX    PTE24       //PTC15、PTE24

#define UART5_RX    PTD8        //PTD8、PTE9
#define UART5_TX    PTD9        //PTD9、PTE8

/**********************************  FTM    ***************************************/

//      模块通道    端口          可选范围              建议
#define FTM0_CH0    PTC1        //PTC1、PTA3            PTA3不要用（与Jtag、SWD冲突）
#define FTM0_CH1    PTC2        //PTC2、PTA4
#define FTM0_CH2    PTC3        //PTC3、PTA5
#define FTM0_CH3    PTC4        //PTC4、PTA6
#define FTM0_CH4    PTD4        //PTD4、PTA7
#define FTM0_CH5    PTD5        //PTD5、PTA0            PTA0不要用（与Jtag、SWD冲突）
#define FTM0_CH6    PTD6        //PTD6、PTA1            PTA1不要用（与Jtag冲突）
#define FTM0_CH7    PTD7        //PTD7、PTA2            PTA2不要用（与Jtag冲突）

//      模块通道    端口          可选范围              
#define FTM1_CH0    PTA8        //PTA8、PTA12、PTB0
#define FTM1_CH1    PTA9        //PTA9、PTA13、PTB1
//      模块通道    端口          可选范围              
#define FTM2_CH0    PTB18       //PTA10、PTB18
#define FTM2_CH1    PTB19       //PTA11、PTB19

#if defined(MK64F12)

#define FTM3_CH0    PTD0        //PTD0、PTE5            
#define FTM3_CH1    PTD1        //PTD1、PTE6
#define FTM3_CH2    PTD2        //PTD2、PTE7
#define FTM3_CH3    PTD3        //PTD3、PTE8
#define FTM3_CH4    PTC8        //PTC8、PTE9
#define FTM3_CH5    PTC9        //PTC9、PTE10            
#define FTM3_CH6    PTC10        //PTC10、PTE11            
#define FTM3_CH7    PTC11        //PTC11、PTE12            

#endif
/**********************************  I2C   ***************************************/

//      模块通道    端口          可选范围              建议
#define I2C0_SCL    PTD8        // PTB0、PTB2、PTD8
#define I2C0_SDA    PTD9        // PTB1、PTB3、PTD9

#define I2C1_SCL    PTC10       // PTE1、PTC10
#define I2C1_SDA    PTC11       // PTE0、PTC11

/**********************************  CAN    ***************************************/

//      模块通道    端口          可选范围              建议
#define CAN0_TX    PTA12        // PTA12、PTB18、
#define CAN0_RX    PTA13        // PTA13、PTB19、

#if (defined(MK60DZ10)||defined(MK60F15))

#define CAN1_TX    PTE24        // PTE24、PTC17、
#define CAN1_RX    PTE25        // PTE25、PTC16、

#endif
/**********************************  SPI   ***************************************/

//      模块通道    端口          可选范围              建议
#define SPI0_SIN    PTD3         // PTC7、PTA17、PTD3
#define SPI0_SOUT   PTD2        // PTC6、PTA16、PTD2
#define SPI0_SCK    PTD1        // PTC5、PTA15、PTD1
#define SPI0_PCS0   PTD0        // PTC4、PTA14、PTD0
#define SPI0_PCS1   PTD4        // PTC3、PTD4、
#define SPI0_PCS2   PTC2        // PTC2、PTD5、
#define SPI0_PCS3   PTC1        // PTC1、PTD6、


#define SPI1_SIN    PTE3        // PTE3、PTB17、
#define SPI1_SOUT   PTE2        // PTE2、PTB16、
#define SPI1_SCK    PTE1        // PTE1、PTB11、
#define SPI1_PCS0   PTE4        // PTE4、PTB10、
#define SPI1_PCS1   PTE0        // PTE0、PTB9、
#define SPI1_PCS2   PTE5        // PTE5、
#define SPI1_PCS3   PTE6        // PTE6、


#define SPI2_SIN    PTD14        // PTD14、PTB23、
#define SPI2_SOUT   PTD13        // PTD13、PTB22、
#define SPI2_SCK    PTD12        // PTD12、PTB21、
#define SPI2_PCS0   PTD11        // PTD11、PTB20、
#define SPI2_PCS1   PTD15        // PTD15、


#endif  //_FIRE_DRIVERS_CFG_H_


