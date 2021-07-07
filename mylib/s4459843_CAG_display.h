/** 
 **************************************************************
 * @file mylib/s4459843_CAG_Display.h
 * @author Yang Zheng - 44598435
 * @date 10052021
 * @brief OLED display
 * REFERENCE: None
 ***************************************************************
 * EXTERNAL FUNCTIONS tsk_CAG_display_ctrl(void);
 ***************************************************************
 * 
 *************************************************************** 
 */
#ifndef S4459843_CAG_DISPLAY_H
#define S4459843_CAG_DISPLAY_H
#include "s4459843_CAG_simulator.h"
#include "s4459843_CAG_keypad_grid.h"
#include "s4459843_reg_oled.h"
#include "oled_pixel.h"
#include "oled_string.h"
#include "s4459843_reg_lta1000g.h"
// Task Priorities (Idle Priority is the lowest priority)
#define DISPLAYTASK_PRIORITY					( tskIDLE_PRIORITY + 2 )

// Task Stack Allocations (must be a multiple of the minimal stack size)
#define DISPLAYTASK_STACK_SIZE		( configMINIMAL_STACK_SIZE * 2 )

extern void s4459843_tsk_display_init(void);
extern SSD1306_COLOR Display_color;
void CAG_display_init(void);
void CAG_Display_refresh(void);
extern void tsk_CAG_display_ctrl(void);
xTaskHandle displayTaskHandle;
SSD1306_COLOR Display_color;
extern uint8_t inverse_color;
uint8_t inverse_color;
#endif
