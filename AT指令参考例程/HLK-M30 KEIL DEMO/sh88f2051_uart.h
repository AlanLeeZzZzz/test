#ifndef _sh88f2051_uart_c_
#define _sh88f2051_uart_c_

#include <88F2051.h>
#include "string.h"

#ifndef   uchar
#define   uchar   unsigned char
#endif
#ifndef   uint
#define   uint    unsigned int
#endif
#ifndef   ushort  
#define   ushort  unsigned short
#endif
#ifndef   ulong
#define   ulong   unsigned long
#endif

extern xdata uchar uart_buf[64];
extern uchar uart_len;
extern uchar uart_tx_buf[6];
extern uchar uart_tx_len;

extern uchar UART_TX_IDLE;

void HLK_uart_init(void);
uchar delay(uchar xx);
void mdelay(uint ms);
uint HLK_uart_read(uchar * date,uint len);
uint HLK_uart_read_TimeOut(uchar * date,uint len,uint TimeOut);
void HLK_uart_clear_rx(void);
void HLK_Printf(char *str);
unsigned int HLK_strlen(const char *str);


#endif