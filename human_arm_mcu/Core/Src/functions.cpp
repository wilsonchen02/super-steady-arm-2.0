#include <HumanArm.h>
#include "main.h"
#include <memory>

extern I2C_HandleTypeDef hi2c1;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;

static std::unique_ptr<HumanArm> Human_arm;

void init() {
  HAL_TIM_Encoder_Start(&htim1,  TIM_CHANNEL_ALL);
  Human_arm = std::make_unique<HumanArm>(&hi2c1, TIM1);
  Human_arm->init();
  //HAL_TIM_PWM_Start(&htim2,  TIM_CHANNEL_1);
}
void loop() {
  Human_arm->spin();
}
