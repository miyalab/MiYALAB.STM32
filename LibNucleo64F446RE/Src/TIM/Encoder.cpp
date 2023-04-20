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
    return true;
}

/**
 * @brief initialize gpio port for tim encoder mode
 * 
 * @param use_channel 
 * @return true 
 * @return false 
 */
bool initGpio(const uint8_t &use_channel)
{
    return true;
}
}
}
}

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------