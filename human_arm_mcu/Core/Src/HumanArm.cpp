#include <HumanArm.h>
#include <stdio.h>


int HumanArm::init(){
	this->wrist_IMU = std::make_unique<IMU>(I2C_handle, IMU_ADDR_LO);
	this->shoulder_IMU = std::make_unique<IMU>(I2C_handle, IMU_ADDR_HI);
	this->elbow_encoder = std::make_unique<Encoder>(TIM_handle);
	this->flex_sensor = std::make_unique<flexSensor>(ADC_handle);
	return 0;
}

int HumanArm::spin(){
	uint16_t encoderScaledAngle = elbow_encoder->get_position_and_scale();
	uint16_t gripper_config = flex_sensor->getResistanceAndScale();
	std::vector<uint16_t> wrist_configuration;
	wrist_IMU->getEulerAnglesAndScale(wrist_configuration);
	std::vector<uint16_t> shoulder_configuration;
	shoulder_IMU->getEulerAnglesAndScale(shoulder_configuration);

	pack_message(wrist_configuration, encoderScaledAngle, shoulder_configuration, gripper_config);
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
