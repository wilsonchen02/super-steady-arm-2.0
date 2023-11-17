#include "encoder.h"
#include "main.h"

void loop() {

}

void init() {
  HAL_TIM_Encoder_Start(&htim1,  TIM_CHANNEL_ALL);
  HAL_TIM_PWM_Start(&htim2,  TIM_CHANNEL_1);
}