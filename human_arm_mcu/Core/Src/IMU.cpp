#include "IMU.h"
#include "stdio.h"

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

static bool inRange(double low, double high, double x)
{
 return (low <= x && x <= high);
}

void IMU::getEulerAngles(std::vector<float> &eulerAngles){
	uint8_t euler_angles[6];
	int16_t roll = 0;
	int16_t pitch = 0;
	int16_t yaw = 0;

	do {
		HAL_I2C_Mem_Read(i2c_handle, address<<1, BNO055_EULER_START_ADDR, I2C_MEMADD_SIZE_8BIT, euler_angles, 6, 30);
		yaw = ((int16_t)euler_angles[0]) | (((int16_t)euler_angles[1]) << 8);
		roll = ((int16_t)euler_angles[2]) | (((int16_t)euler_angles[3]) << 8);
		pitch = ((int16_t)euler_angles[4]) | (((int16_t)euler_angles[5]) << 8);
	}while((!(inRange(0.0, 360, yaw/16.0))) || (!(inRange(-180, 180, pitch/16.0))) || (!(inRange(-90, 90, roll/16.0))));
//	printf("yrp: %f %f %f\n", yaw/16.0, roll/16.0, pitch/16.0);
	eulerAngles.push_back(-1 * roll/16.0);
	eulerAngles.push_back(-1 * pitch/16.0);
	eulerAngles.push_back(360.0 - yaw/16.0);

}


void IMU::getEulerAnglesAndScale(std::vector<uint16_t> &eulerAngles){

	uint8_t euler_angles[6];
	int16_t roll = 0;
	int16_t pitch = 0;
	int16_t yaw = 0;

	do{
		HAL_I2C_Mem_Read(i2c_handle, address<<1, BNO055_EULER_START_ADDR, I2C_MEMADD_SIZE_8BIT, euler_angles, 6, 30);
		yaw = ((((int16_t)euler_angles[0]) | (((int16_t)euler_angles[1]) << 8)));
		roll = ((((int16_t)euler_angles[2]) | (((int16_t)euler_angles[3]) << 8)));
		pitch = ((((int16_t)euler_angles[4]) | (((int16_t)euler_angles[5]) << 8)));
	}while((!(inRange(0.0, 360, yaw/16.0))) || (!(inRange(-180, 180, pitch/16.0))) || (!(inRange(-90, 90, roll/16.0))));

	float rollconv = roll/16.0; //-90 to 90
	float pitchconv = pitch/16.0; // -180 to 180
	float yawconv = yaw/16.0; // 0 to 360

	uint16_t roll_scaled = (uint16_t)((rollconv+90.0)*(1000.0/180.0)) ;
	uint16_t pitch_scaled = (uint16_t)((pitchconv+180.0)*(1000.0/360.0));
	uint16_t yaw_scaled = (uint16_t)((yawconv)*(1000.0/360.0));

	eulerAngles.push_back(roll_scaled);
	eulerAngles.push_back(pitch_scaled);
	eulerAngles.push_back(yaw_scaled);

}

