#ifndef SRC_HUMANARM_H_
#define SRC_HUMANARM_H_

#include "IMU.h"
#include "encoder.h"
#include "xbee.h"
#include "flexSensor.h"
#include <memory>

struct __attribute__ ((__packed__)) SensorData {
	uint16_t gripper;
	uint16_t wrist_roll;
	uint16_t wrist_pitch;
	uint16_t elbow;
	uint16_t shoulder_pitch; // controlled directly by pitch
	uint16_t shoulder_yaw;// joint A is controlled by a combination of roll and yaw
};

union SensorData_u {
	SensorData data_struct;
	uint8_t bytes[sizeof(SensorData)];
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

	int pack_message(std::vector<uint16_t> wrist_configuration, uint16_t enc_cur_angle, std::vector<uint16_t> shoulder_configuration, uint16_t gripper_angle);
	int send_message();

	SensorData_u sensor_info;

};

#endif /* SRC_HUMANARM_H_ */
