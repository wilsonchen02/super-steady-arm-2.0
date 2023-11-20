#ifndef __ENCODER_H
#define __ENCODER_H
#include "main.h"

/* TODO: 
 * Do we want to implement position using the encoder?
 * Or is just getting change in position good?
 
 * This outcoder changes output on Z once per revolution.
 * Could possibly use that to calculate absolute position? 
 * But also our encoder is never going to rotate a full cycle. 
 */

class Encoder {
    public:
    Encoder(TIM_HandleTypeDef *_tim);
    float get_position();

    private:
    void update_position();
    TIM_HandleTypeDef* m_tim;
    uint16_t m_prev_counts;
};

#endif /* __ENCODER_H */
