/*
 * mpu6050.h
 *
 *  Created on: Dec 1, 2024
 *      Author: bala
 */

#ifndef INC_MPU_H_
#define INC_MPU_H_

#include "stm32f4xx.h"
#include "stm32f4xx_hal_i2c.h"

#define MPU6050_ADDR 0xD0

#define SMPLRT_DIV_REG 0x19
#define GYRO_CONFIG_REG 0x1B
#define ACCEL_CONFIG_REG 0x1C
#define ACCEL_XOUT_H_REG 0x3B
#define TEMP_OUT_H_REG 0x41
#define GYRO_XOUT_H_REG 0x43
#define PWR_MGMT_1_REG 0x6B
#define WHO_AM_I_REG 0x75

struct mpu_struct
{
	I2C_HandleTypeDef *hi2c;
	uint8_t status;
	uint16_t ax_raw, ay_raw, az_raw, gx_raw, gy_raw, gz_raw;
	double ax, ay, az, gx, gy, gz;
};

typedef struct mpu_struct mpu_struct;

void mpu_init(mpu_struct *, I2C_HandleTypeDef *);
void mpu_read_raw(mpu_struct *);
void mpu_scale(mpu_struct *);
void mpu_read(mpu_struct *);

#endif /* INC_MPU_H_ */
