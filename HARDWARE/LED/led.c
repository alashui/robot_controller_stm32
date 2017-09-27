#include "led.h"
#include "stm32f4xx.h"

void LED_Init(void)
{
//����һ�����ڳ�ʼ��IO�ڵĽṹ��
	GPIO_InitTypeDef GPIO_InitStructure;
//��ʼ��IO�ڵ�ģʽ	
//��ʼ��GPIOE3��GPIOE4
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);//ʹ��GPIOE��ʱ��	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4| GPIO_Pin_5; //ѡ��Ҫ��ʼ���ľ���IO��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   //IOģʽ����������
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //���ģʽ����©�����죨�Ƿ��Ǹ��ã�
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�������ٶ�
	
	GPIO_Init(GPIOE,&GPIO_InitStructure);


//��ʼ��GPIOG9	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	
	GPIO_Init(GPIOG,&GPIO_InitStructure);
	
		
	
	GPIO_SetBits(GPIOE,GPIO_Pin_3 | GPIO_Pin_4);
	GPIO_SetBits(GPIOG,GPIO_Pin_9);
}
