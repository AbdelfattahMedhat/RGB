#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_

#define COLUMNS 4
#define ROWS 4
#define NO_KEY 'R'
#define DEFAULT_STR_LENGTH 16
void keypad_init(void);
u8 keypad_getchar(void);
u8* KeyPad_scan_string(u8 size);
s32 keypad_generate_number(void);

#endif /* KEYPAD_INTERFACE_H_ */