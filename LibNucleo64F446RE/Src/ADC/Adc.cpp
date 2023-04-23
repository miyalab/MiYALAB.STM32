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
 * File   : Adc.cpp
 * Author : K.Miyauchi
 *
 * Version : 1.00
 */

//--------------------------
// include
//--------------------------
#include "ADC/Adc.hpp"

//--------------------------
// method
//--------------------------
namespace MiYALAB{
namespace STM32{
namespace ADConverter{
ADCMode::ADCMode()
{
    this->handler.Instance = ADC1;
    __HAL_RCC_ADC1_CLK_ENABLE();
}

ADCMode::~ADCMode()
{
    this->disable();
    __HAL_RCC_ADC1_CLK_DISABLE();
}

bool ADCMode::enable(const uint16_t &use_channel, const uint32_t &resolution)
{
    this->handler.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
    this->handler.Init.Resolution = resolution;
    this->handler.Init.ScanConvMode = DISABLE;
    this->handler.Init.ContinuousConvMode = DISABLE;
    this->handler.Init.DiscontinuousConvMode = DISABLE;
    this->handler.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    this->handler.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    this->handler.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    this->handler.Init.NbrOfConversion = 1;
    this->handler.Init.DMAContinuousRequests = DISABLE;
    this->handler.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    if(HAL_ADC_Init(&this->handler) != HAL_OK) return false;

    if(!this->initGpio(use_channel)) return false;
}

int16_t ADCMode::read(const uint16_t &channel)
{
    int16_t ret;

    ADC_ChannelConfTypeDef config = {0};
    config.Rank = 1;
    config.SamplingTime = ADC_SAMPLETIME_3CYCLES;

    constexpr uint32_t ADC_CHANNELS[] = {
        ADC_CHANNEL_0,  ADC_CHANNEL_1,  ADC_CHANNEL_2,  ADC_CHANNEL_3,  ADC_CHANNEL_4, 
        ADC_CHANNEL_5,  ADC_CHANNEL_6,  ADC_CHANNEL_7,  ADC_CHANNEL_8,  ADC_CHANNEL_9,
        ADC_CHANNEL_10, ADC_CHANNEL_11, ADC_CHANNEL_12, ADC_CHANNEL_13, ADC_CHANNEL_14,
        ADC_CHANNEL_15
    };
    int16_t shift=0;
    for(uint16_t bits=channel; bits; bits>>=1, shift++);
    if(shift==0 || shift>16) return -1;
    config.Channel = ADC_CHANNELS[shift-1];

    // ADC読み込み
    if(HAL_ADC_ConfigChannel(&this->handler, &config) != HAL_OK) return -1;
    if(HAL_ADC_Start(&this->handler) != HAL_OK) return -1;
    if(HAL_ADC_PollForConversion(&this->handler, 10) != HAL_OK) return -1;
    if(HAL_ADC_GetState(&this->handler) & HAL_ADC_STATE_REG_EOC){
        ret = HAL_ADC_GetValue(&this->handler);
    }
    if(HAL_ADC_Stop(&this->handler) != HAL_OK) return -1;

    return ret;
}

bool ADCMode::initGpio(const uint16_t &channel)
{
    // GPIO設定
    GPIO_InitTypeDef gpio_config = {0};
    gpio_config.Mode = GPIO_MODE_ANALOG;
    gpio_config.Pull = GPIO_NOPULL;

    if(gpio_config.Pin = channel & ADConverter::IN_00_07){
        // gpio_config.Pin =  GPIO_PIN_0 *  (channel & ADConverter::IN_00);
        // gpio_config.Pin |= GPIO_PIN_1 * ((channel & ADConverter::IN_01) != 0);
        // gpio_config.Pin |= GPIO_PIN_2 * ((channel & ADConverter::IN_02) != 0);
        // gpio_config.Pin |= GPIO_PIN_3 * ((channel & ADConverter::IN_03) != 0);
        // gpio_config.Pin |= GPIO_PIN_4 * ((channel & ADConverter::IN_04) != 0);
        // gpio_config.Pin |= GPIO_PIN_5 * ((channel & ADConverter::IN_05) != 0);
        // gpio_config.Pin |= GPIO_PIN_6 * ((channel & ADConverter::IN_06) != 0);
        // gpio_config.Pin |= GPIO_PIN_7 * ((channel & ADConverter::IN_07) != 0);
        __HAL_RCC_GPIOA_CLK_ENABLE();
        HAL_GPIO_Init(GPIOA, &gpio_config);
    }
    if(gpio_config.Pin = (channel & ADConverter::IN_08_09) >> 8){
        __HAL_RCC_GPIOB_CLK_ENABLE();
        HAL_GPIO_Init(GPIOB, &gpio_config);
    }
    if(gpio_config.Pin = (channel & ADConverter::IN_10_15) >> 10){
        __HAL_RCC_GPIOC_CLK_ENABLE();
        HAL_GPIO_Init(GPIOC, &gpio_config);
    }
    return true;
}
}
}
}

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------