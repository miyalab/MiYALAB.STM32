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

    // TIM エンコーダ設定
    TIM_Encoder_InitTypeDef config = {0};
    config.EncoderMode = (use_channel & TIM::CHANNEL_1) * TIM_ENCODERMODE_TI1 | (use_channel & TIM::CHANNEL_2) * TIM_ENCODERMODE_TI2;
    config.IC1Polarity = TIM_ICPOLARITY_RISING;
    config.IC1Selection = TIM_ICSELECTION_DIRECTTI;
    config.IC1Prescaler = TIM_ICPSC_DIV1;
    config.IC1Filter = 0;
    config.IC2Polarity = TIM_ICPOLARITY_RISING;
    config.IC2Selection = TIM_ICSELECTION_DIRECTTI;
    config.IC2Prescaler = TIM_ICPSC_DIV1;
    config.IC2Filter = 0;
    if(HAL_TIM_Encoder_Init(&this->handler, &config) != HAL_OK) return false;

    TIM_MasterConfigTypeDef master_config = {0};
    master_config.MasterOutputTrigger = TIM_TRGO_RESET;
    master_config.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if(HAL_TIMEx_MasterConfigSynchronization(&this->handler, &master_config) != HAL_OK) return false;

    // GPIO 設定
    if(this->initGpio(use_channel)) return false;
    
    // カウント開始
    if(use_channel & TIM::CHANNEL_1) HAL_TIM_Encoder_Start(&this->handler, TIM_CHANNEL_1);
    if(use_channel & TIM::CHANNEL_2) HAL_TIM_Encoder_Start(&this->handler, TIM_CHANNEL_2);
    this->clear();

    return true;
}
}
}
}

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------