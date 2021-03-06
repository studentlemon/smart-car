#include  "Landzo_1.44TFT.h"

//======================================================
// 128X128液晶底层驱动[8X16]字体库
// 设计者: powerint
// 描  述: [8X16]西文字符的字模数据 (纵向取模,字节倒序)
// !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~
//======================================================
const uint8_t Zk_ASCII8X16[][16]=
{
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//  0
  0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x33,0x30,0x00,0x00,0x00,//! 1
  0x00,0x10,0x0C,0x06,0x10,0x0C,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//" 2
  0x40,0xC0,0x78,0x40,0xC0,0x78,0x40,0x00,0x04,0x3F,0x04,0x04,0x3F,0x04,0x04,0x00,//# 3
  0x00,0x70,0x88,0xFC,0x08,0x30,0x00,0x00,0x00,0x18,0x20,0xFF,0x21,0x1E,0x00,0x00,//$ 4
  0xF0,0x08,0xF0,0x00,0xE0,0x18,0x00,0x00,0x00,0x21,0x1C,0x03,0x1E,0x21,0x1E,0x00,//% 5
  0x00,0xF0,0x08,0x88,0x70,0x00,0x00,0x00,0x1E,0x21,0x23,0x24,0x19,0x27,0x21,0x10,//& 6
  0x10,0x16,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//' 7
  0x00,0x00,0x00,0xE0,0x18,0x04,0x02,0x00,0x00,0x00,0x00,0x07,0x18,0x20,0x40,0x00,//( 8
  0x00,0x02,0x04,0x18,0xE0,0x00,0x00,0x00,0x00,0x40,0x20,0x18,0x07,0x00,0x00,0x00,//) 9
  0x40,0x40,0x80,0xF0,0x80,0x40,0x40,0x00,0x02,0x02,0x01,0x0F,0x01,0x02,0x02,0x00,//* 10
  0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x1F,0x01,0x01,0x01,0x00,//+ 11
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xB0,0x70,0x00,0x00,0x00,0x00,0x00,//, 12
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,//- 13
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00,//. 14
  0x00,0x00,0x00,0x00,0x80,0x60,0x18,0x04,0x00,0x60,0x18,0x06,0x01,0x00,0x00,0x00,/// 15
  0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00,//0 16
  0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//1 17
  0x00,0x70,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00,//2 18
  0x00,0x30,0x08,0x88,0x88,0x48,0x30,0x00,0x00,0x18,0x20,0x20,0x20,0x11,0x0E,0x00,//3 19
  0x00,0x00,0xC0,0x20,0x10,0xF8,0x00,0x00,0x00,0x07,0x04,0x24,0x24,0x3F,0x24,0x00,//4 20
  0x00,0xF8,0x08,0x88,0x88,0x08,0x08,0x00,0x00,0x19,0x21,0x20,0x20,0x11,0x0E,0x00,//5 21
  0x00,0xE0,0x10,0x88,0x88,0x18,0x00,0x00,0x00,0x0F,0x11,0x20,0x20,0x11,0x0E,0x00,//6 22
  0x00,0x38,0x08,0x08,0xC8,0x38,0x08,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,//7 23
  0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00,//8 24
  0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x00,0x31,0x22,0x22,0x11,0x0F,0x00,//9 25
  0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,//: 26
  0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x60,0x00,0x00,0x00,0x00,//; 27
  0x00,0x00,0x80,0x40,0x20,0x10,0x08,0x00,0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x00,//< 28
  0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00,//= 29
  0x00,0x08,0x10,0x20,0x40,0x80,0x00,0x00,0x00,0x20,0x10,0x08,0x04,0x02,0x01,0x00,//> 30
  0x00,0x70,0x48,0x08,0x08,0x08,0xF0,0x00,0x00,0x00,0x00,0x30,0x36,0x01,0x00,0x00,//? 31
  0xC0,0x30,0xC8,0x28,0xE8,0x10,0xE0,0x00,0x07,0x18,0x27,0x24,0x23,0x14,0x0B,0x00,//@ 32
  0x00,0x00,0xC0,0x38,0xE0,0x00,0x00,0x00,0x20,0x3C,0x23,0x02,0x02,0x27,0x38,0x20,//A 33
  0x08,0xF8,0x88,0x88,0x88,0x70,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x11,0x0E,0x00,//B 34
  0xC0,0x30,0x08,0x08,0x08,0x08,0x38,0x00,0x07,0x18,0x20,0x20,0x20,0x10,0x08,0x00,//C 35
  0x08,0xF8,0x08,0x08,0x08,0x10,0xE0,0x00,0x20,0x3F,0x20,0x20,0x20,0x10,0x0F,0x00,//D 36
  0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x20,0x23,0x20,0x18,0x00,//E 37
  0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x00,0x03,0x00,0x00,0x00,//F 38
  0xC0,0x30,0x08,0x08,0x08,0x38,0x00,0x00,0x07,0x18,0x20,0x20,0x22,0x1E,0x02,0x00,//G 39
  0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x20,0x3F,0x21,0x01,0x01,0x21,0x3F,0x20,//H 40
  0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//I 41
  0x00,0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,0x00,//J 42
  0x08,0xF8,0x88,0xC0,0x28,0x18,0x08,0x00,0x20,0x3F,0x20,0x01,0x26,0x38,0x20,0x00,//K 43
  0x08,0xF8,0x08,0x00,0x00,0x00,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x20,0x30,0x00,//L 44
  0x08,0xF8,0xF8,0x00,0xF8,0xF8,0x08,0x00,0x20,0x3F,0x00,0x3F,0x00,0x3F,0x20,0x00,//M 45
  0x08,0xF8,0x30,0xC0,0x00,0x08,0xF8,0x08,0x20,0x3F,0x20,0x00,0x07,0x18,0x3F,0x00,//N 46
  0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x10,0x20,0x20,0x20,0x10,0x0F,0x00,//O 47
  0x08,0xF8,0x08,0x08,0x08,0x08,0xF0,0x00,0x20,0x3F,0x21,0x01,0x01,0x01,0x00,0x00,//P 48
  0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x18,0x24,0x24,0x38,0x50,0x4F,0x00,//Q 49
  0x08,0xF8,0x88,0x88,0x88,0x88,0x70,0x00,0x20,0x3F,0x20,0x00,0x03,0x0C,0x30,0x20,//R 50
  0x00,0x70,0x88,0x08,0x08,0x08,0x38,0x00,0x00,0x38,0x20,0x21,0x21,0x22,0x1C,0x00,//S 51
  0x18,0x08,0x08,0xF8,0x08,0x08,0x18,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,//T 52
  0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,//U 53
  0x08,0x78,0x88,0x00,0x00,0xC8,0x38,0x08,0x00,0x00,0x07,0x38,0x0E,0x01,0x00,0x00,//V 54
  0xF8,0x08,0x00,0xF8,0x00,0x08,0xF8,0x00,0x03,0x3C,0x07,0x00,0x07,0x3C,0x03,0x00,//W 55
  0x08,0x18,0x68,0x80,0x80,0x68,0x18,0x08,0x20,0x30,0x2C,0x03,0x03,0x2C,0x30,0x20,//X 56
  0x08,0x38,0xC8,0x00,0xC8,0x38,0x08,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,//Y 57
  0x10,0x08,0x08,0x08,0xC8,0x38,0x08,0x00,0x20,0x38,0x26,0x21,0x20,0x20,0x18,0x00,//Z 58
  0x00,0x00,0x00,0xFE,0x02,0x02,0x02,0x00,0x00,0x00,0x00,0x7F,0x40,0x40,0x40,0x00,//[ 59
  0x00,0x0C,0x30,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x06,0x38,0xC0,0x00,//\ 60
  0x00,0x02,0x02,0x02,0xFE,0x00,0x00,0x00,0x00,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,//] 61
  0x00,0x00,0x04,0x02,0x02,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//^ 62
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,//_ 63
  0x00,0x02,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//` 64
  0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x19,0x24,0x22,0x22,0x22,0x3F,0x20,//a 65
  0x08,0xF8,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x3F,0x11,0x20,0x20,0x11,0x0E,0x00,//b 66
  0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00,0x00,0x0E,0x11,0x20,0x20,0x20,0x11,0x00,//c 67
  0x00,0x00,0x00,0x80,0x80,0x88,0xF8,0x00,0x00,0x0E,0x11,0x20,0x20,0x10,0x3F,0x20,//d 68
  0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x22,0x22,0x22,0x22,0x13,0x00,//e 69
  0x00,0x80,0x80,0xF0,0x88,0x88,0x88,0x18,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//f 70
  0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x6B,0x94,0x94,0x94,0x93,0x60,0x00,//g 71
  0x08,0xF8,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,//h 72
  0x00,0x80,0x98,0x98,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//i 73
  0x00,0x00,0x00,0x80,0x98,0x98,0x00,0x00,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,//j 74
  0x08,0xF8,0x00,0x00,0x80,0x80,0x80,0x00,0x20,0x3F,0x24,0x02,0x2D,0x30,0x20,0x00,//k 75
  0x00,0x08,0x08,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//l 76
  0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x20,0x3F,0x20,0x00,0x3F,0x20,0x00,0x3F,//m 77
  0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,//n 78
  0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,//o 79
  0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x00,0x80,0xFF,0xA1,0x20,0x20,0x11,0x0E,0x00,//p 80
  0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x0E,0x11,0x20,0x20,0xA0,0xFF,0x80,//q 81
  0x80,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x20,0x20,0x3F,0x21,0x20,0x00,0x01,0x00,//r 82
  0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x33,0x24,0x24,0x24,0x24,0x19,0x00,//s 83
  0x00,0x80,0x80,0xE0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x1F,0x20,0x20,0x00,0x00,//t 84
  0x80,0x80,0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x1F,0x20,0x20,0x20,0x10,0x3F,0x20,//u 85
  0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x00,0x01,0x0E,0x30,0x08,0x06,0x01,0x00,//v 86
  0x80,0x80,0x00,0x80,0x00,0x80,0x80,0x80,0x0F,0x30,0x0C,0x03,0x0C,0x30,0x0F,0x00,//w 87
  0x00,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x31,0x2E,0x0E,0x31,0x20,0x00,//x 88
  0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x80,0x81,0x8E,0x70,0x18,0x06,0x01,0x00,//y 89
  0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x21,0x30,0x2C,0x22,0x21,0x30,0x00,//z 90
  0x00,0x00,0x00,0x00,0x80,0x7C,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x3F,0x40,0x40,//{ 91
  0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,//| 92
  0x00,0x02,0x02,0x7C,0x80,0x00,0x00,0x00,0x00,0x40,0x40,0x3F,0x00,0x00,0x00,0x00,//} 93
  0x00,0x06,0x01,0x01,0x02,0x02,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//~ 94
  
};

