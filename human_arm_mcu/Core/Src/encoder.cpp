#include "encoder.h"

void Encoder::update_position() {
    uint16_t current_counts = this->m_tim->CNT;
    int delta = current_counts - this->m_prev_counts;
    this->m_prev_counts = current_counts;
}

float Encoder::get_position() {
    update_position();
    // current position in angles
    return (this->m_prev_counts / 2500) * 360.0;
}

void Encoder::init(TIM_TypeDef *_tim) {
    this->m_tim = _tim;
    m_tim->CNT = 0;
    m_prev_counts = 0;
}
