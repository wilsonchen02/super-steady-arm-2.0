#ifndef INC_FLEXSENSOR_H_
#define INC_FLEXSENSOR_H_


#include "stm32l4xx_hal.h"


#define FLEX_SENSOR_MIN_RESISTANCE 25000
#define CURRENT_LIMIT_RESISTANCE 47000
#define INPUT_VOLTAGE 5


#define FLEX_SENSOR_FLAT_RESISTANCE 75000

// The flex sensor should have it's own timer and that should start the ADC conversion
// the getResitance() and getResistanceAndScale() functions should only return values from the buffer
//

class flexSensor{
private:
	float curr_resistance;
	const int& clamp(const int& v, const int& lo, const int& hi);

public:
	flexSensor(ADC_HandleTypeDef* hadc1);
	float getResistance();
	uint16_t getResistanceAndScale();
	int setResistance(uint16_t adc_val);


};

#endif /* INC_FLEXSENSOR_H_ */
