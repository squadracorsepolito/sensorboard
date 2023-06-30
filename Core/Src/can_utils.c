#include "can_utils.h"
#include "anal.h"
#include "logger_wrapper.h"
#include "utils.h"
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
    filter.FilterIdLow      = (0xa + UTILS_GET_SENS_TYPE()) << 5;                 // Take all ids from 0
    filter.FilterIdHigh     = (0xa + UTILS_GET_SENS_TYPE()) << 5;  // to 2^11 - 1
    filter.FilterMaskIdHigh = (0xa + UTILS_GET_SENS_TYPE()) << 5;                 // Don't care on can id bits
    filter.FilterMaskIdLow  = (0xa + UTILS_GET_SENS_TYPE()) << 5;                 // Don't care on can id bits
    /* HAL considers IdLow and IdHigh not as just the ID of the can message but
        as the combination of: 
        STDID + RTR + IDE + 4 most significant bits of EXTID
    */
    filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    filter.FilterBank           = 0;
    filter.FilterScale          = CAN_FILTERSCALE_16BIT;
    filter.FilterActivation     = ENABLE;

    HAL_CAN_ConfigFilter(&hcan1, &filter);

    filter.FilterMode       = CAN_FILTERMODE_IDMASK;
    filter.FilterIdLow      = SC22_EVO_CANLV_D_SPACE_PERIPHERALS_CTRL_FRAME_ID << 5;                 // Take all ids from 0
    filter.FilterIdHigh     = SC22_EVO_CANLV_D_SPACE_PERIPHERALS_CTRL_FRAME_ID << 5;  // to 2^11 - 1
    filter.FilterMaskIdHigh = SC22_EVO_CANLV_D_SPACE_PERIPHERALS_CTRL_FRAME_ID << 5;                 // Don't care on can id bits
    filter.FilterMaskIdLow  = SC22_EVO_CANLV_D_SPACE_PERIPHERALS_CTRL_FRAME_ID << 5;                 // Don't care on can id bits
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
        struct sc22_evo_canlv_sens_front_1_t sens_front_1;
        struct sc22_evo_canlv_sens_front_2_t sens_front_2;
        struct sc22_evo_canlv_sens_front_3_t sens_front_3;
        struct sc22_evo_canlv_sens_front_ntc_t sens_front_ntc;
        struct sc22_evo_canlv_sens_front_shutdown_status_t sens_front_sd_status;

        struct sc22_evo_canlv_sens_rear_1_t sens_rear_1;
        struct sc22_evo_canlv_sens_rear_2_t sens_rear_2;
        struct sc22_evo_canlv_sens_rear_3_t sens_rear_3;
        struct sc22_evo_canlv_sens_rear_ntc_t sens_rear_ntc;
        struct sc22_evo_canlv_sens_rear_shutdown_status_t sens_rear_sd_status;
    } msgs;

    tx_header.StdId = id;

    switch (id)
    {
    case SC22_EVO_CANLV_SENS_FRONT_1_FRAME_ID:
        msgs.sens_front_1.brake_straingauge_voltage_m_v = sc22_evo_canlv_sens_front_1_brake_straingauge_voltage_m_v_encode(anal_get_pin_mv(ANAL8));
        msgs.sens_front_1.steering_voltage_m_v = sc22_evo_canlv_sens_front_1_steering_voltage_m_v_encode(anal_get_pin_mv(ANAL5));
        msgs.sens_front_1.throttle_0_voltage_m_v = sc22_evo_canlv_sens_front_1_throttle_0_voltage_m_v_encode(anal_get_pin_mv(ANAL6));
        msgs.sens_front_1.throttle_1_voltage_m_v = sc22_evo_canlv_sens_front_1_throttle_1_voltage_m_v_encode(anal_get_pin_mv(ANAL9));

        tx_header.DLC = sc22_evo_canlv_sens_front_1_pack(buffer, &msgs.sens_front_1, SC22_EVO_CANLV_SENS_FRONT_1_LENGTH);
        can_send(&hcan1, buffer, &tx_header);
        break;
    case SC22_EVO_CANLV_SENS_FRONT_2_FRAME_ID:
        msgs.sens_front_2.brake_pressure_voltage_m_v = sc22_evo_canlv_sens_front_2_brake_pressure_voltage_m_v_encode(anal_get_pin_mv(ANAL7));
        msgs.sens_front_2.pot_fl_voltage_m_v = sc22_evo_canlv_sens_front_2_pot_fl_voltage_m_v_encode(anal_get_pin_mv(POT1));
        msgs.sens_front_2.pot_fr_voltage_m_v = sc22_evo_canlv_sens_front_2_pot_fr_voltage_m_v_encode(anal_get_pin_mv(POT2));

        tx_header.DLC = sc22_evo_canlv_sens_front_2_pack(buffer, &msgs.sens_front_2, SC22_EVO_CANLV_SENS_FRONT_2_LENGTH);
        can_send(&hcan1, buffer, &tx_header);
        break;
    case SC22_EVO_CANLV_SENS_FRONT_3_FRAME_ID:
        msgs.sens_front_3.straingauge_push_fl_voltage_m_v = sc22_evo_canlv_sens_front_3_straingauge_push_fl_voltage_m_v_encode(anal_get_pin_mv(ANAL2));
        msgs.sens_front_3.straingauge_push_fr_voltage_m_v = sc22_evo_canlv_sens_front_3_straingauge_push_fr_voltage_m_v_encode(anal_get_pin_mv(ANAL3));
        msgs.sens_front_3.straingauge_tie_fl_voltage_m_v =  sc22_evo_canlv_sens_front_3_straingauge_tie_fl_voltage_m_v_encode(anal_get_pin_mv(ANAL4));
        msgs.sens_front_3.straingauge_tie_fr_voltage_m_v =  sc22_evo_canlv_sens_front_3_straingauge_tie_fr_voltage_m_v_encode(anal_get_pin_mv(ANAL1));

        tx_header.DLC = sc22_evo_canlv_sens_front_3_pack(buffer, &msgs.sens_front_3, SC22_EVO_CANLV_SENS_FRONT_3_LENGTH);
        can_send(&hcan1, buffer, &tx_header);
        break;
    case SC22_EVO_CANLV_SENS_FRONT_NTC_FRAME_ID:
        break;
    case SC22_EVO_CANLV_SENS_FRONT_SHUTDOWN_STATUS_FRAME_ID:
        msgs.sens_front_sd_status.is_shut_closed_post_bots = sc22_evo_canlv_sens_front_shutdown_status_is_shut_closed_post_bots_encode(gpio_sens_get(SD_SENS3));
        msgs.sens_front_sd_status.is_shut_closed_post_cockpit = sc22_evo_canlv_sens_front_shutdown_status_is_shut_closed_post_cockpit_encode(gpio_sens_get(SD_SENS4));
        msgs.sens_front_sd_status.is_shut_closed_post_inertia = sc22_evo_canlv_sens_front_shutdown_status_is_shut_closed_post_inertia_encode(gpio_sens_get(SD_SENS2));
        msgs.sens_front_sd_status.is_shut_closed_pre_inertia = sc22_evo_canlv_sens_front_shutdown_status_is_shut_closed_pre_inertia_encode(gpio_sens_get(SD_SENS1));

        tx_header.DLC = sc22_evo_canlv_sens_front_shutdown_status_pack(buffer, &msgs.sens_front_sd_status, SC22_EVO_CANLV_SENS_FRONT_SHUTDOWN_STATUS_LENGTH);
        can_send(&hcan1, buffer, &tx_header);
        break;

    case SC22_EVO_CANLV_SENS_REAR_1_FRAME_ID:
        msgs.sens_rear_1.brake_pressure_rear_voltage_m_v = sc22_evo_canlv_sens_rear_1_brake_pressure_rear_voltage_m_v_encode(anal_get_pin_mv(ANAL10));
        msgs.sens_rear_1.pot_rl_voltage_m_v = sc22_evo_canlv_sens_rear_1_pot_rl_voltage_m_v_encode(anal_get_pin_mv(POT2));
        msgs.sens_rear_1.pot_rr_voltage_rr = sc22_evo_canlv_sens_rear_1_pot_rr_voltage_rr_encode(anal_get_pin_mv(POT1));

        tx_header.DLC = sc22_evo_canlv_sens_rear_1_pack(buffer, &msgs.sens_rear_1, SC22_EVO_CANLV_SENS_REAR_1_LENGTH);
        can_send(&hcan1, buffer, &tx_header);
        break;
    case SC22_EVO_CANLV_SENS_REAR_2_FRAME_ID:
        msgs.sens_rear_2.cooling_pressure_dx_voltage_m_v = sc22_evo_canlv_sens_rear_2_cooling_pressure_dx_voltage_m_v_encode(anal_get_pin_mv(ANAL11));
        msgs.sens_rear_2.cooling_pressure_sx_voltage_m_v = sc22_evo_canlv_sens_rear_2_cooling_pressure_sx_voltage_m_v_encode(anal_get_pin_mv(ANAL7));

        tx_header.DLC = sc22_evo_canlv_sens_rear_2_pack(buffer, &msgs.sens_rear_2, SC22_EVO_CANLV_SENS_REAR_2_LENGTH);
        can_send(&hcan1, buffer, &tx_header);
        break;
    case SC22_EVO_CANLV_SENS_REAR_3_FRAME_ID:
        msgs.sens_rear_3.straingauge_push_rl_voltage_m_v = sc22_evo_canlv_sens_rear_3_straingauge_push_rl_voltage_m_v_encode(anal_get_pin_mv(ANAL1));
        msgs.sens_rear_3.straingauge_push_rr_voltage_m_v = sc22_evo_canlv_sens_rear_3_straingauge_push_rr_voltage_m_v_encode(anal_get_pin_mv(ANAL4));
        msgs.sens_rear_3.straingauge_tie_rl_voltage_m_v = sc22_evo_canlv_sens_rear_3_straingauge_tie_rl_voltage_m_v_encode(anal_get_pin_mv(ANAL3));
        msgs.sens_rear_3.straingauge_tie_rr_voltage_m_v = sc22_evo_canlv_sens_rear_3_straingauge_tie_rr_voltage_m_v_encode(anal_get_pin_mv(ANAL2));

        tx_header.DLC = sc22_evo_canlv_sens_rear_2_pack(buffer, &msgs.sens_rear_2, SC22_EVO_CANLV_SENS_REAR_2_LENGTH);
        can_send(&hcan1, buffer, &tx_header);
        break;
    case SC22_EVO_CANLV_SENS_REAR_NTC_FRAME_ID:
        break;
    case SC22_EVO_CANLV_SENS_REAR_SHUTDOWN_STATUS_FRAME_ID:
        msgs.sens_rear_sd_status.is_bsp_din_error = sc22_evo_canlv_sens_rear_shutdown_status_is_bsp_din_error_encode(gpio_sens_get(BSPD_SENS));
        msgs.sens_rear_sd_status.is_shut_closed_post_bspd = sc22_evo_canlv_sens_rear_shutdown_status_is_shut_closed_post_bspd_encode(gpio_sens_get(SD_SENS1));
        msgs.sens_rear_sd_status.is_shut_closed_post_inv_fr = sc22_evo_canlv_sens_rear_shutdown_status_is_shut_closed_post_inv_fr_encode(gpio_sens_get(SD_SENS4));
        msgs.sens_rear_sd_status.is_shut_closed_post_inv_mono = sc22_evo_canlv_sens_rear_shutdown_status_is_shut_closed_post_inv_mono_encode(gpio_sens_get(SD_SENS3));
        msgs.sens_rear_sd_status.is_shut_closed_pre_funghi = sc22_evo_canlv_sens_rear_shutdown_status_is_shut_closed_pre_funghi_encode(gpio_sens_get(SD_SENS2));

        tx_header.DLC = sc22_evo_canlv_sens_rear_shutdown_status_pack(buffer, &msgs.sens_rear_sd_status, SC22_EVO_CANLV_SENS_REAR_SHUTDOWN_STATUS_LENGTH);
        can_send(&hcan1, buffer, &tx_header);
        break;
    default:
        break;
    }
}

void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan) {
    logger_log(LOGGER_ERROR, "sborato");
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    CAN_RxHeaderTypeDef rx_header;
    uint8_t buffer[8] = {0};

    if(HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, buffer) == HAL_OK) {
        if(rx_header.StdId == 0xa + UTILS_GET_SENS_TYPE() && buffer[0] == 0xff && buffer[1] == 0x00) {
            NVIC_SystemReset();
        }
        else if (rx_header.StdId == SC22_EVO_CANLV_D_SPACE_PERIPHERALS_CTRL_FRAME_ID){
            struct sc22_evo_canlv_d_space_peripherals_ctrl_t periph;
            sc22_evo_canlv_d_space_peripherals_ctrl_unpack(&periph, buffer, SC22_EVO_CANLV_D_SPACE_PERIPHERALS_CTRL_LENGTH);

            HAL_GPIO_WritePin(BRK_LGHT_GPIO_OUT_GPIO_Port, BRK_LGHT_GPIO_OUT_Pin, periph.brake_light_on_ctrl ? GPIO_PIN_SET : GPIO_PIN_RESET);
        }
    }
}