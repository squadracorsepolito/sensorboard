
/**
 * @file      ntc.h
 * @prefix    NTC
 * @author    Simone Ruffini [simone.ruffini@squadracose.com
 *                            simone.ruffini.work@gmail.com]
 * @date      Fri Jul  7 11:34:03 AM CEST 2023
 * 
 * @brief     Ntc peripherals handler
 * 
 * @license Licensed under "THE BEER-WARE LICENSE", Revision 69 (see LICENSE)
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Exported types ------------------------------------------------------------*/
enum NTC_enum { NTC1, NTC2, NTC3, NTC4, NTC5, NTC6, NTC_enum_number };

/* Exported constants --------------------------------------------------------*/
#define NTC_PULL_UP_RES_OHM (10000U)
#define NTC_VDIV_VDD_V      (3.3f)

/* Exported variables --------------------------------------------------------*/
extern uint16_t NTC_adc_raw [NTC_enum_number];

/* Exported macros -----------------------------------------------------------*/
#define NTC_RES_FROM_NTC_VDROP(_NTC_VDROP_V_, _PULL_UP_RES_OHM_, _VDIV_V_) \
    ((float)(_NTC_VDROP_V_ / (float)(_VDIV_V_ - _NTC_VDROP_V_) * _PULL_UP_RES_OHM_))

/* Exported functions --------------------------------------------------------*/
float NTC_get_vdrop(enum NTC_enum ntc);

float NTC_get_res(enum NTC_enum ntc);

void NTC_sampling_callback();

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private Macros -----------------------------------------------------------*/
#endif
