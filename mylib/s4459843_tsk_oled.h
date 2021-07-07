#ifndef S4459843_TSK_OLED_H
#define S4459843_TSK_OLED_H
#include "main.h"
// Task Priorities (Idle Priority is the lowest priority)
#define OLEDTASK_PRIORITY					( tskIDLE_PRIORITY + 2 )

// Task Stack Allocations (must be a multiple of the minimal stack size)
#define OLEDTASK_STACK_SIZE		( configMINIMAL_STACK_SIZE * 2 )
struct oledTextMsg
{ 
	int startX;
	int startY;
	char displayText [20];
};
struct dualTimerMsg 
{
	char type;
	unsigned char timerValue;
};

struct dualTimerMsg Timer[2];
extern xTaskHandle leftTaskHandle;
extern xTaskHandle rightTaskHandle;
extern xTaskHandle OLEDTaskHandle;
char buf1[3];
char buf2[3];
struct oledTextMsg OLEDMSG;


extern void s4459843_tsk_oled_init(void);
extern void s4459843_tsk_timer_init(void);
void s4459843_tsk_OLED_ctrl(void);
void s4459843_tsk_TimerLeft_ctrl(void);
void s4459843_tsk_TimerRight_ctrl(void);
void s4459843_tsk_queueTimerDisplay(void);
//extern void s4459843_tsk_oled_ctrl(void);
//void s4459843_tsk_oled_writetwonumbers(uint32_t left, uint32_t right);
void s4459843_tsk_oled_writemsg(struct oledTextMsg Msg);
void my_strcat(char *str1, char *str2);
void myitoa(uint32_t value, char *string, uint8_t radix);

#endif
