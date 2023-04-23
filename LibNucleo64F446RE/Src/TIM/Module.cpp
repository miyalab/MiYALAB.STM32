/*
 * MIT License
 *
 * Copyright (c) 2020-2023 MiYA LAB(K.Miyauchi)
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

bool Module::initGpio(const uint8_t &channel)
{
    // GPIO設定
    GPIO_InitTypeDef gpio_config = {0};
    gpio_config.Mode = GPIO_MODE_AF_PP;
    gpio_config.Pull = GPIO_NOPULL;
    gpio_config.Speed = GPIO_SPEED_FREQ_LOW;

    if(this->handler.Instance == TIM1){
        gpio_config.Alternate = GPIO_AF1_TIM1;
        gpio_config.Pin = (channel & 0x0f) << 8;
        // gpio_config.Pin  = GPIO_PIN_8  *  (channel & TIM::CHANNEL_1);
        // gpio_config.Pin |= GPIO_PIN_9  * ((channel & TIM::CHANNEL_2) != 0);
        // gpio_config.Pin |= GPIO_PIN_10 * ((channel & TIM::CHANNEL_3) != 0);
        // gpio_config.Pin |= GPIO_PIN_11 * ((channel & TIM::CHANNEL_4) != 0);
        __HAL_RCC_GPIOA_CLK_ENABLE();
        HAL_GPIO_Init(GPIOA, &gpio_config);
    }
    else if(this->handler.Instance == TIM2){
        gpio_config.Alternate = GPIO_AF1_TIM2;
        gpio_config.Pin = GPIO_PIN_5 * (channel & TIM::CHANNEL_1);
        if(gpio_config.Pin){
            __HAL_RCC_GPIOA_CLK_ENABLE();
            HAL_GPIO_Init(GPIOA, &gpio_config);
        }
        
        gpio_config.Pin  = GPIO_PIN_3  * ((channel & TIM::CHANNEL_2) != 0);
        gpio_config.Pin |= GPIO_PIN_10 * ((channel & TIM::CHANNEL_3) != 0);
        gpio_config.Pin |= GPIO_PIN_2  * ((channel & TIM::CHANNEL_4) != 0);
        if(gpio_config.Pin){
            __HAL_RCC_GPIOB_CLK_ENABLE();
            HAL_GPIO_Init(GPIOB, &gpio_config);
        }
    }
    else if(this->handler.Instance == TIM3){
        gpio_config.Alternate = GPIO_AF2_TIM3;
        gpio_config.Pin  = GPIO_PIN_4 *  (channel & TIM::CHANNEL_1);
        gpio_config.Pin |= GPIO_PIN_5 * ((channel & TIM::CHANNEL_2) != 0);
        gpio_config.Pin |= GPIO_PIN_0 * ((channel & TIM::CHANNEL_3) != 0);
        gpio_config.Pin |= GPIO_PIN_1 * ((channel & TIM::CHANNEL_4) != 0);
        __HAL_RCC_GPIOB_CLK_ENABLE();
        HAL_GPIO_Init(GPIOB, &gpio_config);
    }
    else if(this->handler.Instance == TIM4){
        gpio_config.Alternate = GPIO_AF2_TIM4;
        gpio_config.Pin = (channel & 0x0f) << 6;
        // gpio_config.Pin  = GPIO_PIN_6 *  (channel & TIM::CHANNEL_1);
        // gpio_config.Pin |= GPIO_PIN_7 * ((channel & TIM::CHANNEL_2) != 0);
        // gpio_config.Pin |= GPIO_PIN_8 * ((channel & TIM::CHANNEL_3) != 0);
        // gpio_config.Pin |= GPIO_PIN_9 * ((channel & TIM::CHANNEL_4) != 0);
        __HAL_RCC_GPIOB_CLK_ENABLE();
        HAL_GPIO_Init(GPIOB, &gpio_config);
    }
    else if(this->handler.Instance == TIM5){
        gpio_config.Alternate = GPIO_AF2_TIM5;
        gpio_config.Pin = channel & 0x0f;
        // gpio_config.Pin  = GPIO_PIN_0 *  (channel & TIM::CHANNEL_1);
        // gpio_config.Pin |= GPIO_PIN_1 * ((channel & TIM::CHANNEL_2) != 0);
        // gpio_config.Pin |= GPIO_PIN_2 * ((channel & TIM::CHANNEL_3) != 0);
        // gpio_config.Pin |= GPIO_PIN_3 * ((channel & TIM::CHANNEL_4) != 0);
        __HAL_RCC_GPIOA_CLK_ENABLE();
        HAL_GPIO_Init(GPIOA, &gpio_config);
    }
    else if(this->handler.Instance == TIM8){
        gpio_config.Alternate = GPIO_AF3_TIM8;
        gpio_config.Pin = (channel & 0x0f) << 6;
        // gpio_config.Pin  = GPIO_PIN_6 *  (channel & TIM::CHANNEL_1);
        // gpio_config.Pin |= GPIO_PIN_7 * ((channel & TIM::CHANNEL_2) != 0);
        // gpio_config.Pin |= GPIO_PIN_8 * ((channel & TIM::CHANNEL_3) != 0);
        // gpio_config.Pin |= GPIO_PIN_9 * ((channel & TIM::CHANNEL_4) != 0);
        __HAL_RCC_GPIOC_CLK_ENABLE();
        HAL_GPIO_Init(GPIOC, &gpio_config);
    }
    else if(this->handler.Instance == TIM12){
        gpio_config.Alternate = GPIO_AF9_TIM12;
        gpio_config.Pin = (channel & 0x03) << 14;
        // gpio_config.Pin  = GPIO_PIN_14 *  (channel & TIM::CHANNEL_1);
        // gpio_config.Pin |= GPIO_PIN_15 * ((channel & TIM::CHANNEL_2) != 0);
        __HAL_RCC_GPIOB_CLK_ENABLE();
        HAL_GPIO_Init(GPIOB, &gpio_config);
    }
    else return false;
    return true;
}
}
}
}

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------