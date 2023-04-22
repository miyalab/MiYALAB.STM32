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
 * File   : Serial.cpp
 * Author : K.Miyauchi
 *
 * Version : 1.00
 */

//--------------------------
// include
//--------------------------
#include "USART/Serial.hpp"

//--------------------------
// global values
//--------------------------
namespace MiYALAB{
namespace STM32{
namespace Serial{
void(*putcharFunction)(uint8_t);
bool(*getcharFunction)(uint8_t*);
bool echo_flag = false;
} 
}
}

//--------------------------
// function
//--------------------------
void __io_putchar(uint8_t ch) {
	// 1文字送信
	MiYALAB::STM32::Serial::putcharFunction(ch);
}

int __io_getchar(void) {
	uint8_t data;

	// 1文字受信
	while (MiYALAB::STM32::Serial::getcharFunction(&data));

	// エコーバック
	if(MiYALAB::STM32::Serial::echo_flag) MiYALAB::STM32::Serial::putcharFunction(data);

	return (data);
}

namespace MiYALAB{
namespace STM32{
namespace Serial{
void stdioEnable(void(*_putchar)(uint8_t), bool(*_getchar)(uint8_t*), const bool &echo)
{
	setbuf(stdout, NULL);
	setbuf(stdin, NULL);
	Serial::putcharFunction = _putchar;
	Serial::getcharFunction = _getchar;
	Serial::echo_flag = echo;
}
}
}
}

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------