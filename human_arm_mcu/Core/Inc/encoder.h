#include "main.h"
 TODO: Change to be actual TIM
constexpr TIM_HandleTypeDEF ENCODER_HTIM = htim2;
constexpr TIM_HandleTypeDEF ENCODER_TIM = TIM2;

/* TODO: 
 * Do we want to implement position using the encoder?
 * Or is just getting change in position good?
 
 * This outcoder changes output on Z once per revolution.
 * Could possibly use that to calculate absolute position? 
 * But also our encoder is never going to rotate a full cycle. 
 */

class Encoder {
    public:
    void init();
    float get_position_change();

    private:
    TIM_HandleTypeDEF m_handler = ENCODER_HTIM;
    TIM_TypeDef* m_tim = ENCODER_TIM;
    uint16_t m_prev_counts;
};