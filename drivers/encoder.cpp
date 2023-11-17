#include "encoder.h"

float Encoder::get_position_change() {
    uint16_t current_counts = this->m_tim->CNT;
    int delta = current_counts - this->m_prev_counts;
    this->m_prev_counts = current_counts;

    //TODO: convert from counts to position somehow
    return static_cast<float>(delta);
}

void Encoder::init() {
    // TODO: Might not need. Check what auto code generation does for us
    // Initalize TIM->CNT to some value?
    // Initalize the channels/timer in encoder mode
    


}
