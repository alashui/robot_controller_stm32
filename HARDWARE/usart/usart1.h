#ifndef _USART1_H
#define _USART1_H

#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 

//#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
#define REC_DATA_LEN 12	     //定义最大接收字节数 12
	  	
//extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	


//定义一个共用体，使浮点数和字符数组公用存储单元
//发送或接受使用字符组，计算使用浮点数
union union_read
	{	
    unsigned char buf[12];
    struct Float_r
					{
            float hander;
            float v;
            float w;
					}Float_RAM;
	};
union union_send
	{	
    unsigned char buf[12];
    struct Float_w
					{
            float hander;
            float v;
            float w;
					}Float_RAM;
	};
	
extern union union_read Read_Data;	
extern union union_send Send_Data;

void My_USART1_Init(void);
void USART1_IRQHandler(void);
void uart1SendChar(u8 ch);
void uart1SendChars(u8 *str, u16 strlen);
int USART1_Receive(const char *str);


#endif
