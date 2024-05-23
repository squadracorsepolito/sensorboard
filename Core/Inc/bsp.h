/**
 * @file    BSP.h
 * @author  Simone Ruffini [simone.ruffini@squadracorsepolito.com, simone.ruffini.work@gmail.com]
 * @date    Sat May 11 11:57:08 PM CEST 2024 (date of creation)
 * @updated Sat May 11 11:57:08 PM CEST 2024 (date of last update)
 * @prefix  varius depending on module
 *
 * @brief   Header files for board support package functions
 *
 * @license Licensed under "THE BEER-WARE LICENSE", Revision 69 
 *          see LICENSE file in the root directory of this software component
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _BSP_H_
#define _BSP_H_

/* ---------- Includes ------------------------------------------------------*/
#include "adc.h"
#include "adc1283.h"
#include "gpio.h"
/* ---------- Exported types ------------------------------------------------*/

// -- NTC (Negative Temperature Coefficient) Thermistor - Mounted Devices

/**
 * @brief NTC Probes
 */
enum NTC_Probe { NTC_Probe1, NTC_Probe2, NTC_Probe3, NTC_Probe4, NTC_Probe5, NTC_Probe6, NTC_Probe_NUM };

/**
 * @brief NTC devices 
 */
enum NTC_Device {
    SF_NTC_DEVICES_START,
    NTC_MotorJacket_FrontRight,
    NTC_MotorJacket_FrontLeft,
    NTC_ColdPlate_Left,
    NTC_ColdPlate_Right,
    SF_NTC_DEVICES_END,
    SR_NTC_DEVICES_START,
    NTC_MotorJacket_RearLeft,
    NTC_MotorJacket_RearRight,
    NTC_Radiator_Left1,
    NTC_Radiator_Left2,
    NTC_Radiator_Right1,
    NTC_Radiator_Right2,
    SR_NTC_DEVICES_END
};

// -- LPPS (Linear Potentiometer Position Sensor)

/**
 * @brief Linear Potentiomenter Position Sensor Devices
 */
enum LPPS_Device {
    SF_LPPS_DEVICES_START,
    LPPS_Damper_FrontLeft,
    LPPS_Damper_FrontRight,
    SF_LPPS_DEVICES_END,
    SR_LPPS_DEVICES_START,
    LPPS_Damper_RearLeft,
    LPPS_Damper_RearRight,
    SR_LPPS_DEVICES_END
};

// -- DSCRHG (Discharge) Status Feedback
/**
 * @brief Discharge Status Feedback Devices
 */
enum DSCHRG_Device { DSCHRG_StatusFeedbackDev };

/**
 * @brief Possibile states of the discharge status feedback device
 */
enum DSCHRG_Status {
    DSCHRG_On,   /*!< Discharge is ON and current is flowing through discharge
                    resistors, discharging (hopefully only) the DC-Link 
                    @NOTE This state could additionally encode a short to gnd
                    or a high-impedence input (truncated wire) of the feedback signal. 
                    This is by design as its considered a safe state */
    DSCHRG_Off,  /*!< Discharge is OFF no current is flowing through discharge resistors */
    DSCHRG_STVDD /*!< A short to vdd is detected on the feedback line */
};

// -- PPS (Piezoresistive Pressure Sensor) Devices
enum PPS_Device {
    SF_PPS_DEVICES_START,
    PPS_BrakeLine_Front,
    SF_PPS_DEVICES_END,
    SR_PPS_DEVICES_START,
    PPS_BrakeLine_Rear,
    PPS_CoolingLine_RearRight,
    PPS_CoolingLine_RearLeft,
    SR_PPS_DEVICES_END
};

// -- APPS (Accelerator Pedal Position Sensor) Channels
enum APPS_Chnl { APPS_Chnl1, APPS_Chnl2 };

// -- GPIO (General Purpuse Input Output)
struct GPIO_Tuple {
    GPIO_TypeDef *GPIO_Port;
    uint16_t GPIO_Pin;
};

