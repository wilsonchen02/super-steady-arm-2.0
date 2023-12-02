#ifndef __IMU_H
#define __IMU_H

#include <vector>
#include <cstdint>
#include "stm32l4xx_hal.h"

// possible I2C addresses
#define IMU_ADDR_LO 0x28
#define IMU_ADDR_HI 0x29

#define BNO055_PAGE_ID_ADDR 0X07
#define BNO055_OPR_MODE_ADDR 0X3D
#define BNO055_PWR_MODE_ADDR 0X3E
#define BNO055_UNIT_SEL_ADDR 0X3B
#define BNO055_EULER_START_ADDR 0X1A

enum adafruit_bno055_opmode{
  OPERATION_MODE_CONFIG = 0X00,
  OPERATION_MODE_ACCONLY = 0X01,
  OPERATION_MODE_MAGONLY = 0X02,
  OPERATION_MODE_GYRONLY = 0X03,
  OPERATION_MODE_ACCMAG = 0X04,
  OPERATION_MODE_ACCGYRO = 0X05,
  OPERATION_MODE_MAGGYRO = 0X06,
  OPERATION_MODE_AMG = 0X07,
  OPERATION_MODE_IMUPLUS = 0X08,
  OPERATION_MODE_COMPASS = 0X09,
  OPERATION_MODE_M4G = 0X0A,
  OPERATION_MODE_NDOF_FMC_OFF = 0X0B,
  OPERATION_MODE_NDOF = 0X0C
};

uint8_t const unitsel = (0 << 7) | //  Android
                    (0 << 4) | // Celsius
                    (0 << 2) | // Degrees
                    (1 << 1) | //  Rads
                    (0 << 0);  //  m/s^2



class IMU {

private:
	I2C_HandleTypeDef* i2c_handle;
	bool is_initialized;
	uint8_t address;


public:
	IMU(I2C_HandleTypeDef* i2c_handle_in, uint8_t address);


	void getEulerAngles(std::vector<float> &eulerAngles);
	void getEulerAnglesAndScale(std::vector<uint16_t> &eulerAngles);



};


#endif /* __IMU_H */
