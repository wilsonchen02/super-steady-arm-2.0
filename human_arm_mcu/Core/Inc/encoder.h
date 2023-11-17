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
    void init(TIM_TypeDef *_tim);
    float get_position_change();

    private:
    TIM_TypeDef* m_tim;
    uint16_t m_prev_counts;
};