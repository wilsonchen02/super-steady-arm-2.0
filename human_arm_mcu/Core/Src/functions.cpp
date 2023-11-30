#include <HumanArm.h>
#include "main.h"
#include <memory>


// For ???
extern I2C_HandleTypeDef hi2c1;

// For encoder
extern TIM_HandleTypeDef htim2;

//for flex sensor
extern TIM_HandleTypeDef htim6;

// For Xbee
extern UART_HandleTypeDef huart1;

extern ADC_HandleTypeDef hadc1;

static std::unique_ptr<HumanArm> Human_arm;

void init() {
  HAL_TIM_Encoder_Start(&htim2,  TIM_CHANNEL_ALL);
  HAL_TIM_Base_Start(&htim6);
  Human_arm = std::make_unique<HumanArm>(&hi2c1, TIM2, &huart1, &hadc1);
  Human_arm->init();
  //HAL_TIM_PWM_Start(&htim2,  TIM_CHANNEL_1);
}
void loop() {
  Human_arm->spin();
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  // Check which version of the timer triggered this callback and toggle LED
  if (htim == &htim6 )
  {
	  HAL_ADC_Start_IT(&hadc1);
  }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){

	if (hadc == &hadc1){
		Human_arm->setFlexSensorResistance(HAL_ADC_GetValue(hadc));
	}
}


