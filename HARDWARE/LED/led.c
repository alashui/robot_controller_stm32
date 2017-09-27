#include "led.h"
#include "stm32f4xx.h"

void LED_Init(void)
{
//定义一个用于初始化IO口的结构体
	GPIO_InitTypeDef GPIO_InitStructure;
//初始化IO口的模式	
//初始化GPIOE3，GPIOE4
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);//使能GPIOE的时钟	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4| GPIO_Pin_5; //选择要初始化的具体IO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   //IO模式：输入或输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //输出模式：开漏或推挽（是否是复用）
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//上拉下拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//最大输出速度
	
	GPIO_Init(GPIOE,&GPIO_InitStructure);


//初始化GPIOG9	
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
