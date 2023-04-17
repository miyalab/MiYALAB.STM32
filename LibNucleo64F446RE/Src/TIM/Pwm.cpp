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
#include "TIM/Pwm.hpp"

//--------------------------
// method
//--------------------------
namespace MiYALAB{
namespace STM32{
namespace TIM{
/**
 * @brief Construct a new Pwm Mode:: Pwm Mode object
 * 
 * @param instance: TIM1 (CH1-4: )
 *                  TIM2 (CH1-4: )
 *                  TIM3 (CH1-4: )
 *                  TIM4 (CH1-4: )
 *                  TIM5 (CH1-4: )
 *                  TIM8 (CH1-4: )
 *                  TIM12(CH1-4: )
 */
PwmMode::PwmMode(TIM_TypeDef *instance) : TIM::Module(instance)
{
    
}

/**
 * @brief Destroy the Pwm Mode:: Pwm Mode object
 * 
 */
PwmMode::~PwmMode()
{
    // PWM停止
    HAL_TIM_PWM_Stop(&this->handler, TIM_CHANNEL_ALL);
    HAL_TIM_PWM_DeInit(&this->handler);
}

/**
 * @brief disable method
 * 
 * @param divide 
 * @param period 
 * @param use_channel 
 * @return true 
 * @return false 
 */
bool PwmMode::enable(const uint16_t &divide, const uint16_t &period, const uint8_t &use_channel)
{
    // TIMレジスタ設定
    this->handler.Init.Prescaler = divide - 1;
    this->handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    this->handler.Init.Period = period - 1;
    this->handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    this->handler.Init.AutoReloadPreload = TIM_AUTOMATICOUTPUT_DISABLE;
    if(HAL_TIM_PWM_Init(&this->handler) != HAL_OK) return false;
    
    // TIMマスタ設定
    TIM_MasterConfigTypeDef master_config = {0};
    master_config.MasterOutputTrigger = TIM_TRGO_RESET;
    master_config.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if(HAL_TIMEx_MasterConfigSynchronization(&this->handler, &master_config) != HAL_OK) return false;

    // TIMブレーキデッドタイム設定
    if(this->handler.Instance == TIM1 || this->handler.Instance == TIM8){
        TIM_BreakDeadTimeConfigTypeDef break_dead_time_config = {0};
        break_dead_time_config.OffStateRunMode = TIM_OSSR_DISABLE;
        break_dead_time_config.OffStateIDLEMode = TIM_OSSI_DISABLE;
        break_dead_time_config.LockLevel = TIM_LOCKLEVEL_OFF;
        break_dead_time_config.DeadTime = 0;
        break_dead_time_config.BreakState = TIM_BREAK_DISABLE;
        break_dead_time_config.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
        break_dead_time_config.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
        if (HAL_TIMEx_ConfigBreakDeadTime(&this->handler, &break_dead_time_config) != HAL_OK) return HAL_ERROR;
    }

    // GPIO設定
    if(!this->initGpio(use_channel)) return false;

    // TIMチャンネル1設定
    TIM_OC_InitTypeDef oc_config = {0};
    oc_config.OCMode = TIM_OCMODE_PWM1;
    oc_config.Pulse = 0;
    oc_config.OCPolarity = TIM_OCPOLARITY_HIGH;
    oc_config.OCFastMode = TIM_OCFAST_DISABLE;
    if(use_channel & TIM::CHANNEL_1){
        if(HAL_TIM_PWM_ConfigChannel(&this->handler, &oc_config, TIM_CHANNEL_1) != HAL_OK) return false;
        HAL_TIM_PWM_Start(&this->handler, TIM_CHANNEL_1);
    }
    if(use_channel & TIM::CHANNEL_2){
        if(HAL_TIM_PWM_ConfigChannel(&this->handler, &oc_config, TIM_CHANNEL_2) != HAL_OK) return false;
        HAL_TIM_PWM_Start(&this->handler, TIM_CHANNEL_2);
    }
    if(use_channel & TIM::CHANNEL_3){
        if(HAL_TIM_PWM_ConfigChannel(&this->handler, &oc_config, TIM_CHANNEL_3) != HAL_OK) return false;
        HAL_TIM_PWM_Start(&this->handler, TIM_CHANNEL_3);
    }
    if(use_channel & TIM::CHANNEL_4){
        if(HAL_TIM_PWM_ConfigChannel(&this->handler, &oc_config, TIM_CHANNEL_4) != HAL_OK) return false;
        HAL_TIM_PWM_Start(&this->handler, TIM_CHANNEL_4);
    }
    return true;
}

/**
 * @brief initialize gpio port for tim pwm mode
 * 
 * @param channel 
 * @return true 
 * @return false 
 */
bool PwmMode::initGpio(const uint8_t &channel)
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
        gpio_config.Pin |= GPIO_PIN_10 * ((channel & TIM::CHANNEL_3) != 0);
        gpio_config.Pin |= GPIO_PIN_11 * ((channel & TIM::CHANNEL_4) != 0);
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
        if(gpio_config.Pin){
            __HAL_RCC_GPIOB_CLK_ENABLE();
            HAL_GPIO_Init(GPIOB, &gpio_config);
        }
    }
    else if(this->handler.Instance == TIM4){
        gpio_config.Alternate = GPIO_AF2_TIM4;
        gpio_config.Pin  = GPIO_PIN_6 *  (channel & TIM::CHANNEL_1);
        gpio_config.Pin |= GPIO_PIN_7 * ((channel & TIM::CHANNEL_2) != 0);
        gpio_config.Pin |= GPIO_PIN_8 * ((channel & TIM::CHANNEL_3) != 0);
        gpio_config.Pin |= GPIO_PIN_9 * ((channel & TIM::CHANNEL_4) != 0);
        if(gpio_config.Pin){
            __HAL_RCC_GPIOB_CLK_ENABLE();
            HAL_GPIO_Init(GPIOB, &gpio_config);
        }
    }
    else if(this->handler.Instance == TIM5){
        gpio_config.Alternate = GPIO_AF2_TIM5;
        gpio_config.Pin  = GPIO_PIN_0 *  (channel & TIM::CHANNEL_1);
        gpio_config.Pin |= GPIO_PIN_1 * ((channel & TIM::CHANNEL_2) != 0);
        gpio_config.Pin |= GPIO_PIN_2 * ((channel & TIM::CHANNEL_3) != 0);
        gpio_config.Pin |= GPIO_PIN_3 * ((channel & TIM::CHANNEL_4) != 0);
        if(gpio_config.Pin){
            __HAL_RCC_GPIOA_CLK_ENABLE();
            HAL_GPIO_Init(GPIOA, &gpio_config);
        }
    }
    else if(this->handler.Instance == TIM8){
        gpio_config.Alternate = GPIO_AF3_TIM8;
        gpio_config.Pin  = GPIO_PIN_6 *  (channel & TIM::CHANNEL_1);
        gpio_config.Pin |= GPIO_PIN_7 * ((channel & TIM::CHANNEL_2) != 0);
        gpio_config.Pin |= GPIO_PIN_8 * ((channel & TIM::CHANNEL_3) != 0);
        gpio_config.Pin |= GPIO_PIN_9 * ((channel & TIM::CHANNEL_4) != 0);
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