#include "STL3GD20.h"

static void writeRegister(I2C_HandleTypeDef *hi2c, uint8_t device_addr, uint8_t addr, uint16_t value) {
	HAL_StatusTypeDef status = HAL_OK;

	status = HAL_I2C_Mem_Write(hi2c, (uint16_t)device_addr, (uint16_t)addr, I2C_MEMADD_SIZE_8BIT, (uint8_t*)(&value), 1, 100);

	if (status != HAL_OK) {

	}
}

static int16_t readRegister(I2C_HandleTypeDef *hi2c, uint8_t device_addr, uint8_t addr) {
	HAL_StatusTypeDef status = HAL_OK;
	uint8_t value = 0;

	status = HAL_I2C_Mem_Read(hi2c, (uint16_t)device_addr, (uint16_t)addr, I2C_MEMADD_SIZE_8BIT, &value, 1, 100);

	if (status != HAL_OK) {
		return -1;
	}

	return value;
}

void STL3GD20_Init(L3gd20 *gyro, I2C_HandleTypeDef hi2c, uint16_t scale) {
	gyro->device_addr = /*0x6B*/0xD4;
	gyro->hi2c = hi2c;
	writeRegister(&(gyro->hi2c), gyro->device_addr, CTRL_REG1, 0b00001111);
	writeRegister(&(gyro->hi2c), gyro->device_addr, CTRL_REG2, 0b00000000);
	writeRegister(&(gyro->hi2c), gyro->device_addr, CTRL_REG3, 0b00001000);
	if (scale == 250)
		writeRegister(&(gyro->hi2c), gyro->device_addr, CTRL_REG4, 0b00000000);
	else if (scale == 500)
		writeRegister(&(gyro->hi2c), gyro->device_addr, CTRL_REG4, 0b00010000);
	else
		writeRegister(&(gyro->hi2c), gyro->device_addr, CTRL_REG4, 0b00110000);
	writeRegister(&(gyro->hi2c), gyro->device_addr, CTRL_REG4, 0b00000000);
}

int32_t STL3GD20_WhoAmI(L3gd20 *gyro) {
	int16_t res = readRegister(&(gyro->hi2c), gyro->device_addr, WHO_AM_I);
	return res;
}

int32_t STL3GD20_Status(L3gd20 *gyro) {
	int16_t res = readRegister(&(gyro->hi2c), gyro->device_addr, STATUS_REG);
	return res;
}

int32_t STL3GD20_GetX(L3gd20 *gyro) {
	int8_t MSB = readRegister(&(gyro->hi2c), gyro->device_addr, 0x29);
	int8_t LSB = readRegister(&(gyro->hi2c), gyro->device_addr, 0x28);
	if (MSB != -1 && LSB != -1) {
		gyro->x_angle = ((MSB << 8) | LSB);
		return gyro->x_angle;
	}
	return -1;
}

int32_t STL3GD20_GetY(L3gd20 *gyro) {
	uint8_t MSB = readRegister(&(gyro->hi2c), gyro->device_addr, 0x2B);
	uint8_t LSB = readRegister(&(gyro->hi2c), gyro->device_addr, 0x2A);
	gyro->y_angle = ((MSB << 8) | LSB);
	return gyro->y_angle;
}

int32_t STL3GD20_GetZ(L3gd20 *gyro) {
	uint8_t MSB = readRegister(&(gyro->hi2c), gyro->device_addr, 0x2D);
	uint8_t LSB = readRegister(&(gyro->hi2c), gyro->device_addr, 0x2C);
	gyro->z_angle = ((MSB << 8) | LSB);
	return gyro->z_angle;
}


