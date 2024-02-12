


#ifndef RGB_H_
#define RGB_H_

#define LAST_COLOR (u8)14
#define FIRST_COLOR (u8)0

#define SHOWROOM 1
#define COLOR_SELECT 0

typedef struct
{
	u8* color;
	u8 red;
	u8 green;
	u8 blue;
	}color_t;

void RGB_init(void);
void generate_color(void);
void RGB_change_mode(void);
void RGB_mode(u8 mode);

#endif /* RGB_H_ */