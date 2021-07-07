/** 
 **************************************************************
 * @file mylib/s4459843_CAG_keypad_grid.h
 * @author Yang Zheng - 44598435
 * @date 10052021
 * @brief keypad
 * REFERENCE: None
 ***************************************************************
 * EXTERNAL FUNCTIONS
 ***************************************************************
 * 
 *************************************************************** 
 */
#ifndef S4459843_CAG_KEYPAD_GRID_H
#define S4459843_CAG_KEYPAD_GRID_H
#include "s4459843_reg_keypad.h"
#include "s4459843_CAG_keypad.h"

// Task Priorities (Idle Priority is the lowest priority)
#define GRIDTASK_PRIORITY					( tskIDLE_PRIORITY + 2 )

// Task Stack Allocations (must be a multiple of the minimal stack size)
#define GRIDTASK_STACK_SIZE		( configMINIMAL_STACK_SIZE * 2 )
xTaskHandle gridTaskHandle;

// Task Priorities (Idle Priority is the lowest priority)
#define GRIDSAMPGIVETASK_PRIORITY					( tskIDLE_PRIORITY + 2 )

// Task Stack Allocations (must be a multiple of the minimal stack size)
#define GRIDSAMPGIVETASK_STACK_SIZE		( configMINIMAL_STACK_SIZE * 2 )
xTaskHandle gridsampgiveTaskHandle;
SemaphoreHandle_t gridSemaphore;	// Semaphore for simulation

void s4459843_tsk_CAG_keypadGrid_init(void);
void CAG_keypadGrid_init(void);
void tsk_CAG_Grid_Mode_processing(void);
void tsk_CAG_Grid_Mode_ctrl(void);
void tsk_CAG_Grid_Mode_sampgive(void);
void tsk_CAG_fsm_ctrl(void);
void subgridXMove(void);
void subgridYMove(void);
void Clear_Simulation(void);
void cell_toggle(uint8_t grid);
void simulation_start(void);
void simulation_stop(void);
extern void simulation_start(void);
extern void simulation_stop(void);
extern uint8_t SubgridXreturn(void);
extern uint8_t SubgridYreturn(void);
extern uint8_t subgrid_X,subgrid_Y;
uint8_t subgrid_X,subgrid_Y;
#endif
