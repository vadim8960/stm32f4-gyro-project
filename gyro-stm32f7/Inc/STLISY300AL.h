#ifndef __STLISY300AL_H__
#define __STLISY300AL_H__

#include "math.h"
#include "stm32f7xx_hal.h"

#define GYRO_SENSETIVITY   0.0033
#define ANALOG_SENSETIVITY 0.0008

extern UART_HandleTypeDef huart3;

typedef struct{
	float curr_angle,
	      last_angle;
	int32_t zero_angle,
	        sens;
	uint32_t curr_time,
	         last_time;
} Lisy300al;

void STLISY300AL_Init(Lisy300al*, ADC_HandleTypeDef*, uint32_t);
float STLISY300AL_GetAngle(Lisy300al*);
void STLISY300AL_ClearData(Lisy300al*);
void STLISY300AL_Handler(Lisy300al*, ADC_HandleTypeDef*);

static uint32_t my_abs(int32_t);

#endif /*__STLISY300AL_H__*/
