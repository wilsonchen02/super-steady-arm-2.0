#include "encoder.h"
#include "stdio.h"

Encoder::Encoder(TIM_TypeDef *_tim): m_tim{_tim}{
    //m_tim->CNT = 0;
    m_prev_counts = 0;
}

void Encoder::update_position() {
    uint16_t current_counts = m_tim->CNT;
    // printf("current_encoder_counts: %d\n", current_counts);
    //int delta = current_counts - m_prev_counts;
    m_prev_counts = current_counts;
}

float Encoder::get_position() {
    update_position();
    // current position in angles
    return 360.0 - ((float)m_prev_counts / 10000.0) * 360.0;
}


uint16_t Encoder::get_position_and_scale(){
	uint16_t output = (uint16_t)get_position();
	uint16_t output_scaled = 700;
	if (output >=250){
		output_scaled = (output-250)*(700/110);
	}


	return output_scaled;
}
