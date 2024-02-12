#define F_CPU 8000000
#include <util/delay.h>
#include "STDTYPES.h"
#include "MemMap.h"
#include "DIO_Interface.h"
#include "ADC_Interface.h"
#include "LCD_interface.h"
#include "KeyPAd_interface.h"
#include "Sensor_interface.h"
#include "motor_interface.h"
#include "FireSystem_Interface.h"



static u16 temperature=0;
static u16 smoke=0;
static const u8* password="12345";
static u8 restart_flag=0;

void FireSystem_init(void);
void FireSystem_status_display(void)
{
	u16 temp=Temperature_SensorLM35_Output();
	u16 temp_smoke;
	if(temperature!=temp)
	{
		LCD_SetCursor(FIRST,LINE_START);
		LCD_writestring("      ");
		LCD_SetCursor(FIRST,LINE_START);
		//LCD_writeNumber(temperature);
		LCD_writeNumber(temp/10);
		LCD_writechar('.');
		LCD_writeNumber(temp%10);
		LCD_writechar('C');
		temperature=temp;
	}
	if(temperature>HEAT_TEMP)
	{
		temp_smoke=Smoke_sensor_Output();
		if(temp_smoke!=smoke)
		{
			LCD_SetCursor(SECOND,LINE_START);
			LCD_writestring("      ");
			LCD_SetCursor(SECOND,LINE_START);
			LCD_writeNumber(temp_smoke/10);
			LCD_writechar('%');
			smoke=temp_smoke;
		}
		
	}
	
}
void FireSystem_status(void)// call status functions
{
	FireSystem_status_display();
	if(temperature>HEAT_TEMP)
	{
		if(smoke>FIRE_SMOKE)
		{
			FireSystem_Fire();
		}
		else
		{
			FireSystem_Heat();	
		}
		
	}
	else if(temperature<FINE_TEMP) // fine state
	{
		FireSystem_Fine(temperature);
	}
}
void FireSystem_Fine(u16 temperature)
{
	LCD_SetCursor(FIRST,10);
	LCD_writestring("FINE");
	DIO_WritePin(MOTOR_RELAY,LOW);
	LCD_SetCursor(SECOND,LINE_START);
	LCD_writestring("      ");
	DIO_WritePin(FIRE_LED,LOW);
	DIO_WritePin(HEAT_LED,LOW);
	DIO_WritePin(FINE_LED,HIGH);
}
void FireSystem_Heat(void)
{
	LCD_SetCursor(FIRST,10);
	LCD_writestring("HEAT");
	DIO_WritePin(MOTOR_RELAY,HIGH);
	DIO_WritePin(FINE_LED,LOW);
	DIO_WritePin(HEAT_LED,HIGH);
	DIO_WritePin(FIRE_LED,LOW);
}
void FireSystem_Fire(void)
{
	u8 flag=0;
	LCD_Clear();
	LCD_SetCursor(FIRST,6);
	LCD_writestring("FIRE");
	LCD_SetCursor(SECOND,LINE_START);
	LCD_writestring("PRESS'='>RESET");
	DIO_WritePin(MOTOR_RELAY,HIGH);
	DIO_WritePin(FINE_LED,LOW);
	DIO_WritePin(HEAT_LED,LOW);
	DIO_WritePin(FIRE_LED,HIGH);
	while(flag==0)
	{
		for(u8 i=0;i<10;i++)
		{
			DIO_WritePin(FIRE_ALARM,HIGH);
			_delay_ms(50);
			if(keypad_getnumber()=='=')
			{
				if(FireSystem_Restart()==TRUE)
				{
					flag=1;
					break;
				}
				LCD_Clear();
				LCD_SetCursor(FIRST,6);
				LCD_writestring("FIRE");
				LCD_SetCursor(SECOND,2);
				LCD_writestring("SYSTEM LOCKED");
			}
		}
	for(u8 i=0;i<10;i++)
	{
		DIO_WritePin(FIRE_ALARM,LOW);
		_delay_ms(50);
		if(keypad_getnumber()=='=')
		{
			if(FireSystem_Restart()==TRUE)
			{
				flag=1;
				break;
			}
			LCD_Clear();
			LCD_SetCursor(FIRST,6);
			LCD_writestring("FIRE");
			LCD_SetCursor(SECOND,2);
			LCD_writestring("SYSTEM LOCKED");
		}
	}
	
	
	}
	LCD_Clear();
	
}
Bool_t FireSystem_Restart(void)
{
	if(restart_flag<3)
	{
		restart_flag=0;
		for(u8 i=0;i<3;i++)
		{
		if(FireSystem_PassWord()==FALSE)
			{
			LCD_SetCursor(SECOND,10);
			LCD_writestring("WRONG");
			_delay_ms(500);
			restart_flag++;
			}
		else
			{
			LCD_SetCursor(SECOND,10);
			LCD_writestring("RIGHT");
			_delay_ms(500);
			LCD_Clear();
			temperature=TRUE;
			smoke=TRUE;
			return TRUE;
			}
		}			
	}
	return FALSE;
}
Bool_t FireSystem_PassWord(void)
{
	LCD_Clear();
	u8* temp_password=KeyPad_scan_string(PASS_LENGTH);
	LCD_SetCursor(SECOND,LINE_START);
	LCD_writestring(temp_password);
	while(keypad_getnumber()==NO_KEY);
	if(string_compare(password,temp_password)==TRUE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

Bool_t string_compare(u8*str1,u8*str2)
{
	u8 i;
	for(i=0;str1[i];i++)
	{
		if(str1[i]!=str2[i])
		{
			return FALSE;
		}
	}
	if(str1[i]!=str2[i])
	{
		return FALSE;
	}
	return TRUE;
}