#include "encoder.h"

float Encoder::get_position_change() {
    uint16_t current_counts = this->m_tim->CNT;
    int delta = current_counts - this->m_prev_counts;
    this->m_prev_counts = current_counts;

    //TODO: convert from counts to position somehow
    return delta / 360.0;
}

void Encoder::init(TIM_TypeDef *_tim) {
    this->m_tim = _tim;
    m_tim->CNT = 0;
    m_prev_counts = 0;
}
