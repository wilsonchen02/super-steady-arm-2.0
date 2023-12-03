#include "main.h"
#include "lcd.h"
#include <stdint.h>
#include <memory>
#include <string>

extern I2C_HandleTypeDef hi2c1;

static std::unique_ptr<LCD> lcd;

void init() {
	lcd = std::make_unique<LCD>(&hi2c1);
	HAL_Delay(50);

//	char data_buf[] = "A";
	lcd->send_data("A");
	HAL_Delay(50);
	lcd->set_cursor(1, 0);
//	data_buf = "bingbong";
	HAL_Delay(50);
	lcd->send_data("bingbong");
	HAL_Delay(50);
	lcd->clear_screen();
	HAL_Delay(50);
	lcd->set_cursor(3, 0);
//	data_buf = "blop";
	lcd->send_data("blop");
	HAL_Delay(50);
	lcd->set_cursor(0, 3);
	lcd->send_data("blung");

}

void loop() {

}
