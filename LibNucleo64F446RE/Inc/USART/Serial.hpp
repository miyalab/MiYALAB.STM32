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
 * File  : Serial.hpp
 * Author: K.Miyauchi
 *
 * Version : 1.00
 */

#ifndef __MiYALAB_STM32_F446RE_USART_SERIAL_HPP__
#define __MiYALAB_STM32_F446RE_USART_SERIAL_HPP__

//--------------------------
// include
//--------------------------
#include <stdio.h>

//--------------------------
// Symbol
//--------------------------
namespace MiYALAB {	
namespace STM32{
namespace Serial{
constexpr uint16_t SERIAL_RECV_BUFFSIZE = 128;
constexpr uint16_t SERIAL_SEND_BUFFSIZE = 64;
}
}
}

//--------------------------
// function prototype
//--------------------------
extern "C" {
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#define GETCHAR_PROTOTYPE int __io_getchar(void)
void __io_putchar(uint8_t ch);
int __io_getchar(void);
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#define GETCHAR_PROTOTYPE int fgetc(FILE* f)
#endif
}

namespace MiYALAB{
namespace STM32{
namespace Serial{
void stdioEnable(void(*_putchar)(uint8_t), bool(*_getchar)(uint8_t*), const bool &echo = false);
}
}
}

//--------------------------
// class
//--------------------------
namespace MiYALAB {	
namespace STM32{
namespace Serial{
typedef enum {
    SERIAL_8N1 = 801,
    SERIAL_8N2,
    SERIAL_8E1 = 811,
    SERIAL_8E2,
    SERIAL_8O1 = 821,
    SERIAL_8O2,
    SERIAL_9N1 = 901,
    SERIAL_9N2,
    SERIAL_9E1 = 911,
    SERIAL_9E2,
    SERIAL_9O1 = 921,
    SERIAL_9O2,
} SerialMode;
}
}
}

#endif // __MiYALAB_STM32_F446RE_USART_COMMON_HPP__

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------