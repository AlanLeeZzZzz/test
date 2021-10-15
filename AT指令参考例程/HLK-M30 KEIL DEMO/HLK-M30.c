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
#include "HLK-M30.h"

unsigned char buf[65];

/*************************************************************************************
***函数名：HLK_IsATMode()
***功能：判断是否进入at指令模式
***参数：无
***返回：0：未进入at指令模式 1：已经进入at指令模式
*************************************************************************************/
unsigned char HLK_IsATMode()
{
	uchar len;
	HLK_uart_clear_rx();
	HLK_Printf("at+ver=?\r\n");
	len=HLK_uart_read_TimeOut(buf,sizeof(buf),300);
	buf[len]=0;
	if(0 == strstr(buf,"at+ver")){              		 //查找接收到的字符是否有at+ver字样
		return 0;                                      //返回0表示为未进入at指令模式
	}
	return 1;                                        //返回1表示为已进入at指令模式
}
/*************************************************************************************
***函数名：HLK_PrintInt()
***功能：将一个整数从串口打印出来
***参数：整数
***返回：无
*************************************************************************************/
void HLK_PrintInt(unsigned long a)
{
    unsigned char i;
    unsigned char s[8]={0,0,0,0,0,0,0,0};
    s[0]=0;
    do{
        for(i=7;i>0;i--)s[i]=s[i-1];
        s[0]=a%10+'0';
        a/=10;
    }while(a>0);

		HLK_Printf(s);
}

/*************************************************************************************
***函数名：HLK_M30_STA_Manual()
***功能：设置模块为STA模式
***参数：
        ssid：要连接的网络名称
				Encryption:加密方式
							0：NONE
							1：WEP_SHARE
							2：WEP_OPEN
							4：WPA_AES
							7：WPA2_AES
							9：WPA/WPA2_AES
				pwd:  连接wifi的密码
***返回：无
*************************************************************************************/
void HLK_M30_STA_Manual(char *ssid,char Encryption, char *pwd)
{
	unsigned int ssidl=HLK_strlen(ssid);
	unsigned int pwdl =HLK_strlen(pwd);
	
	HLK_Printf("at+WM=2\r\n");
	HLK_Printf("at+Sssid=");HLK_Printf(ssid);HLK_Printf("\r\n");
	HLK_Printf("at+Sssidl=");HLK_PrintInt(ssidl);HLK_Printf("\r\n");
	HLK_Printf("at+Sam=");HLK_PrintInt(Encryption);HLK_Printf("\r\n");
	HLK_Printf("at+Spw=");HLK_Printf(pwd);HLK_Printf("\r\n");
	HLK_Printf("at+Spwl=");HLK_PrintInt(pwdl);HLK_Printf("\r\n");
	HLK_Printf("at+dhcp=0\r\n");                     //0:设置静态ip,1:自动获取ip
	HLK_Printf("at+ip=192,168,11,99\r\n");
	HLK_Printf("at+mask=255,255,255,0\r\n");
	HLK_Printf("at+gw=192,168,11,1\r\n");
	HLK_Printf("at+dns=192,168,11,1\r\n");
	HLK_Printf("at+UType=1\r\n");
	HLK_Printf("at+UIp=192.168.0.1\r\n");
	HLK_Printf("at+URPort=8080\r\n");
	HLK_Printf("at+ULPort=8080\r\n");
	HLK_Printf("at+Ub=115200\r\n");
	HLK_Printf("at+Ud=8\r\n");
	HLK_Printf("at+Up=0\r\n");
	HLK_Printf("at+Us=1\r\n");
	HLK_Printf("at+WC=1\r\n");
	HLK_Printf("at+Rb=1\r\n");	
}
/*************************************************************************************
***函数名：HLK_M30_ResetDefault()
***功能：将模块恢复到出厂设置
***参数：无
***返回：0：恢复出厂失败 1：恢复出厂成功
*************************************************************************************/
uchar HLK_M30_ResetDefault(void)
{
	uchar len;
	HLK_Printf("at+Df=1\r\n");
	HLK_uart_clear_rx();
	len=HLK_uart_read_TimeOut(buf,sizeof(buf),500);
	buf[len]=0;
	if(0 == strstr(buf,"ok")){              	
		return 0;                                     
	}
	return 1;                                      
	HLK_Printf("at+Rb=1\r\n");		
}









