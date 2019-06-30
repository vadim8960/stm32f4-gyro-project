#ifndef __STLISY300AL_H__
#define __STLISY300AL_H__

#include "math.h"
#include "stm32f4xx_hal.h"

#define GYRO_SENSETIVITY   0.0033
#define ANALOG_SENSETIVITY 0.0008

typedef struct{
	uint32_t          zero_position;
	float             curr_position;
}Lisy300al;

void Init_Lisy300al(Lisy300al *gyro, ADC_HandleTypeDef *adc);

float make_cardinal(float position);

float get_position(Lisy300al *gyro, ADC_HandleTypeDef *adc);

void clear_position(Lisy300al *gyro);

#endif /*__STLISY300AL_H__*/
