/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include <inttypes.h>
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
#define SHTDWN2_GPIO_IN_Pin GPIO_PIN_13
#define SHTDWN2_GPIO_IN_GPIO_Port GPIOC
#define SHTDWN1_GPIO_IN_Pin GPIO_PIN_14
#define SHTDWN1_GPIO_IN_GPIO_Port GPIOC
#define ADC1283IPT_nCS_GPIO_OUT_Pin GPIO_PIN_15
#define ADC1283IPT_nCS_GPIO_OUT_GPIO_Port GPIOC
#define POT1_ADC_IN14_Pin GPIO_PIN_0
#define POT1_ADC_IN14_GPIO_Port GPIOC
#define ADC1283IPT_DIN_SPI2_MOSI_Pin GPIO_PIN_1
#define ADC1283IPT_DIN_SPI2_MOSI_GPIO_Port GPIOC
#define REF_5V_ADC_IN12_Pin GPIO_PIN_2
#define REF_5V_ADC_IN12_GPIO_Port GPIOC
#define REF_24V_ADC_IN13_Pin GPIO_PIN_3
#define REF_24V_ADC_IN13_GPIO_Port GPIOC
#define POT2_ADC_IN15_Pin GPIO_PIN_0
#define POT2_ADC_IN15_GPIO_Port GPIOA
#define ANAL4_ADC_IN3_Pin GPIO_PIN_1
#define ANAL4_ADC_IN3_GPIO_Port GPIOA
#define ANAL1_ADC_IN0_Pin GPIO_PIN_2
#define ANAL1_ADC_IN0_GPIO_Port GPIOA
#define ANAL2_ADC_IN1_Pin GPIO_PIN_3
#define ANAL2_ADC_IN1_GPIO_Port GPIOA
#define ANAL3_ADC_IN2_Pin GPIO_PIN_4
#define ANAL3_ADC_IN2_GPIO_Port GPIOA
#define ANAL6_ADC_IN5_Pin GPIO_PIN_5
#define ANAL6_ADC_IN5_GPIO_Port GPIOA
#define ANAL7_ADC_IN6_Pin GPIO_PIN_6
#define ANAL7_ADC_IN6_GPIO_Port GPIOA
#define ANAL8_ADC_IN7_Pin GPIO_PIN_7
#define ANAL8_ADC_IN7_GPIO_Port GPIOA
#define ANAL5_ADC_IN4_Pin GPIO_PIN_4
#define ANAL5_ADC_IN4_GPIO_Port GPIOC
#define ANAL10_ADC_IN9_Pin GPIO_PIN_5
#define ANAL10_ADC_IN9_GPIO_Port GPIOC
#define ANAL11_ADC_IN10_Pin GPIO_PIN_0
#define ANAL11_ADC_IN10_GPIO_Port GPIOB
#define ANAL9_ADC_IN8_Pin GPIO_PIN_1
#define ANAL9_ADC_IN8_GPIO_Port GPIOB
#define M95256_D_SPI3_MOSI_Pin GPIO_PIN_2
#define M95256_D_SPI3_MOSI_GPIO_Port GPIOB
#define ADC1283IPT_SCLK_SPI2_SCK_Pin GPIO_PIN_10
#define ADC1283IPT_SCLK_SPI2_SCK_GPIO_Port GPIOB
#define M95256_nW_GPIO_OUT_Pin GPIO_PIN_12
#define M95256_nW_GPIO_OUT_GPIO_Port GPIOB
#define M95256_nS_GPIO_OUT_Pin GPIO_PIN_13
#define M95256_nS_GPIO_OUT_GPIO_Port GPIOB
#define ADC1283IPT_DOUT_SPI2_MISO_Pin GPIO_PIN_14
#define ADC1283IPT_DOUT_SPI2_MISO_GPIO_Port GPIOB
#define LED_ERR_GPIO_OUT_Pin GPIO_PIN_15
#define LED_ERR_GPIO_OUT_GPIO_Port GPIOB
#define LED_STAT3_GPIO_OUT_Pin GPIO_PIN_6
#define LED_STAT3_GPIO_OUT_GPIO_Port GPIOC
#define LED_WARN_GPIO_OUT_Pin GPIO_PIN_7
#define LED_WARN_GPIO_OUT_GPIO_Port GPIOC
#define LED_STAT3_GPIO_OUTC8_Pin GPIO_PIN_8
#define LED_STAT3_GPIO_OUTC8_GPIO_Port GPIOC
#define LED_STAT2_GPIO_OUT_Pin GPIO_PIN_9
#define LED_STAT2_GPIO_OUT_GPIO_Port GPIOC
#define LED_STAT1_GPIO_OUT_Pin GPIO_PIN_8
#define LED_STAT1_GPIO_OUT_GPIO_Port GPIOA
#define T_VCP_TX_USART1_TX_Pin GPIO_PIN_9
#define T_VCP_TX_USART1_TX_GPIO_Port GPIOA
#define T_VCP_RX_USART1_RX_Pin GPIO_PIN_10
#define T_VCP_RX_USART1_RX_GPIO_Port GPIOA
#define SN65HVD23x_R_CAN1_RX_Pin GPIO_PIN_11
#define SN65HVD23x_R_CAN1_RX_GPIO_Port GPIOA
#define SN65HVD23x_D_CAN1_TX_Pin GPIO_PIN_12
#define SN65HVD23x_D_CAN1_TX_GPIO_Port GPIOA
#define SENSE_TYPE_Pin GPIO_PIN_15
#define SENSE_TYPE_GPIO_Port GPIOA
#define M95256_C_SPI3_SCK_Pin GPIO_PIN_10
#define M95256_C_SPI3_SCK_GPIO_Port GPIOC
#define M95256_Q_SPI3_MISO_Pin GPIO_PIN_11
#define M95256_Q_SPI3_MISO_GPIO_Port GPIOC
#define ADS112U04_RX_UART5_TX_Pin GPIO_PIN_12
#define ADS112U04_RX_UART5_TX_GPIO_Port GPIOC
#define ADS112U04_TX_UART5_RX_Pin GPIO_PIN_2
#define ADS112U04_TX_UART5_RX_GPIO_Port GPIOD
#define EMPTY_Pin GPIO_PIN_4
#define EMPTY_GPIO_Port GPIOB
#define ADS112U04_nDRDY_GPIO_IN_Pin GPIO_PIN_5
#define ADS112U04_nDRDY_GPIO_IN_GPIO_Port GPIOB
#define BSPD_ERR_GPIO_IN_Pin GPIO_PIN_6
#define BSPD_ERR_GPIO_IN_GPIO_Port GPIOB
#define BRK_LGHT_GPIO_OUT_Pin GPIO_PIN_7
#define BRK_LGHT_GPIO_OUT_GPIO_Port GPIOB
#define SHTDWN4_GPIO_IN_Pin GPIO_PIN_8
#define SHTDWN4_GPIO_IN_GPIO_Port GPIOB
#define SHTDWN3_GPIO_IN_Pin GPIO_PIN_9
#define SHTDWN3_GPIO_IN_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

// UART
#define VCP_UART_Handle huart1 /*!< Virtual COMM Port UART handle */
#define VCP_TX_LOG_BUF_MAX_TIMEOUT_MS (30U)  //~27ms are necessary to send 400 chars via UART@115kbit/s

// SPI
#define ADC1283_SPI_Handle hspi2
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
