/**
  ******************************************************************************
  * @file    CSSE3010/mylib/s4459843_CAG_keypad_mnemonic.c
  * @author  Yang Zheng
  * @date    10/05/2021
  * @brief   Initialization the keypad and design a Mnemonic mode control
  *          
  ******************************************************************************
  *
  */
#include "s4459843_CAG_keypad_mnemonic.h"

/*
 * Initialize the keypad at Mnemonic mode
 */
void s4459843_tsk_CAG_keypadMnemonic_init(void)
{
	xTaskCreate( (void *) &tsk_CAG_Mnemonic_Mode_ctrl, (const signed char *) "MNEMONIC", MNEMONICTASK_STACK_SIZE, NULL, MNEMONICTASK_PRIORITY+2, &MnemonicTaskHandle );
	xTaskCreate( (void *) &tsk_CAG_Mnemonic_Mode_sampgive, (const signed char *) "MNEMONICSAMPGIVE", MNEMONICSAMPGIVETASK_STACK_SIZE, NULL, MNEMONICSAMPGIVETASK_PRIORITY+2, &mnemonicsampgiveTaskHandle );
}
void CAG_keypadMnemonic_init(void)
{
	command_len=0;
	command_bar[0]='\0';
	selecting_letter='\0';
	selectingOn=0;
	lastpressed=0x00;
	selecting_time=0;
	varing_time=0;
	cursor_flashing_time=0;
	error_time=0;
	varing_state=0;
	cursor_flashing_state=0;
	error_show=0;
}
/*
 * Determine whether the keypad is pressed. If the keypad is pressed, read the value of the keypad
 */
void tsk_CAG_Mnemonic_Mode_processing(void)
{
	if(s4459843_reg_keypad_read_status()==1)
	{
		KeypadStatus=0;
		BRD_LEDGreenToggle();
		switch (pressedkey){
			case 0x00:activate_button(0x00);break;//R1C1
			case 0x01:activate_button(0x01);break;//R1C2
			case 0x02:activate_button(0x02);break;//R1C3
			case 0x03:processing_command();break;//R1C4
			case 0x04:activate_button(0x03);break;//R2C1
			case 0x05:activate_button(0x04);break;//R2C2
			case 0x06:activate_button(0x05);break;//R2C3
			case 0x07:backspace();break;//R2C4
			case 0x08:activate_button(0x06);break;//R3C1
			case 0x09:activate_button(0x07);break;//R3C2
			case 0x0a:activate_button(0x08);break;//R3C3
			case 0x0b:command_clear();break;//R3C4
			case 0x0c:activate_button(0x09);  break;//R4C1
			case 0x0d:activate_button(0x0a);  break;//R4C2
			case 0x0e:break;//R4C3
			case 0x0f:activate_button(0x0b);break;//R4C4
			default:break;
		}
	}
}
/*
 * Controling the mnemonic mode and start check the keypad status
 */
