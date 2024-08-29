/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "can.h"
#include "dma.h"
#include "iwdg.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
// clang-format off
#include "conf.h"
// clang-format on
#include "bsp.h"
#include "can_send_timebase.h"
#include "can_utils.h"
#include "logger_wrapper.h"
#include "stdio.h"
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
char buf[100] = {};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM2_Init();
  MX_ADC1_Init();
  MX_CAN1_Init();
  MX_SPI2_Init();
  MX_SPI3_Init();
  MX_UART5_Init();
  MX_USART1_UART_Init();
  MX_ADC3_Init();
  MX_TIM12_Init();
  MX_TIM6_Init();
  MX_TIM7_Init();
  MX_IWDG_Init();
  /* USER CODE BEGIN 2 */
    logger_init();
    can_init();
    can_send_timebase_init();

    // Show at the start the type of sensorboard in function
    if (SENS_GET_TYPE() == SENS_TYPE_FRONT) {
        HAL_GPIO_WritePin(SENS_FRONT_LED_GPIO_PORT, SENS_FRONT_LED_GPIO_PIN, GPIO_PIN_SET);
        can_send_msg(MCB_SB_FRONT_HELLO_FRAME_ID);
    } else {
        HAL_GPIO_WritePin(SENS_REAR_LED_GPIO_PORT, SENS_REAR_LED_GPIO_PIN, GPIO_PIN_SET);
        can_send_msg(MCB_SB_REAR_HELLO_FRAME_ID);
    }
    uint32_t cnt1ms    = HAL_GetTick() + 1U;
    uint32_t cnt10ms   = HAL_GetTick() + 10U;
    uint32_t cnt100ms  = HAL_GetTick() + 100U;
    uint32_t cnt1000ms = HAL_GetTick() + 1000U;

    uint32_t ntc_sampling_cnt = HAL_GetTick();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1) {
        //DRTB_routine();
        if (HAL_GetTick() >= cnt1ms) {
            cnt1ms += 1U;
        }
        if (HAL_GetTick() >= cnt10ms) {
            cnt10ms += 10U;

#ifdef DEBUG_SERIAL
            char *target = buf;
#ifdef DEBUG_AIN
            for (int i = 0; i < ADC_ADC1_Channel_NUM; i++) {
                float val = ADC_ADC1_getChannel_V((enum ADC_ADC1_Channel)i);
                target += sprintf(target, "%.3f,", val);
            }
#endif  // DEBUG_AIN
#ifdef DEBUG_NTC
            for (int i = 0; i < NTC_Probe_NUM; i++) {
                float val = NTC_Probe_get_resistance((enum NTC_Probe)i);
                target += sprintf(target, "%.3f,", val);
            }
#endif  // DEBUG_NTC
#ifdef DEBUG_SDC
            for (int i = 0; i < SDC_Probe_NUM; i++) {
                uint8_t val = SDC_Probe_get_status((enum SDC_Probe)i);
                target += sprintf(target, "%u,", val);
            }
#endif  // DEBUG_SDC
#ifdef DEBUG_BSPD
            target += sprintf(target, "%u,", BSPD_DEV_IS_IN_ERR());
#endif  // DEBUG_BSPD
#ifdef DEBUG_BRAKE_LIGHT
            target += sprintf(target, "%u,", BRAKE_LIGHT_IS_ON());
#endif  // DEBUG_BRAKE_LIGHT

            // remove last ","
            if (target > buf) {
                target--;
            }
            // add newline at the end
            target += sprintf(target, "\r\n");
            HAL_UART_Transmit(&VCP_UART_Handle, (uint8_t *)buf, strlen(buf), VCP_TX_LOG_BUF_MAX_TIMEOUT_ms);
#endif  // DEBUG_SERIAL
        }
        if (HAL_GetTick() >= cnt100ms) {
            cnt100ms += 100U;
        }
        if (HAL_GetTick() >= cnt1000ms) {
            cnt1000ms += 1000U;
            // Show I'm Alive by blinking sens type led
            if (SENS_GET_TYPE() == SENS_TYPE_FRONT) {
                HAL_GPIO_TogglePin(SENS_FRONT_LED_GPIO_PORT, SENS_FRONT_LED_GPIO_PIN);
            } else {
                HAL_GPIO_TogglePin(SENS_REAR_LED_GPIO_PORT, SENS_REAR_LED_GPIO_PIN);
            }
        }
        // Run NTC Probes sampling
        if (HAL_GetTick() >= ntc_sampling_cnt + NTC_SAMP_PERIOD_ms) {
            ntc_sampling_cnt += NTC_SAMP_PERIOD_ms;
            NTC_Probes_sampling_routine();
        }

        can_send_timebase_routine();
        logger_routine();

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
        HAL_IWDG_Refresh(&hiwdg);  // refresh watchdog ~10ms timeout
    }                              // end while(1)
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
    }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
     eg: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    logger_log(LOGGER_ERROR, "Error in file: %s on line %d", file, line);
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
