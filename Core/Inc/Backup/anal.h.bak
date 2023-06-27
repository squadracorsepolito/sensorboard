#ifndef ANAL_H
#define ANAL_H

#include "adc.h"

typedef enum {
    ANAL1 = 0,
    ANAL2,
    ANAL3,
    ANAL4,
    ANAL5,
    ANAL6,
    ANAL7,
    ANAL8,
    ANAL9,
    ANAL10,
    ANAL11,
    POT1,
    POT2,
    ANAL_PIN_COUNT
} anal_enum;

void anal_init(void);
void anal_adc_callback(ADC_HandleTypeDef *hadc);
uint16_t anal_get_pin_raw(uint8_t index);
float anal_get_pin_mv(uint8_t index);

#endif // ANAL_h