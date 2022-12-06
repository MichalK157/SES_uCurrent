/*
 * tasks.h
 *
 *  Created on: Sep 14, 2022
 *      Author: Mike
 */

#ifndef INC_TASKS_H_
#define INC_TASKS_H_

#include "data_structures.h"

__IO TestTimer timer;
TestControler mainControlers;
//Methods


//Tasks
void m_mainTask(void *argument);
void m_readValues(void *argument);
void m_readFromUSB(void *argument);

#endif /* INC_TASKS_H_ */
