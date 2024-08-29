/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    adc.h
  * @brief   This file contains all the function prototypes for
  *          the adc.c file
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
#ifndef __ADC_H__
#define __ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern ADC_HandleTypeDef hadc1;

extern ADC_HandleTypeDef hadc3;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_ADC1_Init(void);
void MX_ADC3_Init(void);

/* USER CODE BEGIN Prototypes */

#define ADC_ADC1_VREF_V (3.3f) /*!< ADC1 voltage reference in millivolt float*/
#define ADC_ADC1_IIR_ALPHA   (0.1f) /*!< ADC1 Infinite Impulse Response filter (1 order) alpha value (smooth factor)
                                         @NOTE if the sampling changes update this value */

/**
 * @brief Get the resolution of the ADC in bits given the ADC Handle pointer
 * @param HADC_INSTANCE_PTR ADC Handle pointer of type @ref ADC_HandleTypeDef*
 * @return Resolution in bits for the ADC used if it exists otherwise 0
 */
#define ADC_GET_RESOLUTION_BITS(HADC_INSTANCE_PTR)                         \
    (ADC_GET_RESOLUTION(HADC_INSTANCE_PTR) == ADC_RESOLUTION_12B   ? 12U   \
     : ADC_GET_RESOLUTION(HADC_INSTANCE_PTR) == ADC_RESOLUTION_10B ? (10U) \
     : ADC_GET_RESOLUTION(HADC_INSTANCE_PTR) == ADC_RESOLUTION_8B  ? (8U)  \
     : ADC_GET_RESOLUTION(HADC_INSTANCE_PTR) == ADC_RESOLUTION_6B  ? (6U)  \
                                                                   : (0U))
/**
 * @brief  Convert ADC raw value to volts given the adc voltage reference in
 *         volts and its resolution
 * @param  ADC_RAW_VALUE The sampled value from the ADC
 * @param  ADC_RESOLUTION_BITS The resolution of the adc in bits (e.g: 12U)
 * @param  ADC_VREF_mV The ADC reference voltage in millivolts
 * @return Analog rappresentation in volts (float) of ADC_RAW_VALUE
 */
#define ADC_CONV_RAW_TO_V(ADC_RAW_VALUE, ADC_RESOLUTION_BITS, ADC_VREF_V) \
    ((float)(ADC_VREF_V) / ((1U) << (ADC_RESOLUTION_BITS)) * ADC_RAW_VALUE)

/**
 * @brief ADC1 channels name and conversion order
 * @NOTE  If the conversion order or the number of conversion (channels used) by
 *        the ADC changes then update this enum too
 * @details This enum maps the adc channels to the adc input signals from the
 *          schematic and their ranks (conversion step/order)
 */
enum ADC_ADC1_Channel {
    //                        |Periph    | Rank# | Signal Name
    ADC_ADC1_POT2 = 0,     // |ADC1_IN0  | 1     | POT2_ADC_IN15
    ADC_ADC1_DSCHRG_FDBK,  // |ADC1_IN1  | 2     | DSCHRG_FDBK_AIN_ADC_IN
    ADC_ADC1_AIN2,         // |ADC1_IN5  | 3     | AIN2_ADC_IN5
    ADC_ADC1_AIN3,         // |ADC1_IN6  | 4     | AIN3_ADC_IN6
    ADC_ADC1_AIN4,         // |ADC1_IN7  | 5     | AIN4_ADC_IN7
    ADC_ADC1_AIN7,         // |ADC1_IN8  | 6     | AIN7_ADC_IN10
    ADC_ADC1_AIN5,         // |ADC1_IN9  | 7     | AIN5_ADC_IN8
    ADC_ADC1_POT1,         // |ADC1_IN10 | 8     | POT1_ADC_IN14
    ADC_ADC1_AIN1,         // |ADC1_IN14 | 9     | AIN1_ADC_IN4
    ADC_ADC1_AIN6,         // |ADC1_IN15 | 10    | AIN6_ADC_IN9
    ADC_ADC1_Channel_NUM
};

/**
 * @brief Get Volts converted by the ADC on the given channel (last conversion)
 * @param chnl The adc1 channel of type @ref enum ADC_ADC1_Channel
 * @return Last voltage conversion of the ADC channel `chnl` or (-1.0f) in case
 *         of invalid channel
 */
float ADC_ADC1_getChannel_V(enum ADC_ADC1_Channel chnl);

/**
 * @brief ADC callback when DMA finishes copying data
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */

