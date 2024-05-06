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
#include "anal.h"
#include "can_send_timebase.h"
#include "can_utils.h"
#include "data_reading_timebase.h"
#include "logger_wrapper.h"
#include "ntc.h"
#include "utils.h"
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
  MX_ADC1_Init();
  MX_CAN1_Init();
  MX_SPI2_Init();
  MX_SPI3_Init();
  MX_UART5_Init();
  MX_USART1_UART_Init();
  MX_ADC3_Init();
  MX_TIM12_Init();
  MX_TIM2_Init();
  MX_TIM6_Init();
  MX_TIM7_Init();
  MX_IWDG_Init();
  /* USER CODE BEGIN 2 */
    HAL_TIM_Base_Start(&htim2);
    anal_init();
    logger_init();
    can_init();
    can_send_timebase_init();
    //DRTB_init();

    if (UTILS_GET_SENS_TYPE() == SENSE_TYPE_FRONT) {
        HAL_GPIO_WritePin(LED_STAT1_GPIO_OUT_GPIO_Port, LED_STAT1_GPIO_OUT_Pin, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(LED_ERR_GPIO_OUT_GPIO_Port, LED_ERR_GPIO_OUT_Pin, GPIO_PIN_SET);
    }
    uint32_t cnt500ms = HAL_GetTick() + 500U;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1) {
        //DRTB_routine();

        if (HAL_GetTick() >= cnt500ms ) {
            cnt500ms = HAL_GetTick() + 500U;
            NTC_sampling_callback();

            // toggle status led
            HAL_GPIO_TogglePin(LED_STAT2_GPIO_OUT_GPIO_Port,LED_STAT2_GPIO_OUT_Pin);
            
            logger_log(LOGGER_INFO, "%u %u %u %u %u %u", NTC_adc_raw[0],NTC_adc_raw[1],NTC_adc_raw[2],NTC_adc_raw[3],NTC_adc_raw[4],NTC_adc_raw[5]);
            logger_log(LOGGER_INFO, "anal8 %f",anal_get_pin_mv(ANAL8));
            logger_log(LOGGER_INFO, "[%fV  %fOhm] [%fV  %fOhm] [%fV  %fOhm] [%fV  %fOhm] [%fV  %fOhm] [%fV  %fOhm]", 
                       NTC_get_vdrop(0), NTC_get_res(0),
                       NTC_get_vdrop(1), NTC_get_res(1),
                       NTC_get_vdrop(2), NTC_get_res(2),
                       NTC_get_vdrop(3), NTC_get_res(3),
                       NTC_get_vdrop(4), NTC_get_res(4),
                       NTC_get_vdrop(5), NTC_get_res(5));
        }

        can_send_timebase_routine();
        //for(int i=0; i<11; ++i) {
        //  logger_log(LOGGER_INFO, "anal %d: %fv", i, anal_get_pin_mv(i));
        //}
        logger_routine();

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
        HAL_IWDG_Refresh(&hiwdg); // refresh watchdog ~500ms timeout
    }// end while(1)
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
     es: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    logger_log(LOGGER_ERROR,"Error in file: %s on line %d",file,line);
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
