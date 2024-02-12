#include "STDTYPES.h"
#include "Timers.h"
#include "KeyPAd_interface.h"
#include "interrupt_interface.h"
#include "LCD_interface.h"
#include "RGB.h"
#include "Utils.h"
static u8 color,mode;
static const color_t color_arr[15]={{"white",255,255,255}, // white
									{"red",255,0,0}, // red
									{"red",0,255,0}, // green
									{"red",0,0,255}, // blue
									{"red",0,255,255}, // aqua
									{"red",255,255,0}, // yellow
									{"red",255,0,255}, // pink
									{"red",50,100,50}, // off white
									{"red",50,50,50}, // pink lite
									{"red",20,50,120}, // baby blue
									{"red",35,40,25}, // light salmon
									{"red",90,0,90}, // rose
									{"red",138,43,226}, // lavender
									{"red",25,150,75}, // bubbles
									{"red",0,0,0}}; // black
										

	void RGB_init(void) //init function will initialize timer0 and timer1 in 8bit fast pwm mode 
	{
		// initializing timer0 with fast pwm mode with 8 pre scaler
	TIMER0_Init(TIMER0_FASTPWM_MODE,TIMER0_SCALER_8);
	// initializing timer1 with 8 bits fast pwm mode with 8 pre scaler 
 	Timer1_Init(TIMER1_FASTPWM_8BIT_TOP_MODE,TIMER1_SCALER_8);
	 // initializing output compare of timer0 with rising edge
	TIMER0_OC0Mode(OC0_INVERTING);
	// initializing output compare A of timer1 with rising edge
	Timer1_OCRA1Mode(OCRA_INVERTING); 
	// initializing output compare B of timer1 with rising edge
	Timer1_OCRB1Mode(OCRB_INVERTING);
	// Guide Message at beginning of program	
	LCD_SetCursor(FIRST,LINE_START);
	
	LCD_writestring("colors from 1-15");
	// make external interrupt toggle RGB mode
	interrupt_ISR(INT_0,RGB_change_mode);
	}


	void generate_color(void)
	{
		
		RGB_mode(mode);
		
		TIMER0_set_OCR0(color_arr[color].red);
		
		TIMER1_set_OCRA(color_arr[color].green);
		
		TIMER1_set_OCRB(color_arr[color].blue);
		
	}
	

	 
void RGB_mode(u8 mode)
{
	u8 temp=0;
	// this mode make color changing automatically with 0.5 sec delay
	if(mode == SHOWROOM)
	{
		_delay_ms(500);
		color++;
		if(color == 15)
		{
			color = 0;
		}
	
	}
	// this mode make use select color number 
	else if (mode == COLOR_SELECT)
	{
		temp=keypad_getnumber();
		if(temp >= 1 && temp <= 15)
		{
			color = temp - 1;
		}
		
	}
}

void RGB_change_mode(void)
{
	mode^=1;
}

