#include "flexSensor.h"

flexSensor::flexSensor(ADC_HandleTypeDef* hadc1):curr_resistance(0){}

int flexSensor::setResistance(uint16_t adc_val){
	curr_resistance = ((INPUT_VOLTAGE * CURRENT_LIMIT_RESISTANCE)/(65536.0*adc_val/3.3)) - CURRENT_LIMIT_RESISTANCE;
	return 0;
}


float flexSensor::getResistance(){
	return curr_resistance;
}


int flexSensor::getResistanceAndScale(){
	return (curr_resistance-FLEX_SENSOR_FLAT_RESISTANCE)/80;
}
