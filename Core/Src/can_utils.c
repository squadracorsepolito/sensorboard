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
    filter.FilterIdLow      = (0xa + SENS_GET_TYPE()) << 5;                 // Take all ids from 0
    filter.FilterIdHigh     = (0xa + SENS_GET_TYPE()) << 5;  // to 2^11 - 1
    filter.FilterMaskIdHigh = (0xa + SENS_GET_TYPE()) << 5;                 // Don't care on can id bits
    filter.FilterMaskIdLow  = (0xa + SENS_GET_TYPE()) << 5;                 // Don't care on can id bits
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
    filter.FilterIdLow      = MCB_D_SPACE_PERIPHERALS_CTRL_FRAME_ID << 5;                 // Take all ids from 0
    filter.FilterIdHigh     = MCB_D_SPACE_PERIPHERALS_CTRL_FRAME_ID << 5;  // to 2^11 - 1
    filter.FilterMaskIdHigh = MCB_D_SPACE_PERIPHERALS_CTRL_FRAME_ID << 5;                 // Don't care on can id bits
    filter.FilterMaskIdLow  = MCB_D_SPACE_PERIPHERALS_CTRL_FRAME_ID << 5;                 // Don't care on can id bits
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
        struct mcb_sens_front_1_t sens_front_1;
        struct mcb_sens_front_2_t sens_front_2;
        struct mcb_sens_front_3_t sens_front_3;
        struct mcb_sens_front_ntc_t sens_front_ntc;
        struct mcb_sens_front_helo_t sens_front_helo;
        struct mcb_sens_front_shutdown_status_t sens_front_sd_status;

        struct mcb_sens_rear_1_t sens_rear_1;
        struct mcb_sens_rear_2_t sens_rear_2;
        struct mcb_sens_rear_3_t sens_rear_3;
        struct mcb_sens_rear_ntc_t sens_rear_ntc;
        struct mcb_sens_rear_helo_t sens_rear_helo;
        struct mcb_sens_rear_shutdown_status_t sens_rear_sd_status;
    } msgs;

    tx_header.StdId = id;

    switch (id)
    {
    case MCB_SENS_FRONT_1_FRAME_ID:
        msgs.sens_front_1.brake_straingauge_voltage_m_v = mcb_sens_front_1_brake_straingauge_voltage_m_v_encode(0.0);
        msgs.sens_front_1.steering_voltage_m_v = mcb_sens_front_1_steering_voltage_m_v_encode(RME_get_voltage(RME_SteeringAngle)*1000.0);
        msgs.sens_front_1.throttle_0_voltage_m_v = mcb_sens_front_1_throttle_0_voltage_m_v_encode(APPS_get_voltage(APPS_Chnl1)*1000.0);
        msgs.sens_front_1.throttle_1_voltage_m_v = mcb_sens_front_1_throttle_1_voltage_m_v_encode(APPS_get_voltage(APPS_Chnl2)*1000.0);

        tx_header.DLC = mcb_sens_front_1_pack(buffer, &msgs.sens_front_1, MCB_SENS_FRONT_1_LENGTH);
        break;
    case MCB_SENS_FRONT_2_FRAME_ID:
        msgs.sens_front_2.brake_pressure_voltage_m_v = mcb_sens_front_2_brake_pressure_voltage_m_v_encode(PPS_get_voltage(PPS_BrakeLine_Front)*1000.0);
        msgs.sens_front_2.pot_fl_voltage_m_v = mcb_sens_front_2_pot_fl_voltage_m_v_encode(LPPS_get_voltage(LPPS_Damper_FrontLeft)*1000.0);
        msgs.sens_front_2.pot_fr_voltage_m_v = mcb_sens_front_2_pot_fr_voltage_m_v_encode(LPPS_get_voltage(LPPS_Damper_FrontRight)*1000.0);

        tx_header.DLC = mcb_sens_front_2_pack(buffer, &msgs.sens_front_2, MCB_SENS_FRONT_2_LENGTH);
        break;
    case MCB_SENS_FRONT_3_FRAME_ID:
        msgs.sens_front_3.straingauge_push_fl_voltage_m_v = mcb_sens_front_3_straingauge_push_fl_voltage_m_v_encode(0.0);
        msgs.sens_front_3.straingauge_push_fr_voltage_m_v = mcb_sens_front_3_straingauge_push_fr_voltage_m_v_encode(0.0);
        msgs.sens_front_3.straingauge_tie_fl_voltage_m_v =  mcb_sens_front_3_straingauge_tie_fl_voltage_m_v_encode(0.0);
        msgs.sens_front_3.straingauge_tie_fr_voltage_m_v =  mcb_sens_front_3_straingauge_tie_fr_voltage_m_v_encode(0.0);

        tx_header.DLC = mcb_sens_front_3_pack(buffer, &msgs.sens_front_3, MCB_SENS_FRONT_3_LENGTH);
        break;
    case MCB_SENS_FRONT_NTC_FRAME_ID:
        msgs.sens_front_ntc.ntc_1_resistance      = mcb_sens_front_ntc_ntc_1_resistance_encode(NTC_Device_get_resistance(NTC_MotorJacket_FrontRight));
        msgs.sens_front_ntc.ntc_2_resistance      = mcb_sens_front_ntc_ntc_2_resistance_encode(NTC_Device_get_resistance(NTC_MotorJacket_FrontLeft));
        msgs.sens_front_ntc.ntc_3_resistance      = mcb_sens_front_ntc_ntc_3_resistance_encode(NTC_Device_get_resistance(NTC_ColdPlate_Left));
        msgs.sens_front_ntc.ntc_4_resistance      = mcb_sens_front_ntc_ntc_4_resistance_encode(NTC_Device_get_resistance(NTC_ColdPlate_Right));
        msgs.sens_front_ntc.ntc_spare1_resistance = mcb_sens_front_ntc_ntc_spare1_resistance_encode(0.0);
        msgs.sens_front_ntc.ntc_spare2_resistance = mcb_sens_front_ntc_ntc_spare2_resistance_encode(0.0);

        tx_header.DLC = mcb_sens_front_ntc_pack(buffer, &msgs.sens_front_ntc, MCB_SENS_FRONT_NTC_LENGTH);
        break;
    case MCB_SENS_FRONT_SHUTDOWN_STATUS_FRAME_ID:
        msgs.sens_front_sd_status.is_shut_closed_post_bots = mcb_sens_front_shutdown_status_is_shut_closed_post_bots_encode(SDC_Feedback_get_status(SDC_Post_BOTS));
        msgs.sens_front_sd_status.is_shut_closed_post_cockpit = mcb_sens_front_shutdown_status_is_shut_closed_post_cockpit_encode(SDC_Feedback_get_status(SDC_Post_CockpitPushButton));
        msgs.sens_front_sd_status.is_shut_closed_post_inertia = mcb_sens_front_shutdown_status_is_shut_closed_post_inertia_encode(SDC_Feedback_get_status(SDC_Post_InteriaSwitch));
        //msgs.sens_front_sd_status.is_shut_closed_pre_inertia = mcb_sens_front_shutdown_status_is_shut_closed_pre_inertia_encode(SDC_Feedback_get_status(SDC_Post_FrontRightMotorInterlock));
        msgs.sens_front_sd_status.is_shut_closed_pre_inertia = mcb_sens_front_shutdown_status_is_shut_closed_pre_inertia_encode(0U);

        tx_header.DLC = mcb_sens_front_shutdown_status_pack(buffer, &msgs.sens_front_sd_status, MCB_SENS_FRONT_SHUTDOWN_STATUS_LENGTH);
        break;

    case MCB_SENS_REAR_1_FRAME_ID:
        msgs.sens_rear_1.brake_pressure_rear_voltage_m_v = mcb_sens_rear_1_brake_pressure_rear_voltage_m_v_encode(PPS_get_voltage(PPS_BrakeLine_Rear)*1000.0);
        msgs.sens_rear_1.pot_rl_voltage_m_v = mcb_sens_rear_1_pot_rl_voltage_m_v_encode(LPPS_get_voltage(LPPS_Damper_RearLeft)*1000.0);
        msgs.sens_rear_1.pot_rr_voltage_rr = mcb_sens_rear_1_pot_rr_voltage_rr_encode(LPPS_get_voltage(LPPS_Damper_RearRight)*1000.0);

        tx_header.DLC = mcb_sens_rear_1_pack(buffer, &msgs.sens_rear_1, MCB_SENS_REAR_1_LENGTH);
        break;
    case MCB_SENS_REAR_2_FRAME_ID:
        msgs.sens_rear_2.cooling_pressure_dx_voltage_m_v = mcb_sens_rear_2_cooling_pressure_dx_voltage_m_v_encode(PPS_get_voltage(PPS_CoolingLine_RearRight)*1000.0);
        msgs.sens_rear_2.cooling_pressure_sx_voltage_m_v = mcb_sens_rear_2_cooling_pressure_sx_voltage_m_v_encode(PPS_get_voltage(PPS_CoolingLine_RearLeft)*1000.0);

        tx_header.DLC = mcb_sens_rear_2_pack(buffer, &msgs.sens_rear_2, MCB_SENS_REAR_2_LENGTH);
        break;
    case MCB_SENS_REAR_3_FRAME_ID:
        msgs.sens_rear_3.straingauge_push_rl_voltage_m_v = mcb_sens_rear_3_straingauge_push_rl_voltage_m_v_encode(0.0);
        msgs.sens_rear_3.straingauge_push_rr_voltage_m_v = mcb_sens_rear_3_straingauge_push_rr_voltage_m_v_encode(0.0);
        msgs.sens_rear_3.straingauge_tie_rl_voltage_m_v = mcb_sens_rear_3_straingauge_tie_rl_voltage_m_v_encode(0.0);
        msgs.sens_rear_3.straingauge_tie_rr_voltage_m_v = mcb_sens_rear_3_straingauge_tie_rr_voltage_m_v_encode(0.0);

        tx_header.DLC = mcb_sens_rear_2_pack(buffer, &msgs.sens_rear_2, MCB_SENS_REAR_2_LENGTH);
        break;
    case MCB_SENS_REAR_NTC_FRAME_ID:
        msgs.sens_rear_ntc.ntc_1_resistance = mcb_sens_rear_ntc_ntc_1_resistance_encode(NTC_Device_get_resistance(NTC_MotorJacket_RearLeft));
        msgs.sens_rear_ntc.ntc_2_resistance = mcb_sens_rear_ntc_ntc_2_resistance_encode(NTC_Device_get_resistance(NTC_MotorJacket_RearRight));
        msgs.sens_rear_ntc.ntc_3_resistance = mcb_sens_rear_ntc_ntc_3_resistance_encode(NTC_Device_get_resistance(NTC_Radiator_Left1));
        msgs.sens_rear_ntc.ntc_4_resistance = mcb_sens_rear_ntc_ntc_4_resistance_encode(NTC_Device_get_resistance(NTC_Radiator_Left2));
        msgs.sens_rear_ntc.ntc_5_resistance = mcb_sens_rear_ntc_ntc_5_resistance_encode(NTC_Device_get_resistance(NTC_Radiator_Right1));
        msgs.sens_rear_ntc.ntc_6_resistance = mcb_sens_rear_ntc_ntc_6_resistance_encode(NTC_Device_get_resistance(NTC_Radiator_Right2));

        tx_header.DLC = mcb_sens_rear_ntc_pack(buffer, &msgs.sens_rear_ntc, MCB_SENS_REAR_NTC_LENGTH);
        break;
    case MCB_SENS_REAR_SHUTDOWN_STATUS_FRAME_ID:
        msgs.sens_rear_sd_status.is_bsp_din_error = mcb_sens_rear_shutdown_status_is_bsp_din_error_encode(BSPD_DEV_IS_IN_ERR());
        msgs.sens_rear_sd_status.is_shut_closed_post_bspd = mcb_sens_rear_shutdown_status_is_shut_closed_post_bspd_encode(SDC_Feedback_get_status(SDC_Post_BSPD));
        msgs.sens_rear_sd_status.is_shut_closed_post_inv_fr = mcb_sens_rear_shutdown_status_is_shut_closed_post_inv_fr_encode(SDC_Feedback_get_status(SDC_Post_InverterFrontRightMotorInterlock));
        msgs.sens_rear_sd_status.is_shut_closed_post_inv_mono = mcb_sens_rear_shutdown_status_is_shut_closed_post_inv_mono_encode(SDC_Feedback_get_status(SDC_Post_InverterDCBUSInterlock));
        msgs.sens_rear_sd_status.is_shut_closed_pre_funghi = mcb_sens_rear_shutdown_status_is_shut_closed_pre_funghi_encode(SDC_Feedback_get_status(SDC_Pre_MainHoopLeftPushButton));

        tx_header.DLC = mcb_sens_rear_shutdown_status_pack(buffer, &msgs.sens_rear_sd_status, MCB_SENS_REAR_SHUTDOWN_STATUS_LENGTH);
        break;
    case MCB_SENS_FRONT_HELO_FRAME_ID:
    //case MCB_SB_FRONT_HELO:
          msgs.sens_front_helo.time = mcb_sens_front_helo_time_encode(HAL_GetTick());
    //    msgs.sb_front_helo.major= mcb_sb_front_helo_major_encode(VERSION_MAJOR);
    //    msgs.sb_front_helo.minor= mcb_sb_front_helo_minor_encode(VERSION_MINOR);
    //    msgs.sb_front_helo.patch= mcb_sb_front_helo_patch_encode(VERSION_PATCH);

    //    tx_header.DLC = mcb_sb_front_helo_pack(buffer, &msgs.sb_front_helo, MCB_SB_front_HELO_LENGTH);
    //    break;
    case MCB_SENS_REAR_HELO_FRAME_ID:
    //case MCB_SB_REAR_HELO:
          msgs.sens_rear_helo.time = mcb_sens_rear_helo_time_encode(HAL_GetTick());
    //    msgs.sb_rear_helo.major= mcb_sb_rear_helo_major_encode(VERSION_MAJOR);
    //    msgs.sb_rear_helo.minor= mcb_sb_rear_helo_minor_encode(VERSION_MINOR);
    //    msgs.sb_rear_helo.patch= mcb_sb_rear_helo_patch_encode(VERSION_PATCH);

    //    tx_header.DLC = mcb_sb_rear_helo_pack(buffer, &msgs.sb_rear_helo, MCB_SB_REAR_HELO_LENGTH);
    //    break;
        tx_header.DLC = mcb_sens_rear_helo_pack(buffer, &msgs.sens_rear_helo, MCB_SENS_REAR_HELO_FRAME_ID);
        break;
    default:
        return;
    }
    
    can_send(&hcan1, buffer, &tx_header);
}

void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan) {
    logger_log(LOGGER_ERROR, "sborato");
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    CAN_RxHeaderTypeDef rx_header;
    uint8_t buffer[8] = {0};

    if(HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, buffer) == HAL_OK) {
        // Reset when preparing for flash via CAN bus
        if(rx_header.StdId == 0xa + SENS_GET_TYPE() && buffer[0] == 0xff && buffer[1] == 0x00) {
            NVIC_SystemReset();
        }
        else if (rx_header.StdId == MCB_D_SPACE_PERIPHERALS_CTRL_FRAME_ID){
            struct mcb_d_space_peripherals_ctrl_t periph;
            mcb_d_space_peripherals_ctrl_unpack(&periph, buffer, MCB_D_SPACE_PERIPHERALS_CTRL_LENGTH);

             if(periph.brake_light_on_ctrl){
                BRAKE_LIGHT_ON();
            }else{
                BRAKE_LIGHT_OFF();
            }

        }
    }
}
