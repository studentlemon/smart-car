/***********************************************************
 * 文件名       ：K6x_flash.c
 * 说明         ：flash写入擦除
 


 *论坛          ：http://www.landzo.cn
 *库版本        ：V2.0
 *时间          ：15.5.26
************************************************************/

//包含头文件
#include "K6x_flash.h" 


// Flash控制器宏定义 ，内部使用 
#define CCIF    (1<<7)
#define ACCERR  (1<<5)
#define FPVIOL  (1<<4)
#define MGSTAT0 (1<<0)


//Flash命令宏定义，内部使用
#define RD1BLK    0x00   // 读整块Flash
#define RD1SEC    0x01   // 读整个扇区
#define PGMCHK    0x02   // 写入检查
#define RDRSRC    0x03   // 读目标数据
#define PGM4      0x06   // 写入长字
#define ERSBLK    0x08   // 擦除整块Flash
#define ERSSCR    0x09   // 擦除Flash扇区
#define PGMSEC    0x0B   // 写入扇区
#define RD1ALL    0x40   // 读所有的块
#define RDONCE    0x41   // 只读一次
#define PGMONCE   0x43   // 只写一次
#define ERSALL    0x44   // 擦除所有块
#define VFYKEY    0x45   // 验证后门访问钥匙
#define PGMPART   0x80   // 写入分区
#define SETRAM    0x81   // 设定FlexRAM功能

/*************************************************************************
*                             北京航空航天大学
*
*  函数名称：flash_sign_off
*  功能说明：配置Flash存储控制器，清除Flash预读取缓冲
*  参数说明：
*  函数返回：
*  修改时间：2015-5-15   已测试
*  备    注：苏州大学的例程
*************************************************************************/

__RAMFUN void flash_sign_off(void)
{  
    // 清除缓冲
    FMC_PFB0CR |= FMC_PFB0CR_S_B_INV_MASK;
    FMC_PFB1CR |= FMC_PFB0CR_S_B_INV_MASK;
}
/*************************************************************************
*                             北京航空航天大学
*
*  函数名称：flash_cmd_launch
*  功能说明：启动Flash命令
*  参数说明：
*  函数返回：0-成功 1-失败
*  修改时间：2015-5-15   已测试
*  备    注：苏州大学的例程
*************************************************************************/

