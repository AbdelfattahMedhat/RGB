
#ifndef FIRESYSTEM_INTERFACE_H_
#define FIRESYSTEM_INTERFACE_H_

#define HEAT_TEMP 600
#define FINE_TEMP 500
#define FIRE_SMOKE 500

#define FIRE_LED PINC0
#define HEAT_LED PINC1
#define FINE_LED PINC2

#define MOTOR_RELAY PINC4
#define FIRE_ALARM PINC5

#define PASS_LENGTH 5


typedef enum 
{
	FINE,
	HEAT,
	FIRE
	}FireSystem_status_type;
void FireSystem_init(void);
void FireSystem_status_display(void);
void FireSystem_status(void);// call status functions
void FireSystem_Fine(u16 temperature);
void FireSystem_Heat(void);
void FireSystem_Fire(void);
Bool_t FireSystem_Restart(void);
Bool_t FireSystem_PassWord(void);
Bool_t string_compare(u8 * str1,u8 * str2);


#endif /* FIRESYSTEM_INTERFACE_H_ */