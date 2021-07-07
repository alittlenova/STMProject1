/** 
 **************************************************************
 * @file mylib/s4459843_CAG_Simulator.h
 * @author Yang Zheng - 44598435
 * @date 10052021
 * @brief simulator
 * REFERENCE: None
 ***************************************************************
 * EXTERNAL FUNCTIONS tsk_simulation_ctrl(void);
 ***************************************************************
 * 
 *************************************************************** 
 */
#ifndef S4459843_CAG_SIMULATOR_H
#define S4459843_CAG_SIMULATOR_H
#include "main.h"
// Task Priorities (Idle Priority is the lowest priority)
#define SIMULATIONTASK_PRIORITY					( tskIDLE_PRIORITY + 2 )

// Task Stack Allocations (must be a multiple of the minimal stack size)
#define SIMULATIONTASK_STACK_SIZE		( configMINIMAL_STACK_SIZE * 2 )

// Task Priorities (Idle Priority is the lowest priority)
#define SAMPGIVETASK_PRIORITY					( tskIDLE_PRIORITY + 2 )

// Task Stack Allocations (must be a multiple of the minimal stack size)
#define SAMPGIVETASK_STACK_SIZE		( configMINIMAL_STACK_SIZE * 2 )

extern uint8_t cell_live[30][15];
uint8_t cell_livelast[30][15];
extern TickType_t simulation_update_time;
TickType_t simulation_update_time;

extern void s4459843_tsk_simulation_init(void);
void simulation_init(void);
void simulation_march(void);
void tsk_simulation_ctrl(void);
void tsk_simulation_sampgive(void);
extern void Draw_shape(caMessage_t);
xTaskHandle simulationTaskHandle;
xTaskHandle sampgiveTaskHandle;
uint8_t cell_live[30][15];
uint8_t simulation_count[30][15];
extern uint8_t simulationOn;
uint8_t simulationOn;
SemaphoreHandle_t simulationSemaphore;	// Semaphore for simulation

extern uint8_t Simulation_Drive;
uint8_t Simulation_Drive;

typedef struct caMessage 
{ 
	int type ; // Type - Cell , or Lifeform
	int cell_x ; // Cell x position or Lifeform x position
	int cell_y ; // Cell y position or Lifeform y position
} caMessage_t ;
#endif
