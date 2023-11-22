#ifndef SRC_HUMANARM_H_
#define SRC_HUMANARM_H_

#include "IMU.h"
#include "encoder.h"
#include <memory>

class HumanArm {
public:
	HumanArm(I2C_HandleTypeDef* I2C_handle, TIM_TypeDef* TIM_handle): I2C_handle{I2C_handle}, TIM_handle{TIM_handle}{};
	int init();
	int spin();


private:
	std::unique_ptr<IMU> wrist_IMU;
	std::unique_ptr<IMU> shoulder_IMU;
	std::unique_ptr<Encoder> elbow_encoder;

	I2C_HandleTypeDef* I2C_handle;
	TIM_TypeDef* TIM_handle;

	int pack_message(std::vector<double> wrist_configuration, float enc_cur_angle, std::vector<double>shoulder_configuration);
	int send_message();

	double RA_commands[6];
};

#endif /* SRC_HUMANARM_H_ */
