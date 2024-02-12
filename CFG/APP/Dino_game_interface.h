
#ifndef DINO_GAME_INTERFACE_H_
#define DINO_GAME_INTERFACE_H_
/*************speed****************/
#define SPEED 1024
/*************stage***************/
#define STAGE 9
#define STAGE_POSI 15
#define STAGE_RES 103
#define INIT 15
/******************/
#define DINO_POSI 5
#define PR_AG 2
#define GA_OV_LIM 8
/*******************/
#define SCORE_POSI 0

/********************function***************/
void dino_init(void);
void dino_Runnable(void);
void dino_speed(s16 delay);
void dino_stage(void);
void dino_movement(void);
void dino_up_down(void);
void game_over(void);
void dino_score(void);
#endif /* DINO_GAME_INTERFACE_H_ */