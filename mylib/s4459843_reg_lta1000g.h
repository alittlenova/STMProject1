/** 
 **************************************************************
 * @file mylib/s4459843_reg_lta1000g.h
 * @author Yang Zheng - 44598435
 * @date 14032021
 * @brief LTA 1000g LED bar display Mylib register driver
 * REFERENCE: None
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * s4459843_reg_lta1000g_init() - intialise lta1000g driver
 *************************************************************** 
 */
#ifndef S4459843_REG_LTA1000G_H
#define S4459843_REG_LTA1000G_H
#include "main.h"
#include "board.h"
#include "processor_hal.h"
#include "stm32f429xx.h"
#include "s4459843_reg_keypad.h"
#include "s4459843_lib_hamming.h"
extern void s4459843_reg_lta1000g_init(void);
void s4459843_reg_lta1000g_write_value(unsigned char hex_value);
void s4459843_reg_lta1000g_write_value_8bit(uint16_t hex_value);
//extern void s4459843_reg_lta1000g_write_keypad(void);
#endif
