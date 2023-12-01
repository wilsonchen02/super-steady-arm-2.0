#ifndef SRC_HUMANARM_H_
#define SRC_HUMANARM_H_

#include "IMU.h"
#include "encoder.h"
#include "xbee.h"
#include "flexSensor.h"
#include <memory>

struct __attribute__ ((__packed__)) SensorData {
	int gripper;
	int wrist_roll;
	int wrist_pitch;
	int elbow;
	int shoulder_pitch; // controlled directly by pitch
	int shoulder_yaw;// joint A is controlled by a combination of roll and yaw
};

class HumanArm {
public:
	HumanArm(I2C_HandleTypeDef* I2C_handle, TIM_TypeDef* TIM_handle, UART_HandleTypeDef* UART_handle, ADC_HandleTypeDef* hadc1)
		: I2C_handle{I2C_handle}
		, TIM_handle{TIM_handle}
		, UART_handle{UART_handle}
		, ADC_handle{ADC_handle}
		{};
	int init();
	int spin();
	int setFlexSensorResistance(uint16_t adc_val);


private:
	std::unique_ptr<IMU> wrist_IMU;
	std::unique_ptr<IMU> shoulder_IMU;
	std::unique_ptr<Encoder> elbow_encoder;
	std::unique_ptr<flexSensor> flex_sensor;

	I2C_HandleTypeDef* I2C_handle;
	TIM_TypeDef* TIM_handle;
	UART_HandleTypeDef * UART_handle;
	ADC_HandleTypeDef* ADC_handle;

	int pack_message(std::vector<float> wrist_configuration, float enc_cur_angle, std::vector<float> shoulder_configuration, int gripper_angle);
	int send_message();

	SensorData sensor_info;

};

#endif /* SRC_HUMANARM_H_ */
