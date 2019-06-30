#include "STLISY300AL.h"

void Init_Lisy300al(Lisy300al *gyro, ADC_HandleTypeDef *adc) {
	gyro->curr_position = .0f;
	gyro->zero_position = 0;
	for (uint8_t iter = 0; iter < 10; ++iter) {
		HAL_ADC_Start(adc);
		HAL_ADC_PollForConversion(adc, 100);
		gyro->zero_position += HAL_ADC_GetValue(adc);
		HAL_ADC_Stop(adc);
		HAL_Delay(10);
	}
	gyro->zero_position /= 10;
}

float make_cardinal(float position) {
	if (position > 360.0f)
		return position - 360.0f;
	if (position < .0f)
		return position + 360.0f;
	return position;
}

float get_position(Lisy300al *gyro, ADC_HandleTypeDef *adc) {
	uint16_t change = 0;
	uint64_t last_time = HAL_GetTick();
	HAL_ADC_Start(adc);
	HAL_ADC_PollForConversion(adc, 100);
	uint32_t gyro_x = HAL_ADC_GetValue(adc);
	HAL_ADC_Stop(adc);
	if (fabs(gyro_x - gyro->zero_position) > 3)
		change = gyro_x - gyro->zero_position;
	float time = ( (float)(HAL_GetTick()) - (float)(last_time) ) / 100.0;
	float dt = change * time * ANALOG_SENSETIVITY / GYRO_SENSETIVITY;
	gyro->curr_position += dt;
	gyro->curr_position = make_cardinal(gyro->curr_position);
	return gyro->curr_position;
}

void clear_position(Lisy300al *gyro) {
	gyro->curr_position = .0f;
}