// -- SDC (ShutDown Circuit) sensing/feedbacks
enum SDC_Probe { SDC_Probe1, SDC_Probe2, SDC_Probe3, SDC_Probe4, SDC_Probe_NUM };

enum SDC_Feedback {
    SF_SDC_FEEDBACKS_START,
    SDC_Post_FrontRightMotorInterlock,
    SDC_Post_BOTS,
    SDC_Post_CockpitPushButton,
    SDC_Post_InteriaSwitch,
    SF_SDC_FEEDBACKS_END,
    SR_SDC_FEEDBACKS_START,
    SDC_Post_BSPD,
    SDC_Post_InverterDCBUSInterlock,
    SDC_Pre_MainHoopLeftPushButton,
    SDC_Post_InverterFrontRightMotorInterlock,
    SR_SDC_FEEDBACKS_END
};


// -- RME (Rotary Magnetic Encoder) Device
enum RME_Dev {RME_SteeringAngle};

/* ---------- Exported constants --------------------------------------------*/

// -- AIN analog inputs
#define AIN_VDIV_R1_OHM (2.7E3f)
#define AIN_VDIV_R2_OHM (4.99E3f)

// Mappings to hardware peripherals and constants for physical values
// -- VCP (Virtual Communication Port)
#define VCP_UART_Handle               huart1 /*!< Virtual COMM Port UART handle */
#define VCP_TX_LOG_BUF_MAX_TIMEOUT_ms (30U)  //~27ms are necessary to send 400 chars via UART@115kbit/s

// -- ADC1283
#define ADC1283_SPI_Handle hspi2

// -- NTC (Negative Temperature Coefficient) Thermistor - Mounted Devices
#define NTC_SAMP_PERIOD_ms  (50U)
#define NTC_PULL_UP_RES_Ohm (10000U)
#define NTC_PULL_UP_VDD_V   (3.3f)

// -- LPPS (Linear Potentiometer Position Sensor)
#define LPPS_ADC_Handle  hadc1
#define LPPS_VDIV_R1_OHM (26.1E3f)
#define LPPS_VDIV_R2_OHM (39.0E3f)

// -- DSCRHG (Discharge) Status Feedback
#define DSCHRG_ADC_Handle hadc1

#define DSCHRG_ON_STATE_UP_LIMIT_V   (1.2f)
#define DSCHRG_ON_STATE_LOW_LIMIT_V  (0.0f)
#define DSCHRG_OFF_STATE_UP_LIMIT_V  (3.3f)
#define DSCHRG_OFF_STATE_LOW_LIMIT_V (2.2f)

// -- PPS (Piezoresistive Pressure Sensor)
#define PPS_VDIV_R1_OHM AIN_VDIV_R1_OHM
#define PPS_VDIV_R2_OHM AIN_VDIV_R2_OHM

// -- APPS (Accelerator Pedal Position Sensor)
#define APPS_VDIV_R1_OHM AIN_VDIV_R1_OHM
#define APPS_VDIV_R2_OHM AIN_VDIV_R2_OHM

// -- RME (Rotary Magnetic Encoder) Device
#define RME_VDIV_R1_OHM AIN_VDIV_R1_OHM
#define RME_VDIV_R2_OHM AIN_VDIV_R2_OHM

// -- SENS Sensorboard common
#define SENS_TYPE_FRONT GPIO_PIN_RESET
#define SENS_TYPE_REAR  GPIO_PIN_SET

// -- BSPD (Brake System Plausibility Device) Device
#define BSPD_DEV_STATE_OK GPIO_PIN_RESET
#define BSPD_DEV_STATE_ERR GPIO_PIN_SET

#define SENS_FRONT_LED_GPIO_PORT LED_STAT1_GPIO_OUT_GPIO_Port
#define SENS_FRONT_LED_GPIO_PIN  LED_STAT1_GPIO_OUT_Pin
#define SENS_REAR_LED_GPIO_PORT  LED_STAT2_GPIO_OUT_GPIO_Port
#define SENS_REAR_LED_GPIO_PIN   LED_STAT2_GPIO_OUT_Pin

