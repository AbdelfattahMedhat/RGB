/*
 * Car_Interface.h
 *
 * Created: 3/29/2023 9:03:35 PM
 *  Author: abdo
 */ 


#ifndef CAR_INTERFACE_H_
#define CAR_INTERFACE_H_

#define F_B PINA0
#define B_B PINA1
#define R_B PINA2
#define L_B PINA3

void car_init(void);
void Car_Runnable(void);
void Move_Forward(void);
void Move_Backward(void); 
void Move_Right(void);
void Move_Left(void);



#endif /* CAR_INTERFACE_H_ */