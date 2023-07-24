/**
 * @file      ntc.c
 * @prefix    NTC
 * @author    Simone Ruffini [simone.ruffini@squadracose.com
 *                            simone.ruffini.work@gmail.com]
 * @date      Fri Jul  7 11:34:03 AM CEST 2023
 * 
 * @brief     Ntc peripherals handler
 * 
 * @license Licensed under "THE BEER-WARE LICENSE", Revision 69 (see LICENSE)
 */

/* Includes ------------------------------------------------------------------*/
#include "ntc.h"

#include "adc1283.h"
#include "spi.h"
#include "logger_wrapper.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
struct ADC1283_Handle_t hadc1283 = {.hspi         = &ADC1283_SPI_Handle,
                                    .cs_gpio_port = ADC1283IPT_nCS_GPIO_OUT_GPIO_Port,
                                    .cs_gpio_pin  = ADC1283IPT_nCS_GPIO_OUT_Pin};
uint16_t NTC_adc_raw[NTC_enum_number];
float NTC_vdrop_volt[NTC_enum_number];
float NTC_res_ohm[NTC_enum_number];
/* Private function prototypes -----------------------------------------------*/

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

float NTC_get_vdrop(enum NTC_enum ntc) {
    if (ntc == NTC_enum_number)
        return (uint16_t)-1U;
    return NTC_vdrop_volt[ntc];
}
float NTC_get_res(enum NTC_enum ntc) {
    if (ntc == NTC_enum_number)
        return (uint16_t)-1U;
    return NTC_res_ohm[ntc];
}

void NTC_sampling_callback() {
    static enum ADC1283_CHNL_t channels[] = {
        ADC1283_CHNL0, ADC1283_CHNL1, ADC1283_CHNL2, ADC1283_CHNL3, ADC1283_CHNL4, ADC1283_CHNL5};
    const static uint8_t num_channels = sizeof(channels) / sizeof(channels[0]);
    //ADC1283_conv_channels(&hadc1283, num_channels, channels, NTC_vdrop_volt);
    //ADC1283_conv_channels_raw(&hadc1283, num_channels, channels, NTC_adc_raw);
    ADC1283_conv_channel_raw(&hadc1283, ADC1283_CHNL0, &NTC_adc_raw[0]);
    ADC1283_conv_channel_raw(&hadc1283, ADC1283_CHNL1, &NTC_adc_raw[1]);
    ADC1283_conv_channel_raw(&hadc1283, ADC1283_CHNL2, &NTC_adc_raw[2]);
    ADC1283_conv_channel_raw(&hadc1283, ADC1283_CHNL3, &NTC_adc_raw[3]);
    ADC1283_conv_channel_raw(&hadc1283, ADC1283_CHNL4, &NTC_adc_raw[4]);
    ADC1283_conv_channel_raw(&hadc1283, ADC1283_CHNL5, &NTC_adc_raw[5]);
    for(int i=0; i<NTC_enum_number;i++){
        NTC_vdrop_volt[i]=ADC1283_ADC_RAW_TO_PHYS(NTC_adc_raw[i],(3.3f/4096));
        //NTC_res_ohm[i]=0.002*NTC_RES_FROM_NTC_VDROP(NTC_vdrop_volt[i],NTC_PULL_UP_RES_OHM,NTC_VDIV_VDD_V)+(1-0.002)*NTC_res_ohm[i];
        NTC_res_ohm[i]=NTC_RES_FROM_NTC_VDROP(NTC_vdrop_volt[i],NTC_PULL_UP_RES_OHM,NTC_VDIV_VDD_V);
    }
}
/* Private functions ---------------------------------------------------------*/
