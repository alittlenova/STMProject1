/** 
 **************************************************************
 * @file mylib/s4459843_reg_joystick.h
 * @author Yang Zheng - 44598435
 * @date 14032021
 * @brief Joystick
 * REFERENCE: None
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * 
 *************************************************************** 
 */
#ifndef S4459843_REG_JOYSTICK_H
#define S4459843_REG_JOYSTICK_H
#include "board.h"
#include "processor_hal.h"
#include "stm32f429xx.h"
#include "stm32f4xx_hal_gpio_ex.h"
#include "s4459843_reg_iss.h"

ADC_HandleTypeDef AdcHandle1;
ADC_ChannelConfTypeDef AdcChanConfig1;
ADC_HandleTypeDef AdcHandle2;
ADC_ChannelConfTypeDef AdcChanConfig2;

#define JOYSTICK_X_CHANNEL S4459843_REG_ISS_SOURCE_1
#define JOYSTICK_Y_CHANNEL S4459843_REG_ISS_SOURCE_2
#define JOYSTICK_Z_CHANNEL S4459843_REG_ISS_SOURCE_3
#define S4459843_REG_JOYSTICK_Z_READ() joystick_readZ();


extern void s4459843_reg_joystick_init();
void s4459843_reg_joystick_init1();
void s4459843_reg_joystick_init2();
void s4459843_reg_joystick_init3();
extern unsigned char joystick_readZ(void);
extern void s4459843_reg_joystick_iss_isr(int GPIO_P);
extern unsigned int Xvalue;
extern unsigned int Yvalue;
unsigned int Xvalue;
unsigned int Yvalue;
extern uint8_t Joystick_Drive;
uint8_t Joystick_Drive;

#define GPIO_JOYSTICKX 1
#define GPIO_JOYSTICKY 2
#define GPIO_JOYSTICKZ 3
#endif
