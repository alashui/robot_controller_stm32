#ifndef _USART1_H
#define _USART1_H

#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 

//#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
#define REC_DATA_LEN 12	     //�����������ֽ��� 12
	  	
//extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	


//����һ�������壬ʹ���������ַ����鹫�ô洢��Ԫ
//���ͻ����ʹ���ַ��飬����ʹ�ø�����
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