/* ---------- Exported variables --------------------------------------------*/

// -- NTC (Negative Temperature Coefficient) Thermistor - Mounted Devices
/**
 * @brief NTC Probe to ADC1283 channel mapping
 * @NOTE  If the conversion order or the number of conversion (channels used) by
 *        the ADC changes then update this array too
 */
static enum ADC1283_Chnl NTC_probe_to_adc1283_chnl_map[NTC_Probe_NUM] = {[NTC_Probe1] = ADC1283_Chnl0,
                                                                         [NTC_Probe2] = ADC1283_Chnl1,
                                                                         [NTC_Probe3] = ADC1283_Chnl2,
                                                                         [NTC_Probe4] = ADC1283_Chnl3,
                                                                         [NTC_Probe5] = ADC1283_Chnl4,
                                                                         [NTC_Probe6] = ADC1283_Chnl5};
/**
 * @brief Sensorboard Front NTC device to to NTC probe mapping 
 */
static enum NTC_Probe SF_NTC_dev_to_probe_map[] = {[NTC_MotorJacket_FrontRight] = NTC_Probe1,
                                                   [NTC_MotorJacket_FrontLeft]  = NTC_Probe2,
                                                   [NTC_ColdPlate_Left]         = NTC_Probe3,
                                                   [NTC_ColdPlate_Right]        = NTC_Probe4};

/**
 * @brief Sensorboard Rear NTC device to to NTC probe mapping 
 */
static enum NTC_Probe SR_NTC_dev_to_probe_map[] = {[NTC_MotorJacket_RearLeft]  = NTC_Probe1,
                                                   [NTC_MotorJacket_RearRight] = NTC_Probe2,
                                                   [NTC_Radiator_Left1]        = NTC_Probe3,
                                                   [NTC_Radiator_Left2]        = NTC_Probe4,
                                                   [NTC_Radiator_Right1]       = NTC_Probe5,
                                                   [NTC_Radiator_Right2]       = NTC_Probe6};

// -- LPPS (Linear Potentiometer Position Sensor)

/**
 *@brief Sensorboard Front LPPS device to adc1 channel mapping 
 */
static enum ADC_ADC1_Channel SF_LPPS_dev_to_adc1_chnl_map[] =
    {[LPPS_Damper_FrontLeft] = ADC_ADC1_POT1, [LPPS_Damper_FrontRight] = ADC_ADC1_POT2};

/**
 *@brief Sensorboard Rear LPPS device to adc1 channel mapping 
 */
static enum ADC_ADC1_Channel SR_LPPS_dev_to_adc1_chnl_map[] =
    {[LPPS_Damper_RearLeft] = ADC_ADC1_POT2, [LPPS_Damper_RearRight] = ADC_ADC1_POT1};

// -- DSCRHG (Discharge) Status Feedback
/**
 *@brief Sensorboard Rear Discharge Status Feedback to adc1 channel mapping
 */
static enum ADC_ADC1_Channel SR_DSCHRG_dev_to_adc1_chnl_map[] = {[DSCHRG_StatusFeedbackDev] = ADC_ADC1_DSCHRG_FDBK};

// -- PPS (Piezoresistive Pressure Sensor) - Mounted Devices

/**
 *@brief Sensorboard Front Piezoresistive Pressure Sensor device to adc1 channel mapping 
 */
static enum ADC_ADC1_Channel SF_PPS_dev_to_adc1_chnl_map[] = {[PPS_BrakeLine_Front] = ADC_ADC1_AIN3};

/**
 *@brief Sensorboard Rear Piezoresistive Pressure Sensor device to adc1 channel mapping 
 */
static enum ADC_ADC1_Channel SR_PPS_dev_to_adc1_chnl_map[] = {[PPS_CoolingLine_RearLeft]  = ADC_ADC1_AIN3,
                                                              [PPS_BrakeLine_Rear]        = ADC_ADC1_AIN6,
                                                              [PPS_CoolingLine_RearRight] = ADC_ADC1_AIN7};
