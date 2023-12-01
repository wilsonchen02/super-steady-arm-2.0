#include "IMU.h"

IMU::IMU(I2C_HandleTypeDef* i2c_handle_in, uint8_t address): i2c_handle{i2c_handle_in}, address{address}{
  uint8_t conf_page0[2] = {BNO055_PAGE_ID_ADDR, 0x00};
  HAL_I2C_Master_Transmit(i2c_handle, address<<1, conf_page0, sizeof(conf_page0), 5);
  HAL_Delay(2);

  uint8_t pwr_pwrmode[2] = {BNO055_PWR_MODE_ADDR, 0};
  HAL_I2C_Master_Transmit(i2c_handle, address<<1, pwr_pwrmode, sizeof(pwr_pwrmode), 5);
  HAL_Delay(2);

	// Select BNO055 system operation mode (Page 0; 0x3D)
  uint8_t opr_oprmode[2] = {BNO055_OPR_MODE_ADDR, adafruit_bno055_opmode::OPERATION_MODE_NDOF};
  HAL_I2C_Master_Transmit(i2c_handle, address<<1, opr_oprmode, sizeof(opr_oprmode), 5);
  HAL_Delay(2);


  uint8_t unitsel = (0 << 7) | // Orientation = Android
					(0 << 4) | // Temperature = Celsius
					(0 << 2) | // Euler = Degrees
					(1 << 1) | // Gyro = Rads
					(0 << 0);  // Accelerometer = m/s^2
  uint8_t unit_sel[2] = {BNO055_UNIT_SEL_ADDR, unitsel};
  HAL_I2C_Master_Transmit(i2c_handle, address<<1, unit_sel, sizeof(unit_sel), 5);
  HAL_Delay(2);
}

void IMU::getEulerAngles(std::vector<float> &eulerAngles){
	uint8_t euler_angles[6];
	HAL_I2C_Mem_Read(i2c_handle, address<<1, BNO055_EULER_START_ADDR, I2C_MEMADD_SIZE_8BIT, euler_angles, 6, 30);
	int16_t yaw = ((int16_t)euler_angles[0]) | (((int16_t)euler_angles[1]) << 8);
	int16_t roll = ((int16_t)euler_angles[2]) | (((int16_t)euler_angles[3]) << 8);
	int16_t pitch = ((int16_t)euler_angles[4]) | (((int16_t)euler_angles[5]) << 8);
	eulerAngles.push_back(roll/16.0);
	eulerAngles.push_back(pitch/16.0);
	eulerAngles.push_back(yaw/16.0);

}
