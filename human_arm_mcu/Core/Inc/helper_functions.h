#ifndef __HELPER_FUNCTIONS_H
#define __HELPER_FUNCTIONS_H

#include <vector>
#include "../../Eigen/Eigen/Eigen"
#include <math.h>

Eigen::Matrix3f eulers_to_rot_mat(std::vector<float> &eulerAngles);

void rot_mat_to_euler_and_scale(Eigen::Matrix3f &rotation_matrix, std::vector<uint16_t> &scaled_angles);
#endif /* __HELPER_FUNCTIONS_H */
