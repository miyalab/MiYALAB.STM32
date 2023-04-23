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
constexpr uint16_t IN_00 = 0x0001;
constexpr uint16_t IN_01 = 0x0001 << 1;
constexpr uint16_t IN_02 = 0x0001 << 2;
constexpr uint16_t IN_03 = 0x0001 << 3;
constexpr uint16_t IN_04 = 0x0001 << 4;
constexpr uint16_t IN_05 = 0x0001 << 5;
constexpr uint16_t IN_06 = 0x0001 << 6;
constexpr uint16_t IN_07 = 0x0001 << 7;
constexpr uint16_t IN_08 = 0x0001 << 8;
constexpr uint16_t IN_09 = 0x0001 << 9;
constexpr uint16_t IN_10 = 0x0001 << 10;
constexpr uint16_t IN_11 = 0x0001 << 11;
constexpr uint16_t IN_12 = 0x0001 << 12;
constexpr uint16_t IN_13 = 0x0001 << 13;
constexpr uint16_t IN_14 = 0x0001 << 14;
constexpr uint16_t IN_15 = 0x0001 << 15;
constexpr uint16_t IN_00_07 = 0x00ff;
constexpr uint16_t IN_08_09 = 0x0300;
constexpr uint16_t IN_10_15 = 0xfc00;
constexpr uint16_t IN_ALL = 0xffff;
}
}
}

//--------------------------
// class
//--------------------------
namespace MiYALAB{
namespace STM32{
namespace ADConverter{
class ADCMode{
public:
	ADCMode();
	virtual ~ADCMode();
	bool enable(const uint16_t &use_channel, const uint32_t &resolution = ADC_RESOLUTION_12B);
	bool disable();
	int16_t read(uint16_t channel);
protected:
	ADC_HandleTypeDef handler;
	bool initGpio(const uint16_t &channel);
};
}
}
}

#endif // __MiYALAB_STM32_F446RE_ADC_ADC_HPP__

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
