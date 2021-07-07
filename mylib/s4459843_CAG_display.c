/**
  ******************************************************************************
  * @file    CSSE3010/mylib/CAG_display.c
  * @author  Yang Zheng
  * @date    10/05/2021
  * @brief   The OLED display related function. The display FreeRTOS task should 
  * be created in main.c and call the tsk_CAG_display_ctrl().
  ******************************************************************************
  *
  */



#include "s4459843_CAG_display.h"
void s4459843_tsk_display_init(void)
{
	xTaskCreate( (void *) &tsk_CAG_display_ctrl, (const signed char *) "DISPLAY", DISPLAYTASK_STACK_SIZE, NULL, DISPLAYTASK_PRIORITY+2, &displayTaskHandle );
}
/*
 * Initialize the OLED and set the OLED display color to white(by default)
 */
void CAG_display_init(void)
{
	s4459843_reg_lta1000g_init();
	s4459843_reg_oled_init();
	Display_color=SSD1306_WHITE;
	inverse_color=0;
}
/*
 * Refresh the OLED screen, Grid is in 30*15. Display the alive cell in color(white 
 * by default) and dead cell in black.
 */
void CAG_Display_refresh(void)
{
	if(inverse_color==0)
	{
		ssd1306_Fill(Black);
	}
	else
	{
		ssd1306_Fill(SSD1306_WHITE);
	}
	
	for(int i=0;i<30;i++)
	{
		for(int j=0;j<15;j++)
		{
			if(cell_live[i][j]==1)
			{
				ssd1306_DrawPixel(2*i, 2*j, Display_color);
				ssd1306_DrawPixel(2*i+1, 2*j, Display_color);
				ssd1306_DrawPixel(2*i, 2*j+1, Display_color);
				ssd1306_DrawPixel(2*i+1, 2*j+1, Display_color);
			}
		}
	}
	if(CAG_MODE==MODE_Mnemonic)
	{
		ssd1306_SetCursor(64,1);
		ssd1306_WriteString(command_bar, Font_6x8, Display_color);//Draw command string
		if(selectingOn==1)//Draw Selecting Character
		{
			if(cursor_flashing_state==1)
			{
				ssd1306_SetCursor(64+(command_len*6),1);
				ssd1306_WriteChar(selecting_letter, Font_6x8, Display_color);
			}
		}
		if(cursor_flashing_state==1)//Draw cursor
		{
			for(int j=0;j<6;j++)
			{
				ssd1306_DrawPixel(j+64+(command_len*6), 9, Display_color);
			}
		}
		if(error_show==0)
		{
			if(varing_state==0)//Draw help information
			{
				ssd1306_SetCursor(64,11);
				ssd1306_WriteString("A:", Font_6x8, Display_color);
				ssd1306_SetCursor(64,19);
				ssd1306_WriteString("E", Font_6x8, Display_color);
			}
			else if(varing_state==1)
			{
				ssd1306_SetCursor(64,11);
				ssd1306_WriteString("Press B:", Font_6x8, Display_color);
				ssd1306_SetCursor(64,19);
				ssd1306_WriteString("Backspace", Font_6x8, Display_color);
			}
			else if(varing_state==2)
			{
				ssd1306_SetCursor(64,11);
				ssd1306_WriteString("Press C:", Font_6x8, Display_color);
				ssd1306_SetCursor(64,19);
				ssd1306_WriteString("Clear", Font_6x8, Display_color);
			}
			else if(varing_state==3)
			{
				ssd1306_SetCursor(64,11);
				ssd1306_WriteString("Other Key:", Font_6x8, Display_color);
				ssd1306_SetCursor(64,19);
				ssd1306_WriteString("for command", Font_6x8, Display_color);
			}
		}
		else
		{
				ssd1306_SetCursor(64,11);
				ssd1306_WriteString("Error", Font_6x8, Display_color);
				ssd1306_SetCursor(64,19);
				ssd1306_WriteString("Input!", Font_6x8, Display_color);
		}
		
	}
	ssd1306_UpdateScreen();
	s4459843_reg_lta1000g_write_value_8bit( (0x07&subgrid_Y) | (subgrid_X<<3));
}
/*
 * Control the OLED display. The refreshing time is 10ms. This is the main task 
 * function should be used to construct the task of OLED display. Put the function 
 * address into the xtaskCreate() to initiate the task.
 */
void tsk_CAG_display_ctrl(void)
{
	CAG_display_init();
	vTaskDelay(1000);
	for(;;)
	{
		CAG_Display_refresh();
		vTaskDelay(200);
	}
}
