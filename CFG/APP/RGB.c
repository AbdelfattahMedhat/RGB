#include "STDTYPES.h"
#include "Timers.h"
#include "interrupt_interface.h"
#include "KeyPAd_interface.h"
#include "RGB.h"
static u8 color={0};
static const color_t color_arr[15]={{255,255,255}, // white
									{255,0,0}, // red
									{0,255,0}, // green
									{0,0,255}, // blue
									{0,255,255}, // aqua
									{255,255,0}, // yellow
									{255,0,255}, // pink
									{50,100,50}, // off white
									{50,50,50}, // pink lite
									{20,50,120}, // baby blue
									{35,40,25}, // light salmon
									{90,0,90}, // rose
									{138,43,226}, // lavender
									{25,150,75}, // bubbles
									{0,0,0}}; // black
										

	void RGB_init(void) //init function will initialize timer0 and timer1 in 8bit fast pwm mode 
	{
	TIMER0_Init(TIMER0_FASTPWM_MODE,TIMER0_SCALER_8);
 	Timer1_Init(TIMER1_FASTPWM_8BIT_TOP_MODE,TIMER1_SCALER_8);
	TIMER0_OC0Mode(OC0_INVERTING);
	Timer1_OCRA1Mode(OCRA_INVERTING);  //EXTERNAL INTERRUPTS
	Timer1_OCRB1Mode(OCRB_INVERTING);
	interrupt_ISR(INT_0,color_inc);
	interrupt_ISR(INT_1,color_dec);
	
		
	}

// void RGB_init(void)
// {
// 	keypad_init();
// }
	void generate_color(void)
	{
		static u8 color_index;
		TIMER0_set_OCR0(color_arr[color].red);
		TIMER1_set_OCRA(color_arr[color].green);
		TIMER1_set_OCRB(color_arr[color].blue);
		color_index=keypad_getnumber();
		if(color_index>'0' && color_index<'9')
		{
			color=color_index-1;
		}
	}
	
// 	void color_change_delay(u16 ms)
// 	{
// 		u16 x;
// 		for(x=ms;x>0;x/10)
// 		{
// 			_delay_ms(10);
// 			TIMER0_set_OCR0(color_arr[color].red);
// 			TIMER1_set_OCRA(color_arr[color].green);
// 			TIMER1_set_OCRB(color_arr[color].blue);
// 		}
// 	}
	 
	void color_inc(void)
	{
		if(color<LAST_COLOR)
		color++;
		else
		color=FIRST_COLOR;
	}
	void color_dec(void)
	{
		if(color>FIRST_COLOR)
		color--;
		else
		color=LAST_COLOR;
	}