


#ifndef RGB_H_
#define RGB_H_

#define LAST_COLOR (u8)14
#define FIRST_COLOR (u8)0
typedef struct
{
	u8 red;
	u8 green;
	u8 blue;
	}color_t;

void RGB_init(void);
void generate_color(void);
void color_inc(void);
void color_dec(void);


#endif /* RGB_H_ */