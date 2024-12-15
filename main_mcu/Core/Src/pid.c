/*
 * pid.c
 *
 *  Created on: Dec 14, 2024
 *      Author: bala
 */

#include "pid.h"

void pid_init(pid_controller *pid_ctrl, pid_consts consts, state_vars initial_state)
{
    pid_ctrl->consts = consts;
    pid_ctrl->prev_measurements = initial_state;
}

void pid_update(pid_controller *pid_ctrl, state_vars updated_target)
{
    pid_ctrl->target = updated_target;
}

float pid_calculate(pid_controller *pid_ctrl, float measurement, float target)
{
    float error = target - measurement;
    
    int dt = HAL_GetTick() - pid_ctrl->time_prev;

    float error_diff = (error - pid_ctrl->error_prev)/dt;

    pid_ctrl->error_sum += error;

    float pid_res = pid_ctrl->consts.kp * error + pid_ctrl->consts.kd * error_diff + pid_ctrl->consts.ki * pid_ctrl->error_sum;

    return pid_res;
}