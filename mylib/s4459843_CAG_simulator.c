/**
  ******************************************************************************
  * @file    CSSE3010/mylib/CAG_simulator.c
  * @author  Yang Zheng
  * @date    10/05/2021
  * @brief   Initialize the simulator and set the update time. Check the 
  * situation of every cell. The tsk_simulation_ctrl() must be used at 
  * contructing the simulation task with using xTaskCreate();		 
  ******************************************************************************
  *
  */
#include "s4459843_CAG_simulator.h"
void s4459843_tsk_simulation_init(void)
{
	xTaskCreate( (void *) &tsk_simulation_ctrl, (const signed char *) "SIMULATION", SIMULATIONTASK_STACK_SIZE, NULL, SIMULATIONTASK_PRIORITY+2, &simulationTaskHandle );
	xTaskCreate( (void *) &tsk_simulation_sampgive, (const signed char *) "SAMPGIVE", SAMPGIVETASK_STACK_SIZE, NULL, SAMPGIVETASK_PRIORITY+2, &sampgiveTaskHandle );
}
/*
 * set the init condtion of the game and the update time(default 1s)
 */
void simulation_init(void)
{
	Simulation_Drive=1;
	for(int i=0;i<30;i++)
	{
		for(int j=0;j<15;j++)
		{
			// set cell initial state all to dead
			cell_live[i][j]=0;
			cell_livelast[i][j]=0;
			if(i==3&&j==3)
			{
				cell_live[i][j]=1;
				cell_livelast[i][j]=1;
			}
			if(i==5&&j==3)
			{
				cell_live[i][j]=1;
				cell_livelast[i][j]=1;
			}
			if(i==4&&j==4)
			{
				cell_live[i][j]=1;
				cell_livelast[i][j]=1;
			}
			if(i==4&&j==5)
			{
				cell_live[i][j]=1;
				cell_livelast[i][j]=1;
			}
			if(i==5&&j==4)
			{
				cell_live[i][j]=1;
				cell_livelast[i][j]=1;
			}
		}
	}
	simulation_update_time=1000;//initial update time in 1s
}
/*
 * Check the condition of every cell (one by one)
 */ 
void simulation_march(void)
{
	for(int i=0;i<30;i++)
	{
		for(int j=0;j<15;j++)
		{
			cell_livelast[i][j]=cell_live[i][j];//record the cell condition before the check
			simulation_count[i][j]=0;
		}
	}
	for(int i=0;i<30;i++)
	{
		for(int j=0;j<15;j++)
		{
			if(i>0)
			{
				if(cell_livelast[i-1][j]==1)
				{
					 simulation_count[i][j]=simulation_count[i][j]+1;
				}
			}
			if(i<29)
			{
				if(cell_livelast[i+1][j]==1)
				{
					 simulation_count[i][j]=simulation_count[i][j]+1;
				}
			}
			if(j>0)
			{
				if(cell_livelast[i][j-1]==1)
				{
					 simulation_count[i][j]=simulation_count[i][j]+1;
				}
			}
			if(j<14)
			{
				if(cell_livelast[i][j+1]==1)
				{
					 simulation_count[i][j]=simulation_count[i][j]+1;
				}
			}
			if(i>0 && j>0)
			{
				if(cell_livelast[i-1][j-1]==1)
				{
					 simulation_count[i][j]=simulation_count[i][j]+1;
				}
			}
			if(i>0 && j<14)
			{
				if(cell_livelast[i-1][j+1]==1)
				{
					 simulation_count[i][j]=simulation_count[i][j]+1;
				}
			}
			if(i<29 && j>0)
			{
				if(cell_livelast[i+1][j-1]==1)
				{
					 simulation_count[i][j]=simulation_count[i][j]+1;
				}
			}
			if(i<29 && j<14)
			{
				if(cell_livelast[i+1][j+1]==1)
				{
					 simulation_count[i][j]=simulation_count[i][j]+1;
				}
			}
		}
	}
	
	for(int i=0;i<30;i++)
	{
		for(int j=0;j<15;j++)
		{
			//centre-cell
			if(cell_livelast[i][j]==0&&simulation_count[i][j]==3)
			{
				cell_live[i][j]=1;
			}
			if(cell_livelast[i][j]==1&&simulation_count[i][j]<2)
			{
				cell_live[i][j]=0;
			}
			if(cell_livelast[i][j]==1&&simulation_count[i][j]>3)
			{
				cell_live[i][j]=0;
			}
			/*if(cell_livelast[i][j]==1&&simulation_count[i][j]==1)
			{
				cell_live[i][j]=0;
			}*/
			/*if(cell_livelast[i][j]==1&&simulation_count[i][j]==4)
			{
				cell_live[i][j]=0;
			}*/
		}
	}
	
}
/*
 * The infinite loop function need to be included in a task. Use the address 
 * of this function to create the simulation evolution task.
 */
