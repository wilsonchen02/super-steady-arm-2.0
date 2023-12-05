#include <HumanArm.h>
#include <stdio.h>

int HumanArm::init(){
	this->wrist_IMU = std::make_unique<IMU>(I2C_handle, IMU_ADDR_LO);
	this->shoulder_IMU = std::make_unique<IMU>(I2C_handle, IMU_ADDR_HI);
	this->elbow_encoder = std::make_unique<Encoder>(TIM_handle);
	this->flex_sensor = std::make_unique<flexSensor>(ADC_handle);
	// wait for sensor initialization
	HAL_Delay(1000);

	std::vector<float> shoulder_configuration;
	shoulder_IMU->getEulerAngles(shoulder_configuration);

	// The first pose of the shoulder in the magnetic field frame is the global frame
	this->global_frame = std::make_unique<Eigen::Matrix3f>(eulers_to_rot_mat(shoulder_configuration).transpose());
	return 0;
}

int HumanArm::spin(){
	std::vector<float> shoulder_angles;
	shoulder_IMU->getEulerAngles(shoulder_angles);
	Eigen::Matrix3f shoulder_in_w = *this->global_frame * eulers_to_rot_mat(shoulder_angles);
	std::vector<uint16_t> shoulder_configuration;
	rot_mat_to_euler_and_scale(shoulder_in_w, shoulder_configuration);

	float encoderAngle = elbow_encoder->get_position();
	std::vector<float> encoder_angles = {shoulder_angles[0], shoulder_angles[1], shoulder_angles[2] + encoderAngle};
	Eigen::Matrix3f encoder_in_w = *this->global_frame * eulers_to_rot_mat(encoder_angles);
	uint16_t scaled_encoder_angle = elbow_encoder->get_position_and_scale();

	std::vector<float> wrist_angles;
	wrist_IMU->getEulerAngles(wrist_angles);
	Eigen::Matrix3f wrist_in_w = encoder_in_w.transpose() * eulers_to_rot_mat(wrist_angles);
	std::vector<uint16_t> wrist_configuration;
	rot_mat_to_euler_and_scale(wrist_in_w, wrist_configuration);

	uint16_t gripper_config = flex_sensor->getResistanceAndScale();

	pack_message(wrist_configuration, scaled_encoder_angle, shoulder_configuration, gripper_config);
	send_message();
	return 0;
}

int HumanArm::pack_message(std::vector<uint16_t> wrist_configuration, uint16_t enc_cur_angle, std::vector<uint16_t> shoulder_configuration, uint16_t gripper_angle){
	//printf("current_encoder_angle: %f\n", enc_cur_angle);
	sensor_info.data_struct.gripper 		= gripper_angle;
	sensor_info.data_struct.wrist_roll 		= wrist_configuration[0];
	sensor_info.data_struct.wrist_pitch		= wrist_configuration[1];
	sensor_info.data_struct.elbow 			= enc_cur_angle;
	sensor_info.data_struct.shoulder_pitch 	= shoulder_configuration[1];
	sensor_info.data_struct.shoulder_yaw 	= shoulder_configuration[2];
	return 0;
}

int HumanArm::send_message(){
	// Sending 6 * 2 (uint16_t) bytes
	//SensorData sensor_info_test = {0xFF33, 0xEE11, 0xDD22, 0xCC33, 0xBB44, 0xAA55};
//	uint8_t* buf_tx = reinterpret_cast<uint8_t*>(&sensor_info);

	printf("val1:%d, val2:%d, val3:%d, val4:%d, val5:%d, val6:%d\n", sensor_info.data_struct.gripper, sensor_info.data_struct.wrist_roll, sensor_info.data_struct.wrist_pitch, sensor_info.data_struct.elbow, sensor_info.data_struct.shoulder_pitch, sensor_info.data_struct.shoulder_yaw);
	HAL_UART_Transmit(UART_handle, sensor_info.bytes, sizeof(SensorData), UINT32_MAX);
	return 0;
}


int HumanArm::setFlexSensorResistance(uint16_t adc_val){
	flex_sensor->setResistance(adc_val);
	return 0;
}