void tsk_CAG_Mnemonic_Mode_ctrl(void)
{
	CAG_keypadMnemonic_init();
	for(;;)
	{
		if (mnemonicSemaphore != NULL) 
		{
			if ( xSemaphoreTake( mnemonicSemaphore, 10 ) == pdTRUE ) 
			{
				if(CAG_MODE==MODE_Mnemonic)
				{
					tsk_CAG_Mnemonic_Mode_processing();
				}
			}
		}
		vTaskDelay(20);
	}
}
void tsk_CAG_Mnemonic_Mode_sampgive(void)
{
	// Create Semaphores 
	mnemonicSemaphore = xSemaphoreCreateBinary();
	TickType_t xLastWakeTime;
	
	xLastWakeTime = xTaskGetTickCount();
	for (;;) 
	{
		if(CAG_MODE==MODE_Mnemonic)
		{
			if (mnemonicSemaphore != NULL) // Check if semaphore exists
			{	
				// Give mnemonic Semaphore
				xSemaphoreGive(mnemonicSemaphore);
			}
			if(selectingOn==1)
			{
				selecting_time=selecting_time+20;
			}
			if(error_show==1)
			{
				error_time=error_time+20;
				if(error_time>1000)
				{
					error_show=0;
					error_time=0;
				}
			}
				
			if(selecting_time>2000)
			{
				pushing_selecting();
			}
			varing_time=varing_time+20;
			if(varing_time>1000)
			{
				varing_state=(varing_state+1)%4;
				varing_time=0;
			}
			cursor_flashing_time=cursor_flashing_time+20;
			if(cursor_flashing_time>500)
			{
				cursor_flashing_state=1-cursor_flashing_state;
				cursor_flashing_time=0;
			}
		}
		// Wait for 20ms
		vTaskDelayUntil( &xLastWakeTime, 20);
	}
}
void backspace(void)
{
	if(command_len==0)
	{
		command_clear();
	}
	else
	{
		pushing_selecting();
		for(int i=command_len-1;i<6;i++)
		{
			command_bar[i]='\0';
		}
		command_len=command_len-1;
	}
}
void activate_button(uint8_t pressed)
{
	if(command_len<6)
	{
		activate_letter_button(pressed);
	}
}
void activate_letter_button(uint8_t pressed)
{
	if(pressed==0x00)
	{
		if(selectingOn==1)//if previous letter is on selecting
		{
			pushing_selecting();
		}
		command_add_letter('1');
		lastpressed=0x00;
	}
	else if(pressed==0x01)
	{
		if(selectingOn==1)//if previous letter is on selecting
		{
			if(lastpressed==0x01)
			{
				if(selecting_letter=='2')
				{
					selecting_letter='A';
					selecting_time=0;
					lastpressed=0x01;
				}
				else if(selecting_letter=='A')
				{
					selecting_letter='B';
					selecting_time=0;
					lastpressed=0x01;
				}
				else if(selecting_letter=='B')
				{
					selecting_letter='C';
					selecting_time=0;
					lastpressed=0x01;
				}
				else if(selecting_letter=='C')
				{
					selecting_letter='2';
					selecting_time=0;
					lastpressed=0x01;
				}
			}
			else
			{
				pushing_selecting();
				selectingOn=1;//entering selecting model
				selecting_letter='2';
				selecting_time=0;
				lastpressed=0x01;
			}
		}
		else
		{
			selectingOn=1;//entering selecting model
			selecting_letter='2';
			selecting_time=0;
			lastpressed=0x01;
		}
	}
	else if(pressed==0x02)
	{
		if(selectingOn==1)//if previous letter is on selecting
		{
			if(lastpressed==0x02)
			{
				if(selecting_letter=='3')
				{
					selecting_letter='D';
					selecting_time=0;
					lastpressed=0x02;
				}
				else if(selecting_letter=='D')
				{
					selecting_letter='E';
					selecting_time=0;
					lastpressed=0x02;
				}
				else if(selecting_letter=='E')
				{
					selecting_letter='F';
					selecting_time=0;
					lastpressed=0x02;
				}
				else if(selecting_letter=='F')
				{
					selecting_letter='3';
					selecting_time=0;
					lastpressed=0x02;
				}
			}
			else
			{
				pushing_selecting();
				selectingOn=1;//entering selecting model
				selecting_letter='3';
				selecting_time=0;
				lastpressed=0x02;
			}
		}
		else
		{
			selectingOn=1;//entering selecting model
			selecting_letter='3';
			selecting_time=0;
			lastpressed=0x02;
		}
	}
	else if(pressed==0x03)
	{
		if(selectingOn==1)//if previous letter is on selecting
		{
			if(lastpressed==0x03)
			{
				if(selecting_letter=='4')
				{
					selecting_letter='G';
					selecting_time=0;
					lastpressed=0x03;
				}
				else if(selecting_letter=='G')
				{
					selecting_letter='H';
					selecting_time=0;
					lastpressed=0x03;
				}
				else if(selecting_letter=='H')
				{
					selecting_letter='I';
					selecting_time=0;
					lastpressed=0x03;
				}
				else if(selecting_letter=='I')
				{
					selecting_letter='4';
					selecting_time=0;
					lastpressed=0x03;
				}
			}
			else
			{
				pushing_selecting();
				selectingOn=1;//entering selecting model
				selecting_letter='4';
				selecting_time=0;
				lastpressed=0x03;
			}
		}
		else
		{
			selectingOn=1;//entering selecting model
			selecting_letter='4';
			selecting_time=0;
			lastpressed=0x03;
		}
	}
	else if(pressed==0x04)
	{
		if(selectingOn==1)//if previous letter is on selecting
		{
			if(lastpressed==0x04)
			{
				if(selecting_letter=='5')
				{
					selecting_letter='J';
					selecting_time=0;
					lastpressed=0x04;
				}
				else if(selecting_letter=='J')
				{
					selecting_letter='K';
					selecting_time=0;
					lastpressed=0x04;
				}
				else if(selecting_letter=='K')
				{
					selecting_letter='L';
					selecting_time=0;
					lastpressed=0x04;
				}
				else if(selecting_letter=='L')
				{
					selecting_letter='5';
					selecting_time=0;
					lastpressed=0x04;
				}
			}
			else
			{
				pushing_selecting();
				selectingOn=1;//entering selecting model
				selecting_letter='5';
				selecting_time=0;
				lastpressed=0x04;
			}
		}
		else
		{
			selectingOn=1;//entering selecting model
			selecting_letter='5';
			selecting_time=0;
			lastpressed=0x04;
		}
	}
	else if(pressed==0x05)
	{
		if(selectingOn==1)//if previous letter is on selecting
		{
			if(lastpressed==0x05)
			{
				if(selecting_letter=='6')
				{
					selecting_letter='M';
					selecting_time=0;
					lastpressed=0x05;
				}
				else if(selecting_letter=='M')
				{
					selecting_letter='N';
					selecting_time=0;
					lastpressed=0x05;
				}
				else if(selecting_letter=='N')
				{
					selecting_letter='O';
					selecting_time=0;
					lastpressed=0x05;
				}
				else if(selecting_letter=='O')
				{
					selecting_letter='6';
					selecting_time=0;
					lastpressed=0x05;
				}
			}
			else
			{
				pushing_selecting();
				selectingOn=1;//entering selecting model
				selecting_letter='6';
				selecting_time=0;
				lastpressed=0x05;
			}
		}
		else
		{
			selectingOn=1;//entering selecting model
			selecting_letter='6';
			selecting_time=0;
			lastpressed=0x05;
		}
	}
	else if(pressed==0x06)
	{
		if(selectingOn==1)//if previous letter is on selecting
		{
			if(lastpressed==0x06)
			{
				if(selecting_letter=='7')
				{
					selecting_letter='P';
					selecting_time=0;
					lastpressed=0x06;
				}
				else if(selecting_letter=='P')
				{
					selecting_letter='Q';
					selecting_time=0;
					lastpressed=0x06;
				}
				else if(selecting_letter=='Q')
				{
					selecting_letter='R';
					selecting_time=0;
					lastpressed=0x06;
				}
				else if(selecting_letter=='R')
				{
					selecting_letter='S';
					selecting_time=0;
					lastpressed=0x06;
				}
				else if(selecting_letter=='S')
				{
					selecting_letter='7';
					selecting_time=0;
					lastpressed=0x06;
				}
			}
			else
			{
				pushing_selecting();
				selectingOn=1;//entering selecting model
				selecting_letter='7';
				selecting_time=0;
				lastpressed=0x06;
			}
		}
		else
		{
			selectingOn=1;//entering selecting model
			selecting_letter='7';
			selecting_time=0;
			lastpressed=0x06;
		}
	}
	else if(pressed==0x07)
	{
		if(selectingOn==1)//if previous letter is on selecting
		{
			if(lastpressed==0x07)
			{
				if(selecting_letter=='8')
				{
					selecting_letter='T';
					selecting_time=0;
					lastpressed=0x07;
				}
				else if(selecting_letter=='T')
				{
					selecting_letter='U';
					selecting_time=0;
					lastpressed=0x07;
				}
				else if(selecting_letter=='U')
				{
					selecting_letter='V';
					selecting_time=0;
					lastpressed=0x07;
				}
				else if(selecting_letter=='V')
				{
					selecting_letter='8';
					selecting_time=0;
					lastpressed=0x07;
				}
			}
			else
			{
				pushing_selecting();
				selectingOn=1;//entering selecting model
				selecting_letter='8';
				selecting_time=0;
				lastpressed=0x07;
			}
		}
		else
		{
			selectingOn=1;//entering selecting model
			selecting_letter='8';
			selecting_time=0;
			lastpressed=0x07;
		}
	}
	else if(pressed==0x08)
	{
		if(selectingOn==1)//if previous letter is on selecting
		{
			if(lastpressed==0x08)
			{
				if(selecting_letter=='9')
				{
					selecting_letter='W';
					selecting_time=0;
					lastpressed=0x08;
				}
				else if(selecting_letter=='W')
				{
					selecting_letter='X';
					selecting_time=0;
					lastpressed=0x08;
				}
				else if(selecting_letter=='X')
				{
					selecting_letter='Y';
					selecting_time=0;
					lastpressed=0x08;
				}
				else if(selecting_letter=='Y')
				{
					selecting_letter='Z';
					selecting_time=0;
					lastpressed=0x08;
				}
				else if(selecting_letter=='Z')
				{
					selecting_letter='9';
					selecting_time=0;
					lastpressed=0x08;
				}
			}
			else
			{
				pushing_selecting();
				selectingOn=1;//entering selecting model
				selecting_letter='9';
				selecting_time=0;
				lastpressed=0x08;
			}
		}
		else
		{
			selectingOn=1;//entering selecting model
			selecting_letter='9';
			selecting_time=0;
			lastpressed=0x08;
		}
	}
	else if(pressed==0x09)//'0' pressed
	{
		if(selectingOn==1)//if previous letter is on selecting
		{
			pushing_selecting();
		}
		command_add_letter('0');
		lastpressed=0x09;
	}
	else if(pressed==0x0a)//'*' pressed
	{
		if(selectingOn==1)//if previous letter is on selecting
		{
			pushing_selecting();
		}
		command_add_letter('*');
		lastpressed=0x0a;
	}
	else if(pressed==0x0b)//'#' pressed
	{
		if(selectingOn==1)//if previous letter is on selecting
		{
			pushing_selecting();
		}
		command_add_letter('#');
		lastpressed=0x0b;
	}
}
void pushing_selecting(void)
{
	if(selectingOn==1)//if previous letter is on selecting
	{
		command_add_letter(selecting_letter);//push the selecting letter to the commend buffer
		selecting_letter='\0';//clear the selecting letter
		selectingOn=0;	
		selecting_time=0;
	}
}
void command_add_letter(char let)
{
	if(command_len<6)
	{
		command_bar[command_len]=let;
		command_len++;
	}
}
void command_clear(void)
{
	selecting_letter='\0';
	selectingOn=0;
	selecting_time=0;
	for(int i=0;i<6;i++)
	{
		command_bar[i]='\0';
	}
	command_len=0;
}
void error_raise(void)
{
	error_show=1;
	command_clear();
}
void processing_command(void)
{
	pushing_selecting();
	caMessage_t DrawMessage;
	if(command_len>0)
	{
		if(Simulation_Drive==1)
		{
			if( (command_bar[0]=='S') && (command_bar[1]=='T') && (command_bar[2]=='L') && ( command_bar[3]>='0' && command_bar[3]<='2' ) && ( command_bar[4]>='0' && command_bar[4]<='9' ) && ( command_bar[5]>='0' && command_bar[5]<='4' ) )
			{
				//STL<type><x><y>
				DrawMessage.type=0x20+(command_bar[3]-'0');
				DrawMessage.cell_x=(command_bar[4]-'0')*3;
				DrawMessage.cell_y=(command_bar[5]-'0')*3;
				Draw_shape(DrawMessage);
				command_clear(); 
				return;
			}
			else if( (command_bar[0]=='O') && (command_bar[1]=='S') && (command_bar[2]=='C') && ( command_bar[3]>='0' && command_bar[3]<='2' ) && ( command_bar[4]>='0' && command_bar[4]<='9' ) && ( command_bar[5]>='0' && command_bar[5]<='4' ) )
			{
				//OSC<type><x><y>
				DrawMessage.type=0x30+(command_bar[3]-'0');
				DrawMessage.cell_x=(command_bar[4]-'0')*3;
				DrawMessage.cell_y=(command_bar[5]-'0')*3;
				Draw_shape(DrawMessage);
				command_clear(); 
				return;
			}
			else if( (command_bar[0]=='G') && (command_bar[1]=='L') && (command_bar[2]=='D') && ( command_bar[3]>='0' && command_bar[3]<='9' ) && ( command_bar[4]>='0' && command_bar[4]<='4' ) && (command_bar[5]=='\0') )
			{
				//GLD<x><y>
				DrawMessage.type=0x40;
				DrawMessage.cell_x=(command_bar[3]-'0')*3;
				DrawMessage.cell_y=(command_bar[4]-'0')*3;
				Draw_shape(DrawMessage);
				command_clear(); 
				return;
			}
			else if( (command_bar[0]=='*') && (command_bar[1]=='\0') )
			{
				//*
				simulation_start();
				command_clear(); 
				return;
			}
			else if( (command_bar[0]=='#') && (command_bar[1]=='\0') )
			{
				//#
				simulation_stop();
				command_clear(); 
				return;
			}
			else if( (command_bar[0]=='0') && (command_bar[1]=='\0') )
			{
				//0
				Clear_Simulation();
				command_clear(); 
				return;
			}
		}
		if( (command_bar[0]=='D') && (command_bar[1]=='L') && (command_bar[2]=='T') && ( command_bar[3]>='0' && command_bar[3]<='1' )  && (command_bar[4]=='\0') )
		{
			//DLT<type>
			if(command_bar[3]=='0')
			{
				CAG_Simulator_Drive_Delete();
			}
			else if(command_bar[3]=='1')
			{
				CAG_Joystick_Drive_Delete();
			}
		}
		else if( (command_bar[0]=='C') && (command_bar[1]=='R') && (command_bar[2]=='E') && ( command_bar[3]>='0' && command_bar[3]<='1' )  && (command_bar[4]=='\0') )
		{
			//CRE<type>
			if(command_bar[3]=='0')
			{
				CAG_Simulator_Drive_Create();
			}
			else if(command_bar[3]=='1')
			{
				 CAG_Joystick_Drive_Create();
			}
		}
		else
		{
			error_raise();
		}
		command_clear(); 
	}
}

void CAG_Simulator_Drive_Delete(void)
{
	Clear_Simulation();
	simulation_stop();
	Simulation_Drive=0;
}
void CAG_Joystick_Drive_Delete(void)
{
	Joystick_Drive=0;
}
void CAG_Simulator_Drive_Create(void)
{
	Simulation_Drive=1;
	simulation_start();
}
void CAG_Joystick_Drive_Create(void)
{
	Joystick_Drive=1;
}
