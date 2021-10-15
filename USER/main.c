#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "usart3.h"
#include "esp8266.h"
#include "string.h"
#include "timer.h"
#include "led.h"
 
/*
项目的主要内容：STM32配合ESP8266模块与服务器数据交互

ESP8266的连接：USART3（PB10、PB11）

如何判断数据接收完全？
1、出现了换行符；
2、如果超过10ms了都没有下一条数据（TIM7来进行10ms的定时）。
*/


 int main(void)
 {		
	char a[15];
	delay_init();	    	 			//延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 			//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 				//串口初始化为115200
	usart3_init(115200);	 				//串口初始化为115200
	LED_Init();
	 
	esp8266_start_trans();							//esp8266进行初始化 
	
	while(1)
	{
		if(USART3_RX_STA&0x8000)
		{
			printf("USART3_RX_BUF=%s\r\n",USART3_RX_BUF);
			sprintf(a,"%s",USART3_RX_BUF);
			printf("a=%s",a);
			if(strstr((const char*)a,"on"))  GPIO_ResetBits(GPIOB,GPIO_Pin_5);
				
			if(strstr((const char*)a,"off")) GPIO_SetBits(GPIOB,GPIO_Pin_5);
				
			USART3_RX_STA=0;
		}
	}
}

 
 

