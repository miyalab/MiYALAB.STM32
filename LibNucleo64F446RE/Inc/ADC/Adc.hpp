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
 * File   : Adc.hpp
 * Author : K.Miyauchi
 *
 * Version : 2.00
 */

#ifndef __MiYALAB_STM32_F446RE_ADC_ADC_HPP__
#define __MiYALAB_STM32_F446RE_ADC_ADC_HPP__

//--------------------------
// include
//--------------------------
#include "stm32f4xx.h"
#include "stm32f4xx_hal_adc.h"

//--------------------------
// Symbols
//--------------------------
namespace MiYALAB{
namespace STM32{
namespace ADConverter{
constexpr uint16_t IN_01 = 0x01;
constexpr uint16_t IN_02 = 0x01 << 1;
constexpr uint16_t IN_03 = 0x01 << 2;
constexpr uint16_t IN_04 = 0x01 << 3;
constexpr uint16_t IN_05 = 0x01 << 4;
constexpr uint16_t IN_06 = 0x01 << 5;
constexpr uint16_t IN_07 = 0x01 << 6;
constexpr uint16_t IN_08 = 0x01 << 7;
constexpr uint16_t IN_09 = 0x01 << 8;
constexpr uint16_t IN_10 = 0x01 << 9;
constexpr uint16_t IN_11 = 0x01 << 10;
constexpr uint16_t IN_12 = 0x01 << 11;
constexpr uint16_t IN_13 = 0x01 << 12;
constexpr uint16_t IN_14 = 0x01 << 13;
constexpr uint16_t IN_15 = 0x01 << 14;
}
}
}

//--------------------------
// class
//--------------------------
namespace MiYALAB{
namespace STM32{
namespace ADconverter{
class ADCMode{
public:
	ADCMode();
	virtual ~ADCMode();
	bool enable(const uint16_t &divide, const uint16_t &period, const uint8_t &use_channel);
	bool disable();
	int16_t read(uint16_t channel);
protected:
	TIM_HandleTypeDef handler;
	virtual bool initGpio(const uint8_t &channel);
};
}
}
}

#endif // __MiYALAB_STM32_F446RE_ADC_ADC_HPP__

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
