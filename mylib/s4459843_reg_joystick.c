/** 
 **************************************************************
 * @file mylib/s4459843_reg_joystick.c
 * @author Yang Zheng - 44598435
 * @date 14032021
 * @brief Using the joystick to control the dutycycle
*         
 * REFERENCE: None
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * 
 * 
 * 
 * 
 *************************************************************** 
 */
#include "s4459843_reg_joystick.h"

void s4459843_reg_joystick_init(void)
{
	s4459843_reg_joystick_init1();
	s4459843_reg_joystick_init2();
	s4459843_reg_joystick_init3();
	Joystick_Drive=0;
}
void s4459843_reg_joystick_init1(void) //Init X
{

	Xvalue=0x7ff;
	// Enable the GPIO A Clock
  	__GPIOA_CLK_ENABLE();
 
  
	// Initalise PA3 as an Analog input.
  	GPIOA->MODER |= (0x03 << (3 * 2));			//Set bits for Analog input mode
  	GPIOA->OSPEEDR &= ~(0x03<<(3 * 2));
	GPIOA->OSPEEDR |= 0x02<<(3 * 2);  			// Fast speed
	GPIOA->PUPDR &= ~(0x03 << (3 * 2));			//Clear bits for no push/pull


	__ADC1_CLK_ENABLE();						//Enable ADC1 clock

	AdcHandle1.Instance = (ADC_TypeDef *)(ADC1_BASE);						//Use ADC1 (For PA3)
	AdcHandle1.Init.ClockPrescaler        = ADC_CLOCKPRESCALER_PCLK_DIV2;	//Set clock prescaler
	AdcHandle1.Init.Resolution            = ADC_RESOLUTION12b;				//Set 12-bit data resolution
	AdcHandle1.Init.ScanConvMode          = DISABLE;
	AdcHandle1.Init.ContinuousConvMode    = DISABLE;
	AdcHandle1.Init.DiscontinuousConvMode = DISABLE;
	AdcHandle1.Init.NbrOfDiscConversion   = 0;
	AdcHandle1.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;	//No Trigger
	AdcHandle1.Init.ExternalTrigConv      = ADC_EXTERNALTRIGCONV_T1_CC1;		//No Trigger
	AdcHandle1.Init.DataAlign             = ADC_DATAALIGN_RIGHT;				//Right align data
	AdcHandle1.Init.NbrOfConversion       = 1;
	AdcHandle1.Init.DMAContinuousRequests = DISABLE;
	AdcHandle1.Init.EOCSelection          = DISABLE;

	HAL_ADC_Init(&AdcHandle1);		//Initialise ADC

	// Configure ADC Channel
	AdcChanConfig1.Channel = ADC_CHANNEL_3;					//PA3 has Analog Channel 3 connected
	AdcChanConfig1.Rank         = 1;
	AdcChanConfig1.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	AdcChanConfig1.Offset       = 0;

	HAL_ADC_ConfigChannel(&AdcHandle1, &AdcChanConfig1);		//Initialise ADC Channel
}
void s4459843_reg_joystick_init2(void)  //Init Y
{

	Yvalue=0x7ff;
	// Enable the GPIO C Clock

    __GPIOC_CLK_ENABLE();
 

    GPIOC->MODER |= (0x03 << (0 * 2));			//Set bits for Analog input mode
  	GPIOC->OSPEEDR &= ~(0x03<<(0 * 2));
	GPIOC->OSPEEDR |= 0x02<<(0 * 2);  			// Fast speed
	GPIOC->PUPDR &= ~(0x03 << (0 * 2));			//Clear bits for no push/pull


	__ADC2_CLK_ENABLE();						//Enable ADC2 clock

	AdcHandle2.Instance = (ADC_TypeDef *)(ADC2_BASE);						//Use ADC2 (For PC0)
	AdcHandle2.Init.ClockPrescaler        = ADC_CLOCKPRESCALER_PCLK_DIV2;	//Set clock prescaler
	AdcHandle2.Init.Resolution            = ADC_RESOLUTION12b;				//Set 12-bit data resolution
	AdcHandle2.Init.ScanConvMode          = DISABLE;
	AdcHandle2.Init.ContinuousConvMode    = DISABLE;
	AdcHandle2.Init.DiscontinuousConvMode = DISABLE;
	AdcHandle2.Init.NbrOfDiscConversion   = 0;
	AdcHandle2.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;	//No Trigger
	AdcHandle2.Init.ExternalTrigConv      = ADC_EXTERNALTRIGCONV_T1_CC1;		//No Trigger
	AdcHandle2.Init.DataAlign             = ADC_DATAALIGN_RIGHT;				//Right align data
	AdcHandle2.Init.NbrOfConversion       = 1;
	AdcHandle2.Init.DMAContinuousRequests = DISABLE;
	AdcHandle2.Init.EOCSelection          = DISABLE;

	HAL_ADC_Init(&AdcHandle2);		//Initialise ADC

	// Configure ADC Channel
	AdcChanConfig2.Channel = ADC_CHANNEL_10;					//PC0 has Analog Channel 10 connected
	AdcChanConfig2.Rank         = 1;
	AdcChanConfig2.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	AdcChanConfig2.Offset       = 0;

	HAL_ADC_ConfigChannel(&AdcHandle2, &AdcChanConfig2);		//Initialise ADC Channel
}
void s4459843_reg_joystick_init3(void)  //Init Z
{
	// Enable GPIOC Clock
	__GPIOC_CLK_ENABLE();

    GPIOC->OSPEEDR |= (GPIO_SPEED_FAST << 2);	//Set fast speed.
	GPIOC->PUPDR &= ~(0x03 << (2 * 2));			//Clear bits for no push/pull
	GPIOC->MODER &= ~(0x03 << (2 * 2));			//Clear bits for input mode

	// Enable EXTI clock
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	//select trigger source (port c, pin 13) on EXTICR4.
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI2;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI2_PC;
	SYSCFG->EXTICR[0] &= ~(0x000F);

	EXTI->RTSR |= EXTI_RTSR_TR2;	//enable rising dedge
	EXTI->FTSR &= ~EXTI_FTSR_TR2;	//disable falling edge
	
	EXTI->IMR |= EXTI_IMR_IM2;		//Enable external interrupt

	//Enable priority (10) and interrupt callback. Do not set a priority lower than 5.
	HAL_NVIC_SetPriority(EXTI2_IRQn, 10, 0);
	HAL_NVIC_EnableIRQ(EXTI2_IRQn);
}
unsigned char joystick_readZ(void)
{
	unsigned char zstatus=0x00;
	if(s4459843_reg_iss_eventcounter_read(JOYSTICK_Z_CHANNEL)>0)
	{
		s4459843_reg_iss_eventcounter_reset(JOYSTICK_Z_CHANNEL);
		zstatus=0x01;
	}
	return zstatus;
}
void s4459843_reg_joystick_iss_isr(int GPIO_P)
{
	if(GPIO_P==GPIO_JOYSTICKZ)
	{
		s4459843_reg_iss_synchroniser(JOYSTICK_Z_CHANNEL);
	}
}
