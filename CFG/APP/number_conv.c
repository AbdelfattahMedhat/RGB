#define F_CPU 8000000
#include <util/delay.h>
#include "STDTYPES.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "LCD_interface.h"
#include "KeyPAd_interface.h"
#include "number_conv_interface.h"
u32 Number=0;
void number_conv_init(void)
{
	LCD_SetCursor(FIRST,1);
	LCD_writestring("converter  by");
	LCD_SetCursor(SECOND,2);
	LCD_writestring("ABDELFATTAH");
	_delay_ms(1000);
}

void Get_Operation(num_conv_op_type num)
{
	num_conv_op_type flag='0';
	switch(num)
	{
		case DEC:
		LCD_writestring("DEC FOR");
		LCD_SetCursor(SECOND,LINE_START);
		LCD_writestring("1.HEX 2.BIN");
		while(flag=='0' || flag>MIN_OPERATION_NUM)
		{
			flag=keypad_getnumber();
		}
		if(flag=='1')
		{
			Conv_From_Dec_To_Hex();
		}
		else if(flag=='2')
		{
			Conv_From_Dec_To_Bin();
		}
		break;
		case HEX:
		LCD_writestring("HEX FOR");
		LCD_SetCursor(SECOND,LINE_START);
		LCD_writestring("1.DEC 2.BIN");
		while(flag=='0' || flag>MIN_OPERATION_NUM)
		{
			flag=keypad_getnumber();
		}
		if(flag=='1')
		{
			Conv_From_Hex_To_Dec();
		}
		else if(flag=='2')
		{
			Conv_From_Hex_To_Bin();
		}
		break;
		case BIN:
		LCD_writestring("BIN FOR");
		LCD_SetCursor(SECOND,LINE_START);
		LCD_writestring("1.DEC 2.HEX");
		while(flag=='0' || flag>MIN_OPERATION_NUM)
		{
			flag=keypad_getnumber();
		}
		if(flag=='1')
		{
			Conv_From_Bin_To_Dec();
		}
		else if(flag=='2')
		{
			Conv_From_Bin_To_Hex();
		}
		break;
	}
	num=0;
	
}

void number_conv_write_DEC(u16 num)
{
	LCD_writeNumber(num);
}
void number_conv_write_HEX(u16 num)
{ 
 	LCD_WriteHex(num/(16*16));
 	LCD_WriteHex(num);

}
void number_conv_write_BIN(u16 num)
{
u8 flag=0,counter=0;
for(s8 i=15;i>=0;i--)
{
	if(flag==1 || READ_BIT(num,i))
	{
		LCD_writechar(READ_BIT(num,i)+'0');
		flag=1;
		counter++;
	}
	
}
}

