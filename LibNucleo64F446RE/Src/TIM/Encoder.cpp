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
 * File   : Encoder.cpp
 * Author : K.Miyauchi
 *
 * Version : 2.00
 */

//--------------------------
// include
//--------------------------
#include "TIM/Encoder.hpp"

//--------------------------
// method
//--------------------------
namespace MiYALAB{
namespace STM32{
namespace TIM{
/**
 * @brief Construct a new Encoder Mode:: Encoder Mode object
 * 
 * @param instance: TIM1 (CH1-4: PA8,  PA9, PA10, PA11)
 *                  TIM2 (CH1-4: PA5,  PB3, PB10, PB2)
 *                  TIM3 (CH1-4: PB4,  PB5, PB0,  PB1)
 *                  TIM4 (CH1-4: PB6,  PB7, PB8,  PB9)
 *                  TIM5 (CH1-4: PA0,  PA1, PA2,  PA3)
 *                  TIM8 (CH1-4: PC6,  PC7, PC8,  PC9)
 *                  TIM12(CH1-2: PB14, PB15)
 */
EncoderMode::EncoderMode(TIM_TypeDef *instance) : TIM::Module(instance)
{

}

/**
 * @brief Destroy the Encoder Mode:: Encoder Mode object
 * 
 */
EncoderMode::~EncoderMode()
{
    // encoder stop
    this->disable();
}

/**
 * @brief enable method
 * 
 * @param divide 
 * @param period 
 * @param use_channel 
 * @return true 
 * @return false 
 */
bool EncoderMode::enable(const uint16_t &divide, const uint16_t &period, const uint8_t &use_channel)
{
    // TIMレジスタ設定
    this->handler.Init.Prescaler = divide;
    this->handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    this->handler.Init.Period = period;
    this->handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    this->handler.Init.RepetitionCounter = 0;
    this->handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    // TIM
    if(this->initGpio(use_channel)) return false;

    return true;
}

/**
 * @brief initialize gpio port for tim encoder mode
 * 
 * @param channel 
 * @return true 
 * @return false 
 */
bool EncoderMode::initGpio(const uint8_t &channel)
{
    // GPIO設定
    GPIO_InitTypeDef gpio_config = {0};
    gpio_config.Mode = GPIO_MODE_AF_PP;
    gpio_config.Pull = GPIO_NOPULL;
    gpio_config.Speed = GPIO_SPEED_FREQ_LOW;

    if(this->handler.Instance == TIM1){
        gpio_config.Alternate = GPIO_AF1_TIM1;
        gpio_config.Pin  = GPIO_PIN_8  *  (channel & TIM::CHANNEL_1);
        gpio_config.Pin |= GPIO_PIN_9  * ((channel & TIM::CHANNEL_2) != 0);
        if(gpio_config.Pin){
            __HAL_RCC_GPIOA_CLK_ENABLE();
            HAL_GPIO_Init(GPIOA, &gpio_config);
        }
    }
    else if(this->handler.Instance == TIM2){
        gpio_config.Alternate = GPIO_AF1_TIM2;
        gpio_config.Pin = GPIO_PIN_5 * (channel & TIM::CHANNEL_1);
        if(gpio_config.Pin){
            __HAL_RCC_GPIOA_CLK_ENABLE();
            HAL_GPIO_Init(GPIOA, &gpio_config);
        }
        
        gpio_config.Pin  = GPIO_PIN_3  * ((channel & TIM::CHANNEL_2) != 0);
        if(gpio_config.Pin){
            __HAL_RCC_GPIOB_CLK_ENABLE();
            HAL_GPIO_Init(GPIOB, &gpio_config);
        }
    }
    else if(this->handler.Instance == TIM3){
        gpio_config.Alternate = GPIO_AF2_TIM3;
        gpio_config.Pin  = GPIO_PIN_4 *  (channel & TIM::CHANNEL_1);
        gpio_config.Pin |= GPIO_PIN_5 * ((channel & TIM::CHANNEL_2) != 0);
        if(gpio_config.Pin){
            __HAL_RCC_GPIOB_CLK_ENABLE();
            HAL_GPIO_Init(GPIOB, &gpio_config);
        }
    }
    else if(this->handler.Instance == TIM4){
        gpio_config.Alternate = GPIO_AF2_TIM4;
        gpio_config.Pin  = GPIO_PIN_6 *  (channel & TIM::CHANNEL_1);
        gpio_config.Pin |= GPIO_PIN_7 * ((channel & TIM::CHANNEL_2) != 0);
        if(gpio_config.Pin){
            __HAL_RCC_GPIOB_CLK_ENABLE();
            HAL_GPIO_Init(GPIOB, &gpio_config);
        }
    }
    else if(this->handler.Instance == TIM5){
        gpio_config.Alternate = GPIO_AF2_TIM5;
        gpio_config.Pin  = GPIO_PIN_0 *  (channel & TIM::CHANNEL_1);
        gpio_config.Pin |= GPIO_PIN_1 * ((channel & TIM::CHANNEL_2) != 0);
        if(gpio_config.Pin){
            __HAL_RCC_GPIOA_CLK_ENABLE();
            HAL_GPIO_Init(GPIOA, &gpio_config);
        }
    }
    else if(this->handler.Instance == TIM8){
        gpio_config.Alternate = GPIO_AF3_TIM8;
        gpio_config.Pin  = GPIO_PIN_6 *  (channel & TIM::CHANNEL_1);
        gpio_config.Pin |= GPIO_PIN_7 * ((channel & TIM::CHANNEL_2) != 0);
        if(gpio_config.Pin){
            __HAL_RCC_GPIOC_CLK_ENABLE();
            HAL_GPIO_Init(GPIOC, &gpio_config);
        }
    }
    else if(this->handler.Instance == TIM12){
        gpio_config.Alternate = GPIO_AF9_TIM12;
        gpio_config.Pin  = GPIO_PIN_14 *  (channel & TIM::CHANNEL_1);
        gpio_config.Pin |= GPIO_PIN_15 * ((channel & TIM::CHANNEL_2) != 0);
        if(gpio_config.Pin){
            __HAL_RCC_GPIOB_CLK_ENABLE();
            HAL_GPIO_Init(GPIOB, &gpio_config);
        }
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