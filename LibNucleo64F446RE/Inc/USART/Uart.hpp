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
 * File   : Uart.hpp
 * Author : K.Miyauchi
 *
 * Version : 2.00
 */

#ifndef __MiYALAB_STM32_F446RE_USART_UART_HPP__
#define __MiYALAB_STM32_F446RE_USART_UART_HPP__

//--------------------------
// include
//--------------------------
#include "stm32f4xx.h"
#include "stm32f4xx_hal_uart.h"

//--------------------------
// function prototype
//--------------------------
extern "C" {
void USART1_IRQHandler();
void USART2_IRQHandler();
void USART3_IRQHandler();
void UART4_IRQHandler();
void UART5_IRQHandler();
void USART6_IRQHandler();
}

//--------------------------
// class
//--------------------------
namespace MiYALAB{
namespace STM32{
namespace USART{
class UartMode{
public:
	UartMode(USART_TypeDef *instance);
	virtual ~UartMode();
	bool enable(const uint32_t &baudrate, const uint32_t &length = UART_WORDLENGTH_8B, const uint32_t &stopbits = UART_STOPBITS_1, const uint32_t parity = UART_PARITY_NONE);
    int16_t available();
    int16_t read();
    template<typename T> size_t print(const T &data);
    template<typename T> size_t print(const T *data);
    template<typename T> size_t println(const T data){size_t length = this->print(data); this->transmit((uint8_t*)"\n", 1); return length+1;}
    template<typename T> size_t write(const T &data);
    template<typename T> size_t write(const T *data){return this->print(data);}

private:
	UART_HandleTypeDef handler;
    int16_t recv_index;
    int16_t read_index;
    uint8_t *recv_data;
    bool gpioInit();
    bool receive(uint8_t *str, const uint16_t &size, const uint16_t &timeout = 0xff) {return (HAL_UART_Receive(&this->handler, str, size, timeout)==HAL_OK);}
    bool transmit(const uint8_t *str, const uint16_t &size, const uint16_t &timeout = 0xff) {return (HAL_UART_Transmit(&this->handler, str, size, timeout)==HAL_OK);}
};
}
}
}

#endif // __MiYALAB_STM32_F446RE_USART_UART_HPP__

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
