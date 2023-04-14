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
 * File   : Pwm.hpp
 * Author : K.Miyauchi
 *
 * Version : 2.00
 */

#ifndef __MiYALAB_STM32_F446RE_TIM_ENCODER_HPP__
#define __MiYALAB_STM32_F446RE_TIM_ENCODER_HPP__

//--------------------------
// include
//--------------------------
#include "TIM/Common.hpp"

//--------------------------
// class
//--------------------------
namespace MiYALAB{
namespace STM32{
namespace TIM{
class EncoderMode: public TIM::Module{
public:
	EncoderMode(TIM_TypeDef *instance);
	virtual ~EncoderMode();
	bool enable(const uint16_t &divide, const uint16_t &period, const uint8_t &use_channel) override;

    void clear(){this->handler.Instance->CNT = TIM::ENCODER_CENTER;}
    int16_t count(){return this->handler.Instance->CNT - TIM::ENCODER_CENTER;}
private:
	bool initGpio(const uint8_t &channel) override;
};
}
}
}

#endif // __MiYALAB_STM32_F446RE_TIM_ENCODER_HPP__

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
