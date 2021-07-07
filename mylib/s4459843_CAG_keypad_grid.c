/**
  ******************************************************************************
  * @file    CSSE3010/mylib/s4459843_CAG_keypad_mnemonic.c
  * @author  Yang Zheng
  * @date    10/05/2021
  * @brief   Initialization the keypad and design a grid mode control
  *          
  ******************************************************************************
  *
  */
#include "s4459843_CAG_keypad_grid.h"
/*
 * Initialize the keypad at grid mode,set the x and y grid value to 0
 */
void s4459843_tsk_CAG_keypadGrid_init(void)
{
	xTaskCreate( (void *) &tsk_CAG_Grid_Mode_ctrl, (const signed char *) "GRID", GRIDTASK_STACK_SIZE, NULL, GRIDTASK_PRIORITY+2, &gridTaskHandle );
	xTaskCreate( (void *) &tsk_CAG_Grid_Mode_sampgive, (const signed char *) "GRIDSAMPGIVE", GRIDSAMPGIVETASK_STACK_SIZE, NULL, GRIDSAMPGIVETASK_PRIORITY+2, &gridsampgiveTaskHandle );
}
void CAG_keypadGrid_init(void)
{
	subgrid_X=0;
	subgrid_Y=0;
}
uint8_t SubgridXreturn(void)
{
	return subgrid_X;
}
uint8_t SubgridYreturn(void)
{
	return subgrid_Y;
}

/*
 * Determine whether the keypad is pressed. If the keypad is pressed, read the value of the keypad
   Determine the function of each botton on the keypad
 */
void tsk_CAG_Grid_Mode_processing(void)
{
	if(s4459843_reg_keypad_read_status()==1)
	{
		KeypadStatus=0;
		BRD_LEDGreenToggle();
		if(Simulation_Drive==1)
		{
			switch (pressedkey){
				case 0x00:cell_toggle(0x00);  break;//R1C1
				case 0x01:cell_toggle(0x01);  break;//R1C2
				case 0x02:cell_toggle(0x02);  break;//R1C3
				case 0x03:simulation_start();  break;//R1C4
				case 0x04:cell_toggle(0x03);  break;//R2C1
				case 0x05:cell_toggle(0x04);  break;//R2C2
				case 0x06:cell_toggle(0x05);  break;//R2C3
				case 0x07:simulation_stop();  break;//R2C4
				case 0x08:cell_toggle(0x06);  break;//R3C1
				case 0x09:cell_toggle(0x07);  break;//R3C2
				case 0x0a:cell_toggle(0x08);  break;//R3C3
				case 0x0b:Clear_Simulation();  break;//R3C4
				case 0x0c:subgridXMove();  break;//R4C1
				case 0x0d:subgridYMove();  break;//R4C2
				case 0x0e:break;//R4C3
				case 0x0f:break;//R4C4
				default:break;
			}	
		}
	}
}
/*
 * Controling the grid mode and start check the keypad status
 */
void tsk_CAG_Grid_Mode_ctrl(void)
{
	CAG_keypadGrid_init();
	for(;;)
	{
		if(CAG_MODE==MODE_Grid)
		{
			tsk_CAG_Grid_Mode_processing();
			//BRD_LEDGreenToggle();
		}
		vTaskDelay(20);
	}
}
void tsk_CAG_Grid_Mode_sampgive(void)
{
	// Create Semaphores 
	gridSemaphore = xSemaphoreCreateBinary();
	TickType_t xLastWakeTime;
	
	xLastWakeTime = xTaskGetTickCount();
	for (;;) {
		if (gridSemaphore != NULL) {	// Check if semaphore exists
			// Give simulation Semaphore
			xSemaphoreGive(gridSemaphore);
		}
		// Wait for 20ms
		 vTaskDelayUntil( &xLastWakeTime, 20);
	}
}
/*
 * Determine the movement rule in the x direction
 */
void subgridXMove(void)
{
	subgrid_X=(subgrid_X+1)%10;
}
/*
 * Determine the movement rule in the y direction
 */
void subgridYMove(void)
{
	subgrid_Y=(subgrid_Y+1)%5;
}
/*
 * Make every cell to dead
 */
void Clear_Simulation(void)
{
	for(int i=0;i<30;i++)
	{
		for(int j=0;j<30;j++)
		{
			cell_live[i][j]=0;
		}
	}
}
/*
 * Let the keyboard be able to operate all area
 */
void cell_toggle(uint8_t grid)
{
	int subx,suby;
	caMessage_t DrawMessage;
	subx=grid%3;
	suby=grid/3;
	DrawMessage.cell_x=(subgrid_X*3)+subx;
	DrawMessage.cell_y=(subgrid_Y*3)+suby;
	DrawMessage.type=0x11-cell_live[DrawMessage.cell_x][DrawMessage.cell_y];
	Draw_shape(DrawMessage);
	//cell_live[(subgrid_X*3)+subx][(subgrid_Y*3)+suby] = (~cell_live[(subgrid_X*3)+subx][(subgrid_Y*3)+suby]) & 0x01;
}
/*
 * start simulation
 */
void simulation_start(void)
{
	simulationOn=1;
	//vtask resume for simulation task
}
/*
 * stop simulation
 */
void simulation_stop(void)
{
	simulationOn=0;
	//vtask suspend for simulation task
}
