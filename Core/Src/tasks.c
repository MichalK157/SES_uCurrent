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

__IO uint32_t ADCValues[8];
uint8_t RX_USB_Buffor[64];
static ChannelsControler channels;
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim2;
extern TestTimer timer;
extern TestControler mainControlers;



void m_mainTask(void *argument)
{
	extern osMessageQueueId_t outputValuessHanlde;
	MX_USB_DEVICE_Init();
	Data_Q data;
	memset(&data, '\0',sizeof(Data_Q));
	while(1)
	{
		//CDC_Transmit_FS((uint8_t*)"TEST\n\r", 6);

		osStatus_t rv = osMessageQueueGet(outputValuessHanlde, &data, 0, 10);
		if(rv == osOK)
		{
			CDC_Transmit_FS((uint8_t*)data.data, strlen(data.data));
		}
		osDelay(50);
	}
}
void m_readValues(void *argument)
{
	extern osMessageQueueId_t outputValuessHanlde;
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)ADCValues, 8);
	HAL_TIM_Base_Start_IT(&htim2);
	Data_Q data;
	char str[100];
	char channel[15];
	memset(&data,'\0', sizeof(Data_Q));
	while(1)
	{

		//str = calloc(100, sizeof(char));
		memset((char*)&str,'\0',100*sizeof(char));
		//check active channels and test time duration.
		//setup for next steps

		for(int i = 0; i<8; i++)
			{
				if(HAL_GPIO_ReadPin(GPIOB, InputPins[i]) == GPIO_PIN_RESET)
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
							else
								continue;
						}
						else
							continue;

					}
					else if (channels.active[i] == DeviceOut)
					{
						channels.channel[i].startTime = timer.step;
						channels.active[i] = TestRunnig;
					}
					else
						continue;
				}
				else
				{
					if(channels.active[i] != DeviceOut)
						channels.active[i] = DeviceOut;

				}
			}


		for(int i = 0; i<8; i++){
			if(channels.active[i]==TestRunnig)
			{

				//channel = calloc(15,sizeof(char));
				memset((char*)&channel,'\0',15*sizeof(char));
				channels.channel[i].value = ADCValues[i];

				if(channels.unit[i] == uA)
				{
					sprintf(channel,"[%d]%ld{%s};",
							i+1,
							channels.channel[i].value*prescaler_uA,
							"uA");
					strcat(str,channel);
					if(channels.channel[i].value >= mainControlers.threshold_uA)
					{
						channels.unit[i] = mA;
						HAL_GPIO_WritePin(GPIOC, OutputPins[i], GPIO_PIN_SET);
					}

				}
				else
				{
					sprintf(channel,"[%d]%ld{%s};",
							i+1,channels.
							channel[i].value*prescaler_mA,
							"mA");
					strcat(str,channel);
					if(channels.channel[i].value <= mainControlers.threshold_mA)
						channels.unit[i] = uA;
					HAL_GPIO_WritePin(GPIOC, OutputPins[i], GPIO_PIN_RESET);
				}
			}
			else
				continue;

		}
		//
		if(strlen(str)>0)
		{
			memcpy(data.data, str,100);
			osMessageQueuePut(outputValuessHanlde, &data, 0,10);
			memset(&str,'\0',100);
		}
			osDelay(100);
	}
}
void m_readFromUSB(void *argument)
{
	extern osMessageQueueId_t outputValuessHanlde;
	Data_Q data;
	memset(&data,'\0',sizeof(data));
	char *t = "\n\rGet Data:\n\r";
	while(1)
	{

		if(strlen((char*)RX_USB_Buffor)>0)
		{
			// parse data to TestControler
			//CDC_Transmit_FS((uint8_t*)RX_USB_Buffor,strlen((char*)RX_USB_Buffor));

			memcpy(data.data, t, strlen(t));
			strcat(data.data,(char*)RX_USB_Buffor);
			osMessageQueuePut(outputValuessHanlde, &data, 0, 10);
			memset(RX_USB_Buffor,'\0',64);
			//vPortFree(str);
			//setTestControler(&mainControlers, time, uA, mA, ch)
			//vPortFree(input);
		}
		//CDC_Transmit_FS((uint8_t*)str,strlen(str));

		osDelay(500);
	}
}


