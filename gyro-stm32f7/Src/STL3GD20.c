#include "STL3GD20.h"

static void writeRegister(I2C_HandleTypeDef *hi2c, uint8_t device_addr, uint8_t addr, uint8_t value) {

}

static int32_t readRegister(I2C_HandleTypeDef *hi2c, uint8_t device_addr, uint8_t addr) {

}

void STL3GD20_Init(L3gd20 *gyro, I2C_HandleTypeDef hi2c, uint16_t scale) {
	gyro->device_addr = 0x6B;
	gyro->hi2c = hi2c;
	writeRegister(&(gyro->device_addr), gyro->device_addr, CTRL_REG1, 0b00001111);
	writeRegister(&(gyro->device_addr), gyro->device_addr, CTRL_REG2, 0b00000000);
	writeRegister(&(gyro->device_addr), gyro->device_addr, CTRL_REG3, 0b00001000);
	if (scale == 250)
		writeRegister(&(gyro->device_addr), gyro->device_addr, CTRL_REG4, 0b00000000);
	else if (scale == 500)
		writeRegister(&(gyro->device_addr), gyro->device_addr, CTRL_REG4, 0b00010000);
	else
		writeRegister(&(gyro->device_addr), gyro->device_addr, CTRL_REG4, 0b00110000);
	writeRegister(&(gyro->device_addr), gyro->device_addr, CTRL_REG4, 0b00000000);
}

int32_t STL3GD20_GetX(L3gd20 *gyro) {
	uint8_t MSB = readRegister(&(gyro->hi2c), gyro->device_addr, 0x29);
	uint8_t LSB = readRegister(&(gyro->hi2c), gyro->device_addr, 0x28);
	gyro->x_angle = ((MSB << 8) | LSB);
	return gyro->x_angle;
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


