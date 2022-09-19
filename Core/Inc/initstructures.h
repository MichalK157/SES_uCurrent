/*
 * initstructures.h
 *
 *  Created on: Sep 14, 2022
 *      Author: Mike
 */

#ifndef INC_INITSTRUCTURES_H_
#define INC_INITSTRUCTURES_H_

#include "data_structures.h"

void initTimer(TestTimer *obj);
void resetTimer(TestTimer *obj);
void initTestControler(TestControler *obj);
void setTestControler(TestControler *obj, int32_t time, uint32_t uA, uint32_t mA, uint8_t ch);
void resetTestControler(TestControler *obj);
void initChannelsControler(ChannelsControler *obj);

#endif /* INC_INITSTRUCTURES_H_ */
