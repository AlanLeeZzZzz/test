 /*
 ***************************************************************************
 * (c) Copyright, Shenzhen Hi-Link ElectronicTechnology co.,Ltd/HI-LINK(HK) CO.,LIMITED.
 * All Rights Reserved.
 *
 *Shenzhen Hi-Link ElectronicTechnology co.,Ltd/HI-LINK(HK) CO.,LIMITED
 *3F.5# Building,Minxing Industrial Park
 *MingZhi LongHua District
 *Shenzhen,China.
 *
 ***************************************************************************
 *
 */

#include "sh88f2051_uart.h"

xdata uchar uart_buf[64];
uchar uart_len=0;
uchar uart_tx_buf[6];
uchar uart_tx_len=0;

uchar UART_TX_IDLE=0;

uchar delay(uchar xx)
 {
	 uint i,j;
	 for(;xx>0;xx--){
		 for(i=0;i<1000;i++){
			 j++;
		 }
	 }
	 return j;
 }
 
 void mdelay(uint ms)
 {
	 for(;ms;ms--){
		 delay(1);
	 }
 }

/*************************************************************************************
***函数名：HLK_uart_init()
***功能：串口初始化
***参数：无
***返回：无
*************************************************************************************/
void HLK_uart_init(void)
{
	CLKCON = CLKCON& ~(0x3<<5);	   //设置系统时钟
	uart_len=0;
			//4800
	PCON=(1<<7);   //波特率加倍	   SSTAT=0
	SCON=((1<<6)|(1<<5)|(1<<4));
//	SBUF=0;
	SADDR=0;
	SADEN=0;


	TR1=0;
	TMOD &= ~((1<<7)||(1<<6)||(3<<4));
	TMOD |= ((2<<4));		 //8位计数器  定时器1工作在方式2
	TCON1 &= ~((1<<6)||(1<<3)||(1<<1));
	TCON1 |= ((1<<3));	 //系统时钟作为定时器时钟


//	TH1=0xff-0x08;	//115200
//	TL1=0xff-0x08;
	TH1=256-9;	//115200
	TL1=256-9;

//	TH1=256-109;  //115200
//	TL1=256-109;

	TR1=1;
	ES0=1; //允许uart中断
	TI=0;
	RI=0;
	EA=1;  

	
}
/*************************************************************************************
***函数名：HLK_uart_read_TimeOut()
***功能：读串口数据
***参数：
					date:数据存放缓存
					len:可以读取的长度
***返回：数据长度
*************************************************************************************/
uint HLK_uart_read(uchar * date,uint len)
 {
	 if(uart_len<len){
		 mdelay(100);
	 }
	 if(uart_len){
		 ES0=0;
		 memcpy(date,uart_buf,uart_len);
		 uart_len=0;
		 ES0=1;
	 }	   
	 return 0;
 }
/*************************************************************************************
***函数名：HLK_uart_read_TimeOut()
***功能：读串口数据
***参数：
					date:数据存放缓存
					len:可以读取的长度
					TimeOut:限制读取数据时间
***返回：数据长度
*************************************************************************************/
 uint HLK_uart_read_TimeOut(uchar * date,uint len,uint TimeOut)
 {
	 uint iret=0; //date的位置指示
	 
	 do{
		 mdelay(1);
		 
			 ES0=0;
		 if(uart_len){  //不为0就表示有数据
		 	uchar x;
			if((iret+uart_len)<=len)
				x=uart_len;
			else
				x=len-iret;  //iret注定不会超过len
			
			 memcpy(date+iret,uart_buf,(uint)x);
			 iret+=x;
			 uart_len=uart_len-x;  //去除已经copy的
		 }
		 ES0=1;
	 }while((iret<len)&&(0 != TimeOut--));  //接收到指定长度的数据或者时间到
	 
	 return iret;
 }
 
/*************************************************************************************
***函数名：HLK_uart_clear_rx()
***功能：清串口数据
***参数：无
***返回：无
*************************************************************************************/
 void HLK_uart_clear_rx(void)
 {
	 ES0=0;
	 uart_len=0;
	 ES0=1;
 }
/*************************************************************************************
***函数名：HLK_strlen()
***功能：求字符串长度
***参数：字符串
***返回：无
*************************************************************************************/
 unsigned int HLK_strlen(const char *str)
{
	unsigned int i;
	for (i = 0; str[i]!= '\0'; i++)
		;
	return i;
}
/*************************************************************************************
***函数名：print_char()
***功能：从串口打印一个字节
***参数：一个字节
***返回：无
*************************************************************************************/
 void print_char(unsigned char v)
 {		 
	 ES0=0;
	 TI=0;
	 SBUF=v;
	 while(0 == TI);
	 TI=0;
	 ES0=1;
 }
 
/*************************************************************************************
***函数名：HLK_Printf()
***功能：串口打印字符串
***参数：需要从串口输出的内容
***返回：无
*************************************************************************************/
void HLK_Printf(char *str)
{
	unsigned char len=HLK_strlen(str);
	while(len--){
		 print_char(*(str++));
	 }
} 
/*************************************************************************************
***函数名：UART_int()
***功能：串口接收中断函数
***参数：无
***返回：无
*************************************************************************************/
 void UART_int (void) interrupt 4
{
 uchar x;
 
 if(RI){
	 RI=0;
	 x=SBUF;
	 if(sizeof(uart_buf) > uart_len){
		 uart_buf[uart_len++]=x;
	 }
	 else{
		 ;
	 }
 }
 
 if(TI){
	 TI=0;
	 if(uart_tx_len){
		 UART_TX_IDLE=0;
		 SBUF=uart_tx_buf[6-(uart_tx_len--)];
	 }
	 else{
		 UART_TX_IDLE=1;
	 }
 }
}