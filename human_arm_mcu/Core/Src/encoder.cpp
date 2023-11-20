#include "encoder.h"


Encoder::Encoder(TIM_HandleTypeDef *_tim): m_tim{_tim}{
    m_tim->Instance->CNT = 0;
    m_prev_counts = 0;
}

void Encoder::update_position() {
    uint16_t current_counts = m_tim->Instance->CNT;
    int delta = current_counts - m_prev_counts;
    m_prev_counts = current_counts;
}

float Encoder::get_position() {
    update_position();
    // current position in angles
    return (m_prev_counts / 2500) * 360.0;
}
