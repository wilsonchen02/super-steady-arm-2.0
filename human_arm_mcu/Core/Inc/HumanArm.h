#ifndef SRC_HUMANARM_H_
#define SRC_HUMANARM_H_

#include "IMU.h"
#include "encoder.h"

class HumanArm {
public:
	HumanArm(IMU wrist_IMU, IMU shoulder_IMU, Encoder elbow_encoder): wrist_IMU{wrist_IMU}, shoulder_IMU{shoulder_IMU}, elbow_encoder{elbow_encoder}{};
	int init();
	int spin();


private:
	IMU wrist_IMU;
	IMU shoulder_IMU;
	Encoder elbow_encoder;

	int pack_message(std::vector<double> wrist_configuration, float enc_cur_angle, std::vector<double>shoulder_configuration);
	int send_message();

	double RA_commands[6];
};

#endif /* SRC_HUMANARM_H_ */
