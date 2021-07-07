 /** 
 **************************************************************
 * @file mylib/s4459843_reg_iss.c
 * @author MyName - MyStudent ID
 * @date 22022018
 * @brief mylib template driver
 * REFERENCE: DON'T JUST COPY THIS BLINDLY.pdf 
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 *************************************************************** 
 */
#include "s4459843_reg_iss.h"
uint32_t iss_eventcounter_val[8];
uint32_t iss_lasttimer_val[8];
uint32_t iss_delay_val[8];
void s4459843_reg_iss_init(void)
{
	for(int i=0;i<8;i++)
	{
		iss_eventcounter_val[i]=0;
		iss_lasttimer_val[i]=HAL_GetTick();
		iss_delay_val[i]=50;
	}
}



void s4459843_reg_iss_synchroniser(unsigned char signal_source_index)
{
	uint32_t time,lasttime;
	time=HAL_GetTick();
	lasttime=s4459843_reg_iss_lasttimer_read(signal_source_index);
	if(time-lasttime>iss_delay_val[signal_source_index])
	{
		iss_eventcounter_val[signal_source_index]++;
	}
	s4459843_reg_iss_lasttimer_reset(signal_source_index);
}
uint32_t s4459843_reg_iss_eventcounter_read(unsigned char signal_source_index)
{
	return iss_eventcounter_val[signal_source_index];
}
uint32_t s4459843_reg_iss_lasttimer_read(unsigned char signal_source_index)
{
	return iss_lasttimer_val[signal_source_index];
}
void s4459843_reg_iss_eventcounter_reset(unsigned char signal_source_index)
{
	iss_eventcounter_val[signal_source_index]=0;
}
void s4459843_reg_iss_lasttimer_reset(unsigned char signal_source_index)
{
	iss_lasttimer_val[signal_source_index]=HAL_GetTick();
}
void s4459843_reg_iss_delaytimer_ctrl(unsigned char signal_source_index, int delay_value)
{
	iss_delay_val[signal_source_index]=delay_value;
}
