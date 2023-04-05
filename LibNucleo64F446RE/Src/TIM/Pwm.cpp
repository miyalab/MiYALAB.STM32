/*
 * MIT License
 *
 * Copyright (c) 2023 MiYA LAB(K.Miyauchi)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * File   : Pwm.cpp
 * Author : K.Miyauchi
 *
 * Version : 1.00
 */

#ifndef __MiYALAB_STM32_F446RE_TIM_HPP__
#define __MiYALAB_STM32_F446RE_TIM_HPP__

//--------------------------
// TIM機能使用許可
//--------------------------
#define HAL_TIM_MODULE_ENABLED

//--------------------------
// include
//--------------------------
#include "TIM/Pwm.hpp"

//--------------------------
// method
//--------------------------
namespace MiYALAB{
namespace STM32{
TimPwmMode::TimPwmMode(TIM_TypeDef *instance)
{
    this->handler.Instance = instance;
    
    if(instance == TIM1)       __HAL_RCC_TIM1_CLK_ENABLE();
    else if(instance == TIM2)  __HAL_RCC_TIM2_CLK_ENABLE();
    else if(instance == TIM3)  __HAL_RCC_TIM3_CLK_ENABLE();
    else if(instance == TIM4)  __HAL_RCC_TIM4_CLK_ENABLE();
    else if(instance == TIM5)  __HAL_RCC_TIM5_CLK_ENABLE();
    else if(instance == TIM8)  __HAL_RCC_TIM8_CLK_ENABLE();
    else if(instance == TIM12) __HAL_RCC_TIM12_CLK_ENABLE();
}

TimPwmMode::~TimPwmMode()
{
    
    if(this->handler.Instance == TIM1)       __HAL_RCC_TIM1_CLK_DISABLE();
    else if(this->handler.Instance == TIM2)  __HAL_RCC_TIM2_CLK_DISABLE();
    else if(this->handler.Instance == TIM3)  __HAL_RCC_TIM3_CLK_DISABLE();
    else if(this->handler.Instance == TIM4)  __HAL_RCC_TIM4_CLK_DISABLE();
    else if(this->handler.Instance == TIM5)  __HAL_RCC_TIM5_CLK_DISABLE();
    else if(this->handler.Instance == TIM8)  __HAL_RCC_TIM8_CLK_DISABLE();
    else if(this->handler.Instance == TIM12) __HAL_RCC_TIM12_CLK_DISABLE();
}

bool TimPwmMode::enable(uint16_t divide, uint16_t period, uint8_t use_channel)
{
    bool ret = true;
    
    if(use_channel & TIM::CHANNEL_1){

    }
    if(use_channel & TIM::CHANNEL_2){

    }
    if(use_channel & TIM::CHANNEL_3){
    
    }
    if(use_channel & TIM::CHANNEL_4){

    }
    return ret;
}

void TimPwmMode::pwmOut(uint8_t channel, uint16_t duty)
{
    if(channel & TIM::CHANNEL_1) this->handler.Instance->CCR1 = duty;
    if(channel & TIM::CHANNEL_2) this->handler.Instance->CCR2 = duty;
    if(channel & TIM::CHANNEL_3) this->handler.Instance->CCR3 = duty;
    if(channel & TIM::CHANNEL_4) this->handler.Instance->CCR4 = duty;
}

}
}

#endif // __MiYALAB_STM32_F446RE_TIM_PWM_HPP__

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------