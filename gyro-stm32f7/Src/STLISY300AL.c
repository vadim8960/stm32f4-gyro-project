#include "STLISY300AL.h"

void STLISY300AL_Init(Lisy300al *gyro, ADC_HandleTypeDef *adc, uint32_t sensitivity){
	gyro->zero_angle = .0f;
	for (uint16_t _iter = 0; _iter < 100; ++_iter) {
		HAL_ADC_Start(adc);
		HAL_ADC_PollForConversion(adc, 100);
		gyro->zero_angle += HAL_ADC_GetValue(adc);
		HAL_ADC_Stop(adc);
		HAL_Delay(10);
	}
	gyro->zero_angle /= 100.0f;
	gyro->curr_angle = .0f;
	gyro->last_angle = .0f;
	gyro->last_time = 0;
	gyro->last_time = 0;
	gyro->sensitivity = sensitivity;
}

float STLISY300AL_GetAngle(Lisy300al *gyro) {
	return gyro->curr_angle;
}

void STLISY300AL_ClearData(Lisy300al *gyro) {
	gyro->curr_angle = gyro->last_angle = .0f;
}

void STLISY300AL_Handler(Lisy300al *gyro, ADC_HandleTypeDef *adc) {
	HAL_ADC_Start(adc);
	HAL_ADC_PollForConversion(adc, 100);
	uint16_t data = HAL_ADC_GetValue(adc);
	HAL_ADC_Stop(adc);

	int32_t change = (my_abs(data - (uint32_t)(gyro->zero_angle)) > gyro->sensitivity) ? data - gyro->zero_angle : 0 ;

	gyro->last_time = gyro->curr_time;
	gyro->curr_time = HAL_GetTick();
	float dt = ( (float)(gyro->curr_time) - (float)(gyro->last_time) ) / 1000.0f;

	gyro->curr_angle += (change * dt * ANALOG_SENSITIVITY / GYRO_SENSITIVITY);
	if (gyro->curr_angle > 360.0f) gyro->curr_angle -= 360.0f;
	if (gyro->curr_angle < .0f)    gyro->curr_angle += 360.0f;
}

static uint32_t my_abs(int32_t data) {
	if (data < 0)
		return -data;
	return data;
}
