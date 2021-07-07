#include "s4459843_tsk_joystick.h"
xTaskHandle joystickTaskHandle;
void s4459843_tsk_joystick_init(void)
{
	xTaskCreate( (void *) &s4459843_tsk_joystick_ctrl, (const signed char *) "JOYSTICK", OLEDTASK_STACK_SIZE, NULL, OLEDTASK_PRIORITY+2, joystickTaskHandle );
}
void s4459843_tsk_joystick_ctrl(void)
{
	s4459843_reg_joystick_init();
	for(;;)
	{
		if(Joystick_Drive==1)
		{
			if(s4459843_reg_iss_eventcounter_read(JOYSTICK_Z_CHANNEL)>0)
			{
				s4459843_reg_iss_eventcounter_reset(JOYSTICK_Z_CHANNEL);
				Clear_Simulation();
			}
			HAL_ADC_Start(&AdcHandle1); // Start ADC conversion
			while (HAL_ADC_PollForConversion(&AdcHandle1, 10) != HAL_OK);
			Xvalue = ADC1->DR;		//Read ADC1 Data Register for converted value.
			
			HAL_ADC_Start(&AdcHandle2); // Start ADC conversion
			while (HAL_ADC_PollForConversion(&AdcHandle2, 10) != HAL_OK);
			Yvalue = ADC2->DR;		//Read ADC2 Data Register for converted value.
			
			if(Xvalue<=0x7ff)
			{
				Display_color=SSD1306_WHITE;
				inverse_color=0;
			}
			else
			{
				Display_color=Black;
				inverse_color=1;
			}
			if(Yvalue<0x555)
			{
				simulation_update_time=500;
			}
			else if(Yvalue<0xaaa)
			{
				simulation_update_time=2000;
			}
			else
			{
				simulation_update_time=10000;
			}
		}
		vTaskDelay(100);
	}
}