const uint8_t Zk_ASCII6x8[][6] =
{
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // sp
  { 0x00, 0x00, 0x00, 0x2f, 0x00, 0x00 },   // !
  { 0x00, 0x00, 0x07, 0x00, 0x07, 0x00 },   // "
  { 0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14 },   // #
  { 0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12 },   // $
  { 0x00, 0x62, 0x64, 0x08, 0x13, 0x23 },   // %
  { 0x00, 0x36, 0x49, 0x55, 0x22, 0x50 },   // &
  { 0x00, 0x00, 0x05, 0x03, 0x00, 0x00 },   // '
  { 0x00, 0x00, 0x1c, 0x22, 0x41, 0x00 },   // (
  { 0x00, 0x00, 0x41, 0x22, 0x1c, 0x00 },   // )
  { 0x00, 0x14, 0x08, 0x3E, 0x08, 0x14 },   // *
  { 0x00, 0x08, 0x08, 0x3E, 0x08, 0x08 },   // +
  { 0x00, 0x00, 0x00, 0xA0, 0x60, 0x00 },   // ,
  { 0x00, 0x08, 0x08, 0x08, 0x08, 0x08 },   // -
  { 0x00, 0x00, 0x60, 0x60, 0x00, 0x00 },   // .
  { 0x00, 0x20, 0x10, 0x08, 0x04, 0x02 },   // /
  { 0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E },   // 0
  { 0x00, 0x00, 0x42, 0x7F, 0x40, 0x00 },   // 1
  { 0x00, 0x42, 0x61, 0x51, 0x49, 0x46 },   // 2
  { 0x00, 0x21, 0x41, 0x45, 0x4B, 0x31 },   // 3
  { 0x00, 0x18, 0x14, 0x12, 0x7F, 0x10 },   // 4
  { 0x00, 0x27, 0x45, 0x45, 0x45, 0x39 },   // 5
  { 0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30 },   // 6
  { 0x00, 0x01, 0x71, 0x09, 0x05, 0x03 },   // 7
  { 0x00, 0x36, 0x49, 0x49, 0x49, 0x36 },   // 8
  { 0x00, 0x06, 0x49, 0x49, 0x29, 0x1E },   // 9
  { 0x00, 0x00, 0x36, 0x36, 0x00, 0x00 },   // :
  { 0x00, 0x00, 0x56, 0x36, 0x00, 0x00 },   // ;
  { 0x00, 0x08, 0x14, 0x22, 0x41, 0x00 },   // <
  { 0x00, 0x14, 0x14, 0x14, 0x14, 0x14 },   // =
  { 0x00, 0x00, 0x41, 0x22, 0x14, 0x08 },   // >
  { 0x00, 0x02, 0x01, 0x51, 0x09, 0x06 },   // ?
  { 0x00, 0x32, 0x49, 0x59, 0x51, 0x3E },   // @
  { 0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C },   // A
  { 0x00, 0x7F, 0x49, 0x49, 0x49, 0x36 },   // B
  { 0x00, 0x3E, 0x41, 0x41, 0x41, 0x22 },   // C
  { 0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C },   // D
  { 0x00, 0x7F, 0x49, 0x49, 0x49, 0x41 },   // E
  { 0x00, 0x7F, 0x09, 0x09, 0x09, 0x01 },   // F
  { 0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A },   // G
  { 0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F },   // H
  { 0x00, 0x00, 0x41, 0x7F, 0x41, 0x00 },   // I
  { 0x00, 0x20, 0x40, 0x41, 0x3F, 0x01 },   // J
  { 0x00, 0x7F, 0x08, 0x14, 0x22, 0x41 },   // K
  { 0x00, 0x7F, 0x40, 0x40, 0x40, 0x40 },   // L
  { 0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F },   // M
  { 0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F },   // N
  { 0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E },   // O
  { 0x00, 0x7F, 0x09, 0x09, 0x09, 0x06 },   // P
  { 0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E },   // Q
  { 0x00, 0x7F, 0x09, 0x19, 0x29, 0x46 },   // R
  { 0x00, 0x46, 0x49, 0x49, 0x49, 0x31 },   // S
  { 0x00, 0x01, 0x01, 0x7F, 0x01, 0x01 },   // T
  { 0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F },   // U
  { 0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F },   // V
  { 0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F },   // W
  { 0x00, 0x63, 0x14, 0x08, 0x14, 0x63 },   // X
  { 0x00, 0x07, 0x08, 0x70, 0x08, 0x07 },   // Y
  { 0x00, 0x61, 0x51, 0x49, 0x45, 0x43 },   // Z
  { 0x00, 0x00, 0x7F, 0x41, 0x41, 0x00 },   // [
  { 0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55 },   // 55
  { 0x00, 0x00, 0x41, 0x41, 0x7F, 0x00 },   // ]
  { 0x00, 0x04, 0x02, 0x01, 0x02, 0x04 },   // ^
  { 0x00, 0x40, 0x40, 0x40, 0x40, 0x40 },   // _
  { 0x00, 0x00, 0x01, 0x02, 0x04, 0x00 },   // '
  { 0x00, 0x20, 0x54, 0x54, 0x54, 0x78 },   // a
  { 0x00, 0x7F, 0x48, 0x44, 0x44, 0x38 },   // b
  { 0x00, 0x38, 0x44, 0x44, 0x44, 0x20 },   // c
  { 0x00, 0x38, 0x44, 0x44, 0x48, 0x7F },   // d
  { 0x00, 0x38, 0x54, 0x54, 0x54, 0x18 },   // e
  { 0x00, 0x08, 0x7E, 0x09, 0x01, 0x02 },   // f
  { 0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C },   // g
  { 0x00, 0x7F, 0x08, 0x04, 0x04, 0x78 },   // h
  { 0x00, 0x00, 0x44, 0x7D, 0x40, 0x00 },   // i
  { 0x00, 0x40, 0x80, 0x84, 0x7D, 0x00 },   // j
  { 0x00, 0x7F, 0x10, 0x28, 0x44, 0x00 },   // k
  { 0x00, 0x00, 0x41, 0x7F, 0x40, 0x00 },   // l
  { 0x00, 0x7C, 0x04, 0x18, 0x04, 0x78 },   // m
  { 0x00, 0x7C, 0x08, 0x04, 0x04, 0x78 },   // n
  { 0x00, 0x38, 0x44, 0x44, 0x44, 0x38 },   // o
  { 0x00, 0xFC, 0x24, 0x24, 0x24, 0x18 },   // p
  { 0x00, 0x18, 0x24, 0x24, 0x18, 0xFC },   // q
  { 0x00, 0x7C, 0x08, 0x04, 0x04, 0x08 },   // r
  { 0x00, 0x48, 0x54, 0x54, 0x54, 0x20 },   // s
  { 0x00, 0x04, 0x3F, 0x44, 0x40, 0x20 },   // t
  { 0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C },   // u
  { 0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C },   // v
  { 0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C },   // w
  { 0x00, 0x44, 0x28, 0x10, 0x28, 0x44 },   // x
  { 0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C },   // y
  { 0x00, 0x44, 0x64, 0x54, 0x4C, 0x44 },   // z
  { 0x14, 0x14, 0x14, 0x14, 0x14, 0x14 }    // horiz lines
};

