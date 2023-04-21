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
 * File   : Module.hpp
 * Author : K.Miyauchi
 *
 * Version : 2.00
 */

#ifndef __MiYALAB_STM32_F446RE_TIM_MODULE_HPP__
#define __MiYALAB_STM32_F446RE_TIM_MODULE_HPP__

//--------------------------
// include
//--------------------------
#include "stm32f4xx.h"
#include "stm32f4xx_hal_tim.h"

//--------------------------
// Symbols
//--------------------------
namespace MiYALAB{
namespace STM32{
namespace TIM{
constexpr uint8_t CHANNEL_1 = 0x01;
constexpr uint8_t CHANNEL_2 = 0x02;
constexpr uint8_t CHANNEL_3 = 0x04;
constexpr uint8_t CHANNEL_4 = 0x08;
constexpr uint8_t CHANNEL_ALL = 0xff;

constexpr uint16_t ENCODER_CENTER = (1 << 15) - 1;
constexpr uint16_t ENCODER_MAX = (1<<16) - 1;
}
}
}

//--------------------------
// class
//--------------------------
namespace MiYALAB{
namespace STM32{
namespace TIM{
class Module{
public:
	Module(TIM_TypeDef *instance);
	virtual ~Module();
	virtual bool enable(const uint16_t &divide, const uint16_t &period, const uint8_t &use_channel){return false;}
	virtual bool disable(){return false;}
protected:
	TIM_HandleTypeDef handler;
	virtual bool initGpio(const uint8_t &channel);
};
}
}
}

#endif // __MiYALAB_STM32_F446RE_TIM_MODULE_HPP__

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
