/**
 * @file    bsp.c
 * @author  Simone Ruffini [simone.ruffini@squadracorsepolito.com, simone.ruffini.work@gmail.com]
 * @date    Sat May 11 11:57:08 PM CEST 2024 (date of creation)
 * @updated Sat May 11 11:57:08 PM CEST 2024 (date of last update)
 * @prefix  varius depending on module
 *
 * @brief   Implementation of the board support package functions
 * @details This code contains the implementation of functions acting on the 
 *          specific peripherals of this board
 *
 * @license Licensed under "THE BEER-WARE LICENSE", Revision 69 
 *          see LICENSE file in the root directory of this software component
 */

/*---------- Includes -------------------------------------------------------*/

#include "bsp.h"

// NTC stuff
#include "adc1283.h"
#include "spi.h"

/*---------- Private define -------------------------------------------------*/

// -- Virtual Communication Port

// -- NTC

// -- NTC -- ADC1283

// -- Potentiometers

// -- Discharge feedback

/*---------- Private macro --------------------------------------------------*/

// -- Virtual Communication Port

// -- NTC

// -- NTC -- ADC1283

// -- Potentiometers

// -- Discharge feedback

/*---------- Private variables ----------------------------------------------*/

// -- Virtual Communication Port

// -- ADC1283
struct ADC1283_Handle hadc1283 = {.hspi         = &ADC1283_SPI_Handle,
                                  .cs_gpio_port = ADC1283IPT_nCS_GPIO_OUT_GPIO_Port,
                                  .cs_gpio_pin  = ADC1283IPT_nCS_GPIO_OUT_Pin};

// -- NTC (Negative Temperature Coefficient) Thermistor

#ifdef NTC_DEBUG
uint16_t NTC_Probe_adc_raw[NTC_Probe_NUM];
#endif
float NTC_Probe_adc_V[NTC_Probe_NUM];
float NTC_Probe_res_Ohm[NTC_Probe_NUM];

// -- LPPS (Linear Potentiometer Position Sensor)

// -- DSCRHG (Discharge) Status Feedback

/*---------- Private function prototypes ------------------------------------*/

// -- Virtual Communication Port

// -- NTC

// -- Potentiometers

// -- Discharge feedback

/*---------- Exported Variables ---------------------------------------------*/

// -- Virtual Communication Port

// -- NTC

// -- NTC -- ADC1283

// -- Potentiometers

// -- Discharge feedback

/*---------- Exported Functions ---------------------------------------------*/

// -- Virtual Communication Port

// -- NTC

float NTC_Probe_get_vdrop(enum NTC_Probe ntc_probe) {
    if (ntc_probe == NTC_Probe_NUM)
        return (-1.0f);
    return NTC_Probe_adc_V[ntc_probe];
}
float NTC_Probe_get_resistance(enum NTC_Probe ntc_probe) {
    if (ntc_probe == NTC_Probe_NUM)
        return (-1.0f);
    return NTC_Probe_res_Ohm[ntc_probe];
}

void NTC_Probes_sampling_routine() {
#ifdef NTC_DEBUG
    ADC1283_conv_channels_raw(&hadc1283, NTC_Probe_NUM, NTC_probe_to_adc1283_chnl_map, NTC_Probe_adc_raw);
#endif
    ADC1283_conv_channels(&hadc1283, NTC_Probe_NUM, NTC_probe_to_adc1283_chnl_map, NTC_Probe_adc_V);
    for (int i = 0; i < NTC_Probe_NUM; i++) {
#ifdef NTC_DEBUG
        NTC_Probe_adc_V[i] = ADC1283_ADC_RAW_TO_PHYS(NTC_Probe_adc_raw[i]);
#endif
        NTC_Probe_res_Ohm[i] = (0.02f) *
                                   NTC_RES_FROM_NTC_VDROP(NTC_Probe_adc_V[i], NTC_PULL_UP_RES_Ohm, NTC_PULL_UP_VDD_V) +
                               (1.0f - 0.02f) * NTC_Probe_res_Ohm[i];
    }
}

float NTC_Device_get_vdrop(enum NTC_Device ntc_device) {
    // Chck for plausibility
    if (ntc_device == SF_NTC_DEVICES_START || ntc_device == SR_NTC_DEVICES_START || ntc_device == SF_NTC_DEVICES_END ||
        ntc_device == SR_NTC_DEVICES_END) {
        return (-1.0f);
    }
    enum NTC_Probe ntc_probe;
    if (ntc_device > SF_NTC_DEVICES_START && ntc_device < SF_NTC_DEVICES_END) {
        ntc_probe = SF_NTC_dev_to_probe_map[ntc_device];
    } else if (ntc_device > SR_NTC_DEVICES_START && ntc_device < SR_NTC_DEVICES_END) {
        ntc_probe = SR_NTC_dev_to_probe_map[ntc_device];
    } else {
        // Error, should be never here
        return (-1.0f);
    }
    return NTC_Probe_get_vdrop(ntc_probe);
}

