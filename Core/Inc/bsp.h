/**
 * @file    BSP.h
 * @author  Simone Ruffini [simone.ruffini@squadracorsepolito.com, simone.ruffini.work@gmail.com]
 * @date    Sat May 11 11:57:08 PM CEST 2024 (date of creation)
 * @updated Sat May 11 11:57:08 PM CEST 2024 (date of last update)
 * @prefix  varius depending on module
 *
 * @brief   Header files for board support package functions
 *
 * @license Licensed under "THE BEER-WARE LICENSE", Revision 69 
 *          see LICENSE file in the root directory of this software component
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _BSP_H_
#define _BSP_H_

/* ---------- Includes ------------------------------------------------------*/
#include "adc1283.h"
/* ---------- Exported types ------------------------------------------------*/

// -- NTC

/**
 * @brief NTC probes on ADC1283
 */
enum NTC_Probe { NTC_Probe1, NTC_Probe2, NTC_Probe3, NTC_Probe4, NTC_Probe5, NTC_Probe6, NTC_probesNum };

/**
 * @brief NTC probes mapping on ADC1283 channels
 * @NOTE  If the conversion order or the number of conversion (channels used) by
 *        the ADC changes then update this array too
 */
static enum ADC1283_Chnl NTC_adc1283_chnls_map[NTC_probesNum] = {[NTC_Probe1] = ADC1283_Chnl0,
                                                                 [NTC_Probe2] = ADC1283_Chnl1,
                                                                 [NTC_Probe3] = ADC1283_Chnl2,
                                                                 [NTC_Probe4] = ADC1283_Chnl3,
                                                                 [NTC_Probe5] = ADC1283_Chnl4,
                                                                 [NTC_Probe6] = ADC1283_Chnl5};

/* ---------- Exported constants --------------------------------------------*/

// Mappings to hardware peripherals and constants for physical values

// -- NTC
#define NTC_PULL_UP_RES_OHM (10000U)
#define NTC_PULL_UP_VDD_V   (3.3f)

#define ADC1283_SPI_Handle hspi2

/* ---------- Exported variables --------------------------------------------*/

// -- NTC

/* ---------- Exported macros -----------------------------------------------*/

// -- NTC
/**
 * @brief Get NTC resistance value from the voltage drop read on the ADC channel
 * @note  Check the schematic to understand how it is calculated
 * @param _NTC_VDROP_V_ voltage drop (float) on the NTC read by the ADC 
 * @param _PULL_UP_RES_OHM_ pull-up resistance in ohm (float) on the NTC 
 * @param _PULL_UP_VDD_V_ voltage reference on the pull-up resistor in volts (float)
 * @return NTC resistance in Ohm (float)
 */
#define NTC_RES_FROM_NTC_VDROP(_NTC_VDROP_V_, _PULL_UP_RES_OHM_, _PULL_UP_VDD_V_) \
    ((float)(_NTC_VDROP_V_ / (float)(_PULL_UP_VDD_V_ - _NTC_VDROP_V_) * _PULL_UP_RES_OHM_))

/* ---------- Exported functions --------------------------------------------*/

// -- NTC

/*
 * @brief Get NTC voltage drop on the voltage divider
 * @param ntc_probe NTC probe @ref NTC_Probe to get the value
 * @return Voltage drop on the voltage divider (float)
 */
float NTC_get_vdrop(enum NTC_Probe ntc_probe);

/*
 * @brief Get NTC voltage drop on the voltage divider
 * @param ntc_probe NTC probe @ref NTC_Probe to get the value
 * @return Voltage drop on the voltage divider (float)
 */
float NTC_get_res(enum NTC_Probe ntc_probe);

void NTC_sampling_routine();

/* ---------- Private types -------------------------------------------------*/

// -- NTC

/* ---------- Private variables ---------------------------------------------*/

// -- NTC

/* ---------- Private constants ---------------------------------------------*/

// -- NTC

// -- Discharge feedback

/* ---------- Private Macros ------------------------------------------------*/

// -- NTC

#endif
