#include "STDTYPES.h"
#include "DIO_Interface.h"
#include "motor_interface.h"
#include "Car_Interface.h"


	

	void car_init()
	{
		//DO NOTHING .
	}
	void Car_Runnable(void)
	{
		if(DIO_ReadPin(F_B)==LOW)
		{
			Move_Forward();
		}
		else if(DIO_ReadPin(B_B)==LOW)
		{
			Move_Backward();
		}
		else if(DIO_ReadPin(R_B)==LOW)
		{
			Move_Right();
		}
		else if(DIO_ReadPin(L_B)==LOW)
		{
			Move_Left();
		}
		else
		{
			motor_stop(M1);
			motor_stop(M2);
			motor_stop(M3);
			motor_stop(M4);
		}
	}
	
	void Move_Forward(void)
	{
		motor_run_cw(M1);
		motor_run_cw(M2);
		motor_run_cw(M3);
		motor_run_cw(M4);
	}
	void Move_Backward(void)
	{
	motor_run_ccw(M1);
	motor_run_ccw(M2);
	motor_run_ccw(M3);
	motor_run_ccw(M4);
	}
	void Move_Right(void)
	{
	motor_run_cw(M1);
	motor_run_cw(M2);
	motor_run_ccw(M3);
	motor_run_ccw(M4);	
	}
	void Move_Left(void)
	{
		motor_run_ccw(M1);
		motor_run_ccw(M2);
		motor_run_cw(M3);
		motor_run_cw(M4);
	}