#include "main.h"
#include "lcd.h"
#include <stdint.h>
#include <string>
#include <memory>

extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim10;

static std::unique_ptr<LCD> lcd;
static uint16_t test_buf[6] = {0, 100, 200, 300, 500, 1000};

void init() {
	lcd = std::make_unique<LCD>(&hi2c1);

	HAL_Delay(100);
	lcd->clear_screen();
	HAL_Delay(100);
	lcd->init_servo_labels();
	HAL_Delay(100);

	// Start timer
	HAL_TIM_Base_Start_IT(&htim10);
}

void loop() {
	test_buf[0] += 1;
//	lcd->send_servo_angles(test_buf);
	HAL_Delay(100);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim == &htim10)
  {
	  lcd->send_servo_angles(test_buf);
  }
}
