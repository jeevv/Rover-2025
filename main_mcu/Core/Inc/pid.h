/*
 * pid.h
 *
 *  Created on: Dec 14, 2024
 *      Author: bala
 */

#ifndef INC_PID_H_
#define INC_PID_H_

#define IMU_CONTROL

#include "stm32f4xx.h"

typedef struct state_vars
{
    float x,y,z;
}state_vars;

/*
typedef struct state_vars
{
    xyz linear, angular;
}state_vars;
*/

typedef struct pid_consts
{
    float kp, kd, ki;
}pid_consts;

typedef struct pid_controller
{
    pid_consts consts;
    state_vars prev_measurements, target;
    float error_prev, error_sum;
    int time_prev;

}pid_controller;

void pid_init(pid_controller *, pid_consts, state_vars);

void pid_update(pid_controller *, state_vars);

float pid_calculate(pid_controller *, float, float);

#endif /* INC_PID_H_ */
