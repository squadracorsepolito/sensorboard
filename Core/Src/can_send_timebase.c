#include "can_send_timebase.h"
#include "can_utils.h"
//#include "utils.h"
#include "bsp.h"

TIMEBASE_HandleTypeDef can_send_timebase_handle;

STMLIBS_StatusTypeDef front_analog_cb(void)
{
    can_send_msg(MCB_SB_FRONT_ANALOG_DEVICE_FRAME_ID);
    return STMLIBS_OK;
}

STMLIBS_StatusTypeDef front_pot_cb(void)
{
    can_send_msg(MCB_SB_FRONT_POTENTIOMETER_FRAME_ID);
    return STMLIBS_OK;
}

STMLIBS_StatusTypeDef front_ntc_cb(void)
{
    can_send_msg(MCB_SB_FRONT_NTC_RESISTANCE_FRAME_ID);
    return STMLIBS_OK;
}

STMLIBS_StatusTypeDef front_sd_status_cb(void)
{
    can_send_msg(MCB_SB_FRONT_SD_CSENSING_STATUS_FRAME_ID);
    return STMLIBS_OK;
}

STMLIBS_StatusTypeDef rear_analog_cb(void)
{
    can_send_msg(MCB_SB_REAR_ANALOG_DEVICE_FRAME_ID);
    return STMLIBS_OK;
}

STMLIBS_StatusTypeDef rear_pot_cb(void)
{
    can_send_msg(MCB_SB_REAR_POTENTIOMETER_FRAME_ID);
    return STMLIBS_OK;
}

STMLIBS_StatusTypeDef rear_crit_cb(void)
{
    can_send_msg(MCB_SB_REAR_CRITICAL_PERIPHERALS_FRAME_ID);
    return STMLIBS_OK;
}

STMLIBS_StatusTypeDef rear_ntc_cb(void)
{
    can_send_msg(MCB_SB_REAR_NTC_RESISTANCE_FRAME_ID);
    return STMLIBS_OK;
}

STMLIBS_StatusTypeDef rear_sd_status_cb(void)
{
    can_send_msg(MCB_SB_REAR_SD_CSENSING_STATUS_FRAME_ID);
    return STMLIBS_OK;
}

void can_send_timebase_init(void)
{
    uint8_t interval;

    TIMEBASE_init(&can_send_timebase_handle, &CAN_SEND_TIMEBASE_TIM_HANDLE, 10000);

    TIMEBASE_add_interval(&can_send_timebase_handle, 10000, &interval);
    if (SENS_GET_TYPE() == SENS_TYPE_REAR)
    {
        TIMEBASE_register_callback(&can_send_timebase_handle, interval, rear_analog_cb);
        TIMEBASE_register_callback(&can_send_timebase_handle, interval, rear_pot_cb);
        TIMEBASE_register_callback(&can_send_timebase_handle, interval, rear_crit_cb);
        //TIMEBASE_register_callback(&can_send_timebase_handle, interval, rear_3_cb);
        // TIMEBASE_register_callback(&can_send_timebase_handle, interval, rear_ntc_cb);
        TIMEBASE_register_callback(&can_send_timebase_handle, interval, rear_sd_status_cb);
    }
    else
    {
        TIMEBASE_register_callback(&can_send_timebase_handle, interval, front_analog_cb);
        TIMEBASE_register_callback(&can_send_timebase_handle, interval, front_pot_cb);
        //TIMEBASE_register_callback(&can_send_timebase_handle, interval, front_3_cb);
        // TIMEBASE_register_callback(&can_send_timebase_handle, interval, front_ntc_cb);
        TIMEBASE_register_callback(&can_send_timebase_handle, interval, front_sd_status_cb);
    }
}

void can_send_timebase_routine(void)
{
    TIMEBASE_routine(&can_send_timebase_handle);
}

void can_send_timebase_timerElapsed_irq(TIM_HandleTypeDef *htim)
{
    TIMEBASE_TimerElapsedCallback(&can_send_timebase_handle, htim);
}
