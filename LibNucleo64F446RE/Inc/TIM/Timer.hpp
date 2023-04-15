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
 * File   : Timer.hpp
 * Author : K.Miyauchi
 *
 * Version : 2.00
 */

#ifndef __MiYALAB_STM32_F446RE_TIM_TIMER_HPP__
#define __MiYALAB_STM32_F446RE_TIM_TIMER_HPP__

//--------------------------
// include
//--------------------------
#include "TIM/Common.hpp"

//--------------------------
// function prototype
//--------------------------
extern "C" {
void TIM6_DAC_IRQHandler(void);
void TIM7_IRQHandler(void);
}

//--------------------------
// class
//--------------------------
namespace MiYALAB{
namespace STM32{
namespace TIM{
class TimerMode: public TIM::Module{
public:
	TimerMode(TIM_TypeDef *instance);
	virtual ~TimerMode();
	bool enable(const uint16_t &divide, const uint16_t &period, void(*function)(void));
};
}
}
}

#endif // __MiYALAB_STM32_F446RE_TIM_TIMER_HPP__

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
