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
#include "ntc.h"

#include "logger_wrapper.h"

TIMEBASE_HandleTypeDef DRTB_handle;

STMLIBS_StatusTypeDef _DRTB_ntc_callback(void) {
    NTC_sampling_callback();
    return STMLIBS_OK;
}

void DRTB_init(void) {
    volatile STMLIBS_StatusTypeDef ret_code = STMLIBS_OK;
    uint8_t interval;
    // htim7 provides a fCLK of 1MHz

    // Initialize timbase to 100000us(100ms) base update period
    ret_code = TIMEBASE_init(&DRTB_handle, &DRTB_TIM_HANDLE, 100000);
    assert_param(ret_code == STMLIBS_OK);
    // Add an event every 500000us (500ms)
    ret_code = TIMEBASE_add_interval(&DRTB_handle, 500000, &interval);
    assert_param(ret_code == STMLIBS_OK);
    // Register a callback to that event
    ret_code = TIMEBASE_register_callback(&DRTB_handle, interval, _DRTB_ntc_callback);
    assert_param(ret_code == STMLIBS_OK);
}

void DRTB_routine(void) {
    TIMEBASE_routine(&DRTB_handle);
}

volatile uint32_t drtb_counter;
void DRTB_timerElapsed_irq(TIM_HandleTypeDef *htim) {
    drtb_counter++;
    TIMEBASE_TimerElapsedCallback(&DRTB_handle, htim);
}
