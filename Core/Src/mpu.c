/*
 * mpu.c
 *
 *  Created on: Dec 1, 2024
 *      Author: bala
 */
#include "mpu.h"

void mpu_init(mpu_struct *mpu, I2C_HandleTypeDef *hi2c)
{
	mpu->hi2c = hi2c;

	uint8_t tx_data;
	uint8_t rx_data;


	HAL_I2C_Mem_Read (hi2c, MPU6050_ADDR,WHO_AM_I_REG,1, &rx_data, 1, 1000);

	if (rx_data == 0x68)  // 0x68 will be returned by the sensor if everything goes well
	{
		mpu->status = 1;
		// power management register 0X6B we should write all 0's to wake the sensor up
		tx_data = 0;
		HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, PWR_MGMT_1_REG, 1,&tx_data, 1, 1000);

		// Set tx_data RATE of 1KHz by writing SMPLRT_DIV register
		tx_data = 0x07;
		HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &tx_data, 1, 1000);

		// Set accelerometer configuration in ACCEL_CONFIG Register
		// XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 ->   2g
		tx_data = 0x00;
		HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &tx_data, 1, 1000);

		// Set Gyroscopic configuration in GYRO_CONFIG Register
		// XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 ->   250  /s
		tx_data = 0x00;
		HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &tx_data, 1, 1000);
	}

	else
	{
		mpu->status = 0;
	}


}

void mpu_read_raw(mpu_struct *mpu)
{
	uint8_t tx_data[6];

	// Read 6 BYTES of tx_data starting from ACCEL_XOUT_H register

	HAL_I2C_Mem_Read (mpu->hi2c, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, tx_data, 6, 1000);

	mpu->ax_raw = (uint16_t)(tx_data[0] << 8 | tx_data [1]);
	mpu->ay_raw = (uint16_t)(tx_data[2] << 8 | tx_data [3]);
	mpu->az_raw = (uint16_t)(tx_data[4] << 8 | tx_data [5]);


		// Read 6 BYTES of tx_data starting from GYRO_XOUT_H register

	HAL_I2C_Mem_Read (mpu->hi2c, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, tx_data, 6, 1000);

	mpu->gx_raw = (uint16_t)(tx_data[0] << 8 | tx_data [1]);
	mpu->gy_raw = (uint16_t)(tx_data[2] << 8 | tx_data [3]);
	mpu->gz_raw = (uint16_t)(tx_data[4] << 8 | tx_data [5]);

}

void mpu_scale(mpu_struct *mpu)
{
	mpu->ax = (mpu->ax_raw * 9.81) / 16384.0;
	mpu->ay = (mpu->ay_raw * 9.81) / 16384.0;
	mpu->az = (mpu->az_raw * 9.81) / 16384.0;

	mpu->gx = (mpu->gx_raw * 0.0174) / 131.0;
	mpu->gy = (mpu->gy_raw * 0.0174) / 131.0;
	mpu->gz = (mpu->gz_raw * 0.0174) / 131.0;

}

void mpu_read(mpu_struct *mpu)
{
	uint8_t tx_data[6];

	// Read 6 BYTES of tx_data starting from ACCEL_XOUT_H register

	HAL_I2C_Mem_Read (mpu->hi2c, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, tx_data, 6, 1000);

	mpu->ax_raw = (uint16_t)(tx_data[0] << 8 | tx_data [1]);
	mpu->ay_raw = (uint16_t)(tx_data[2] << 8 | tx_data [3]);
	mpu->az_raw = (uint16_t)(tx_data[4] << 8 | tx_data [5]);

			/*** convert the RAW values into acceleration in 'g'
			     we have to divide according to the Full scale value set in FS_SEL
			     I have configured FS_SEL = 0. So I am dividing by 16384.0
			     for more details check ACCEL_CONFIG Register              ****/

	mpu->ax = (mpu->ax_raw * 9.81) / 16384.0;
	mpu->ay = (mpu->ay_raw * 9.81) / 16384.0;
	mpu->az = (mpu->az_raw * 9.81) / 16384.0;


		// Read 6 BYTES of tx_data starting from GYRO_XOUT_H register

	HAL_I2C_Mem_Read (mpu->hi2c, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, tx_data, 6, 1000);

	mpu->gx_raw = (uint16_t)(tx_data[0] << 8 | tx_data [1]);
	mpu->gy_raw = (uint16_t)(tx_data[2] << 8 | tx_data [3]);
	mpu->gz_raw = (uint16_t)(tx_data[4] << 8 | tx_data [5]);

			/* convert the RAW values into dps ( /s)
			     we have to divide according to the Full scale value set in FS_SEL
			     I have configured FS_SEL = 0. So I am dividing by 131.0
			     for more details check GYRO_CONFIG Register              **/

	mpu->gx = (mpu->gx_raw * 0.0174) / 131.0;
	mpu->gy = (mpu->gy_raw * 0.0174) / 131.0;
	mpu->gz = (mpu->gz_raw * 0.0174) / 131.0;
}

