/**
 * @file      data_reading_timebase.c
 * @prefix    DRTB
 * @author    Simone Ruffini [simone.ruffini@squadracorse.com 
 *                            simone.ruffini.work@gmail.com]
 * @author    Federico Carbone [federico.carbone@squadracorse.com]
 * @date      Mon Jul 10 04:02:38 PM CEST 2023
 *
 * @brief     Data reading timebase source file
 *
 * @license Licensed under "THE BEER-WARE LICENSE", Revision 69 (see LICENSE)
 */
#include "data_reading_timebase.h"

#include "tim.h"

//#include <stdio.h>
//#include <string.h>
//#include "usart.h"

//#include "errors.h"
#include "logger_wrapper.h"
#include "ntc.h"

TIMEBASE_HandleTypeDef DRTB_handle;

STMLIBS_StatusTypeDef _DRTB_1000us_callback(void) {
    NTC_sampling_callback();
    return STMLIBS_OK;
}

void DRTB_init(void) {
    uint8_t interval;
    // htim7 provides a fCLK of 1MHz

    // Initialize timbase to 1000us(1ms) base update period
    TIMEBASE_init(&DRTB_handle, &htim7, 1000);
    // Add an event every 100 timebase update events (100ms)
    TIMEBASE_add_interval(&DRTB_handle, 10000, &interval);
    // Register a callback to that event
    TIMEBASE_register_callback(&DRTB_handle, interval, _DRTB_1000us_callback);
}

void DRTB_routine(void) {
    TIMEBASE_routine(&DRTB_handle);
}

void DRTB_timerElapsed_irq(TIM_HandleTypeDef *htim) {
    TIMEBASE_TimerElapsedCallback(&DRTB_handle, htim);
}
