
#include "STDTYPES.h"
#include "MemMap.h"
#include "KeyPAd_interface.h"
#include "LCD_interface.h"
#include "DIO_Interface.h"
#include "seven_seg_interface.h"
#include "Timers.h"
#include "RGB.h"
#include "Utils.h"


	
int main(void)
{
	DIO_Init();
	LCD_init();
	keypad_init();
	Timer1_Init(TIMER1_NORMAL_MODE,TIMER1_SCALER_8);
	RGB_init();
	while (1)
	{
		LCD_writeNumber();
	//generate_color();
	}
	
}
