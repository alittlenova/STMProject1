/** 
 **************************************************************
 * @file mylib/s4459843_reg_keypad.h
 * @author MyName - MyStudent ID
 * @date 22022018
 * @brief mylib template driver
 * REFERENCE: DON'T JUST COPY THIS BLINDLY.pdf 
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * s4459843_reg_keypad_init() - intialise mylib template driver
 * s4459843_reg_keypad_set() - set mylib template driver 
 *************************************************************** 
 */
#ifndef KEYPAD_REG_H
#define KEYPAD_REG_H
#include "board.h"
#include "processor_hal.h"
#include "s4459843_reg_iss.h"
#include "s4459843_reg_lta1000g.h"


//Here might be change in the future
#define ROW1 S4459843_REG_ISS_SOURCE_4
#define ROW2 S4459843_REG_ISS_SOURCE_5
#define ROW3 S4459843_REG_ISS_SOURCE_6
#define ROW4 S4459843_REG_ISS_SOURCE_7
extern void s4459843_reg_keypad_init(void);
extern void s4459843_reg_keypad_fsmprocessing(void);
void keypad_gpio_init(void);
void keypad_writecol(unsigned char colval);
//Here Need to be change in the future
#define keypad_col1() 0x00
#define keypad_col2() 0x01
#define keypad_col3() 0x02
#define keypad_col4() 0x03
//might be something but not void
unsigned char keypad_readrow(void);
int s4459843_reg_keypad_read_status(void);
unsigned char s4459843_reg_keypad_read_key(void);
extern int s4459843_reg_keypad_read_ascii(void);
extern unsigned char s4459843_reg_keypad_read_hex(void);
void s4459843_reg_keypad_iss_isr(int GPIO_P);
unsigned char KeypadFsmCurrentstate;
extern int KeypadStatus;
int KeypadStatus;
unsigned char KeypadValue;
//Here might be change in the future
#define INIT_STATE 0x00
#define RSCAN1_STATE 0x01
#define RSCAN2_STATE 0x02
#define RSCAN3_STATE 0x03
#define RSCAN4_STATE 0x04

#define GPIO_ROW1 0
#define GPIO_ROW2 1
#define GPIO_ROW3 2
#define GPIO_ROW4 3
#endif
