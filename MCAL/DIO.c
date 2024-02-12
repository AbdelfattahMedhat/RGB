

#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"


#include "DIO_Interface.h"
#include "DIO_Private.h"
#define PORT_SIZE 8   //bits number in ports

void DIO_Init(void)
{
		DIO_Pin_type i;
	 	for (i=PINA0;i<TOTAL_PINS;i++)
		{
	 		DIO_InitPin(i,PinsStatusArray[i]);
		}
}
void DIO_InitPin(DIO_Pin_type pin,DIO_PinStatus_type status)
{
	u8 port=pin/PORT_SIZE;
	u8 pin_num = pin%PORT_SIZE;
	switch(status)
	{
		case OUTPUT:
		switch(port)
		{
			case PA:
			SET_BIT( DDRA,pin_num);
			CLR_BIT(PORTA,pin_num);
			break;
			case PB:
			SET_BIT( DDRB,pin_num);
			CLR_BIT(PORTB,pin_num);
			break;
			case PC:
			SET_BIT( DDRC,pin_num);
			CLR_BIT(PORTC,pin_num);
			break;
			case PD:
			SET_BIT( DDRD,pin_num);
			CLR_BIT(PORTD,pin_num);
			break;		
		}
		break;
		case INFREE:
		switch(pin/8)
		{
			case PA:
			CLR_BIT(DDRA,pin_num);
			CLR_BIT(PORTA,pin_num);
			break;
			case PB:
			CLR_BIT(DDRB,pin_num);
			CLR_BIT(PORTB,pin_num);
			break;
			case PC:
			CLR_BIT(DDRC,pin_num);
			CLR_BIT(PORTC,pin_num);
			break;
			case PD:
			CLR_BIT(DDRD,pin_num);
			CLR_BIT(PORTD,pin_num);
			break;
		}
		break;
		
		case INPULL:
		switch(port)
		{
			case PA:
			CLR_BIT(DDRA,pin_num);
			SET_BIT(PORTA,pin_num);
			break;
			case PB:
			CLR_BIT(DDRB,pin_num);
			SET_BIT(PORTB,pin_num);
			break;
			case PC:
			CLR_BIT(DDRC,pin_num);
			SET_BIT(PORTC,pin_num);
			break;
			case PD:
			CLR_BIT(DDRD,pin_num);
			SET_BIT(PORTD,pin_num);
			break;
		}
		break;
	}
}



void DIO_WritePin(DIO_Pin_type pin,DIO_PinVoltage_type volt)
{
	u8 port=pin/PORT_SIZE;
	u8 pin_num = pin%PORT_SIZE;
	if (volt==HIGH)
	{
		switch(port)
		{
			case PA:
			
			SET_BIT(PORTA,pin_num);
			break;
			case PB:
			
			SET_BIT(PORTB,pin_num);
			break;
			case PC:
			
			SET_BIT(PORTC,pin_num);
			break;
			case PD:
			
			SET_BIT(PORTD,pin_num);
			break;
		}
		
	}
	else if (volt==LOW)
	{
		switch(pin/8)
		{
			case PA:
			
			CLR_BIT(PORTA,pin_num);
			break;
			case PB:
			
			CLR_BIT(PORTB,pin_num);
			break;
			case PC:
			
			CLR_BIT(PORTC,pin_num);
			break;
			case PD:
			
			CLR_BIT(PORTD,pin_num);
			break;
		}
	}
	else
	{
		/* do nothing */
	}
	
}


DIO_PinVoltage_type DIO_ReadPin(DIO_Pin_type pin)
{
	u8 port=pin/PORT_SIZE;
	u8 pin_num = pin%PORT_SIZE;
	DIO_PinVoltage_type volt=LOW;
	
	switch(port)
	{
		case PA:
		
		volt=READ_BIT(PINA,pin_num);
		break;
		case PB:
		
		volt=READ_BIT(PINB,pin_num);
		break;
		case PC:
		
		volt=READ_BIT(PINC,pin_num);
		break;
		case PD:
		
		volt=READ_BIT(PIND,pin_num);
		break;
	}
	
	return volt;
}
void DIO_TogglePin(DIO_Pin_type pin)
{
	u8 port=pin/PORT_SIZE;
	u8 pin_num = pin%PORT_SIZE;
	switch(port)
	{
		case PA:
		TOG_BIT(PORTA,pin_num);
		break;
		
		case PB:
		TOG_BIT(PORTB,pin_num);
		break;
		
		case PC:
		TOG_BIT(PORTC,pin_num);
		break;
		 
		case PD:
		TOG_BIT(PORTD,pin_num);
		break; 
	}
}
void DIO_WritePort(DIO_Port_type port,u8 value)
{
	switch(port)
	{
		case PA:
		PORTA=value;
		break;
		case PB:
		PORTB=value;
		break;
		case PC:
		PORTC=value;
		break;
		case PD:
		PORTD=value;
		break;
	}
}
u8 DIO_ReadPort(DIO_Port_type port)
{
	u8 Read=0;
	switch(port)
	{
		case PA:
		Read=PINA;
		break;
		
		case PB:
		Read=PINB;
		break;
		
		case PC:
		Read=PINC;
		break;
		
		case PD:
		Read=PIND;
		break;
	}
	return Read;
}

// Error_t DIO_ReadPin(DIO_Port_type port,u8 pin_num,DIO_PinVoltage_type*Pvolt)
// {
// 	if (Pvolt==NULLPTR)
// 	{
// 		return NULL_PTR_ERROR;
// 	}
// 	else if ((port>PD)||(pin_num>7))
// 	{
// 	 return OUT_OF_RANGE;	
// 	}
// 	else
// 	{
// 		switch(port)
// 		{
// 			case PA:
// 			
// 			*Pvolt=READ_BIT(PINA,pin_num);
// 			break;
// 			case PB:
// 			
// 			*Pvolt=READ_BIT(PINB,pin_num);
// 			break;
// 			case PC:
// 			
// 			*Pvolt=READ_BIT(PINC,pin_num);
// 			break;
// 			case PD:
// 			
// 			*Pvolt=READ_BIT(PIND,pin_num);
// 			break;
// 		}
// 		return OK;
// 	}
// }



