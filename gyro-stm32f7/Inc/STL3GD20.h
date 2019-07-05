#ifndef __STL3GD20_H__
#define __STL3GD20_H__

#include "stm32f7xx_hal.h"

#define CTRL_REG1  0x20
#define CTRL_REG2  0x21
#define CTRL_REG3  0x22
#define CTRL_REG4  0x23
#define CTRL_REG5  0x24
#define STATUS_REG 0x27
#define WHO_AM_I   0x0F

typedef struct {
	uint8_t device_addr;
	int32_t x_angle,
			y_angle,
			z_angle;
	I2C_HandleTypeDef hi2c;
} L3gd20;

void STL3GD20_Init(L3gd20*, I2C_HandleTypeDef, uint16_t);
int32_t STL3GD20_GetX(L3gd20*);
int32_t STL3GD20_GetY(L3gd20*);
int32_t STL3GD20_GetZ(L3gd20*);
int32_t STL3GD20_WhoAmI(L3gd20*);
int32_t STL3GD20_Status(L3gd20*);


static void writeRegister(I2C_HandleTypeDef*, uint8_t, uint8_t, uint16_t);
static int16_t readRegister(I2C_HandleTypeDef*, uint8_t, uint8_t);

#endif /*__STL3GD20_H__*/
