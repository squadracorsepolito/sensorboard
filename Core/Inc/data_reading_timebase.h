/**
 * @file      data_reading_timebase.h
 * @prefix    DRTB
 * @author    Simone Ruffini [simone.ruffini@squadracorse.com 
 *                            simone.ruffini.work@gmail.com]
 * @author    Federico Carbone [federico.carbone@squadracorse.com]
 * @date      Mon Jul 10 04:02:38 PM CEST 2023
 *
 * @brief     Data reading timebase header file
 *
 * @license Licensed under "THE BEER-WARE LICENSE", Revision 69 (see LICENSE)
 */
#ifndef _DATA_READING_TIMEBASE_H
#define _DATA_READING_TIMEBASE_H

#include "timebase.h"
#include "tim.h"

void DRTB_init(void);
void DRTB_routine(void);
void DRTB_timerElapsed_irq(TIM_HandleTypeDef *htim);

#endif // DATA_READING_TIMEBASE_H
