#ifndef _DEFINE51_H
#define	_DEFINE51_H

typedef	bit				Bit;
typedef	bit				Bool;
typedef	unsigned char	Byte;
typedef	unsigned int	Word;
typedef	unsigned long	Dword;
typedef	unsigned char	uchar;
typedef	unsigned int	uint;
typedef	unsigned long	ulong;
typedef	unsigned char	uint8;
typedef	unsigned int	uint16;
typedef	unsigned long	uint32;
typedef signed char  	int8;
typedef	signed int  	int16;
typedef	signed long	    int32;


#define	MAKE_DWORD(v1,v2) (((Dword)(v1)<<16) + (Dword)(v2))
#define	MAKE_WORD(v1,v2)  (((Word)(v1)<<8) + (Word)(v2))
#define	HI_WORD(v1)	 	  ((Word)((v1)>>16))
#define	LO_WORD(v1)		  ((Word)((v1)&0xffff))
#define	HI_BYTE(v1)	 	  ((Byte)((v1)>>8))
#define	LO_BYTE(v1)		  ((Byte)((v1)&0xff))

#define	BYTE_0(v1)	 	  ((char *)(&v1))[0]
#define	BYTE_1(v1)	 	  ((char *)(&v1))[1]
#define	BYTE_2(v1)	 	  ((char *)(&v1))[2]
#define	BYTE_3(v1)	 	  ((char *)(&v1))[3]

#define LongToBin(n) \
(                    \
((n >> 21) & 0x80) | \
((n >> 18) & 0x40) | \
((n >> 15) & 0x20) | \
((n >> 12) & 0x10) | \
((n >>  9) & 0x08) | \
((n >>  6) & 0x04) | \
((n >>  3) & 0x02) | \
((n      ) & 0x01)   \
)
#define Bin(n) LongToBin(0x##n##l)	//write binary charactor set,exsample : Bin(11111111) = 0xff

#endif
