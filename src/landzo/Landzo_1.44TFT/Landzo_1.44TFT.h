#ifndef _LANDZO_144TFT_H
#define _LANDZO_144TFT_H

#include "include.h"
/********************************************************************/

#define BlackRGBH   0xff
#define BlackRGBL   0xff

#define DispRGBH    0x00
#define DispRGBL    0x1f

/*-----------------------------------------------------------------------
TFT          : 1.44TFT屏显示

编写日期          ：2015-8-20
最后修改日期      ：2015-8-20
-----------------------------------------------------------------------*/


void TFT_Init(void) ;
void Output_Pixel(uint16 x,uint16 y) ;
void Display_Desc(void) ;
void dsp_single_colour(uint8 DISH,uint8 DISL) ;
void Display_ASCII6X8(uint16 x,uint16 y,uint8 ch[]);
void  write_command(uint8 command);
void  RamAdressSet(void) ;
void TFT_WrDat(uint8 data) ;
void TFT_Set_Pos(uint8 x,uint8 y) ;
void TFT_Claer(void) ;  //清屏

void TFT_txt(void);  //测试用

/********************************************************************/

#endif
