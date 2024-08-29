#include "can_utils.h"
#include "logger_wrapper.h"
#include "bsp.h"
#include "gpio_sensing.h"

CAN_TxHeaderTypeDef tx_header;

void can_tx_header_init() {
    tx_header.ExtId = 0;
    tx_header.IDE   = CAN_ID_STD;
    tx_header.RTR   = CAN_RTR_DATA;
}

void can_init(void) {
    CAN_FilterTypeDef filter;
    filter.FilterMode       = CAN_FILTERMODE_IDMASK;
    filter.FilterIdLow      = BSP_XCP_MSG_ID << 5;                 // Take all ids from 0
    filter.FilterIdHigh     = BSP_XCP_MSG_ID << 5;  // to 2^11 - 1
    filter.FilterMaskIdHigh = BSP_XCP_MSG_ID << 5;                 // Don't care on can id bits
    filter.FilterMaskIdLow  = BSP_XCP_MSG_ID << 5;                 // Don't care on can id bits
    /* HAL considers IdLow and IdHigh not as just the ID of the can message but
        as the combination of: 
        STDID + RTR + IDE + 4 most significant bits of EXTID
    */
    filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    filter.FilterBank           = 0;
    filter.FilterScale          = CAN_FILTERSCALE_16BIT;
    filter.FilterActivation     = ENABLE;

    HAL_CAN_ConfigFilter(&hcan1, &filter);

    filter.FilterMode       = CAN_FILTERMODE_IDLIST;
    filter.FilterIdLow      = 0x201 << 5;                 // Take all ids from 0
    filter.FilterIdHigh     = 0x201 << 5;  // to 2^11 - 1
    filter.FilterMaskIdHigh = 0x201 << 5;                 // Don't care on can id bits
    filter.FilterMaskIdLow  = 0x201 << 5;                 // Don't care on can id bits
    /* HAL considers IdLow and IdHigh not as just the ID of the can message but
        as the combination of: 
        STDID + RTR + IDE + 4 most significant bits of EXTID
    */
    filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    filter.FilterBank           = 1;
    filter.FilterScale          = CAN_FILTERSCALE_16BIT;
    filter.FilterActivation     = ENABLE;

    HAL_CAN_ConfigFilter(&hcan1, &filter);

    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_ERROR | CAN_IT_RX_FIFO0_MSG_PENDING);
    HAL_CAN_Start(&hcan1);

    // Send Helo Message at start 
    //SENS_TYPE() == SENS_TYPE_FRONT ? can_send_msg(MCB_SB_FRONT_HELO) : can_send_msg(MCB_SB_REAR_HELO);
}

HAL_StatusTypeDef can_wait(CAN_HandleTypeDef *hcan, uint8_t timeout) {
    uint32_t tick = HAL_GetTick();
    while (HAL_CAN_GetTxMailboxesFreeLevel(hcan) == 0) {
        if(HAL_GetTick() - tick > timeout) return HAL_TIMEOUT;
    }
    return HAL_OK;
}

HAL_StatusTypeDef can_send(CAN_HandleTypeDef *hcan, uint8_t *buffer, CAN_TxHeaderTypeDef *header) {
    if(can_wait(hcan, 1) != HAL_OK) return HAL_TIMEOUT;
    uint32_t mailbox;

    volatile HAL_StatusTypeDef status = HAL_CAN_AddTxMessage(hcan, header, buffer, &mailbox);

    return status;
}