/************************************************************************
TFT 一行可以显示16个字符，可以显示8行。
************************************************************************/

#define TFT_SCK  PTE5_OUT
#define TFT_SDA  PTE2_OUT
#define TFT_RST  PTE3_OUT
#define TFT_AO   PTE6_OUT
#define TFT_CS   PTE4_OUT
#define DDRA_SDA DDRE2
#define TFT_SDAI PTE2_INT



/*
4线SPI使用说明：
VBT 供内部DC-DC电压，3.3~4.3V，如果使用5V电压，为保险起见串一个100~500欧的电阻
VCC 供内部逻辑电压 1.8~6V
GND 地



CS  片选管脚
A0  命令数据选择管脚
RES 模块复位管脚
SCK（SCLK） ，时钟脚，由MCU控制
SDA（MOSI） ，主输出从输入数据脚，由MCU控制

*/
/*************************************************************************
*                            北京航空航天大学
*
*  函数名称：TFT_COMDLY
*  功能说明：TFT命令延时
*  参数说明:
*  函数返回：无
*  修改时间：2015-8-20
*  备    注：
*************************************************************************/
void TFT_COMDLY(void){
  vuint16 TFTDlyC ;
  for(TFTDlyC = 0 ;TFTDlyC < 5 ; TFTDlyC++) ;
  
}
/*************************************************************************
*                            北京航空航天大学
*
*  函数名称：TFT_DLY
*  功能说明：TFT延时程序，
*  参数说明:
*  函数返回：无
*  修改时间：2015-8-20
*  备    注：
*************************************************************************/
void TFT_DLY(uint16 ms){
  vuint16 TFTDlyC ,TFTcount;
  uint16 TFTdlay ;
  TFTdlay = ms ;
  for(TFTDlyC = 0 ;TFTDlyC < TFTdlay ; TFTDlyC++) {
    for(TFTcount = 0;TFTcount < 50 ;TFTcount ++); 
  }
  
}
/*************************************************************************
*                            北京航空航天大学
*
*  函数名称：write_command
*  功能说明：TFT命令指令函数
*  参数说明: command   命令
*  函数返回：无
*  修改时间：2015-8-20
*  备    注：
*************************************************************************/
void  write_command(uint8 command){
  vuint8 temp ;
  TFT_CS = 0 ;
  TFT_AO = 0 ;
  TFT_COMDLY() ;
  for(temp = 0 ; temp < 8 ; temp ++){
    TFT_COMDLY() ;
    TFT_SDA = (command)>>7 ;
    TFT_SCK = 0 ;
    asm ("nop"); 
    TFT_SCK = 1 ;
    command <<= 1 ;
  }
  TFT_CS = 1 ;  
  
}
/*************************************************************************
*                            北京航空航天大学
*
*  函数名称：write_data
*  功能说明：TFT写数据函数
*  参数说明: command   命令
*  函数返回：无
*  修改时间：2015-8-20
*  备    注：
*************************************************************************/
void  write_data(uint8 data){
  vuint8 temp ;
  TFT_CS = 0 ;
  TFT_AO = 1 ;
  TFT_COMDLY() ;
  for(temp = 0 ; temp < 8 ; temp ++){
    TFT_COMDLY() ;
    TFT_SDA = (data)>>7 ;
    TFT_SCK = 0 ;
    asm ("nop"); 
    TFT_SCK = 1 ;
    data <<= 1 ;
  }
  TFT_CS = 1 ;  
  
}
/*************************************************************************
*                            北京航空航天大学
*
*  函数名称：read_data
*  功能说明：TFT读数据函数
*  参数说明: command   命令
*  函数返回：无
*  修改时间：2015-8-20
*  备    注：
*************************************************************************/