// -- APPS (Accelerator Position Sensor) Channels
/**
 *@brief Sensorboard Front Accelerator Position Sensor Channels to adc1 channel mapping
 */
static enum ADC_ADC1_Channel SF_APPS_chnl_to_adc1_chnl_map[] =
    {[APPS_Chnl1] = ADC_ADC1_AIN2, [APPS_Chnl2] = ADC_ADC1_AIN5};

// -- RME (Rotary Magnetic Encoder) Device
/**
 *@brief Sensorboard Front Rotary Magnetic Encoder Devices to adc1 channel mapping
 */
static enum ADC_ADC1_Channel SF_RME_dev_to_adc1_chnl_map[] = {[RME_SteeringAngle] = ADC_ADC1_AIN1};

// -- BRAKE Brake light control
static struct GPIO_Tuple BRAKE_Dev_Handle = {.GPIO_Port = BRK_LGHT_GPIO_OUT_GPIO_Port, .GPIO_Pin = BRK_LGHT_GPIO_OUT_Pin};

// -- BSPD (Brake System Plausibility Device) Device
static struct GPIO_Tuple BSPD_Dev_Handle = {.GPIO_Port = BSPD_ERR_GPIO_IN_GPIO_Port, .GPIO_Pin = BSPD_ERR_GPIO_IN_Pin};

// -- SENS Sensorboard common
static struct GPIO_Tuple SENS_Type_Handle = {.GPIO_Port = SENS_TYPE_GPIO_Port, .GPIO_Pin = SENS_TYPE_Pin};

// -- SDC (ShutDown Circuit) sensing/feedbacks

static struct GPIO_Tuple SDC_probe_to_gpio_map[SDC_Probe_NUM] = {
    [SDC_Probe1] = {.GPIO_Port = SDC_IN1_GPIO_IN_GPIO_Port, .GPIO_Pin = SDC_IN1_GPIO_IN_Pin},
    [SDC_Probe2] = {.GPIO_Port = SDC_IN2_GPIO_IN_GPIO_Port, .GPIO_Pin = SDC_IN2_GPIO_IN_Pin},
    [SDC_Probe3] = {.GPIO_Port = SDC_IN3_GPIO_IN_GPIO_Port, .GPIO_Pin = SDC_IN3_GPIO_IN_Pin},
    [SDC_Probe4] = {.GPIO_Port = SDC_IN4_GPIO_IN_GPIO_Port, .GPIO_Pin = SDC_IN4_GPIO_IN_Pin}};

static enum SDC_Probe SF_SDC_feedback_to_sdc_probe_map[] = {[SDC_Post_FrontRightMotorInterlock] = SDC_Probe1,
                                                            [SDC_Post_BOTS]                     = SDC_Probe2,
                                                            [SDC_Post_CockpitPushButton]        = SDC_Probe3,
                                                            [SDC_Post_InteriaSwitch]            = SDC_Probe4

};
static enum SDC_Probe SR_SDC_feedback_to_sdc_probe_map[] = {[SDC_Post_BSPD]                             = SDC_Probe1,
                                                            [SDC_Post_InverterDCBUSInterlock]           = SDC_Probe2,
                                                            [SDC_Pre_MainHoopLeftPushButton]            = SDC_Probe3,
                                                            [SDC_Post_InverterFrontRightMotorInterlock] = SDC_Probe4

};

/* ---------- Exported macros -----------------------------------------------*/

// -- NTC (Negative Temperature Coefficient) Thermistor - Mounted Devices
/**
 * @brief Get NTC resistance value from the voltage drop read on the ADC channel
 * @note  Check the schematic to understand how it is calculated
 * @param _NTC_VDROP_V_ voltage drop (float) on the NTC read by the ADC 
 * @param _PULL_UP_RES_OHM_ pull-up resistance in ohm (float) on the NTC 
 * @param _PULL_UP_VDD_V_ voltage reference on the pull-up resistor in volts (float)
 * @return NTC resistance in Ohm (float)
 */
