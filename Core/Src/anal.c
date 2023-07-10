#include "anal.h"

#include <memory.h>

#define ANAL_SMOOTH_ALPHA 0.1f
uint16_t anal_data[ANAL_PIN_COUNT];

uint16_t anal_dma_data[ANAL_PIN_COUNT];

void anal_init(void) {
    memset(anal_dma_data, 0, sizeof(anal_dma_data));
    memset(anal_data, 0, sizeof(anal_data));

    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)anal_dma_data, ANAL_PIN_COUNT);
}

void anal_adc_callback(ADC_HandleTypeDef *hadc) {
    static uint8_t is_first = 1;
    if (hadc->Instance == hadc1.Instance) {
        if (is_first) {
            is_first = 0;
            memcpy(anal_data, anal_dma_data, sizeof(anal_data));
        }
        for (uint8_t i = 0; i < ANAL_PIN_COUNT; ++i) {
            anal_data[i] = ANAL_SMOOTH_ALPHA * anal_dma_data[i] + (1 - ANAL_SMOOTH_ALPHA) * anal_data[i];
        }
    }
}

uint16_t anal_get_pin_raw(uint8_t index) {
    return anal_data[index];
}

float anal_get_pin_mv(uint8_t index) {
    return (float)anal_data[index] * 3300 / 4095;
}