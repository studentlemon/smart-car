#ifndef _LANDZOmotor_H
#define _LANDZOmotor_H

#include "include.h"

#define   LIN_COUNT  1000

void MeasureSpeed_one_init(void);
void MeasureSpeed_double_init(void);
uint16_t MeasureSpeed_one_test(void);
void MeasureSpeed_double_test(void);
void speed_count_Init(void) ;   //
void speed_count_read(SPEEDCOUT *speedre1,uint8 *turnre1,vuint8 *dmacount  , int16 *speedcount1,    //
                      SPEEDCOUT *speedre2,uint8 *turnre2,vuint8 *lptcount,vuint16 *DMAlastcout,int16 *speedcount2) ;      //速度数据的读取
void speed1_count_read(vuint8 *dmacount , int16 *speedcount1, vuint8 *lptcount,int16 *speedcount2) ;


#endif