void can_send_msg(uint32_t id) {
    uint8_t buffer[8] = {0};
    union {
        struct mcb_sb_front_analog_device_t sens_front_analog;
        struct mcb_sb_front_potentiometer_t sens_front_pot;
        struct mcb_sb_front_ntc_resistance_t sens_front_ntc;
        struct mcb_sb_front_hello_t sens_front_hello;
        struct mcb_sb_front_sd_csensing_status_t sens_front_sd_status;

        struct mcb_sb_rear_analog_device_t sens_rear_analog;
        struct mcb_sb_rear_potentiometer_t sens_rear_pot;
        struct mcb_sb_rear_critical_peripherals_t sens_rear_crit;
        struct mcb_sb_rear_ntc_resistance_t sens_rear_ntc;
        struct mcb_sb_rear_hello_t sens_rear_hello;
        struct mcb_sb_rear_sd_csensing_status_t sens_rear_sd_status;
    } msgs;

    tx_header.StdId = id;

    switch (id)
    {
    case MCB_SB_FRONT_ANALOG_DEVICE_FRAME_ID:
        msgs.sens_front_analog.brake_press_front_voltage = mcb_sb_front_analog_device_brake_press_front_voltage_encode(PPS_get_voltage(PPS_BrakeLine_Front)*1000.0);
        msgs.sens_front_analog.steer_rme_voltage = mcb_sb_front_analog_device_steer_rme_voltage_encode(RME_get_voltage(RME_SteeringAngle)*1000.0);
        msgs.sens_front_analog.apps_0_voltage = mcb_sb_front_analog_device_apps_0_voltage_encode(APPS_get_voltage(APPS_Chnl1)*1000.0);
        msgs.sens_front_analog.apps_1_voltage = mcb_sb_front_analog_device_apps_0_voltage_encode(APPS_get_voltage(APPS_Chnl2)*1000.0);

        tx_header.DLC = mcb_sb_front_analog_device_pack(buffer, &msgs.sens_front_analog, MCB_SB_FRONT_ANALOG_DEVICE_LENGTH);
        break;
    case MCB_SB_FRONT_POTENTIOMETER_FRAME_ID:
        msgs.sens_front_pot.lpps_damper_fl_voltage = mcb_sb_front_potentiometer_lpps_damper_fl_voltage_encode(LPPS_get_voltage(LPPS_Damper_FrontLeft)*1000.0);
        msgs.sens_front_pot.lpps_damper_fr_voltage = mcb_sb_front_potentiometer_lpps_damper_fr_voltage_encode(LPPS_get_voltage(LPPS_Damper_FrontRight)*1000.0);

        tx_header.DLC = mcb_sb_front_potentiometer_pack(buffer, &msgs.sens_front_pot, MCB_SB_FRONT_POTENTIOMETER_LENGTH);
        break;
    case MCB_SB_FRONT_NTC_RESISTANCE_FRAME_ID:
        msgs.sens_front_ntc.jacket_fr_ntc_resistance      = mcb_sb_front_ntc_resistance_jacket_fr_ntc_resistance_encode(NTC_Device_get_resistance(NTC_MotorJacket_FrontRight));
        msgs.sens_front_ntc.jacket_fl_ntc_resistance      = mcb_sb_front_ntc_resistance_jacket_fl_ntc_resistance_encode(NTC_Device_get_resistance(NTC_MotorJacket_FrontLeft));
        msgs.sens_front_ntc.coldplate_l_ntc_resistance      = mcb_sb_front_ntc_resistance_coldplate_l_ntc_resistance_is_in_range(NTC_Device_get_resistance(NTC_ColdPlate_Left));
        msgs.sens_front_ntc.coldplate_r_ntc_resistance      = mcb_sb_front_ntc_resistance_coldplate_r_ntc_resistance_is_in_range(NTC_Device_get_resistance(NTC_ColdPlate_Right));
        msgs.sens_front_ntc.spare_ntc_0_resistance = mcb_sb_front_ntc_resistance_spare_ntc_0_resistance_encode(0.0);
        msgs.sens_front_ntc.spare_ntc_1_resistance = mcb_sb_front_ntc_resistance_spare_ntc_1_resistance_encode(0.0);

        tx_header.DLC = mcb_sb_front_ntc_resistance_pack(buffer, &msgs.sens_front_ntc, MCB_SB_FRONT_NTC_RESISTANCE_LENGTH);
        break;
    case MCB_SB_FRONT_SD_CSENSING_STATUS_FRAME_ID:
        msgs.sens_front_sd_status.sdc_post_bots_is_active = mcb_sb_front_sd_csensing_status_sdc_post_bots_is_active_encode(SDC_Feedback_get_status(SDC_Post_BOTS));
        msgs.sens_front_sd_status.sdc_post_cp_push_btn_is_active = mcb_sb_front_sd_csensing_status_sdc_post_cp_push_btn_is_active_encode(SDC_Feedback_get_status(SDC_Post_CockpitPushButton));
        msgs.sens_front_sd_status.sdc_post_inertia_is_active = mcb_sb_front_sd_csensing_status_sdc_post_inertia_is_active_encode(SDC_Feedback_get_status(SDC_Post_InteriaSwitch));

        tx_header.DLC = mcb_sb_front_sd_csensing_status_pack(buffer, &msgs.sens_front_sd_status, MCB_SB_FRONT_SD_CSENSING_STATUS_LENGTH);
        break;

    case MCB_SB_REAR_ANALOG_DEVICE_FRAME_ID:
        msgs.sens_rear_analog.brake_press_rear_voltage = mcb_sb_rear_analog_device_brake_press_rear_voltage_encode(PPS_get_voltage(PPS_BrakeLine_Rear)*1000.0);
        msgs.sens_rear_analog.cool_press_right_voltage = mcb_sb_rear_analog_device_cool_press_right_voltage_encode(PPS_get_voltage(PPS_CoolingLine_RearRight)*1000.0);
        msgs.sens_rear_analog.cool_press_left_voltage = mcb_sb_rear_analog_device_cool_press_left_voltage_encode(PPS_get_voltage(PPS_CoolingLine_RearLeft)*1000.0);

        tx_header.DLC = mcb_sb_rear_analog_device_pack(buffer, &msgs.sens_rear_analog, MCB_SB_REAR_ANALOG_DEVICE_LENGTH);
        break;
    case MCB_SB_REAR_POTENTIOMETER_FRAME_ID:
        msgs.sens_rear_pot.lpps_damper_rl_voltage = mcb_sb_rear_potentiometer_lpps_damper_rl_voltage_encode(LPPS_get_voltage(LPPS_Damper_RearLeft)*1000.0);
        msgs.sens_rear_pot.lpps_damper_rr_voltage = mcb_sb_rear_potentiometer_lpps_damper_rr_voltage_encode(LPPS_get_voltage(LPPS_Damper_RearRight)*1000.0);

        tx_header.DLC = mcb_sb_rear_potentiometer_pack(buffer, &msgs.sens_rear_pot, MCB_SB_REAR_POTENTIOMETER_LENGTH);
        break;
    case MCB_SB_REAR_CRITICAL_PERIPHERALS_FRAME_ID:
        msgs.sens_rear_crit.discharge_is_open = mcb_sb_rear_critical_peripherals_discharge_is_open_encode(DSCHRG_get_status());
        msgs.sens_rear_crit.bspd_has_error = mcb_sb_rear_critical_peripherals_bspd_has_error_encode(BSPD_DEV_IS_IN_ERR());

        tx_header.DLC = mcb_sb_rear_critical_peripherals_pack(buffer, &msgs.sens_rear_crit, MCB_SB_REAR_CRITICAL_PERIPHERALS_LENGTH);
        break;
    case MCB_SB_REAR_NTC_RESISTANCE_FRAME_ID:
        msgs.sens_rear_ntc.jacket_rl_ntc_resistance = mcb_sb_rear_ntc_resistance_jacket_rl_ntc_resistance_encode(NTC_Device_get_resistance(NTC_MotorJacket_RearLeft));
        msgs.sens_rear_ntc.jacket_rr_ntc_resistance = mcb_sb_rear_ntc_resistance_jacket_rr_ntc_resistance_encode(NTC_Device_get_resistance(NTC_MotorJacket_RearRight));
        msgs.sens_rear_ntc.rad_rl_in_ntc_resistance = mcb_sb_rear_ntc_resistance_rad_rl_in_ntc_resistance_encode(NTC_Device_get_resistance(NTC_Radiator_Left1));
        msgs.sens_rear_ntc.rad_rl_out_ntc_resistance = mcb_sb_rear_ntc_resistance_rad_rl_out_ntc_resistance_encode(NTC_Device_get_resistance(NTC_Radiator_Left2));
        msgs.sens_rear_ntc.rad_rr_in_ntc_resistance = mcb_sb_rear_ntc_resistance_rad_rr_in_ntc_resistance_encode(NTC_Device_get_resistance(NTC_Radiator_Right1));
        msgs.sens_rear_ntc.rad_rr_out_ntc_resistance = mcb_sb_rear_ntc_resistance_rad_rr_out_ntc_resistance_encode(NTC_Device_get_resistance(NTC_Radiator_Right2));

        tx_header.DLC = mcb_sb_rear_ntc_resistance_pack(buffer, &msgs.sens_rear_ntc, MCB_SB_REAR_NTC_RESISTANCE_LENGTH);
        break;
    case MCB_SB_REAR_SD_CSENSING_STATUS_FRAME_ID:
        msgs.sens_rear_sd_status.sdc_post_bspd_is_closed = mcb_sb_rear_sd_csensing_status_sdc_post_bspd_is_closed_encode(SDC_Feedback_get_status(SDC_Post_BSPD));
        msgs.sens_rear_sd_status.sdc_post_inv_fr_is_closed = mcb_sb_rear_sd_csensing_status_sdc_post_inv_fr_is_closed_encode(SDC_Feedback_get_status(SDC_Post_InverterFrontRightMotorInterlock));
        msgs.sens_rear_sd_status.sdc_post_dc_bus_is_closed = mcb_sb_rear_sd_csensing_status_sdc_post_dc_bus_is_closed_encode(SDC_Feedback_get_status(SDC_Post_InverterDCBUSInterlock));
        msgs.sens_rear_sd_status.sdc_pre_push_btns_is_closed = mcb_sb_rear_sd_csensing_status_sdc_pre_push_btns_is_closed_encode(SDC_Feedback_get_status(SDC_Pre_MainHoopLeftPushButton));

        tx_header.DLC = mcb_sb_rear_sd_csensing_status_pack(buffer, &msgs.sens_rear_sd_status, MCB_SB_REAR_SD_CSENSING_STATUS_LENGTH);
        break;
    case MCB_SB_FRONT_HELLO_FRAME_ID:
        msgs.sens_front_hello.fw_major_version = mcb_sb_front_hello_fw_major_version_encode(1);
        msgs.sens_front_hello.fw_minor_version = mcb_sb_front_hello_fw_minor_version_encode(2);
        msgs.sens_front_hello.fw_patch_version = mcb_sb_front_hello_fw_patch_version_encode(3);

        tx_header.DLC = mcb_sb_front_hello_pack(buffer, &msgs.sens_front_hello, MCB_SB_FRONT_HELLO_LENGTH);
        break;
    case MCB_SB_REAR_HELLO_FRAME_ID:
        msgs.sens_rear_hello.fw_major_version = mcb_sb_rear_hello_fw_major_version_encode(1);
        msgs.sens_rear_hello.fw_minor_version = mcb_sb_rear_hello_fw_minor_version_encode(2);
        msgs.sens_rear_hello.fw_patch_version = mcb_sb_rear_hello_fw_patch_version_encode(3);

        tx_header.DLC = mcb_sb_rear_hello_pack(buffer, &msgs.sens_rear_hello, MCB_SB_REAR_HELLO_LENGTH);
        break;
    default:
        return;
    }
    
    can_send(&hcan1, buffer, &tx_header);
}

void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan) {
    // logger_log(LOGGER_ERROR, "sborato");
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    CAN_RxHeaderTypeDef rx_header;
    uint8_t buffer[8] = {0};

    if(HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, buffer) == HAL_OK) {
        // Reset when preparing for flash via CAN bus
        if(rx_header.StdId == BSP_XCP_MSG_ID && buffer[0] == 0xff && buffer[1] == 0x00) {
            NVIC_SystemReset();
        }
        else if (rx_header.StdId == 0x201/*MCB_D_SPACE_PERIPHERALS_CTRL_FRAME_ID*/){
            struct mcb_dspace_peripherals_ctrl_t periph;
            mcb_dspace_peripherals_ctrl_unpack(&periph, buffer, MCB_DSPACE_PERIPHERALS_CTRL_LENGTH);

             if(periph.brake_light_active_cmd){
                BRAKE_LIGHT_ON();
            }else{
                BRAKE_LIGHT_OFF();
            }

        }
    }
}