uint8  read_data(void){
  uint8 temp,data ;
  data = 0 ;
  DDRA_SDA = 0 ;
  TFT_COMDLY() ;
  TFT_CS = 0 ;
  TFT_AO = 1 ;
  TFT_COMDLY() ;
  for(temp = 0 ; temp < 8 ; temp ++){
    TFT_SCK = 1 ;
    TFT_COMDLY() ;
    data |= TFT_SDAI ;
    TFT_COMDLY() ;
    TFT_SCK = 0 ;
    data <<= 1 ;
  }
  TFT_CS = 1 ;  
  DDRA_SDA = 1 ; 
  return data ;
}
/*************************************************************************
*                            北京航空航天大学
*
*  函数名称：TFT_Reset
*  功能说明：TFT复位
*  参数说明:  
*  函数返回：无
*  修改时间：2015-8-20
*  备    注：
*************************************************************************/
void TFT_Reset(void){
    TFT_RST = 0 ;
    TFT_DLY(100) ;
    TFT_RST = 1 ;
    TFT_DLY(100) ;
}
/*************************************************************************
*                            北京航空航天大学
*
*  函数名称：TFT_DataWrite
*  功能说明：TFT复位
*  参数说明:  
*  函数返回：无
*  修改时间：2015-8-20
*  备    注：
*************************************************************************/
void TFT_DataWrite(uint8 DataH,uint8 DataL){
  write_data(DataH) ;
  write_data(DataL) ;
}
/*************************************************************************
*                            北京航空航天大学
*
*  函数名称：dsp_single_colour
*  功能说明：背景颜色设置
*  参数说明:  
*  函数返回：无
*  修改时间：2015-8-20
*  备    注：
*************************************************************************/
void dsp_single_colour(uint8 DISH,uint8 DISL)
{
 uint8 i,j;
 RamAdressSet();
 write_command(0x2C);
 for (i=0;i<128;i++)
    for (j=0;j<128;j++)
        TFT_DataWrite(DISH,DISL);
}
/*************************************************************************
*                            北京航空航天大学
*
*  函数名称: TFT_Claer 
*  功能说明：背景颜色设置
*  参数说明:  
*  函数返回：无
*  修改时间：2015-8-20
*  备    注：
*************************************************************************/
void TFT_Claer(void){
  uint8 i,j;
 RamAdressSet();
 write_command(0x2C);
 for (i=0;i<128;i++)
    for (j=0;j<128;j++)
        TFT_DataWrite(0xff,0xff);
  
}
/*************************************************************************
*                            北京航空航天大学
*
*  函数名称：TFT_Init
*  功能说明：TFT初始化
*  参数说明:  
*  函数返回：无
*  修改时间：2015-8-20
*  备    注：
*************************************************************************/
void TFT_Init(void){
  
      /**************
      PIN初始化
      *************/
  gpio_init (PTE2, GPO,HIGH);
  gpio_init (PTE4, GPO,HIGH);
  gpio_init (PTE5, GPO,HIGH);
  gpio_init (PTE6, GPO,HIGH);
  gpio_init (PTE3, GPO,LOW);

      
      /**************
      TFT初始化
      *************/
      TFT_Reset() ;
     
      write_command(0x11); //Exit Sleep
	TFT_DLY(20);
	write_command(0x26); //Set Default Gamma
	write_data(0x04);
	write_command(0xB1);//Set Frame Rate
	write_data(0x0e);
	write_data(0x10);
	write_command(0xC0); //Set VRH1[4:0] & VC[2:0] for VCI1 & GVDD
	write_data(0x08);
	write_data(0x00);
	write_command(0xC1); //Set BT[2:0] for AVDD & VCL & VGH & VGL
	write_data(0x05);
	write_command(0xC5); //Set VMH[6:0] & VML[6:0] for VOMH & VCOML
	write_data(0x38);
	write_data(0x40);
	
	write_command(0x3a); //Set Color Format
	write_data(0x05);
	write_command(0x36); //RGB
	write_data(0xc8);
	
	write_command(0x2A); //Set Column Address
	write_data(0x00);
	write_data(0x00);
	write_data(0x00);
	write_data(0x7F);
	write_command(0x2B); //Set Page Address
	write_data(0x00);
	write_data(0x00);
	write_data(0x00);
	write_data(0x9F);
	
	write_command(0xB4); 
	write_data(0x00);
	
	write_command(0xf2); //Enable Gamma bit
	write_data(0x01);
	write_command(0xE0); 
	write_data(0x3f);//p1
	write_data(0x22);//p2
	write_data(0x20);//p3
	write_data(0x30);//p4
	write_data(0x29);//p5
	write_data(0x0c);//p6
	write_data(0x4e);//p7
	write_data(0xb7);//p8
	write_data(0x3c);//p9
	write_data(0x19);//p10
	write_data(0x22);//p11
	write_data(0x1e);//p12
	write_data(0x02);//p13
	write_data(0x01);//p14
	write_data(0x00);//p15
	write_command(0xE1); 
	write_data(0x00);//p1
	write_data(0x1b);//p2
	write_data(0x1f);//p3
	write_data(0x0f);//p4
	write_data(0x16);//p5
	write_data(0x13);//p6
	write_data(0x31);//p7
	write_data(0x84);//p8
	write_data(0x43);//p9
	write_data(0x06);//p10
	write_data(0x1d);//p11
	write_data(0x21);//p12
	write_data(0x3d);//p13
	write_data(0x3e);//p14
	write_data(0x3f);//p15
	
	write_command(0x29); // Display On
	write_command(0x2C);
        TFT_Claer();
	  
        
}
/*************************************************************************
*                            北京航空航天大学
*
*  函数名称：RamAdressSet
*  功能说明：RAM地址设置
*  参数说明:
*  函数返回：无
*  修改时间：2015-8-20
*  备    注：
*************************************************************************/
void  RamAdressSet(void)
{
   write_command(0x2A);
   write_data(0x00);
   write_data(0x00);
   write_data(0x00);
   write_data(0x7f);
  
   write_command(0x2B);
   write_data(0x00);
   write_data(0x00);
   write_data(0x00);
   write_data(0x9f);		  
}
/*************************************************************************
*                            北京航空航天大学
*
*  函数名称：PutPixel
*  功能说明：RAM地址设置
*  参数说明: x_start   X方向起始地址，
*            y_start   Y方向起始地址
*            color     颜色
*  函数返回：无
*  修改时间：2015-8-20
*  备    注：
*************************************************************************/

