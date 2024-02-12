 
#ifndef NUMBER_CONV_INTERFACE_H_
#define NUMBER_CONV_INTERFACE_H_

#define OPERATION_NUM '3'
#define  MIN_OPERATION_NUM '2'
#define  LENGTH 4 // HEX ,DEC or BIN length
#define MAX_DEC_NUM 65535
#define MAX_BIN_NUM 4095
typedef enum {
	DEC='1',
	HEX='2',
	BIN='3'
	}num_conv_op_type;

void number_conv_init(void);
void Get_Operation(num_conv_op_type num);
void number_conv_write_HEX(u16 num);
void number_conv_write_DEC(u16 num);
void number_conv_write_BIN(u16 num);
void Conv_From_Dec_To_Hex(void);
void Conv_From_Dec_To_Bin(void);
void Conv_From_Hex_To_Dec(void);
void Conv_From_Hex_To_Bin(void);
void Conv_From_Bin_To_Dec(void);
void Conv_From_Bin_To_Hex(void);
u16 Bin_to_Dec(u8 * bin,u8 size);
u16 Hex_to_Dec(u8 * hex,u8 size);
#endif /* NUMBER_CONV_INTERFACE_H_ */