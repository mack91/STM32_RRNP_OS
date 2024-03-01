/* Define to prevent recursive inclusion -------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "OsMain.h"
#include "main.h"


void (*taskQueue[MAX_TASK_QUEUE])(void)= {0U};



void Os_Task1ms(void)
{
	HAL_GPIO_TogglePin(D2_1ms_GPIO_Port,D2_1ms_Pin);
}
void Os_Task5ms(void)
{
	HAL_GPIO_TogglePin(D3_5ms_GPIO_Port,D3_5ms_Pin);
}
void Os_Task10ms(void)
{
	HAL_GPIO_TogglePin(D4_10ms_GPIO_Port,D4_10ms_Pin);
}
/*
 * Brief  : Called periodically under timer interrupt.
 * 			Evaluates and pipelines the task
 */
void scheduler_run()
{
	static uint32_t taskQueueindex = 0U;
	static uint32_t schTimeKeeper = 0U;

	schTimeKeeper++;
	taskQueue[taskQueueindex] = &(Os_Task1ms);
	taskQueueindex++;
	if(MAX_TASK_QUEUE < taskQueueindex )
	{
		/*Drawback of this strategy : After 10 tasks the buffer roll overs, so if there is any task which is pending execution in buffer then it shall be lost*/
		taskQueueindex = 0U;	/*Circular buffer to keep queuing the task*/
	}

	if(0U == (schTimeKeeper % TASK_5MS))
	{
		taskQueue[taskQueueindex] = &(Os_Task5ms);
		taskQueueindex++;
	}
	if(MAX_TASK_QUEUE < taskQueueindex )
	{
		/*Drawback of this strategy : After 10 tasks the buffer roll overs, so if there is any task which is pending execution in buffer then it shall be lost*/
		taskQueueindex = 0U;	/*Circular buffer to keep queuing the task*/
	}

	if(0U == (schTimeKeeper % TASK_10MS))
	{
		taskQueue[taskQueueindex] = &(Os_Task10ms);
		taskQueueindex++;
		schTimeKeeper = 0U;
	}
	if(MAX_TASK_QUEUE < taskQueueindex )
	{
		/*Drawback of this strategy : After 10 tasks the buffer roll overs, so if there is any task which is pending execution in buffer then it shall be lost*/
		taskQueueindex = 0U;	/*Circular buffer to keep queuing the task*/
	}
}


void OsTaskRun(void)
{
	for(uint8_t taskindex=0;taskindex<MAX_TASK_QUEUE;taskindex++)
	{
		if(NULL == taskQueue[taskindex])
		{
			/* Do Nothing and move to next one */
		}
		else
		{
			(*taskQueue[taskindex])();
			taskQueue[taskindex] = 0U;	/*Clearing the index value after succesful execution*/
		}
	}
}