static uint32 flash_cmd_launch(void)
{
    // 清除访问错误标志位和非法访问标志位
    FTFE_FSTAT = ACCERR | FPVIOL;
    
    // 启动命令
    FTFE_FSTAT = CCIF;

    // 等待命令结束
    while(!(FTFE_FSTAT & CCIF));

    // 检查错误标志
    if(FTFE_FSTAT & (ACCERR | FPVIOL | MGSTAT0))
        return 1 ; //执行命令出错
  
    return 0; //执行命令成功
}
/*************************************************************************
*                             北京航空航天大学
*
*  函数名称：flash_init
*  功能说明：初始化flash模块
*  参数说明：
*  函数返回：。
*  修改时间：2015-5-15   已测试
*  备    注：苏州大学的例程
*************************************************************************/
__RAMFUN void hw_flash_init(void)
{
	//清除FMC缓冲区
    flash_sign_off();
    
    // 禁止看门狗
    WDOG_UNLOCK = 0xC520;
    WDOG_UNLOCK = 0xD928;
    WDOG_STCTRLH = 0;    // 禁止看门狗
    
    // 等待命令完成
    while(!(FTFE_FSTAT & CCIF));
    
    // 清除访问出错标志位
    FTFE_FSTAT = ACCERR | FPVIOL;
}
/*************************************************************************
*                             北京航空航天大学
*
*  函数名称：flash_erase_sector
*  功能说明：擦除指定flash扇区
*  参数说明：sectorNo：扇区号
*  函数返回：函数执行状态：0=正常；非0=异常。
*  修改时间：2015-5-15   已测试
*  备    注：苏州大学的例程
*************************************************************************/
__RAMFUN uint8 flash_erase_sector(uint16 sectorNo)
{

    union
    {
        uint32  word;
        uint8   byte[4];
    } dest;
    
    dest.word    = (uint32)(sectorNo*(1<<11));
//
    // 设置擦除命令
    FTFE_FCCOB0 = ERSSCR; // 擦除扇区命令
    
//     设置目标地址
    FTFE_FCCOB1 = dest.byte[2];
    FTFE_FCCOB2 = dest.byte[1];
    FTFE_FCCOB3 = dest.byte[0];

 
//    // 执行命令序列
//    if(1 == hw_flash_cmd_launch())    //若执行命令出现错误
//        return 1;     //擦除命令错误
    
    FTFE_FSTAT = ACCERR | FPVIOL;    // 清除访问错误标志位和非法访问标志位
    FTFE_FSTAT = CCIF;               // 启动命令
    while(!(FTFE_FSTAT & CCIF));    // 等待命令结束
    if(FTFE_FSTAT & (ACCERR | FPVIOL | MGSTAT0))    // 检查错误标志
        return 1 ; //执行命令出错

    
    // 若擦除sector0时，则解锁设备
    if(dest.word <= 0x800)
    {
        // 写入4字节
        FTFE_FCCOB0 = PGM4; 
        // 设置目标地址
        FTFE_FCCOB1 = 0x00;
        FTFE_FCCOB2 = 0x04;
        FTFE_FCCOB3 = 0x0C;
        // 数据
        FTFE_FCCOB4 = 0xFF;
        FTFE_FCCOB5 = 0xFF;
        FTFE_FCCOB6 = 0xFF;
        FTFE_FCCOB7 = 0xFE;
        // 执行命令序列
//        if(1 == hw_flash_cmd_launch())  //若执行命令出现错误
//            return 2;   //解锁命令错误
        FTFE_FSTAT = ACCERR | FPVIOL;    // 清除访问错误标志位和非法访问标志位
        FTFE_FSTAT = CCIF;               // 启动命令
        while(!(FTFE_FSTAT & CCIF));    // 等待命令结束
        if(FTFE_FSTAT & (ACCERR | FPVIOL | MGSTAT0))    // 检查错误标志
            return 2 ; //执行命令出错        
    }  
    return 0;  //成功返回
}
/*************************************************************************
*                             北京航空航天大学
*
*  函数名称：flash_write
*  功能说明：flash写入操作
*  参数说明：sectNo：目标扇区号 （K60N512实际使用0~255）
*         offset:写入扇区内部偏移地址（0~2043）
*         cnt：写入字节数目（0~2043）
*         buf：源数据缓冲区首地址
*  函数返回：函数执行状态：0=正常；非0=异常。
*  修改时间：2015-5-15   已测试
*  备    注：苏州大学的例程
*************************************************************************/
__RAMFUN uint8 flash_write(uint16 sectNo,uint16 offset,uint16 cnt,uint8 buf[])
{
    uint32 size;
    uint32 destaddr;
    
    union
    {
        uint32   word;
        uint8_t  byte[4];
    } dest;
    
    if(offset%4 != 0)
        return 1;   //参数设定错误，偏移量未对齐（4字节对齐）
    
    // 设置写入命令
    FTFE_FCCOB0 = PGM4;
    destaddr = (uint32)(sectNo*(1<<11) + offset);//计算地址
    dest.word = destaddr;
    for(size=0; size<cnt; size+=4, dest.word+=4, buf+=4)
    {
        // 设置目标地址
        FTFE_FCCOB1 = dest.byte[2];
        FTFE_FCCOB2 = dest.byte[1];
        FTFE_FCCOB3 = dest.byte[0];
 
        // 拷贝数据
        FTFE_FCCOB4 = buf[3];
        FTFE_FCCOB5 = buf[2];
        FTFE_FCCOB6 = buf[1];
        FTFE_FCCOB7 = buf[0];
        

        FTFE_FSTAT = ACCERR | FPVIOL;    // 清除访问错误标志位和非法访问标志位
        FTFE_FSTAT = CCIF;               // 启动命令
        while(!(FTFE_FSTAT & CCIF));    // 等待命令结束
        if(FTFE_FSTAT & (ACCERR | FPVIOL | MGSTAT0))    // 检查错误标志
             return 2;  //写入命令错误
    }
    
    return 0;  //成功执行
}