void PutPixel(uint8 x_start,uint8 y_start,uint16 color)
{
	write_data(0x2a);
	write_data(x_start);
	write_data(0x5f);
	write_data(0x2b);
	write_data(y_start+0x34);
	write_data(0x7F);
	write_data(0x2c);
	write_data(color>>8);
	write_data(color&0xff);
	
}

/*************************************************************************
*                            北京航空航天大学
*
*  函数名称：RedLine
*  功能说明：
*  参数说明: 
*  函数返回：无
*  修改时间：2015-8-20
*  备    注：
*************************************************************************/

void RedLine(void)
{
	uint8 i=0,j=0;
	i=66;   // 11格灰阶
	for(j=0;j<16;j++)
	{
		PutPixel(i,j,0xf800);
	}

}

/*************************************************************************
*                            北京航空航天大学
*
*  函数名称：Display_ASCII6X8
*  功能说明：打印6x8的英文字符
*  参数说明: x   X方向起始地址，
*            y   Y方向起始地址
*           ch[]     字符串
*  函数返回：无
*  修改时间：2015-8-20
*  备    注：
*************************************************************************/
void Display_ASCII6X8(uint16 x,uint16 y,uint8 ch[])
{
  uint8_t c=0,i=0,j=0;
  while (ch[j]!='\0')
  {
    c =ch[j]-32;
    if(x>126){x=0;y+=6;}
    
    for(i=0;i<6;i++){
      TFT_Set_Pos(x,y);
      TFT_WrDat(Zk_ASCII6x8[c][i]);      
      y++ ;
    }
    j++;
  }
}
/*************************************************************************
*                            北京航空航天大学
*
*  函数名称：Display_ASCII8X16
*  功能说明：打印8x16的英文字符
*  参数说明: x   X方向起始地址，
*            y   Y方向起始地址
*           ch[]     字符串
*  函数返回：无
*  修改时间：2015-8-20
*  备    注：
*************************************************************************/
void Display_ASCII8X16(uint16 x,uint16 y,uint8 ch[])
{
  uint8_t c=0,i=0,j=0;
  while (ch[j]!='\0')
  {
    c =ch[j]-32;
    if(x>126){x=0;y+=8;}
    
    for(i=0;i<8;i++){
      TFT_Set_Pos(x,y);
      TFT_WrDat(Zk_ASCII8X16[c][i]);
      y++ ;
    }
    x -= 8 ;
    y -= 8 ;
    for(i=0;i<8;i++){
      TFT_Set_Pos(x,y);
      TFT_WrDat(Zk_ASCII8X16[c][i+8]);
      y++ ;
    }
    x += 8 ;
    j++;
  }
	
}
/*************************************************************************
*                            北京航空航天大学
*
*  函数名称：Display_Desc
*  功能说明：显示初始化信息
*  参数说明: 
*  函数返回：无
*  修改时间：2015-8-20
*  备    注：
*************************************************************************/

