 /** 
 **************************************************************
 * @file mylib/s4459843_reg_keypad.c
 * @author MyName - MyStudent ID
 * @date 22022018
 * @brief mylib template driver
 * REFERENCE: DON'T JUST COPY THIS BLINDLY.pdf 
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * s4459843_reg_keypad_init() - intialise mylib template driver
 * s4459843_reg_keypad_set() - set mylib template driver 
 *************************************************************** 
 */
#include "s4459843_reg_keypad.h"

void s4459843_reg_keypad_init(void) 
{
	KeypadFsmCurrentstate=INIT_STATE;
	keypad_gpio_init();
}
void s4459843_reg_keypad_fsmprocessing(void)
{
	pressedkey=s4459843_reg_keypad_read_key();
	if(KeypadFsmCurrentstate==INIT_STATE)
	{
		KeypadFsmCurrentstate=RSCAN1_STATE;
		keypad_writecol(keypad_col1());
	}
	else if(KeypadFsmCurrentstate==RSCAN1_STATE)
	{
		KeypadFsmCurrentstate=RSCAN2_STATE;
		keypad_writecol(keypad_col2());
	}
	else if(KeypadFsmCurrentstate==RSCAN2_STATE)
	{
		KeypadFsmCurrentstate=RSCAN3_STATE;
		keypad_writecol(keypad_col3());
	}
	else if(KeypadFsmCurrentstate==RSCAN3_STATE)
	{
		KeypadFsmCurrentstate=RSCAN4_STATE;
		keypad_writecol(keypad_col4());
	}
	else if(KeypadFsmCurrentstate==RSCAN4_STATE)
	{
		KeypadFsmCurrentstate=RSCAN1_STATE;
		keypad_writecol(keypad_col1());
	}
	
	//s4459843_reg_lta1000g_write_keypad();
}
void keypad_gpio_init(void)
{
	// Enable GPIOF Clock
	__GPIOF_CLK_ENABLE();
	__GPIOE_CLK_ENABLE();

    GPIOF->OSPEEDR |= (GPIO_SPEED_FAST << 12);	//Set fast speed.
	GPIOF->PUPDR &= ~(0x03 << (12 * 2));			//Clear bits for no push/pull
	GPIOF->MODER &= ~(0x03 << (12 * 2));			//Clear bits for I/O mode
	GPIOF->MODER |= (0x01 << (12 * 2));   			//Set for output mode
	GPIOF->OTYPER &= ~(0x01 << 12);       			//Clear Bit for Push/Pull outtput

	GPIOF->OSPEEDR |= (GPIO_SPEED_FAST << 13);	//Set fast speed.
	GPIOF->PUPDR &= ~(0x03 << (13 * 2));			//Clear bits for no push/pull
	GPIOF->MODER &= ~(0x03 << (13 * 2));			//Clear bits for I/O mode
	GPIOF->MODER |= (0x01 << (13 * 2));   			//Set for output mode
	GPIOF->OTYPER &= ~(0x01 << 13);       			//Clear Bit for Push/Pull outtput

	GPIOF->OSPEEDR |= (GPIO_SPEED_FAST << 14);	//Set fast speed.
	GPIOF->PUPDR &= ~(0x03 << (14 * 2));			//Clear bits for no push/pull
	GPIOF->MODER &= ~(0x03 << (14 * 2));			//Clear bits for I/O mode
	GPIOF->MODER |= (0x01 << (14 * 2));   			//Set for output mode
	GPIOF->OTYPER &= ~(0x01 << 14);       			//Clear Bit for Push/Pull outtput

	GPIOE->OSPEEDR |= (GPIO_SPEED_FAST << 13);	//Set fast speed.
	GPIOE->PUPDR &= ~(0x03 << (13 * 2));			//Clear bits for no push/pull
	GPIOE->MODER &= ~(0x03 << (13 * 2));			//Clear bits for I/O mode
	GPIOE->MODER |= (0x01 << (13 * 2));   			//Set for output mode
	GPIOE->OTYPER &= ~(0x01 << 13);       			//Clear Bit for Push/Pull outtput


	// Enable GPIOF Clock
	__GPIOF_CLK_ENABLE();

    GPIOF->OSPEEDR |= (GPIO_SPEED_FAST << 3);	//Set fast speed.
	GPIOF->PUPDR &= ~(0x03 << (3 * 2));			//Clear bits for no push/pull
	GPIOF->MODER &= ~(0x03 << (3 * 2));			//Clear bits for input mode

	GPIOF->OSPEEDR |= (GPIO_SPEED_FAST << 5);	//Set fast speed.
	GPIOF->PUPDR &= ~(0x03 << (5 * 2));			//Clear bits for no push/pull
	GPIOF->MODER &= ~(0x03 << (5 * 2));			//Clear bits for input mode

	GPIOF->OSPEEDR |= (GPIO_SPEED_FAST << 10);	//Set fast speed.
	GPIOF->PUPDR &= ~(0x03 << (10 * 2));			//Clear bits for no push/pull
	GPIOF->MODER &= ~(0x03 << (10 * 2));			//Clear bits for input mode

	GPIOF->OSPEEDR |= (GPIO_SPEED_FAST << 15);	//Set fast speed.
	GPIOF->PUPDR &= ~(0x03 << (15 * 2));			//Clear bits for no push/pull
	GPIOF->MODER &= ~(0x03 << (15 * 2));			//Clear bits for input mode



	// Enable EXTI clock
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	
	//select trigger source (port f, pin 3) on EXTICR1.
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI3;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PF;
	SYSCFG->EXTICR[0] &= ~(0x000F);
	
	//select trigger source (port f, pin 5) on EXTICR2.
	SYSCFG->EXTICR[1] &= ~SYSCFG_EXTICR2_EXTI5;
	SYSCFG->EXTICR[1] |= SYSCFG_EXTICR2_EXTI5_PF;
	SYSCFG->EXTICR[1] &= ~(0x000F);

	//select trigger source (port f, pin 10) on EXTICR3.
	SYSCFG->EXTICR[2] &= ~SYSCFG_EXTICR3_EXTI10;
	SYSCFG->EXTICR[2] |= SYSCFG_EXTICR3_EXTI10_PF;
	SYSCFG->EXTICR[2] &= ~(0x000F);

	//select trigger source (port f, pin 15) on EXTICR4.
	SYSCFG->EXTICR[3] &= ~SYSCFG_EXTICR4_EXTI15;
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI15_PF;
	SYSCFG->EXTICR[3] &= ~(0x000F);
	
	EXTI->RTSR &= ~EXTI_RTSR_TR3;	//disable rising dedge
	EXTI->FTSR |= EXTI_FTSR_TR3;	//enable falling edge
	
	EXTI->RTSR &= ~EXTI_RTSR_TR5;	//disable rising dedge
	EXTI->FTSR |= EXTI_FTSR_TR5;	//enable falling edge
	
	EXTI->RTSR &= ~EXTI_RTSR_TR10;	//disable rising dedge
	EXTI->FTSR |= EXTI_FTSR_TR10;	//enable falling edge
	
	EXTI->RTSR &= ~EXTI_RTSR_TR15;	//disable rising dedge
	EXTI->FTSR |= EXTI_FTSR_TR15;	//enable falling edge
	
	EXTI->IMR |= EXTI_IMR_IM3;		//Enable external interrupt
	EXTI->IMR |= EXTI_IMR_IM5;		//Enable external interrupt
	EXTI->IMR |= EXTI_IMR_IM10;		//Enable external interrupt
	EXTI->IMR |= EXTI_IMR_IM15;		//Enable external interrupt





	//Enable priority (10) and interrupt callback. Do not set a priority lower than 5.
	HAL_NVIC_SetPriority(EXTI3_IRQn, 10, 0);
	HAL_NVIC_EnableIRQ(EXTI3_IRQn);
	
	//Enable priority (10) and interrupt callback. Do not set a priority lower than 5.
	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 10, 1);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
	
	//Enable priority (10) and interrupt callback. Do not set a priority lower than 5.
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 10, 2);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}
void keypad_writecol(unsigned char colval)
{
	//set col 0,1,2,3 to the low state
	if(colval==keypad_col1())//Fi7rst column
	{
		GPIOE->ODR &= ~(0x01 << 13);	//Col1 low
		GPIOF->ODR |= (0x01 << 14);	//Col2 high
		GPIOF->ODR |= (0x01 << 13);	//Col3 high
		GPIOF->ODR |= (0x01 << 12);	//Col4 high
	}
	else if(colval==keypad_col2())//Second column
	{
		GPIOE->ODR |= (0x01 << 13);	//Col1 high
		GPIOF->ODR &= ~(0x01 << 14);	//Col2 low
		GPIOF->ODR |= (0x01 << 13);	//Col3 high
		GPIOF->ODR |= (0x01 << 12);	//Col4 high
	}
	else if(colval==keypad_col3())//Third column
	{
		GPIOE->ODR |= (0x01 << 13);	//Col1 high
		GPIOF->ODR |= (0x01 << 14);	//Col2 high
		GPIOF->ODR &= ~(0x01 << 13);	//Col3 low
		GPIOF->ODR |= (0x01 << 12);	//Col4 high
	}
	else if(colval==keypad_col4())//Forth column
	{
		GPIOE->ODR |= (0x01 << 13);	//Col1 high
		GPIOF->ODR |= (0x01 << 14);	//Col2 high
		GPIOF->ODR |= (0x01 << 13);	//Col3 high
		GPIOF->ODR &= ~(0x01 << 12);	//Col4 low
	}
}
unsigned char keypad_readrow(void)
{
	unsigned char rstatus=0x00;
	static unsigned char lastrow=0x00;
	if(s4459843_reg_iss_eventcounter_read(ROW1)>0)
	{
		s4459843_reg_iss_eventcounter_reset(ROW1);
		rstatus=0x01;
	}
	if(s4459843_reg_iss_eventcounter_read(ROW2)>0)
	{
		s4459843_reg_iss_eventcounter_reset(ROW2);
		
		rstatus=0x02;
	}
	if(s4459843_reg_iss_eventcounter_read(ROW3)>0)
	{
		s4459843_reg_iss_eventcounter_reset(ROW3);
		
		rstatus=0x04;
	}
	if(s4459843_reg_iss_eventcounter_read(ROW4)>0)
	{
		s4459843_reg_iss_eventcounter_reset(ROW4);
		
		rstatus=0x08;
	}
	if(rstatus==0x00)
	{
		KeypadStatus=0;
	}
	else
	{
		KeypadStatus=1;
		lastrow=rstatus;
	}
	return lastrow;
}
int s4459843_reg_keypad_read_status(void)
{
	if(KeypadStatus==1)
	{
		KeypadStatus=0;
		return 1;
	}
	else
	{
		return 0;
	}
}
unsigned char s4459843_reg_keypad_read_key(void)
{
	unsigned char row,rowmask;
	row=0x00;
	rowmask=keypad_readrow();
	if((rowmask & 0x01)==0x01)
	{
		row=0x00;//start at first row 0x00-0x03
	}
	else if((rowmask & 0x02)==0x02)
	{
		row=0x04;//start at second row 0x04-0x07
	}
	else if((rowmask & 0x04)==0x04)
	{
		row=0x08;//start at third row 0x08-0x0b
	}
	else if((rowmask & 0x08)==0x08)
	{
		row=0x0c;//default start at forth row 0x0c-0x0f
	}
	
	
	if(KeypadFsmCurrentstate==0x01)
	{
		return row+0x00;//The last FSM status record
		//return 0x04;
	}
	else if(KeypadFsmCurrentstate==0x02)
	{
		return row+0x01;
		//return 0x01;
	}
	else if(KeypadFsmCurrentstate==0x03)
	{
		return row+0x02;
		//return 0x02;
	}
	else if(KeypadFsmCurrentstate==0x04)
	{
		return row+0x03;
		//return 0x03;
	}
	else
	{
		return 0x00;
	}
}
int s4459843_reg_keypad_read_ascii(void)
{
	unsigned char kstatus;
	kstatus=s4459843_reg_keypad_read_key();
	switch (kstatus){
		case 0x00:return 49;  break;//R1C1
		case 0x01:return 50;  break;//R1C2
		case 0x02:return 51;  break;//R1C3
		case 0x03:return 65;  break;//R1C4
		case 0x04:return 52;  break;//R2C1
		case 0x05:return 53;  break;//R2C2
		case 0x06:return 54;  break;//R2C3
		case 0x07:return 66;  break;//R2C4
		case 0x08:return 55;  break;//R3C1
		case 0x09:return 56;  break;//R3C2
		case 0x0a:return 57;  break;//R3C3
		case 0x0b:return 67;  break;//R3C4
		case 0x0c:return 48;  break;//R4C1
		case 0x0d:return 70;  break;//R4C2
		case 0x0e:return 69;  break;//R4C3
		case 0x0f:return 68;  break;//R4C4
	}
}
unsigned char s4459843_reg_keypad_read_hex(void)
{
	unsigned char kstatus;
	kstatus=s4459843_reg_keypad_read_key();
	switch (kstatus){
		case 0x00:return 0x01;  break;//R1C1
		case 0x01:return 0x02;  break;//R1C2
		case 0x02:return 0x03;  break;//R1C3
		case 0x03:return 0x0a;  break;//R1C4
		case 0x04:return 0x04;  break;//R2C1
		case 0x05:return 0x05;  break;//R2C2
		case 0x06:return 0x06;  break;//R2C3
		case 0x07:return 0x0b;  break;//R2C4
		case 0x08:return 0x07;  break;//R3C1
		case 0x09:return 0x08;  break;//R3C2
		case 0x0a:return 0x09;  break;//R3C3
		case 0x0b:return 0x0c;  break;//R3C4
		case 0x0c:return 0x00;  break;//R4C1
		case 0x0d:return 0x0f;  break;//R4C2
		case 0x0e:return 0x0e;  break;//R4C3
		case 0x0f:return 0x0d;  break;//R4C4
	}
}
void s4459843_reg_keypad_iss_isr(int GPIO_P)
{
	if(GPIO_P==GPIO_ROW1)
	{
		s4459843_reg_iss_synchroniser(ROW1);
	}
	else if(GPIO_P==GPIO_ROW2)
	{
		s4459843_reg_iss_synchroniser(ROW2);
	}
	else if(GPIO_P==GPIO_ROW3)
	{
		s4459843_reg_iss_synchroniser(ROW3);
	}
	else if(GPIO_P==GPIO_ROW4)
	{
		s4459843_reg_iss_synchroniser(ROW4);
	}
}
