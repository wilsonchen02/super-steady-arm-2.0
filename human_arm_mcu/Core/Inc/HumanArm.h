#ifndef SRC_HUMANARM_H_
#define SRC_HUMANARM_H_

#include "IMU.h"
#include "encoder.h"
#include "xbee.h"
#include <memory>

struct __attribute__ ((__packed__)) SensorData {
	uint16_t servo0;
	uint16_t servo1;
	uint16_t servo2;
	uint16_t servo3;
	uint16_t servo4;
	uint16_t servo5;
};

class HumanArm {
public:
	HumanArm(I2C_HandleTypeDef* I2C_handle, TIM_TypeDef* TIM_handle, UART_HandleTypeDef* UART_handle)
		: I2C_handle{I2C_handle}
		, TIM_handle{TIM_handle}
		, UART_handle{UART_handle}
		{};
	int init();
	int spin();


private:
	std::unique_ptr<IMU> wrist_IMU;
	std::unique_ptr<IMU> shoulder_IMU;
	std::unique_ptr<Encoder> elbow_encoder;

	I2C_HandleTypeDef* I2C_handle;
	TIM_TypeDef* TIM_handle;
	UART_HandleTypeDef * UART_handle;

	int pack_message(std::vector<float> wrist_configuration, float enc_cur_angle, std::vector<float> shoulder_configuration);
	int send_message();

	SensorData sensor_info;

	float RA_commands[6];
};

#endif /* SRC_HUMANARM_H_ */
