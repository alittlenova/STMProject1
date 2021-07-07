/** 
 **************************************************************
 * @file mylib/s4459843_CAG_keypad_mnemonic.h
 * @author Yang Zheng - 44598435
 * @date 10052021
 * @brief keypad
 * REFERENCE: None
 ***************************************************************
 * EXTERNAL FUNCTIONS tsk_CAG_Mnemonic_Mode_ctrl(void);
 ***************************************************************
 * 
 *************************************************************** 
 */
#ifndef S4459843_CAG_KEYPAD_MNEMONIC_H
#define S4459843_CAG_KEYPAD_MNEMONIC_H
#include "s4459843_reg_keypad.h"
#include "s4459843_CAG_keypad.h"
#include "s4459843_CAG_keypad_grid.h"

// Task Priorities (Idle Priority is the lowest priority)
#define MNEMONICTASK_PRIORITY					( tskIDLE_PRIORITY + 2 )

// Task Stack Allocations (must be a multiple of the minimal stack size)
#define MNEMONICTASK_STACK_SIZE		( configMINIMAL_STACK_SIZE * 2 )
xTaskHandle MnemonicTaskHandle;

// Task Priorities (Idle Priority is the lowest priority)
#define MNEMONICSAMPGIVETASK_PRIORITY					( tskIDLE_PRIORITY + 2 )

// Task Stack Allocations (must be a multiple of the minimal stack size)
#define MNEMONICSAMPGIVETASK_STACK_SIZE		( configMINIMAL_STACK_SIZE * 2 )
xTaskHandle mnemonicsampgiveTaskHandle;
SemaphoreHandle_t mnemonicSemaphore;	// Semaphore for simulation

extern char command_bar[6];
char command_bar[6];
extern char command_len;
char command_len;

int varing_time;
int cursor_flashing_time;
int error_time;

extern uint8_t varing_state;
extern uint8_t cursor_flashing_state;
extern uint8_t error_show;
uint8_t varing_state;
uint8_t cursor_flashing_state;
uint8_t error_show;

int selecting_time;
uint8_t selectingOn;
char selecting_letter;
uint8_t lastpressed;
extern void s4459843_tsk_CAG_keypadGrid_init(void);
void CAG_keypadMnemonic_init(void);
void tsk_CAG_Mnemonic_Mode_processing(void);
extern void tsk_CAG_Mnemonic_Mode_ctrl(void);
void tsk_CAG_Mnemonic_Mode_sampgive(void);
void backspace(void);
void activate_button(uint8_t pressed);
void activate_letter_button(uint8_t pressed);
void pushing_selecting(void);
void command_add_letter(char let);
void command_clear(void);
void error_raise(void);
void processing_command(void);
void CAG_Simulator_Drive_Delete(void);
void CAG_Joystick_Drive_Delete(void);
void CAG_Simulator_Drive_Create(void);
void CAG_Joystick_Drive_Create(void);
#endif
