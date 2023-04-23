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

int16_t ADCMode::read(const uint16_t channel)
{

}

bool ADCMode::initGpio(const uint16_t &channel)
{
    GPIO_InitTypeDef gpio_config = {0};
    gpio_config.Mode = GPIO_MODE_ANALOG;
    gpio_config.Pull = GPIO_NOPULL;

    if(channel & ADConverter::IN_00_07){
        gpio_config.Pin =  GPIO_PIN_0 *  (channel & ADConverter::IN_00);
        gpio_config.Pin |= GPIO_PIN_1 * ((channel & ADConverter::IN_01) != 0);
        gpio_config.Pin |= GPIO_PIN_2 * ((channel & ADConverter::IN_02) != 0);
        gpio_config.Pin |= GPIO_PIN_3 * ((channel & ADConverter::IN_03) != 0);
        gpio_config.Pin |= GPIO_PIN_4 * ((channel & ADConverter::IN_04) != 0);
        gpio_config.Pin |= GPIO_PIN_5 * ((channel & ADConverter::IN_05) != 0);
        gpio_config.Pin |= GPIO_PIN_6 * ((channel & ADConverter::IN_06) != 0);
        gpio_config.Pin |= GPIO_PIN_7 * ((channel & ADConverter::IN_07) != 0);
        if(gpio_config.Pin){
            __HAL_RCC_GPIOA_CLK_ENABLE();
        }
    }
    if(channel & ADConverter::IN_08_09){
        if(gpio_config.Pin){
            __HAL_RCC_GPIOB_CLK_ENABLE();
        }
    }
    if(channel & ADConverter::IN_10_15){
        if(gpio_config.Pin){
            __HAL_RCC_GPIOC_CLK_ENABLE();
        }
    }
    return true;
}
}
}
}

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------