#include "helper_functions.h"

Eigen::Matrix3f eulers_to_rot_mat(std::vector<float> &eulerAngles) {
	// Assumes input angles are in degrees
	// TODO: Check contents of eulerAngles to make sure it is populated with 3 angles
	Eigen::AngleAxisf rollAngle(eulerAngles[0] * M_PI/180.0, Eigen::Vector3f::UnitX());
	Eigen::AngleAxisf pitchAngle(eulerAngles[1] * M_PI/180.0, Eigen::Vector3f::UnitY());
	Eigen::AngleAxisf yawAngle(eulerAngles[2] * M_PI/180.0, Eigen::Vector3f::UnitZ());
	Eigen::Quaternion<float> q = rollAngle * yawAngle * pitchAngle;
	Eigen::Matrix3f rotation_matrix = q.matrix();
	return rotation_matrix;
}

void rot_mat_to_euler_and_scale(Eigen::Matrix3f &rotation_matrix, std::vector<uint16_t> &scaled_angles) {
	//TODO: Check order of axes
	Eigen::Vector3f euler = rotation_matrix.eulerAngles(0, 1, 2);

	float roll_deg = euler[0] * 180.0/M_PI;
	float pitch_deg = euler[1] * 180.0/M_PI;
	float yaw_deg = euler[2] * 180.0/M_PI;

	uint16_t roll_scaled = (uint16_t)(roll_deg*(1000.0/180.0));
	uint16_t pitch_scaled = (uint16_t)((pitch_deg+180.0)*(1000.0/360.0));
	uint16_t yaw_scaled = (uint16_t)((yaw_deg+180)*(1000.0/360.0));

	scaled_angles.push_back(roll_scaled);
	scaled_angles.push_back(pitch_scaled);
	scaled_angles.push_back(yaw_scaled);
}