#define NTC_RES_FROM_NTC_VDROP(_NTC_VDROP_V_, _PULL_UP_RES_OHM_, _PULL_UP_VDD_V_) \
    ((float)(_NTC_VDROP_V_ / (float)(_PULL_UP_VDD_V_ - _NTC_VDROP_V_) * _PULL_UP_RES_OHM_))

// -- DSCRHG (Discharge) Status Feedback

/**
 * @brief TODO
 */
#define DSCHRG_ADC_V_TO_STATUS_ENCODE(                                                                           \
    _ADC_VAL_V_, _ON_STATE_UP_LIMIT_V_, _ON_STATE_LOW_LIMIT_V_, _OFF_STATE_UP_LIMIT_V_, _OFF_STATE_LOW_LIMIT_V_) \
    (_ADC_VAL_V_ >= _ON_STATE_LOW_LIMIT_V_ && _ADC_VAL_V_ <= _ON_STATE_UP_LIMIT_V_     ? DSCHRG_On               \
     : _ADC_VAL_V_ >= _OFF_STATE_LOW_LIMIT_V_ && _ADC_VAL_V_ <= _OFF_STATE_UP_LIMIT_V_ ? DSCHRG_Off              \
                                                                                       : DSCHRG_STVDD)

// -- SENS Sensorboard Common

/**
 * @brief Get the sensor operation type either as FRONT sens or REAR sens
 * @return Either SENS_TYPE_FRONT or SENS_TYPE_REAR
 */
#define SENS_GET_TYPE() HAL_GPIO_ReadPin(SENS_Type_Handle.GPIO_Port, SENS_Type_Handle.GPIO_Pin)

// -- BRAKE Brake light control
#define BRAKE_LIGHT_ON()     HAL_GPIO_WritePin(BRAKE_Dev_Handle.GPIO_Port, BRAKE_Dev_Handle.GPIO_Pin, GPIO_PIN_SET)
#define BRAKE_LIGHT_OFF()    HAL_GPIO_WritePin(BRAKE_Dev_Handle.GPIO_Port, BRAKE_Dev_Handle.GPIO_Pin, GPIO_PIN_RESET)
#define BRAKE_LIGHT_TOGGLE() HAL_GPIO_TogglePin(BRAKE_Dev_Handle.GPIO_Port, BRAKE_Dev_Handle.GPIO_Pin)

// -- BSPD (Brake System Plausibility Device) Error
/**
 * @brief Get the state of the BSPD Device
 * @return Either: 
 *         - BSPD_DEV_STATE_OK if no error on the device
 *         - BSPD_DEV_STATE_ERR if an error occured
 */
#define BSPD_DEV_GET_STATUS() HAL_GPIO_ReadPin(BSPD_Dev_Handle.GPIO_Port, BSPD_Dev_Handle.GPIO_Pin)
#define BSPD_DEV_IS_IN_ERR() HAL_GPIO_ReadPin(BSPD_Dev_Handle.GPIO_Port, BSPD_Dev_Handle.GPIO_Pin) == BSPD_DEV_STATE_ERR ? (1U): (0U)
#define BSPD_DEV_IS_OK() HAL_GPIO_ReadPin(BSPD_Dev_Handle.GPIO_Port, BSPD_Dev_Handle.GPIO_Pin)== BSPD_DEV_STATE_OK ? (1U): (0U)

/* ---------- Exported functions --------------------------------------------*/

// -- NTC (Negative Temperature Coefficient) Thermistor - Mounted Devices

/*
 * @brief Get NTC Probe voltage drop on the voltage divider
 * @param ntc_probe NTC device @ref enum NTC_Probe
 * @return Voltage drop on the voltage divider (float), -1.0f if error
 */
float NTC_Probe_get_vdrop(enum NTC_Probe ntc_probe);

/*
 * @brief Get NTC Probe resistance value
 * @param ntc_probe NTC device @ref enum NTC_Probe
 * @return NTC resistance (float), -1.0f if error
 */
