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
***��������HLK_uart_init()
***���ܣ����ڳ�ʼ��
***��������
***���أ���
*************************************************************************************/
void HLK_uart_init(void)
{
	CLKCON = CLKCON& ~(0x3<<5);	   //����ϵͳʱ��
	uart_len=0;
			//4800
	PCON=(1<<7);   //�����ʼӱ�	   SSTAT=0
	SCON=((1<<6)|(1<<5)|(1<<4));
//	SBUF=0;
	SADDR=0;
	SADEN=0;


	TR1=0;
	TMOD &= ~((1<<7)||(1<<6)||(3<<4));
	TMOD |= ((2<<4));		 //8λ������  ��ʱ��1�����ڷ�ʽ2
	TCON1 &= ~((1<<6)||(1<<3)||(1<<1));
	TCON1 |= ((1<<3));	 //ϵͳʱ����Ϊ��ʱ��ʱ��


//	TH1=0xff-0x08;	//115200
//	TL1=0xff-0x08;
	TH1=256-9;	//115200
	TL1=256-9;

//	TH1=256-109;  //115200
//	TL1=256-109;

	TR1=1;
	ES0=1; //����uart�ж�
	TI=0;
	RI=0;
	EA=1;  

	
}
/*************************************************************************************
***��������HLK_uart_read_TimeOut()
***���ܣ�����������
***������
					date:���ݴ�Ż���
					len:���Զ�ȡ�ĳ���
***���أ����ݳ���
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
***��������HLK_uart_read_TimeOut()
***���ܣ�����������
***������
					date:���ݴ�Ż���
					len:���Զ�ȡ�ĳ���
					TimeOut:���ƶ�ȡ����ʱ��
***���أ����ݳ���
*************************************************************************************/
 uint HLK_uart_read_TimeOut(uchar * date,uint len,uint TimeOut)
 {
	 uint iret=0; //date��λ��ָʾ
	 
	 do{
		 mdelay(1);
		 
			 ES0=0;
		 if(uart_len){  //��Ϊ0�ͱ�ʾ������
		 	uchar x;
			if((iret+uart_len)<=len)
				x=uart_len;
			else
				x=len-iret;  //iretע�����ᳬ��len
			
			 memcpy(date+iret,uart_buf,(uint)x);
			 iret+=x;
			 uart_len=uart_len-x;  //ȥ���Ѿ�copy��
		 }
		 ES0=1;
	 }while((iret<len)&&(0 != TimeOut--));  //���յ�ָ�����ȵ����ݻ���ʱ�䵽
	 
	 return iret;
 }
 
/*************************************************************************************
***��������HLK_uart_clear_rx()
***���ܣ��崮������
***��������
***���أ���
*************************************************************************************/
 void HLK_uart_clear_rx(void)
 {
	 ES0=0;
	 uart_len=0;
	 ES0=1;
 }
/*************************************************************************************
***��������HLK_strlen()
***���ܣ����ַ�������
***�������ַ���
***���أ���
*************************************************************************************/
 unsigned int HLK_strlen(const char *str)
{
	unsigned int i;
	for (i = 0; str[i]!= '\0'; i++)
		;
	return i;
}
/*************************************************************************************
***��������print_char()
***���ܣ��Ӵ��ڴ�ӡһ���ֽ�
***������һ���ֽ�
***���أ���
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
***��������HLK_Printf()
***���ܣ����ڴ�ӡ�ַ���
***��������Ҫ�Ӵ������������
***���أ���
*************************************************************************************/
void HLK_Printf(char *str)
{
	unsigned char len=HLK_strlen(str);
	while(len--){
		 print_char(*(str++));
	 }
} 
/*************************************************************************************
***��������UART_int()
***���ܣ����ڽ����жϺ���
***��������
***���أ���
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