#include <HumanArm.h>
#include "main.h"


extern I2C_HandleTypeDef hi2c1;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;

static Encoder elbow_encoder(&htim1);
static IMU wrist_IMU(&hi2c1, IMU_ADDR_LO);
static IMU shoulder_IMU(&hi2c1, IMU_ADDR_HI);

static HumanArm Human_arm(wrist_IMU ,shoulder_IMU, elbow_encoder);


void loop() {
  Human_arm.spin();
}

void init() {
  HAL_TIM_Encoder_Start(&htim1,  TIM_CHANNEL_ALL);
  //HAL_TIM_PWM_Start(&htim2,  TIM_CHANNEL_1);
}
