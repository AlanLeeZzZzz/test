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
***��������main()
***���ܣ�������
***��������
***���أ���
*************************************************************************************/
void main()
{	
	HLK_uart_init();  
// 	HLK_M30_ResetDefault();  //��ģ��ָ�����������
	HLK_M30_STA_Manual("WIFI-mark",9, "markmarkmark123");  //wifi����ΪWIFI-mark������markmarkmark123,���ܷ�ʽΪ��WPA/WPA2_AES
	while(1)
	{

	}
		  
}