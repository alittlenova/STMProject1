#include "s4459843_tsk_oled.h"
xTaskHandle leftTaskHandle;
xTaskHandle rightTaskHandle;
xTaskHandle OLEDTaskHandle;
void s4459843_tsk_oled_init(void)
{
	xTaskCreate( (void *) &s4459843_tsk_OLED_ctrl, (const signed char *) "OLED", OLEDTASK_STACK_SIZE, NULL, OLEDTASK_PRIORITY+2, &OLEDTaskHandle );
}
void s4459843_tsk_timer_init(void)
{
	Timer[0].type='l';
	Timer[1].type='r';
	Timer[0].timerValue=0;
	Timer[1].timerValue=0;
	xTaskCreate( (void *) &s4459843_tsk_TimerRight_ctrl, (const signed char *) "RIGHTTIMER", OLEDTASK_STACK_SIZE, NULL, OLEDTASK_PRIORITY+1, &rightTaskHandle );
	xTaskCreate( (void *) &s4459843_tsk_TimerLeft_ctrl, (const signed char *) "LEFTTIMER", OLEDTASK_STACK_SIZE, NULL, OLEDTASK_PRIORITY, &leftTaskHandle );
}
void s4459843_tsk_OLED_ctrl(void)
{
	s4459843_reg_oled_init();
	vTaskDelay(1000);
	for(;;)
	{
		s4459843_tsk_queueTimerDisplay();
		BRD_LEDBlueToggle();
		vTaskDelay(10);
	}
}
void s4459843_tsk_TimerLeft_ctrl(void)
{
	vTaskDelay(1000);
	for (;;) 
	{
		Timer[0].timerValue++;
		Timer[0].timerValue=Timer[0].timerValue % 100;
		//s4459843_tsk_queueTimerDisplay();
		//BRD_LEDBlueToggle();
		vTaskDelay(1000);
	}
}
void s4459843_tsk_TimerRight_ctrl(void)
{
	vTaskDelay(1000);
	for (;;) 
	{
		Timer[1].timerValue++;
		Timer[1].timerValue=Timer[1].timerValue % 100;
		//s4459843_tsk_queueTimerDisplay();
		BRD_LEDRedToggle();
		vTaskDelay(100);
	}
}
void s4459843_tsk_queueTimerDisplay(void)
{	
	OLEDMSG.displayText[0]='\0';
	buf1[0]='\0';
	buf2[0]='\0';
	if(Timer[0].timerValue<100 && Timer[1].timerValue<100)
	{
		myitoa(Timer[0].timerValue,buf1,10);
		myitoa(Timer[1].timerValue,buf2,10);
		my_strcat(OLEDMSG.displayText,buf1);
		my_strcat(OLEDMSG.displayText,"   ");
		my_strcat(OLEDMSG.displayText,buf2);
		s4459843_tsk_oled_writemsg(OLEDMSG);
	}
}
void s4459843_tsk_oled_writemsg(struct oledTextMsg Msg)
{
		//Clear Screen
		ssd1306_Fill(Black);
		//Drawing text
		ssd1306_SetCursor(Msg.startX,Msg.startY);
		ssd1306_WriteString(Msg.displayText, Font_11x18, SSD1306_WHITE);
		ssd1306_UpdateScreen();
}
void my_strcat(char *str1, char *str2)
{
    char *pt = str1;
    while(*str1!='\0') str1++;
    while(*str2!='\0') *str1++ = *str2++;
    *str1 = '\0';
    //return pt;
}
void myitoa(uint32_t value, char *string, uint8_t radix)
{
    uint32_t     i, d;
    uint8_t     flag = 0;
    char    *ptr = string;
 
    /* This implementation only works for decimal numbers. */
    if (radix != 10)
    {
        *ptr = 0;
        //return string;
    }
 
    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        //return string;
    }
 
    /* if this is a negative value insert the minus sign. */
    if ((int)value < 0 )
    {
        *ptr++ = '-';
 
        /* Make the value positive. */
        value *= -1;
    }
 
    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;
 
        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }
 
    /* Null terminate the string. */
    *ptr = 0;
}
