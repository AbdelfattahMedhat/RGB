/*****************************headers files***************/
#define F_CPU 8000000
#include <util/delay.h>
#include "STDTYPES.h"
#include "MemMap.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "ADC_Interface.h"
#include "LCD_interface.h"
#include "seven_seg_interface.h"
#include "KeyPAd_interface.h"
#include "interrupt_interface.h"
#include "Dino_game_interface.h"
#include "Dino_private.h"
/********************global variables*********************/

s16 speed=0;
static volatile u8 mov_flag=0;
static s8 tree_posi=INIT;
static u8 score;

/*********************functions***********************/

void dino_init(void)
{
	LCD_SetCGRAM(0);
	LCD_WriteDataInCGRAM(Dino);
	LCD_SetCGRAM(8);
	LCD_WriteDataInCGRAM(Tree);
}


void dino_Runnable(void)
{
	dino_stage();
	dino_score();
	speed=SPEED-ADC_READ(ADC0);
	dino_movement();
	game_over();
	LCD_SetCursor(SECOND,tree_posi);
	LCD_writechar(1);
	dino_speed(speed);
	LCD_SetCursor(SECOND,tree_posi);
	LCD_writechar(' ');
	tree_posi--;
	if(tree_posi==-1)
	{
		tree_posi=INIT;
	}
	interrupt_ISR(INT_0,dino_up_down);
	
}


void dino_speed(s16 delay)
{
	while(0<delay)
	{
		_delay_ms(10);
		delay-=10;
	}	
}

void dino_stage(void)
{
	static u8 temp=INIT;
	if(speed/STAGE_RES!=temp)
	{
		LCD_SetCursor(FIRST,STAGE_POSI);
		LCD_writeNumber(STAGE-(speed/STAGE_RES));
		temp=speed/STAGE_RES;
	}
}

void dino_movement(void)
{
	static u8 flag_test;
	if(flag_test!=mov_flag)
	{
		LCD_SetCursor(FIRST,DINO_POSI);
		LCD_writechar(' ');
		LCD_SetCursor(SECOND,DINO_POSI);
		LCD_writechar(' ');
		flag_test=mov_flag;
	}
	if(mov_flag==0)
	{
		LCD_SetCursor(SECOND,DINO_POSI);
	}
	else
	{
		LCD_SetCursor(FIRST,DINO_POSI);
	}
	LCD_writechar(0);
}

void dino_up_down(void)
{
	TOG_BIT(mov_flag,0);
}

void game_over(void)
{
	u8 i=0;
	if(mov_flag==0 && tree_posi==DINO_POSI)
	{
		LCD_Clear();
		mov_flag=1;
		LCD_SetCursor(SECOND,PR_AG);
		LCD_writestring("PRESS AGAIN");
		while(mov_flag==1)
		{
			LCD_SetCursor(FIRST,i);
			LCD_writestring("GAME OVER");
			_delay_ms(200);
			LCD_SetCursor(FIRST,i);
			LCD_writestring("         ");
			i++;
			if(i==GA_OV_LIM)
			{
				i=0;
			}
			
		}
		LCD_Clear();
		tree_posi=INIT;
		speed=INIT;
		score=0;
	}
	
}

void dino_score(void)
{
	if(mov_flag==1 && tree_posi==DINO_POSI)
	{
		score=score+10;
	}
	LCD_SetCursor(FIRST,SCORE_POSI);
	LCD_writeNumber(score);
	seven_seg_Write_number((u8)score/10);
}