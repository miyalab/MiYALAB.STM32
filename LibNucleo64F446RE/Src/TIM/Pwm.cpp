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
 * @param instance: TIM1 (CH1-4: PA8,  PA9, PA10, PA11)
 *                  TIM2 (CH1-4: PA5,  PB3, PB10, PB2)
 *                  TIM3 (CH1-4: PB4,  PB5, PB0,  PB1)
 *                  TIM4 (CH1-4: PB6,  PB7, PB8,  PB9)
 *                  TIM5 (CH1-4: PA0,  PA1, PA2,  PA3)
 *                  TIM8 (CH1-4: PC6,  PC7, PC8,  PC9)
 *                  TIM12(CH1-2: PB14, PB15)
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
    this->disable();
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

    // TIMチャンネル設定
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
}
}
}

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------