#include "flexSensor.h"
#include <stdio.h>
flexSensor::flexSensor(ADC_HandleTypeDef* hadc1):curr_resistance(0){}

int flexSensor::setResistance(uint16_t adc_val){

	//curr_resistance = ((3.3*adc_val/65536)/(INPUT_VOLTAGE * CURRENT_LIMIT_RESISTANCE)) - CURRENT_LIMIT_RESISTANCE;
	curr_resistance = ((INPUT_VOLTAGE * CURRENT_LIMIT_RESISTANCE)/(3.3*adc_val/256)) - CURRENT_LIMIT_RESISTANCE;

	return 0;
}


float flexSensor::getResistance(){
	return curr_resistance;
}


uint16_t flexSensor::getResistanceAndScale(){
	return (curr_resistance-FLEX_SENSOR_FLAT_RESISTANCE)/150;
}