float NTC_Device_get_resistance(enum NTC_Device ntc_device) {
    // Guard agains invalid values
    if (ntc_device == SF_NTC_DEVICES_START || ntc_device == SR_NTC_DEVICES_START || ntc_device == SF_NTC_DEVICES_END ||
        ntc_device == SR_NTC_DEVICES_END) {
        return (-1.0f);
    }
    enum NTC_Probe ntc_probe;
    if (ntc_device > SF_NTC_DEVICES_START && ntc_device < SF_NTC_DEVICES_END) {
        ntc_probe = SF_NTC_dev_to_probe_map[ntc_device];
    } else if (ntc_device > SR_NTC_DEVICES_START && ntc_device < SR_NTC_DEVICES_END) {
        ntc_probe = SR_NTC_dev_to_probe_map[ntc_device];
    } else {
        // Error, should never be here
        return (-1.0f);
    }
    return NTC_Probe_get_resistance(ntc_probe);
}

// -- LPPS (Linear Potentiometer Position Sensor)

float LPPS_get_voltage(enum LPPS_Device lpps_device) {
    // Guard agains invalid values
    if (lpps_device == SF_LPPS_DEVICES_START || lpps_device == SR_LPPS_DEVICES_START ||
        lpps_device == SF_LPPS_DEVICES_END || lpps_device == SR_LPPS_DEVICES_END) {
        return (-1.0f);
    }
    enum ADC_ADC1_Channel adc1_chnl;
    if (lpps_device > SF_LPPS_DEVICES_START && lpps_device < SF_LPPS_DEVICES_END) {
        adc1_chnl = SF_LPPS_dev_to_adc1_chnl_map[lpps_device];
    } else if (lpps_device > SR_LPPS_DEVICES_START && lpps_device < SR_LPPS_DEVICES_END) {
        adc1_chnl = SR_LPPS_dev_to_adc1_chnl_map[lpps_device];
    } else {
        // Error, should never be here
        return (-1.0f);
    }
    float adc_volt = ADC_ADC1_getChannel_V(adc1_chnl);
    return adc_volt != (-1.0f) ? __DYN_RANGE_LVL_SHIFT(adc_volt, LPPS_VDIV_R1_OHM, LPPS_VDIV_R2_OHM) : (-1.0f);
}

// -- DSCRHG (Discharge) Status Feedback

float DSCHRG_get_voltage() {
    return ADC_ADC1_getChannel_V(SR_DSCHRG_dev_to_adc1_chnl_map[DSCHRG_StatusFeedbackDev]);
}

enum DSCHRG_Status DSCHRG_get_status() {
    float adc_volt = ADC_ADC1_getChannel_V(SR_DSCHRG_dev_to_adc1_chnl_map[DSCHRG_StatusFeedbackDev]);
    return DSCHRG_ADC_V_TO_STATUS_ENCODE(adc_volt,
                                         DSCHRG_ON_STATE_UP_LIMIT_V,
                                         DSCHRG_ON_STATE_LOW_LIMIT_V,
                                         DSCHRG_OFF_STATE_UP_LIMIT_V,
                                         DSCHRG_OFF_STATE_LOW_LIMIT_V);
}

// -- PPS (Piezoresistive Pressure Sensor)
float PPS_get_voltage(enum PPS_Device pps_device){
    // Guard agains invalid values
    if (pps_device == SF_PPS_DEVICES_START || pps_device == SR_PPS_DEVICES_START ||
        pps_device == SF_PPS_DEVICES_END || pps_device == SR_PPS_DEVICES_END) {
        return (-1.0f);
    }
    enum ADC_ADC1_Channel adc1_chnl;
    if (pps_device > SF_PPS_DEVICES_START && pps_device < SF_PPS_DEVICES_END) {
        adc1_chnl = SF_PPS_dev_to_adc1_chnl_map[pps_device];
    } else if (pps_device > SR_PPS_DEVICES_START && pps_device < SR_PPS_DEVICES_END) {
        adc1_chnl = SR_PPS_dev_to_adc1_chnl_map[pps_device];
    } else {
        // Error, should never be here
        return (-1.0f);
    }
    float adc_volt = ADC_ADC1_getChannel_V(adc1_chnl);
    return adc_volt != (-1.0f) ? __DYN_RANGE_LVL_SHIFT(adc_volt, PPS_VDIV_R1_OHM, PPS_VDIV_R2_OHM) : (-1.0f);
}

// -- APPS (Accelerator Pedal Position Sensor)

float APPS_get_voltage(enum APPS_Chnl apps_chnl){
    enum ADC_ADC1_Channel adc1_chnl = SF_APPS_chnl_to_adc1_chnl_map[apps_chnl];
    float adc_volt = ADC_ADC1_getChannel_V(adc1_chnl);
    return adc_volt != (-1.0f) ? __DYN_RANGE_LVL_SHIFT(adc_volt, APPS_VDIV_R1_OHM, APPS_VDIV_R2_OHM) : (-1.0f);
    
}

/*---------- Private Functions ---------------------------------------------*/
