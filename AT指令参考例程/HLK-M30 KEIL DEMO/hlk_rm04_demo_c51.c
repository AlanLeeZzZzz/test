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
 
#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"

#include <88F2051.h>
#include "intrins.h"
#include "stdarg.h"
#include "sh88f2051_uart.h"
#include "hlk-m30.h"
 


/*************************************************************************************
***函数名：main()
***功能：主函数
***参数：无
***返回：无
*************************************************************************************/
void main()
{	
	HLK_uart_init();  
// 	HLK_M30_ResetDefault();  //将模块恢复到出厂设置
	HLK_M30_STA_Manual("WIFI-mark",9, "markmarkmark123");  //wifi名称为WIFI-mark，密码markmarkmark123,加密方式为：WPA/WPA2_AES
	while(1)
	{

	}
		  
}