void Conv_From_Dec_To_Hex(void)
{
	u8 digit=0;
	u32 temp=0;
	LCD_Clear();
	LCD_writestring("DEC:");
	LCD_SetCursor(SECOND,LINE_START);
	LCD_writestring("HEX:");
	while(digit!='c')
	{
		 digit=keypad_getnumber();
		  
		temp=Number;
		temp=((temp*10)+(digit-'0'));
		if(digit>='0' && digit<='9' && temp<=MAX_DEC_NUM)
		{
			if(Number==0)
			{
				LCD_SetCursor(FIRST,LENGTH);
				LCD_writestring("            ");
				LCD_SetCursor(SECOND,LENGTH);
				LCD_writestring("            ");
				LCD_SetCursor(FIRST,LENGTH);
			}
			LCD_writechar(digit);
			Number=temp;	
		}
		else if(digit=='=')
		{
			LCD_SetCursor(SECOND,LENGTH);
			number_conv_write_HEX(Number);
			Number=0;
		}
		
	}
	
}
void Conv_From_Dec_To_Bin(void)
{
	u8 digit=0;
	u32 temp=0;
	LCD_Clear();
	LCD_writestring("DEC:");
	LCD_SetCursor(SECOND,LINE_START);
	LCD_writestring("BIN:");
	while(digit!='c')
	{
		digit=keypad_getnumber();
		temp=Number;
		temp=((temp*10)+(digit-'0'));
		if(digit>='0' && digit<='9' && temp<=MAX_BIN_NUM)
		{
			if(Number==0)
			{
				LCD_SetCursor(FIRST,LENGTH);
				LCD_writestring("            ");
				LCD_SetCursor(SECOND,LENGTH);
				LCD_writestring("            ");
				LCD_SetCursor(FIRST,LENGTH);
			}
			LCD_writechar(digit);
			Number=temp;
		}
		else if(digit=='=')
		{
			LCD_SetCursor(SECOND,LENGTH);
			number_conv_write_BIN(Number);
			Number=0;
		}
		
	}
}
void Conv_From_Hex_To_Dec(void)
{
	u8 digit=0,hex[4]={0};
		s8 i=3;
	LCD_Clear();
	LCD_writestring("HEX:");
	LCD_SetCursor(SECOND,LINE_START);
	LCD_writestring("DEC:");
	while(digit!='c')
	{
		digit=keypad_getnumber();
		
		if(digit=='=')
		{
			i++;
			LCD_SetCursor(SECOND,LENGTH);
			LCD_writeNumber(Hex_to_Dec(hex,i));
			for(i=0;i<4;i++)
			{
				hex[i]=0;
			}
			i=3;
		}
		else if(digit!=NO_KEY && i>=0)
		{
			if(Number==0 && i==3)
			{
				LCD_SetCursor(FIRST,LENGTH);
				LCD_writestring("            ");
				LCD_SetCursor(SECOND,LENGTH);
				LCD_writestring("            ");
				LCD_SetCursor(FIRST,LENGTH);
			}
			LCD_writechar(digit);
			hex[i]=digit;
			i--;
		}
	}
}
void Conv_From_Hex_To_Bin(void)
{
	u8 digit=0,hex[4]={0};
	s8 i=3;
	LCD_Clear();
	LCD_writestring("HEX:");
	LCD_SetCursor(SECOND,LINE_START);
	LCD_writestring("BIN:");
	while(digit!='c')
	{
		digit=keypad_getnumber();
		
		if(digit=='=')
		{
			i++;
			LCD_SetCursor(SECOND,LENGTH);
			number_conv_write_BIN(Hex_to_Dec(hex,i));
			for(i=0;i<4;i++)
			{
				hex[i]=0;
			}
			i=3;
		}
		else if(digit!=NO_KEY && i>0)
		{
			if(Number==0 && i==3)
			{
				LCD_SetCursor(FIRST,LENGTH);
				LCD_writestring("            ");
				LCD_SetCursor(SECOND,LENGTH);
				LCD_writestring("            ");
				LCD_SetCursor(FIRST,LENGTH);
			}
			LCD_writechar(digit);
			hex[i]=digit;
			i--;
		}
	}
}
void Conv_From_Bin_To_Dec(void)
{
	u8 digit=0,bin[12]={0};
	s8 i=11;
	LCD_Clear();
	LCD_writestring("BIN:");
	LCD_SetCursor(SECOND,LINE_START);
	LCD_writestring("DEC:");
	while(digit!='c')
	{
		digit=keypad_getnumber();
		
		if(digit=='=')
		{
			i++;
			LCD_SetCursor(SECOND,LENGTH);
			LCD_writeNumber(Bin_to_Dec(bin,i));
			for(i=0;i<12;i++)
			{
				bin[i]=0;
			}
			i--;
		}
		else if((digit=='0' || digit=='1')&&i>=0)//3 is least index in bin array
		{
			if(i==11)
			{
				LCD_SetCursor(FIRST,LENGTH);
				LCD_writestring("            ");
				LCD_SetCursor(SECOND,LENGTH);
				LCD_writestring("            ");
				LCD_SetCursor(FIRST,LENGTH);
			}
			LCD_writechar(digit);
			bin[i]=digit;
			i--;
		}
	}
}
void Conv_From_Bin_To_Hex(void)
{
	u8 digit=0,bin[12]={0};
	s8 i=11;
	LCD_Clear();
	LCD_writestring("BIN:");
	LCD_SetCursor(SECOND,LINE_START);
	LCD_writestring("HEX:");
	while(digit!='c')
	{
		digit=keypad_getnumber();
		
		if(digit=='=')
		{
			i++;
			LCD_SetCursor(SECOND,LENGTH);
			number_conv_write_HEX(Bin_to_Dec(bin,i));
			for(i=0;i<12;i++)
			{
				bin[i]=0;
			}
			i--;
		}
		else if((digit=='0' || digit=='1')&&i>=0)//3 is least index in bin array
		{
			if(i==11)
			{
				LCD_SetCursor(FIRST,LENGTH);
				LCD_writestring("            ");
				LCD_SetCursor(SECOND,LENGTH);
				LCD_writestring("            ");
				LCD_SetCursor(FIRST,LENGTH);
			}
			LCD_writechar(digit);
			bin[i]=digit;
			i--;
		}
	}
}
u16 Hex_to_Dec(u8 * hex,u8 size)
{
	s8 i;
	u16 num=0;
	for(i=3;i>=size;i--)
	{
		if(hex[i]>='0' && hex[i]<='9')
		num=(num*16)+(hex[i]-'0');
		else
		num=(num*16)+(hex[i]-'A'+10);
	}
	return num;
}

u16 Bin_to_Dec(u8 * bin,u8 size)
{
	s8 i;
	u16 num=0;
	for(i=11;i>=size;i--)
	{
		num=(num*2)+(bin[i]-'0');	
	}
	return num;
}