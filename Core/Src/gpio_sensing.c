#include "gpio_sensing.h"

GPIO_TypeDef *ports[GPIO_PINS_N] = {
    [SD_SENS1] = SHTDWN1_GPIO_IN_GPIO_Port,
    [SD_SENS2] = SHTDWN2_GPIO_IN_GPIO_Port,
    [SD_SENS3] = SHTDWN3_GPIO_IN_GPIO_Port,
    [SD_SENS4] = SHTDWN4_GPIO_IN_GPIO_Port,
    [BSPD_SENS] = BSPD_ERR_GPIO_IN_GPIO_Port,
};

uint8_t pins[GPIO_PINS_N] = {
    [SD_SENS1] = SHTDWN1_GPIO_IN_Pin,
    [SD_SENS2] = SHTDWN2_GPIO_IN_Pin,
    [SD_SENS3] = SHTDWN3_GPIO_IN_Pin,
    [SD_SENS4] = SHTDWN4_GPIO_IN_Pin,
    [BSPD_SENS] = BSPD_ERR_GPIO_IN_Pin,
};

GPIO_PinState gpio_sens_get(GPIO_SENS_PIN_t gpio) {
    return HAL_GPIO_ReadPin(ports[gpio], pins[gpio]);
}