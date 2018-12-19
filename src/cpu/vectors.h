/******************************************************************************
* File:    vectors.h
*
* Purpose: Provide custom interrupt service routines for Kinetis.
*
* NOTE: This vector table is a superset table, so interrupt sources might be
*       listed that are not available on the specific Kinetis device you are
*       using.
******************************************************************************/

#ifndef __VECTORS_H
#define __VECTORS_H     1

// function prototype for default_isr in vectors.c
void default_isr(void);
void abort_isr(void);

void pit_init_100(void);

void hard_fault_handler_c(unsigned int *hardfault_args);

/* Interrupt Vector Table Function Pointers */
typedef void pointer(void);

extern void Reset_Handler(void);
extern unsigned long __BOOT_STACK_ADDRESS[];
//extern void __iar_program_start(void);
// Address     Vector IRQ   Source module   Source description
#define VECTOR_0      (pointer*)__BOOT_STACK_ADDRESS	//          ARM core        Initial Supervisor SP    启动栈地址
#define VECTOR_1      Reset_Handler	// 0x0000_0004 1 -          ARM core        Initial Program Counter  复位中断函数
#define VECTOR_2      default_isr     // 0x0000_0008 2 -          ARM core        Non-maskable Interrupt (NMI)
#define VECTOR_3      default_isr     // 0x0000_000C 3 -          ARM core        Hard Fault
#define VECTOR_4      default_isr     // 0x0000_0010 4 -
#define VECTOR_5      default_isr     // 0x0000_0014 5 -          ARM core         Bus Fault
#define VECTOR_6      default_isr     // 0x0000_0018 6 -          ARM core         Usage Fault
#define VECTOR_7      default_isr     // 0x0000_001C 7 -                           
#define VECTOR_8      default_isr     // 0x0000_0020 8 -                           
#define VECTOR_9      default_isr     // 0x0000_0024 9 -
#define VECTOR_10      default_isr     // 0x0000_0028 10 -
#define VECTOR_11      default_isr     // 0x0000_002C 11 -         ARM core         Supervisor call (SVCall)
#define VECTOR_12      default_isr     // 0x0000_0030 12 -         ARM core         Debug Monitor
#define VECTOR_13      default_isr     // 0x0000_0034 13 -                          
#define VECTOR_14      default_isr     // 0x0000_0038 14 -         ARM core         Pendable request for system service (PendableSrvReq)
#define VECTOR_15      default_isr     // 0x0000_003C 15 -         ARM core         System tick timer (SysTick)
#define VECTOR_16      default_isr     // 0x0000_0040 16     0     DMA              DMA Channel 0 transfer complete
#define VECTOR_17      default_isr     // 0x0000_0044 17     1     DMA              DMA Channel 1 transfer complete
#define VECTOR_18      default_isr     // 0x0000_0048 18     2     DMA              DMA Channel 2 transfer complete
#define VECTOR_19      default_isr     // 0x0000_004C 19     3     DMA              DMA Channel 3 transfer complete
#define VECTOR_20      default_isr     // 0x0000_0050 20     4     DMA              DMA Channel 4 transfer complete
#define VECTOR_21      default_isr     // 0x0000_0054 21     5     DMA              DMA Channel 5 transfer complete
#define VECTOR_22      default_isr     // 0x0000_0058 22     6     DMA              DMA Channel 6 transfer complete
#define VECTOR_23      default_isr     // 0x0000_005C 23     7     DMA              DMA Channel 7 transfer complete
#define VECTOR_24      default_isr     // 0x0000_0060 24     8     DMA              DMA Channel 8 transfer complete
#define VECTOR_25      default_isr     // 0x0000_0064 25     9     DMA              DMA Channel 9 transfer complete
#define VECTOR_26      default_isr     // 0x0000_0068 26    10     DMA              DMA Channel 10 transfer complete
#define VECTOR_27      default_isr     // 0x0000_006C 27    11     DMA              DMA Channel 11 transfer complete
#define VECTOR_28      default_isr     // 0x0000_0070 28    12     DMA              DMA Channel 12 transfer complete
#define VECTOR_29      default_isr     // 0x0000_0074 29    13     DMA              DMA Channel 13 transfer complete
#define VECTOR_30      default_isr     // 0x0000_0078 30    14     DMA              DMA Channel 14 transfer complete
#define VECTOR_31      default_isr     // 0x0000_007C 31    15     DMA              DMA Channel 15 transfer complete
#define VECTOR_32      default_isr     // 0x0000_0080 32    16     DMA              DMA Error Interrupt Channels 0-15
#define VECTOR_33      default_isr     // 0x0000_0084 33    17     MCM              Normal interrupt
#define VECTOR_34      default_isr     // 0x0000_0088 34    18     Flash memory     Command Complete
#define VECTOR_35      default_isr     // 0x0000_008C 35    19     Flash memory     Read Collision
#define VECTOR_36      default_isr     // 0x0000_0090 36    20     Mode Controller  Low Voltage Detect,Low Voltage Warning, Low Leakage Wakeup
#define VECTOR_37      default_isr     // 0x0000_0094 37    21     LLWU
#define VECTOR_38      default_isr     // 0x0000_0098 38    22     WDOG
#define VECTOR_39      default_isr     // 0x0000_009C 39    23		RNGB
#define VECTOR_40      default_isr     // 0x0000_00A0 40    24     I2C0
#define VECTOR_41      default_isr     // 0x0000_00A4 41    25     I2C1
#define VECTOR_42      default_isr     // 0x0000_00A8 42    26     SPI0             Single interrupt vector for all sources
#define VECTOR_43      default_isr     // 0x0000_00AC 43    27     SPI1             Single interrupt vector for all sources
#define VECTOR_44      default_isr     // 0x0000_00B0 44    28     SPI2             Single interrupt vector for all sources
#define VECTOR_45      default_isr     // 0x0000_00B4 45    29     CAN0             OR'ed Message buffer (0-15)
#define VECTOR_46      default_isr     // 0x0000_00B8 46    30     CAN0             Bus Off
#define VECTOR_47      default_isr     // 0x0000_00BC 47    31     CAN0             Error
#define VECTOR_48      default_isr     // 0x0000_00C0 48    32     CAN0             Transmit Warning
#define VECTOR_49      default_isr     // 0x0000_00C4 49    33     CAN0             Receive Warning
#define VECTOR_50      default_isr     // 0x0000_00C8 50    34     CAN0             Wake Up
#define VECTOR_51      default_isr     // 0x0000_00CC 51    35     CAN0             Individual Matching Elements Update (IMEU)
#define VECTOR_52      default_isr     // 0x0000_00D0 52    36     CAN0             Lost receive
#define VECTOR_53      default_isr     // 0x0000_00D4 53    37     CAN1             OR'ed Message buffer (0-15)
#define VECTOR_54      default_isr     // 0x0000_00D8 54    38     CAN1             Bus off
#define VECTOR_55      default_isr     // 0x0000_00DC 55    39     CAN1             Error
#define VECTOR_56      default_isr     // 0x0000_00E0 56    40     CAN1             Transmit Warning
#define VECTOR_57      default_isr     // 0x0000_00E4 57    41     CAN1             Receive Warning
#define VECTOR_58      default_isr     // 0x0000_00E8 58    42     CAN1             Wake Up
#define VECTOR_59      default_isr     // 0x0000_00EC 59    43     CAN1             Individual Matching Elements Update (IMEU)
#define VECTOR_60      default_isr     // 0x0000_00F0 60    44     CAN1             Lost receive 
#define VECTOR_61      default_isr     // 0x0000_00F4 61    45     UART0            Single interrupt vector for UART status sources
#define VECTOR_62      default_isr     // 0x0000_00F8 62    46     UART0            Single interrupt vector for UART error sources
#define VECTOR_63      default_isr     // 0x0000_00FC 63    47     UART1            Single interrupt vector for UART status sources
#define VECTOR_64      default_isr     // 0x0000_0100 64    48     UART1            Single interrupt vector for UART error sources
#define VECTOR_65      default_isr     // 0x0000_0104 65    49     UART2            Single interrupt vector for UART status sources
#define VECTOR_66      default_isr     // 0x0000_0108 66    50     UART2            Single interrupt vector for UART error sources
#define VECTOR_67      default_isr     // 0x0000_010C 67    51     UART3            Single interrupt vector for UART status sources
#define VECTOR_68      default_isr     // 0x0000_0110 68    52     UART3            Single interrupt vector for UART error sources
#define VECTOR_69      default_isr     // 0x0000_0114 69    53     UART4            Single interrupt vector for UART status sources
#define VECTOR_70      default_isr     // 0x0000_0118 70    54     UART4            Single interrupt vector for UART error sources
#define VECTOR_71      default_isr     // 0x0000_011C 71    55     UART5            Single interrupt vector for UART status sources
#define VECTOR_72      default_isr     // 0x0000_0120 72    56     UART5            Single interrupt vector for UART error sources
#define VECTOR_73      default_isr     // 0x0000_0124 73    57     ADC0
#define VECTOR_74      default_isr     // 0x0000_0128 74    58     ADC1
#define VECTOR_75      default_isr     // 0x0000_012C 75    59     CMP0             High-speed comparator 
#define VECTOR_76      default_isr     // 0x0000_0130 76    60     CMP1
#define VECTOR_77      default_isr     // 0x0000_0134 77    61     CMP2
#define VECTOR_78      default_isr     // 0x0000_0138 78    62     FTM0 			 Single interrupt vector for all sources
#define VECTOR_79      default_isr     // 0x0000_013C 79    63     FTM1 			 Single interrupt vector for all sources
#define VECTOR_80      default_isr     // 0x0000_0140 80    64     FTM2 			 Single interrupt vector for all sources
#define VECTOR_81      default_isr     // 0x0000_0144 81    65     CMT
#define VECTOR_82      default_isr     // 0x0000_0148 82    66     RTC Timer interrupt
#define VECTOR_83      default_isr     // 0x0000_014C 83    67
#define VECTOR_84      default_isr     // 0x0000_0150 84    68     PIT Channel 0
#define VECTOR_85      default_isr     // 0x0000_0154 85    69     PIT Channel 1
#define VECTOR_86      default_isr     // 0x0000_0158 86    70     PIT Channel 2
#define VECTOR_87      default_isr     // 0x0000_015C 87    71     PIT Channel 3
#define VECTOR_88      default_isr     // 0x0000_0160 88    72     PDB
#define VECTOR_89      default_isr     // 0x0000_0164 89    73     USB OTG
#define VECTOR_90      default_isr     // 0x0000_0168 90    74     USB Charger Detect
#define VECTOR_91      default_isr     // 0x0000_016C 91    75		ENET			 IEEE 1588 Timer interrupt			 
#define VECTOR_92      default_isr     // 0x0000_0170 92    76		ENET			 Transmit interrupt
#define VECTOR_93      default_isr     // 0x0000_0174 93    77		ENET			 Receive interrupt
#define VECTOR_94      default_isr     // 0x0000_0178 94    78		ENET			 Error and miscellaneous interrupt
#define VECTOR_95      default_isr     // 0x0000_017C 95    79     I2S
#define VECTOR_96      default_isr     // 0x0000_0180 96    80     SDHC
#define VECTOR_97      default_isr     // 0x0000_0184 97    81     DAC0
#define VECTOR_98      default_isr     // 0x0000_0188 98    82     DAC1
#define VECTOR_99      default_isr     // 0x0000_018C 99    83     TSI 			 Single interrupt vector for all sources
#define VECTOR_100      default_isr     // 0x0000_0190 100   84     MCG
#define VECTOR_101      default_isr     // 0x0000_0194 101   85     Low Power Timer
#define VECTOR_102      default_isr     // 0x0000_0198 102   86     Segment LCD 	 Single interrupt vector for all sources
#define VECTOR_103      default_isr     // 0x0000_019C 103   87     Port control module Pin Detect (Port A)
#define VECTOR_104      default_isr     // 0x0000_01A0 104   88     Port control module Pin Detect (Port B)
#define VECTOR_105      default_isr     // 0x0000_01A4 105   89     Port control module Pin Detect (Port C)
#define VECTOR_106      default_isr     // 0x0000_01A8 106   90     Port control module Pin Detect (Port D)
#define VECTOR_107      default_isr     // 0x0000_01AC 107   91     Port control module Pin Detect (Port E)
#define VECTOR_108      default_isr     // 0x0000_01B0 108   92    
#define VECTOR_109      default_isr     // 0x0000_01B4 109   93    
#define VECTOR_110      default_isr     // 0x0000_01B8 110   94    
#define VECTOR_111      default_isr     // 0x0000_01BC 111   95    
#define VECTOR_112      default_isr     // 0x0000_01C0 112   96    
#define VECTOR_113      default_isr     // 0x0000_01C4 113   97    
#define VECTOR_114      default_isr     // 0x0000_01C8 114   98    
#define VECTOR_115      default_isr     // 0x0000_01CC 115   99    
#define VECTOR_116      default_isr     // 0x0000_01D0 116   100
#define VECTOR_117      default_isr     // 0x0000_01D4 117   101
#define VECTOR_118      default_isr     // 0x0000_01D8 118   102
#define VECTOR_119      default_isr     // 0x0000_01DC 119   103
#define VECTOR_120      default_isr     // 
#define VECTOR_121      default_isr     // 
#define VECTOR_122      default_isr     // 
#define VECTOR_123      default_isr     // 
#define VECTOR_124      default_isr     // 
#define VECTOR_125      default_isr     // 
#define VECTOR_126      default_isr     // 
#define VECTOR_127      default_isr     // 
#define VECTOR_128      default_isr     // 
#define VECTOR_129      default_isr     // 
#define VECTOR_130      default_isr     // 
#define VECTOR_131      default_isr     // 
#define VECTOR_132      default_isr     // 
#define VECTOR_133      default_isr     // 
#define VECTOR_134      default_isr     // 
#define VECTOR_135      default_isr     // 
#define VECTOR_136      default_isr     // 
#define VECTOR_137      default_isr     // 
#define VECTOR_138      default_isr     // 
#define VECTOR_139      default_isr     // 
#define VECTOR_140      default_isr     // 
#define VECTOR_141      default_isr     // 
#define VECTOR_142      default_isr     // 
#define VECTOR_143      default_isr     // 
#define VECTOR_144      default_isr     // 
#define VECTOR_145      default_isr     // 
#define VECTOR_146      default_isr     // 
#define VECTOR_147      default_isr     // 
#define VECTOR_148      default_isr     // 
#define VECTOR_149      default_isr     // 
#define VECTOR_150      default_isr     // 
#define VECTOR_151      default_isr     // 
#define VECTOR_152      default_isr     // 
#define VECTOR_153      default_isr     // 
#define VECTOR_154      default_isr     // 
#define VECTOR_155      default_isr     // 
#define VECTOR_156      default_isr     // 
#define VECTOR_157      default_isr     // 
#define VECTOR_158      default_isr     // 
#define VECTOR_159      default_isr     // 
#define VECTOR_160      default_isr     // 
#define VECTOR_161      default_isr     // 
#define VECTOR_162      default_isr     // 
#define VECTOR_163      default_isr     // 
#define VECTOR_164      default_isr     // 
#define VECTOR_165      default_isr     // 
#define VECTOR_166      default_isr     // 
#define VECTOR_167      default_isr     // 
#define VECTOR_168      default_isr     // 
#define VECTOR_169      default_isr     // 
#define VECTOR_170      default_isr     // 
#define VECTOR_171      default_isr     // 
#define VECTOR_172      default_isr     // 
#define VECTOR_173      default_isr     // 
#define VECTOR_174      default_isr     // 
#define VECTOR_175      default_isr     // 
#define VECTOR_176      default_isr     // 
#define VECTOR_177      default_isr     // 
#define VECTOR_178      default_isr     // 
#define VECTOR_179      default_isr     // 
#define VECTOR_180      default_isr     // 
#define VECTOR_181      default_isr     // 
#define VECTOR_182      default_isr     // 
#define VECTOR_183      default_isr     // 
#define VECTOR_184      default_isr     // 
#define VECTOR_185      default_isr     // 
#define VECTOR_186      default_isr     // 
#define VECTOR_187      default_isr     // 
#define VECTOR_188      default_isr     // 
#define VECTOR_189      default_isr     // 
#define VECTOR_190      default_isr     // 
#define VECTOR_191      default_isr     // 
#define VECTOR_192      default_isr     // 
#define VECTOR_193      default_isr     // 
#define VECTOR_194      default_isr     // 
#define VECTOR_195      default_isr     // 
#define VECTOR_196      default_isr     // 
#define VECTOR_197      default_isr     // 
#define VECTOR_198      default_isr     // 
#define VECTOR_199      default_isr     // 
#define VECTOR_200      default_isr     // 
#define VECTOR_201      default_isr     // 
#define VECTOR_202      default_isr     // 
#define VECTOR_203      default_isr     // 
#define VECTOR_204      default_isr     // 
#define VECTOR_205      default_isr     // 
#define VECTOR_206      default_isr     // 
#define VECTOR_207      default_isr     // 
#define VECTOR_208      default_isr     // 
#define VECTOR_209      default_isr     // 
#define VECTOR_210      default_isr     // 
#define VECTOR_211      default_isr     // 
#define VECTOR_212      default_isr     // 
#define VECTOR_213      default_isr     // 
#define VECTOR_214      default_isr     // 
#define VECTOR_215      default_isr     // 
#define VECTOR_216      default_isr     // 
#define VECTOR_217      default_isr     // 
#define VECTOR_218      default_isr     // 
#define VECTOR_219      default_isr     // 
#define VECTOR_220      default_isr     // 
#define VECTOR_221      default_isr     // 
#define VECTOR_222      default_isr     // 
#define VECTOR_223      default_isr     // 
#define VECTOR_224      default_isr     // 
#define VECTOR_225      default_isr     // 
#define VECTOR_226      default_isr     // 
#define VECTOR_227      default_isr     // 
#define VECTOR_228      default_isr     // 
#define VECTOR_229      default_isr     // 
#define VECTOR_230      default_isr     // 
#define VECTOR_231      default_isr     // 
#define VECTOR_232      default_isr     // 
#define VECTOR_233      default_isr     // 
#define VECTOR_234      default_isr     // 
#define VECTOR_235      default_isr     // 
#define VECTOR_236      default_isr     // 
#define VECTOR_237      default_isr     // 
#define VECTOR_238      default_isr     // 
#define VECTOR_239      default_isr     // 
#define VECTOR_240      default_isr     // 
#define VECTOR_241      default_isr     // 
#define VECTOR_242      default_isr     // 
#define VECTOR_243      default_isr     // 
#define VECTOR_244      default_isr     // 
#define VECTOR_245      default_isr     // 
#define VECTOR_246      default_isr     // 
#define VECTOR_247      default_isr     // 
#define VECTOR_248      default_isr     // 
#define VECTOR_249      default_isr     // 
#define VECTOR_250      default_isr     // 
#define VECTOR_251      default_isr     // 
#define VECTOR_252      default_isr     // 
#define VECTOR_253      default_isr     // 
#define VECTOR_254      default_isr     // 
#define VECTOR_255      default_isr     // 
#define CONFIG_1		(pointer*)0xffffffff
#define CONFIG_2		(pointer*)0xffffffff
#define CONFIG_3		(pointer*)0xffffffff
#define CONFIG_4		(pointer*)0xfffffffe

#endif /*__VECTORS_H*/

/* End of "vectors.h" */