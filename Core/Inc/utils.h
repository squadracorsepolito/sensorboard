#ifndef UTILS_H
#define UTILS_H

#include "gpio.h"

#define SENSE_TYPE_FRONT    0
#define SENSE_TYPE_REAR     1

#define UTILS_GET_SENS_TYPE() HAL_GPIO_ReadPin(SENSE_TYPE_GPIO_Port, SENSE_TYPE_Pin)

#endif // UTILS_H