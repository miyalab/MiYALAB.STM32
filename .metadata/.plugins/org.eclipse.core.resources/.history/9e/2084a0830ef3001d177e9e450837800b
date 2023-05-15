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
 * File   : Timer.cpp
 * Author : K.Miyauchi
 *
 * Version : 1.00
 */

//--------------------------
// include
//--------------------------
#include "TIM/Timer.hpp"

//--------------------------
// global values
//--------------------------
TIM_HandleTypeDef *tim_handler6;
TIM_HandleTypeDef *tim_handler7;

void (*interruptFunction6)(void);
void (*interruptFunction7)(void);

//--------------------------
// method
//--------------------------
namespace MiYALAB{
namespace STM32{
namespace TIM{
/**
 * @brief Construct a new Timer Mode:: Timer Mode object
 * 
 * @param instance TIM6, TIM7
 */
TimerMode::TimerMode(TIM_TypeDef *instance) : TIM::Module(instance)
{
    // TIMクロック許可
    if(instance == TIM6){
        HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
        tim_handler6 = &this->handler;
    }
    else if(instance == TIM7){
        HAL_NVIC_SetPriority(TIM7_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(TIM7_IRQn);
        tim_handler7 = &this->handler;
    }
}

/**
 * @brief Destroy the Timer Mode:: Timer Mode object
 * 
 */
TimerMode::~TimerMode()
{
    // TIMクロック不許可
    HAL_TIM_Base_Stop_IT(&this->handler);
    HAL_TIM_Base_DeInit(&this->handler);
    if(this->handler.Instance == TIM6){
        HAL_NVIC_DisableIRQ(TIM6_DAC_IRQn);
        tim_handler6 = nullptr;
    } 
    else if(this->handler.Instance == TIM7) {
		HAL_NVIC_DisableIRQ(TIM7_IRQn);
        tim_handler7 = nullptr;
    }
}

bool TimerMode::enable(void(*function)(void), const uint16_t &divide, const uint16_t &period)
{
    // TIMレジスタ設定
    this->handler.Init.Prescaler = divide - 1;
    this->handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    this->handler.Init.Period = period - 1;
    this->handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    if(HAL_TIM_Base_Init(&this->handler) != HAL_OK) return false;

    // TIMマスタ設定
    TIM_MasterConfigTypeDef master_config = {0};
    master_config.MasterOutputTrigger = TIM_TRGO_RESET;
    master_config.MasterSlaveMode = TIM_MASTERSLAVEMODE_ENABLE;
    if(HAL_TIMEx_MasterConfigSynchronization(&this->handler, &master_config) != HAL_OK) return false;

    // タイマー割り込み許可
    if(this->handler.Instance == TIM6) interruptFunction6 = function;
    else if(this->handler.Instance == TIM7) interruptFunction7 = function;
    HAL_TIM_Base_Start_IT(&this->handler);

    return true;
}
}
}
}

//--------------------------
// interrupt handler
//--------------------------
void TIM6_DAC_IRQHandler(void)
{
	HAL_TIM_IRQHandler(tim_handler6);
    interruptFunction6();
}

void TIM7_IRQHandler(void)
{
	HAL_TIM_IRQHandler(tim_handler7);
	interruptFunction7();
}

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------