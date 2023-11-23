#include <HumanArm.h>
#include "main.h"
#include <memory>


// For ???
extern I2C_HandleTypeDef hi2c1;

// For encoder
extern TIM_HandleTypeDef htim2;

// For Xbee
extern UART_HandleTypeDef huart1;

static std::unique_ptr<HumanArm> Human_arm;

void init() {
  HAL_TIM_Encoder_Start(&htim2,  TIM_CHANNEL_ALL);
  Human_arm = std::make_unique<HumanArm>(&hi2c1, TIM2, &huart1);
  Human_arm->init();
  //HAL_TIM_PWM_Start(&htim2,  TIM_CHANNEL_1);
}
void loop() {
  Human_arm->spin();
}
