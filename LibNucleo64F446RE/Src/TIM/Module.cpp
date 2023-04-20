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

//--------------------------
// include
//--------------------------
#include "TIM/Module.hpp"

//--------------------------
// method
//--------------------------
namespace MiYALAB{
namespace STM32{
namespace TIM{
/**
 * @brief Construct a new Module:: Module object
 * 
 * @param instance 
 */
Module::Module(TIM_TypeDef *instance)
{    
    this->handler.Instance = instance;

    // TIMクロック許可
    if(this->handler.Instance == TIM1)       __HAL_RCC_TIM1_CLK_ENABLE();
    else if(this->handler.Instance == TIM2)  __HAL_RCC_TIM2_CLK_ENABLE();
    else if(this->handler.Instance == TIM3)  __HAL_RCC_TIM3_CLK_ENABLE();
    else if(this->handler.Instance == TIM4)  __HAL_RCC_TIM4_CLK_ENABLE();
    else if(this->handler.Instance == TIM5)  __HAL_RCC_TIM5_CLK_ENABLE();
    else if(this->handler.Instance == TIM6)  __HAL_RCC_TIM6_CLK_ENABLE();
    else if(this->handler.Instance == TIM7)  __HAL_RCC_TIM7_CLK_ENABLE();
    else if(this->handler.Instance == TIM8)  __HAL_RCC_TIM8_CLK_ENABLE();
    else if(this->handler.Instance == TIM9)  __HAL_RCC_TIM9_CLK_ENABLE();
    else if(this->handler.Instance == TIM10) __HAL_RCC_TIM10_CLK_ENABLE();
    else if(this->handler.Instance == TIM11) __HAL_RCC_TIM11_CLK_ENABLE();
    else if(this->handler.Instance == TIM12) __HAL_RCC_TIM12_CLK_ENABLE();
}

/**
 * @brief Destroy the Module:: Module object
 * 
 */
Module::~Module()
{
    // TIMクロック不許可
    if(this->handler.Instance == TIM1)       __HAL_RCC_TIM1_CLK_DISABLE();
    else if(this->handler.Instance == TIM2)  __HAL_RCC_TIM2_CLK_DISABLE();
    else if(this->handler.Instance == TIM3)  __HAL_RCC_TIM3_CLK_DISABLE();
    else if(this->handler.Instance == TIM4)  __HAL_RCC_TIM4_CLK_DISABLE();
    else if(this->handler.Instance == TIM5)  __HAL_RCC_TIM5_CLK_DISABLE();
    else if(this->handler.Instance == TIM6)  __HAL_RCC_TIM6_CLK_DISABLE();
    else if(this->handler.Instance == TIM7)  __HAL_RCC_TIM7_CLK_DISABLE();
    else if(this->handler.Instance == TIM8)  __HAL_RCC_TIM8_CLK_DISABLE();
    else if(this->handler.Instance == TIM9)  __HAL_RCC_TIM9_CLK_DISABLE();
    else if(this->handler.Instance == TIM10) __HAL_RCC_TIM10_CLK_DISABLE();
    else if(this->handler.Instance == TIM11) __HAL_RCC_TIM11_CLK_DISABLE();
    else if(this->handler.Instance == TIM12) __HAL_RCC_TIM12_CLK_DISABLE();
}
}
}
}

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------