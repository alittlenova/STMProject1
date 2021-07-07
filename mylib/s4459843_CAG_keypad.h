/** 
 **************************************************************
 * @file mylib/s4459843_CAG_Simulator.h
 * @author Yang Zheng - 44598435
 * @date 10052021
 * @brief keypad
 * REFERENCE: None
 ***************************************************************
 * EXTERNAL FUNCTIONS modeSwitch(void)
 ***************************************************************
 * 
 *************************************************************** 
 */
#ifndef S4459843_CAG_KEYPAD_H
#define S4459843_CAG_KEYPAD_H

#define MODE_Grid 0x00
#define MODE_Mnemonic 0x01

#include "s4459843_CAG_keypad_grid.h"
#include "s4459843_CAG_keypad_mnemonic.h"

// Task Priorities (Idle Priority is the lowest priority)
#define KEYPADTASK_PRIORITY					( tskIDLE_PRIORITY + 2 )

// Task Stack Allocations (must be a multiple of the minimal stack size)
#define KEYPADTASK_STACK_SIZE		( configMINIMAL_STACK_SIZE * 2 )
xTaskHandle keypadTaskHandle;

uint8_t CAG_MODE;
unsigned char pressedkey;

void CAG_keypad_init(void);
void tsk_CAG_fsm_ctrl(void);
extern void modeSwitch(void);
#endif