void Display_Desc(void)
{ 
    Display_ASCII6X8(120,0,"LANDZO0");
    Display_ASCII8X16(20,0,"LANDZO1");
}

/*************************************************************************
*                            北京航空航天大学
*
*  函数名称：TFT_Set_Pos
*  功能说明：设置TFT定位点
*  参数说明: 
*  函数返回：无
*  修改时间：2015-8-20
*  备    注：
*************************************************************************/

 void TFT_Set_Pos(uint8 x,uint8 y)
 {
        write_command(0x2A);  //Column Address Set        ****
	write_data(0);//xsh 
	write_data(x);//xsl 
	write_data(0x00);//xeh 
	write_data(0x7f);//xel 	
	write_command(0x2B);//Row Address Set             ****
	write_data(0);//ysh 
	write_data(y);//ysl
        write_data(0x00);//yeh 
	write_data(0x7f);//yel 
   
 }

/*************************************************************************
*                            北京航空航天大学
*
*  函数名称：TFT_WrDat
*  功能说明：显示
*  参数说明: 
*  函数返回：无
*  修改时间：2015-8-20
*  备    注：
*************************************************************************/
void TFT_WrDat(uint8 data){
    uint8_t i=8;
  
 write_command(0x2c);
	
  while(i--)
  {
    if(data&0x80){
      TFT_DataWrite(DispRGBH,DispRGBL);
    }
    else{
      TFT_DataWrite(BlackRGBH,BlackRGBL);
    }
    data<<=1;
  }
}
/*************************************************************************
*                            北京航空航天大学
*
*  函数名称：TFT_txt
*  功能说明：显示
*  参数说明: 
*  函数返回：无
*  修改时间：2015-8-20
*  备    注：
*************************************************************************/
void TFT_txt(void){
  static uint8 ii ;
         switch(ii)
       {
        case 0: dsp_single_colour(0xff,0xff);//白色
                break;
        case 1: dsp_single_colour(0x00,0x00);//黑色
                break;
        case 2: dsp_single_colour(0xf8,0x00);//红色
                break;
        case 3: dsp_single_colour(0x07,0xe0);//绿色
                break;
        case 4: dsp_single_colour(0x00,0x1f);//蓝色
                break;
        case 5: dsp_single_colour(0xfc,0x07);//棕红色
                break;
        case 6: dsp_single_colour(0xbc,0x40);//棕色
                break;
        case 7: dsp_single_colour(0x01,0xcf);//深蓝色
                break;
        case 8: dsp_single_colour(0x7d,0x7c);//浅蓝色
                break;
       }
       Display_ASCII6X8(20,10,"Landzo"); 
       Display_ASCII6X8(20,30,"TFTLCD TEST");
       Display_ASCII6X8(20,50,"www.landzo.cn");
       ii++;
       if(ii>8) ii = 0;
}