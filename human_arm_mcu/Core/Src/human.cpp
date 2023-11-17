#include "encoder.h"
#include "main.h"
Encoder encoder;

extern I2C_HandleTypeDef hi2c1;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;


void loop() {
  float enc_cur_angle = encoder.get_position();
}

void init() {
  HAL_TIM_Encoder_Start(&htim1,  TIM_CHANNEL_ALL);
  HAL_TIM_PWM_Start(&htim2,  TIM_CHANNEL_1);
  encoder.init(TIM1);
}
