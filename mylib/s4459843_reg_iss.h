/** 
 **************************************************************
 * @file mylib/s4459843_reg_iss.h
 * @author MyName - MyStudent ID
 * @date 22022018
 * @brief mylib template driver
 * REFERENCE: DON'T JUST COPY THIS BLINDLY.pdf 
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 *************************************************************** 
 */
#ifndef ISS_REG_H
#define ISS_REG_H
#include "board.h"
#include "processor_hal.h"

#define S4459843_REG_ISS_SOURCE_1 0
#define S4459843_REG_ISS_SOURCE_2 1
#define S4459843_REG_ISS_SOURCE_3 2
#define S4459843_REG_ISS_SOURCE_4 3
#define S4459843_REG_ISS_SOURCE_5 4
#define S4459843_REG_ISS_SOURCE_6 5
#define S4459843_REG_ISS_SOURCE_7 6
#define S4459843_REG_ISS_SOURCE_8 7

extern uint32_t iss_eventcounter_val[8];
extern uint32_t iss_lasttimer_val[8];
extern uint32_t iss_delay_val[8];

extern void s4459843_reg_iss_init(void);
extern void s4459843_reg_iss_synchroniser(unsigned char signal_source_index);
extern uint32_t s4459843_reg_iss_eventcounter_read(unsigned char signal_source_index);
extern uint32_t s4459843_reg_iss_lasttimer_read(unsigned char signal_source_index);
extern void s4459843_reg_iss_eventcounter_reset(unsigned char signal_source_index);
extern void s4459843_reg_iss_lasttimer_reset(unsigned char signal_source_index);
extern void s4459843_reg_iss_delaytimer_ctrl(unsigned char signal_source_index, int delay_value);
#endif