void tsk_simulation_ctrl(void)
{
	simulation_init();
	simulationOn=1;
	vTaskDelay(4000);
	for(;;)
	{
		if (simulationSemaphore != NULL) 
		{
			if ( xSemaphoreTake( simulationSemaphore, 10 ) == pdTRUE ) 
			{
				if(simulationOn==1)
				{
					simulation_march();
				}
			}
		}
		vTaskDelay(50);
	}
}
void tsk_simulation_sampgive( void ) 
{
	// Create Semaphores 
	simulationSemaphore = xSemaphoreCreateBinary();
	TickType_t xLastWakeTime;
	
	xLastWakeTime = xTaskGetTickCount();
	for (;;) {
		if (simulationSemaphore != NULL) {	// Check if semaphore exists
			// Give simulation Semaphore
			xSemaphoreGive(simulationSemaphore);
		}
		// Wait for some ms
		if(simulation_update_time==500)
		{
			vTaskDelayUntil( &xLastWakeTime, 500);
		}
		else if(simulation_update_time==2000)
		{
			vTaskDelayUntil( &xLastWakeTime, 2000);
		}
		else
		{
			vTaskDelayUntil( &xLastWakeTime, 10000);
		}
	}
}
void Draw_shape(caMessage_t DrawMessage)
{
	uint8_t xstart;
	uint8_t ystart;
	xstart=DrawMessage.cell_x;
	ystart=DrawMessage.cell_y;
	if(DrawMessage.type==0x10)//draw one dead cell
	{
		cell_live[xstart][ystart] = 0x00;
	}
	else if(DrawMessage.type==0x11)//draw one alive cell
	{
		cell_live[xstart][ystart] = 0x01;
	}
	else if(DrawMessage.type==0x20)//block
	{
		//row1
		cell_live[xstart][ystart] = 0x00;
		cell_live[xstart+1][ystart] = 0x00;
		cell_live[xstart+2][ystart] = 0x00;
		//row2
		cell_live[xstart][ystart+1] = 0x00;
		cell_live[xstart+1][ystart+1] = 0x01;
		cell_live[xstart+2][ystart+1] = 0x01;
		//row3
		cell_live[xstart][ystart+2] = 0x00;
		cell_live[xstart+1][ystart+2] = 0x01;
		cell_live[xstart+2][ystart+2] = 0x01;
	}
	else if(DrawMessage.type==0x21)//beehive
	{
		if(xstart+3<30)
		{
			//row1
			cell_live[xstart][ystart] = 0x00;
			cell_live[xstart+1][ystart] = 0x01;
			cell_live[xstart+2][ystart] = 0x01;
			cell_live[xstart+3][ystart] = 0x00;
			//row2
			cell_live[xstart][ystart+1] = 0x01;
			cell_live[xstart+1][ystart+1] = 0x00;
			cell_live[xstart+2][ystart+1] = 0x00;
			cell_live[xstart+3][ystart+1] = 0x01;
			//row3
			cell_live[xstart][ystart+2] = 0x00;
			cell_live[xstart+1][ystart+2] = 0x01;
			cell_live[xstart+2][ystart+2] = 0x01;
			cell_live[xstart+3][ystart+2] = 0x00;
		}
	}
	else if(DrawMessage.type==0x22)//loaf
	{
		//row1
		cell_live[xstart][ystart] = 0x00;
		cell_live[xstart+1][ystart] = 0x00;
		cell_live[xstart+2][ystart] = 0x00;
		//row2
		cell_live[xstart][ystart+1] = 0x00;
		cell_live[xstart+1][ystart+1] = 0x00;
		cell_live[xstart+2][ystart+1] = 0x00;
		//row3
		cell_live[xstart][ystart+2] = 0x00;
		cell_live[xstart+1][ystart+2] = 0x00;
		cell_live[xstart+2][ystart+2] = 0x00;
	}
	else if(DrawMessage.type==0x30)//blinker
	{
		//row1
		cell_live[xstart][ystart] = 0x00;
		cell_live[xstart+1][ystart] = 0x00;
		cell_live[xstart+2][ystart] = 0x00;
		//row2
		cell_live[xstart][ystart+1] = 0x00;
		cell_live[xstart+1][ystart+1] = 0x00;
		cell_live[xstart+2][ystart+1] = 0x00;
		//row3
		cell_live[xstart][ystart+2] = 0x00;
		cell_live[xstart+1][ystart+2] = 0x00;
		cell_live[xstart+2][ystart+2] = 0x00;
	}
	else if(DrawMessage.type==0x31)//toad
	{
		//row1
		cell_live[xstart][ystart] = 0x00;
		cell_live[xstart+1][ystart] = 0x00;
		cell_live[xstart+2][ystart] = 0x00;
		//row2
		cell_live[xstart][ystart+1] = 0x00;
		cell_live[xstart+1][ystart+1] = 0x00;
		cell_live[xstart+2][ystart+1] = 0x00;
		//row3
		cell_live[xstart][ystart+2] = 0x00;
		cell_live[xstart+1][ystart+2] = 0x00;
		cell_live[xstart+2][ystart+2] = 0x00;
	}
	else if(DrawMessage.type==0x32)//beacon
	{
		//row1
		cell_live[xstart][ystart] = 0x00;
		cell_live[xstart+1][ystart] = 0x00;
		cell_live[xstart+2][ystart] = 0x00;
		//row2
		cell_live[xstart][ystart+1] = 0x00;
		cell_live[xstart+1][ystart+1] = 0x00;
		cell_live[xstart+2][ystart+1] = 0x00;
		//row3
		cell_live[xstart][ystart+2] = 0x00;
		cell_live[xstart+1][ystart+2] = 0x00;
		cell_live[xstart+2][ystart+2] = 0x00;
	}
	else if(DrawMessage.type==0x40)//glider
	{
		//row1
		cell_live[xstart][ystart] = 0x00;
		cell_live[xstart+1][ystart] = 0x00;
		cell_live[xstart+2][ystart] = 0x00;
		//row2
		cell_live[xstart][ystart+1] = 0x00;
		cell_live[xstart+1][ystart+1] = 0x00;
		cell_live[xstart+2][ystart+1] = 0x00;
		//row3
		cell_live[xstart][ystart+2] = 0x00;
		cell_live[xstart+1][ystart+2] = 0x00;
		cell_live[xstart+2][ystart+2] = 0x00;
	}
}
