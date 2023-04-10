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

constexpr uint16_t UART_RECV_BUFFSIZE = 128;

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
	bool enable(const uint32_t &baudrate, const uint32_t &length, const uint32_t &stopbits, const uint32_t parity);
    bool receive(uint8_t *c, const uint16_t &timeout = 0xff) {return (HAL_UART_Receive(&this->handler, c, 1, timeout)==HAL_OK);}
    bool receive(uint8_t *str, const uint16_t &size, const uint16_t &timeout = 0xff) {return (HAL_UART_Receive(&this->handler, str, size, timeout)==HAL_OK);}
    bool transmit(const uint8_t &c, const uint16_t &timeout = 0xff) {return (HAL_UART_Transmit(&this->handler, &c, 1, timeout)==HAL_OK);}
    bool transmit(const uint8_t *str, const uint16_t &size, const uint16_t &timeout = 0xff) {return (HAL_UART_Transmit(&this->handler, str, size, timeout)==HAL_OK);}
private:
	UART_HandleTypeDef handler;
    bool gpioInit();
};
}
}
}

#endif // __MiYALAB_STM32_F446RE_USART_UART_HPP__

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
