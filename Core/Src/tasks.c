/*
 * tasks.c
 *
 *  Created on: Sep 14, 2022
 *      Author: Mike
 */

#include "cmsis_os.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "stdio.h"
#include "string.h"
#include "tasks.h"
#include "errno.h"
#include "initstructures.h"

__IO uint32_t ADCValues[8];
uint8_t RX_USB_Buffor[255];
static ChannelsControler channels;
extern osThreadId_t mainTaskHandle;

void m_mainTask(void *argument)
{
	MX_USB_DEVICE_Init();
	Data_Q data;
	memset(&data, 0,sizeof(Data_Q));
	//osThreadSuspend(mainTaskHandle);
	uint32_t channel_value = 0;
	while(1)
	{
		for(uint8_t i=0; i<8; i++)
		{
			data.active[i] = channels.active[i];
			if(channels.active[i] == TestRunnig)
			{
				channel_value = circular_buffer_calculate_mean(&channels.channel[i].buffer);
				if(channel_value > 0x1000)
				{
					data.value[i] = channel_value & 0x0fff;
					data.uinit[i] = mA;
				}
				else
				{
					data.value[i] = channel_value;
					data.uinit[i] = uA;
				}
			}
		}
		CDC_Transmit_FS((uint8_t*)&data, sizeof(Data_Q));
		osDelay(50);
	}
}
void m_readValues(void *argument)
{
	extern ADC_HandleTypeDef hadc1;
	extern TIM_HandleTypeDef htim2;
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)ADCValues, 8);
	HAL_TIM_Base_Start_IT(&htim2);
	initChannelsControler(&channels);
	//osThreadResume(mainTaskHandle);
	uint32_t value_read = 0;
	while(1)
	{
		//check active channels and test time duration.
		//setup for next steps
		for(int i = 0; i<8; i++)
		{
			if(mainControlers.activeChanelsCount[i] == Active && HAL_GPIO_ReadPin(GPIOB, InputPins[i]) == GPIO_PIN_RESET)
			{
				if(channels.active[i] == TestRunnig)
				{
					if(timer.step-channels.channel[i].startTime >= mainControlers.testtime)
					{
						channels.active[i] = TestEndDeviceIn;
					}
					else if(timer.step-channels.channel[i].startTime<0)
					{
						if(timer.step-channels.channel[i].startTime + timer.maxstep >= mainControlers.testtime)
							channels.active[i] = TestEndDeviceIn;
					}
				}
				else if (channels.active[i] == DeviceOut)
				{
					channels.channel[i].startTime = timer.step;
					channels.active[i] = TestRunnig;
				}
			}
			else
			{
				if(channels.active[i] != DeviceOut)
				{
					channels.active[i] = DeviceOut;
				}
			}
		}

		for(int i = 0; i<8; i++)
		{
			if(mainControlers.activeChanelsCount[i] == Active && channels.active[i] == TestRunnig)
			{
				value_read = ADCValues[i];

				if(channels.unit[i] == uA)
				{
					circular_buffer_write(&channels.channel[i].buffer, value_read);
					if(value_read >= mainControlers.threshold_uA)
					{
						channels.unit[i] = mA;
						HAL_GPIO_WritePin(GPIOC, OutputPins[i], GPIO_PIN_SET);
					}
				}
				else
				{
					circular_buffer_write(&channels.channel[i].buffer, value_read | 0x1000);
					if(value_read <= mainControlers.threshold_mA)
					{
						channels.unit[i] = uA;
						HAL_GPIO_WritePin(GPIOC, OutputPins[i], GPIO_PIN_RESET);
					}
				}
			}
		}
		osDelay(5);
	}
}
void m_readFromUSB(void *argument)
{
	char tempCoonstance[64];
	char tempValues[64];
	while(1)
	{
		if(strlen((char*)RX_USB_Buffor)>0)
		{

			size_t l_iter = 0;
			for(char *ptr = strchr((char*)RX_USB_Buffor,';'); ptr != NULL; ptr=strchr(ptr+1,';'))
				{
					size_t iter = ptr-(char*)RX_USB_Buffor;
					char* iter_l = strchr((char*)RX_USB_Buffor+l_iter,'<');
					char* iter_p = strchr((char*)RX_USB_Buffor+l_iter,'>');
					strncpy(tempValues,iter_l +1,(uint8_t)(iter_p-iter_l -1));
					strncpy(tempCoonstance,
							(char*)RX_USB_Buffor+l_iter,
							(size_t)(iter_l - (char*)RX_USB_Buffor+l_iter));

					if(strncmp((char*)"Testtime",tempCoonstance,8)==0)
						mainControlers.testtime = atoi(tempValues);

					else if (strncmp((char*)"Treshold_uA",tempCoonstance,11)==0)
						mainControlers.threshold_uA = atoi(tempValues);

					else if (strncmp((char*)"Treshold_mA",tempCoonstance,11)==0)
						mainControlers.threshold_mA = atoi(tempValues);

					else if (strncmp((char*)"Activechannels",tempCoonstance,14)==0)
					{
						uint8_t ch = 1;
						mainControlers.activeChanelsCount[0] = atoi(tempValues);
						for(char *i = strchr(tempValues,','); i!=NULL; i=strchr(i+1,','))
							{
								mainControlers.activeChanelsCount[ch] = atoi(i+1);
								ch++;
							}
					}
					memset(tempCoonstance,'\0',64);
					memset(tempValues,'\0',64);
					l_iter = iter+1;
				}

			memset(RX_USB_Buffor,'\0',256);
		}

		osDelay(500);
	}
}
