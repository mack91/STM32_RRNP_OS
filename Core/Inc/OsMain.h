/*
 * OsMain.h
 *
 *  Created on: Feb 25, 2024
 *      Author: mayan
 */

#ifndef INC_OSMAIN_H_
#define INC_OSMAIN_H_


#define MAX_TASK_QUEUE	10U

#define TASK_1MS	1U
#define TASK_5MS	5U
#define TASK_10MS	10U

extern void (*taskQueue[MAX_TASK_QUEUE])(void);

/*Function Prototype declaration*/
void scheduler_run();
void OsTaskRun(void);
void Os_Task1ms(void);
void Os_Task5ms(void);
void Os_Task10ms(void);

#endif /* INC_OSMAIN_H_ */


