#include "can_send_timebase.h"
#include "can_utils.h"
#include "utils.h"

TIMEBASE_HandleTypeDef can_send_timebase_handle;

STMLIBS_StatusTypeDef front_1_cb(void)
{
    can_send_msg(MCB_SENS_FRONT_1_FRAME_ID);
    return STMLIBS_OK;
}

STMLIBS_StatusTypeDef front_2_cb(void)
{
    can_send_msg(MCB_SENS_FRONT_2_FRAME_ID);
    return STMLIBS_OK;
}

STMLIBS_StatusTypeDef front_3_cb(void)
{
    can_send_msg(MCB_SENS_FRONT_3_FRAME_ID);
    return STMLIBS_OK;
}

STMLIBS_StatusTypeDef front_ntc_cb(void)
{
    can_send_msg(MCB_SENS_FRONT_NTC_FRAME_ID);
    return STMLIBS_OK;
}

STMLIBS_StatusTypeDef front_sd_status_cb(void)
{
    can_send_msg(MCB_SENS_FRONT_SHUTDOWN_STATUS_FRAME_ID);
    return STMLIBS_OK;
}

STMLIBS_StatusTypeDef rear_1_cb(void)
{
    can_send_msg(MCB_SENS_REAR_1_FRAME_ID);
    return STMLIBS_OK;
}

STMLIBS_StatusTypeDef rear_2_cb(void)
{
    can_send_msg(MCB_SENS_REAR_2_FRAME_ID);
    return STMLIBS_OK;
}

STMLIBS_StatusTypeDef rear_3_cb(void)
{
    can_send_msg(MCB_SENS_REAR_3_FRAME_ID);
    return STMLIBS_OK;
}

STMLIBS_StatusTypeDef rear_ntc_cb(void)
{
    can_send_msg(MCB_SENS_REAR_NTC_FRAME_ID);
    return STMLIBS_OK;
}

STMLIBS_StatusTypeDef rear_sd_status_cb(void)
{
    can_send_msg(MCB_SENS_REAR_SHUTDOWN_STATUS_FRAME_ID);
    return STMLIBS_OK;
}

void can_send_timebase_init(void)
{
    uint8_t interval;

    TIMEBASE_init(&can_send_timebase_handle, &CAN_SEND_TIMEBASE_TIM_HANDLE, 10000);

    TIMEBASE_add_interval(&can_send_timebase_handle, 10000, &interval);
    if (UTILS_GET_SENS_TYPE() == SENSE_TYPE_REAR)
    {
        TIMEBASE_register_callback(&can_send_timebase_handle, interval, rear_1_cb);
        TIMEBASE_register_callback(&can_send_timebase_handle, interval, rear_2_cb);
        TIMEBASE_register_callback(&can_send_timebase_handle, interval, rear_3_cb);
        TIMEBASE_register_callback(&can_send_timebase_handle, interval, rear_ntc_cb);
        TIMEBASE_register_callback(&can_send_timebase_handle, interval, rear_sd_status_cb);
    }
    else
    {
        TIMEBASE_register_callback(&can_send_timebase_handle, interval, front_1_cb);
        TIMEBASE_register_callback(&can_send_timebase_handle, interval, front_2_cb);
        TIMEBASE_register_callback(&can_send_timebase_handle, interval, front_3_cb);
        TIMEBASE_register_callback(&can_send_timebase_handle, interval, front_ntc_cb);
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
