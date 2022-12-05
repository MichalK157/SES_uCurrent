/*
 * data_structures.h
 *
 *  Created on: Sep 14, 2022
 *      Author: Mike
 */

#ifndef INC_DATA_STRUCTURES_H_
#define INC_DATA_STRUCTURES_H_

#include "stdio.h"
#include "stm32f4xx_hal.h"
#include "circular_buffer.h"

//can be tune letter
#define prescaler_uA 16 // 0,000066 * (1/4096) * 10^9
#define prescaler_mA 32 // 0,0132 * (1/4096) * 10^6

typedef struct{
	uint32_t value[8];
	uint8_t uinit[8];
	uint8_t active[8];
}Data_Q;

typedef struct{
	int32_t step;
	int32_t maxstep;
}TestTimer;

typedef struct{
	CircularBuffer buffer;
	int32_t startTime;
}Channel;

typedef struct{
	int32_t testtime;
	uint32_t threshold_uA;
	uint32_t threshold_mA;
	uint8_t activeChanelsCount[8];
}TestControler;

typedef struct{
	Channel channel[8];
	uint8_t active[8];
	uint8_t unit[8];
}ChannelsControler;

enum{
	uA,
	mA
};

enum{
	TestRunnig,
	TestEndDeviceIn,
	DeviceOut
};

enum{
	Channel1,
	Channel2,
	Channel3,
	Channel4,
	Channel5,
	Channel6,
	Channel7,
	Channel8,
};

enum{
	Active,
	Inactive
};

static const uint16_t InputPins[8] = {
		GPIO_PIN_4,
		GPIO_PIN_5,
		GPIO_PIN_6,
		GPIO_PIN_7,
		GPIO_PIN_12,
		GPIO_PIN_13,
		GPIO_PIN_14,
		GPIO_PIN_15
};
static const uint16_t OutputPins[8] = {
		GPIO_PIN_0,
		GPIO_PIN_1,
		GPIO_PIN_2,
		GPIO_PIN_3,
		GPIO_PIN_4,
		GPIO_PIN_5,
		GPIO_PIN_6,
		GPIO_PIN_7
};
#endif /* INC_DATA_STRUCTURES_H_ */
