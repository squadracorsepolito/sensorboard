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

// -- NTC

/*---------- Private macro --------------------------------------------------*/

// -- NTC

/*---------- Private variables ----------------------------------------------*/

// -- NTC
struct ADC1283_Handle hadc1283 = {.hspi         = &ADC1283_SPI_Handle,
                                  .cs_gpio_port = ADC1283IPT_nCS_GPIO_OUT_GPIO_Port,
                                  .cs_gpio_pin  = ADC1283IPT_nCS_GPIO_OUT_Pin};
#ifdef NTC_DEBUG
uint16_t NTC_adc_raw[NTC_probesNum];
#endif
float NTC_adc_V[NTC_probesNum];
float NTC_res_Ohm[NTC_probesNum];

/*---------- Private function prototypes ------------------------------------*/

// -- NTC

/*---------- Exported Variables ---------------------------------------------*/

// -- NTC

/*---------- Exported Functions ---------------------------------------------*/

// -- NTC

float NTC_get_vdrop(enum NTC_Probe ntc_probe) {
    if (ntc_probe == NTC_probesNum)
        return (-1.0f);
    return NTC_adc_V[ntc_probe];
}
float NTC_get_res(enum NTC_Probe ntc_probe) {
    if (ntc_probe == NTC_probesNum)
        return (-1.0f);
    return NTC_res_Ohm[ntc_probe];
}

void NTC_sampling_routine() {
#ifdef NTC_DEBUG
    ADC1283_conv_channels_raw(&hadc1283, NTC_probesNum, NTC_adc1283_chnls_map, NTC_adc_raw);
#endif
    ADC1283_conv_channels(&hadc1283, NTC_probesNum, NTC_adc1283_chnls_map, NTC_adc_V);
    for (int i = 0; i < NTC_probesNum; i++) {
#ifdef NTC_DEBUG
        NTC_adc_V[i] = ADC1283_ADC_RAW_TO_PHYS(NTC_adc_raw[i]);
#endif
        NTC_res_Ohm[i] = (0.02f) * NTC_RES_FROM_NTC_VDROP(NTC_adc_V[i], NTC_PULL_UP_RES_OHM, NTC_PULL_UP_VDD_V) +
                         (1.0f - 0.02f) * NTC_res_Ohm[i];
        //NTC_res_ohm[i] = NTC_RES_FROM_NTC_VDROP(NTC_vdrop_volt[i], NTC_PULL_UP_RES_OHM, NTC_PULL_UP_VDD_V);
    }
}

/*---------- Private Functions ---------------------------------------------*/
