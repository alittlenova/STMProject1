/**
  ******************************************************************************
  * @file    CSSE3010/mylib/CAG_display.c
  * @author  Yang Zheng
  * @date    10/05/2021
  * @brief   Initialization the keypad and design a fsm transform function
  *          Design mode switch function.
  ******************************************************************************
  *
  */
#include "s4459843_CAG_keypad.h"
/*
 * Initialize the keypad
 */
void s4459843_tsk_CAG_keypad_init(void)
{
	xTaskCreate( (void *) &tsk_CAG_fsm_ctrl, (const signed char *) "KEYPAD", KEYPADTASK_STACK_SIZE, NULL, KEYPADTASK_PRIORITY+2, &keypadTaskHandle );
}
void CAG_keypad_init(void)
{
	CAG_MODE=MODE_Grid;
	pressedkey=0x00;
	s4459843_reg_keypad_init(); 
	//BRD_LEDRedOn();
}
/*
 * This function is use to transform the FSM every 50 ms
 */
void tsk_CAG_fsm_ctrl(void)
{
	TickType_t xLastWakeTime;
	CAG_keypad_init();
	xLastWakeTime = xTaskGetTickCount();
	for(;;)
	{
		s4459843_reg_keypad_fsmprocessing(); 
		vTaskDelayUntil( &xLastWakeTime, 50);
	}
}
/*
 * This function is use to change the mode and will be called by the Userbotton on board
 */
void modeSwitch(void)
{
	if(CAG_MODE==MODE_Grid)
	{
		CAG_MODE=MODE_Mnemonic;
		BRD_LEDRedOff();
		BRD_LEDBlueOn();
	}
	else
	{
		CAG_MODE=MODE_Grid;
		BRD_LEDRedOn();
		BRD_LEDBlueOff();
	}
}