float NTC_Probe_get_resistance(enum NTC_Probe ntc_probe);

/*
 * @brief Get NTC Device resistance (works for both SF and SR devices)
 * @param ntc_device NTC device @ref enum NTC_Probe
 * @return NTC resistance (float), -1.0f if error
 */
float NTC_Device_get_resistance(enum NTC_Device ntc_device);

/*
 * @brief Get NTC Device resistance (works for bot SF and SR devices)
 * @param ntc_device NTC device @ref enum NTC_Device
 * @return NTC resistance (float), -1.0f if error
 */
float NTC_Device_get_resistance(enum NTC_Device ntc_device);

/*
 * @brief Sampling function, must be called periodically with period @ref NTC_SAMP_PERIOD_ms
 */
void NTC_Probes_sampling_routine();

// -- LPPS (Linear Potentiometer Position Sensor)
/*
 * @brief Get voltage of the given linear potentionmeter sensor  (works for both SF and SR devices)
 * @param lpps_device LPPS device @ref enum LPPS_Device
 * @return Voltage level of the LPPS (float), -1.0f if error
 */
float LPPS_get_voltage(enum LPPS_Device lpps_device);

// -- DSCRHG (Discharge) Status Feedback

/**
 * @brief Return the Discharge Status Feedback Device voltage level
 * @return Voltage level of the Discharge Status Feedback device (float)
 */
float DSCHRG_get_voltage();

/**
 * @brief Return the Discharge Status Feedback Device status 
 * @return status of DSCHRG @ref enum DSCHRG_Status
 */
enum DSCHRG_Status DSCHRG_get_status();

// -- PPS (Piezoresistive Pressure Sensor)

/*
 * @brief Get voltage of the given Piezoresistive Pressure Sesensor (works for both SF and SR devices)
 * @param pps_device PPS device @ref enum PPS_Device
 * @return Voltage level of the PPS (float), -1.0f if error
 */
float PPS_get_voltage(enum PPS_Device pps_device);

// -- APPS (Accelerator Pedal Position Sensor)

/*
 * @brief Get voltage of the given Accelerator Pedal Position Sensor channel
 * @param apps_chnl APPS channel @ref enum APPS_Chnl
 * @return Voltage level of the APPS channel (float), -1.0f if error
 */
float APPS_get_voltage(enum APPS_Chnl apps_chnl);

// -- SDC (ShutDown Circuit) sensing/feedbacks

uint8_t SDC_Probe_get_status(enum SDC_Probe sdc_probe);

uint8_t SDC_Feedback_get_status(enum SDC_Feedback sdc_feedback);

// -- RME (Rotary Magnetic Encoder) Device
float RME_get_voltage(enum RME_Dev rme_device);

/* ---------- Private types -------------------------------------------------*/

/* ---------- Private variables ---------------------------------------------*/

/* ---------- Private constants ---------------------------------------------*/

/* ---------- Private Macros ------------------------------------------------*/

/**
 * @brief Dynamic range level shift from ADC dynamic range to sensor input dynamic range
 * @details Check schematic. ADC_V = (R2)/(R1+R2) * AIN_V (voltage divider method)
 *          where R1 is the series resistor to LPPS output and R2 is the parallel
 *          resistor to LPPS output
 * @param _ADC_V_ voltage converted from ADC of relative sensor device (float)
 * @param _VDIV_R1_OHM_ voltage divider R1 resistor in Ohm (float)
 * @param _VDIV_R2_OHM_ voltage divider R2 resistor in Ohm (float)
 * @return sensor input voltage level (AIN_V) in it's original dyanmic range
 */
#define __DYN_RANGE_LVL_SHIFT(_ADC_V_, _VDIV_R1_OHM_, _VDIV_R2_OHM_) \
    ((float)(_VDIV_R1_OHM_ + _VDIV_R2_OHM_) / (_VDIV_R2_OHM_) * _ADC_V_)

#endif
