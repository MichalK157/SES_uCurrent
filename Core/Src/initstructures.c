/*
 * initstructures.c
 *
 *  Created on: Sep 14, 2022
 *      Author: Mike
 */
#include "initstructures.h"
#include "stdio.h"
#include "string.h"

void initTimer(TestTimer *obj)
{
	obj->maxstep = 10000;
	obj->step = 0;
}

void resetTimer(TestTimer *obj)
{
	obj->step = 0;
}

void initTestControler(TestControler *obj)
{
	obj->activeChanelsCount = 8;
	obj->testtime = 20; // in [s]
	obj->threshold_mA = 100; //need to check and add const value to define
	obj->threshold_uA = 4050;
}

void setTestControler(TestControler *obj, int32_t time, uint32_t uA, uint32_t mA, uint8_t ch)
{
	obj->activeChanelsCount = ch;
	obj->testtime = time;
	obj->threshold_uA = uA;
	obj->threshold_mA = mA;
}

void resetTestControler(TestControler *obj)
{
	obj->testtime = 20;
}

void initChannelsControler(ChannelsControler *obj)
{
	memset(obj->active,DeviceOut,8);
	memset(obj->unit,uA,8);
	memset(obj->channel,0,8*sizeof(Channel));
}
