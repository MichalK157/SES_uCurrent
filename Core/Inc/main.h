/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BSS_G1_Pin GPIO_PIN_0
#define BSS_G1_GPIO_Port GPIOC
#define BSS_G2_Pin GPIO_PIN_1
#define BSS_G2_GPIO_Port GPIOC
#define BSS_G3_Pin GPIO_PIN_2
#define BSS_G3_GPIO_Port GPIOC
#define BSS_G4_Pin GPIO_PIN_3
#define BSS_G4_GPIO_Port GPIOC
#define BSS_G5_Pin GPIO_PIN_4
#define BSS_G5_GPIO_Port GPIOC
#define BSS_G6_Pin GPIO_PIN_5
#define BSS_G6_GPIO_Port GPIOC
#define NC5_Pin GPIO_PIN_12
#define NC5_GPIO_Port GPIOB
#define NC6_Pin GPIO_PIN_13
#define NC6_GPIO_Port GPIOB
#define NC7_Pin GPIO_PIN_14
#define NC7_GPIO_Port GPIOB
#define NC8_Pin GPIO_PIN_15
#define NC8_GPIO_Port GPIOB
#define BSS_G7_Pin GPIO_PIN_6
#define BSS_G7_GPIO_Port GPIOC
#define BSS_G8_Pin GPIO_PIN_7
#define BSS_G8_GPIO_Port GPIOC
#define NC1_Pin GPIO_PIN_4
#define NC1_GPIO_Port GPIOB
#define NC2_Pin GPIO_PIN_5
#define NC2_GPIO_Port GPIOB
#define NC3_Pin GPIO_PIN_6
#define NC3_GPIO_Port GPIOB
#define NC4_Pin GPIO_PIN_7
#define NC4_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
