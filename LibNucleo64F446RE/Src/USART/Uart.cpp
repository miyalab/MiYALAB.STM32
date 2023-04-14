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
 * File   : Uart.cpp
 * Author : K.Miyauchi
 *
 * Version : 1.00
 */

//--------------------------
// include
//--------------------------
#include "USART/Uart.hpp"

//--------------------------
// global values
//--------------------------
UART_HandleTypeDef *uart_handler1, *uart_handler2, *uart_handler3, *uart_handler4, *uart_handler5, *uart_handler6;
uint8_t *recv1, *recv2, *recv3, *recv4, *recv5, *recv6;
uint8_t *recv_data1, *recv_data2, *recv_data3, *recv_data4, *recv_data5, *recv_data6; 
uint16_t *recv_index1, *recv_index2, *recv_index3, *recv_index4, *recv_index5, *recv_index6;

//--------------------------
// method
//--------------------------
namespace MiYALAB{
namespace STM32{
namespace USART{
UartMode::UartMode(USART_TypeDef *instance)
{
    // USARTクロック許可 / 送受信割込み許可
    if(instance == USART1){
        __HAL_RCC_USART1_CLK_ENABLE();
		HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(USART1_IRQn);
    }
    else if(instance == USART2){
        __HAL_RCC_USART2_CLK_ENABLE();
		HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(USART2_IRQn);
    }
    else if(instance == USART3){
        __HAL_RCC_USART3_CLK_ENABLE();
		HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(USART3_IRQn);
    }
    else if(instance == UART4){
        __HAL_RCC_UART4_CLK_ENABLE();
		HAL_NVIC_SetPriority(UART4_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(UART4_IRQn);
    }
    else if(instance == UART5){
        __HAL_RCC_UART5_CLK_ENABLE();
		HAL_NVIC_SetPriority(UART5_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(UART5_IRQn);
    }
    else if(instance == USART6){
        __HAL_RCC_USART6_CLK_ENABLE();
		HAL_NVIC_SetPriority(USART6_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(USART6_IRQn);
    }
    this->handler.Instance = instance;
}

UartMode::~UartMode()
{
    // UART停止
    HAL_UART_DeInit(&this->handler);

    // USARTクロック不許可 / 割り込み停止
    if(this->handler.Instance == USART1){
        __HAL_RCC_USART1_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(USART1_IRQn);
    }
    else if(this->handler.Instance == USART2){
        __HAL_RCC_USART2_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(USART2_IRQn);
    }
    else if(this->handler.Instance == USART3){
        __HAL_RCC_USART3_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(USART3_IRQn);
    }
    else if(this->handler.Instance == UART4){
        __HAL_RCC_UART4_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(UART4_IRQn);
    }
    else if(this->handler.Instance == UART5){
        __HAL_RCC_UART5_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(UART5_IRQn);
    }
    else if(this->handler.Instance == USART6){
        __HAL_RCC_USART6_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(USART6_IRQn);
    }
}

bool UartMode::enable(const uint32_t &baudrate, const uint32_t &length, const uint32_t &stopbits, const uint32_t parity)
{
    // UART設定
    this->handler.Init.BaudRate = baudrate;
    this->handler.Init.WordLength = length;
    this->handler.Init.StopBits = stopbits;
    this->handler.Init.Parity = parity;
    this->handler.Init.Mode = UART_MODE_TX_RX;
    this->handler.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    this->handler.Init.OverSampling = UART_OVERSAMPLING_16;
    if(HAL_UART_Init(&this->handler) != HAL_OK) return false;

    if(gpioInit() == false) return false;

    return true;
}

bool UartMode::gpioInit()
{
    GPIO_InitTypeDef gpio_config = {0};
    gpio_config.Mode = GPIO_MODE_AF_PP;
    gpio_config.Pull = GPIO_PULLUP;
    gpio_config.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

    if(this->handler.Instance == USART1){
        gpio_config.Alternate = GPIO_AF7_USART1;
        gpio_config.Pin = GPIO_PIN_9 | GPIO_PIN_10;
        __HAL_RCC_GPIOA_CLK_ENABLE();
        HAL_GPIO_Init(GPIOA, &gpio_config);
    }
    else if(this->handler.Instance == USART2){
        gpio_config.Alternate = GPIO_AF7_USART2;
        gpio_config.Pin = GPIO_PIN_2 | GPIO_PIN_3;
        __HAL_RCC_GPIOA_CLK_ENABLE();
        HAL_GPIO_Init(GPIOA, &gpio_config);
    }
    else if(this->handler.Instance == USART3){
        gpio_config.Alternate = GPIO_AF7_USART3;
        gpio_config.Pin = GPIO_PIN_10 | GPIO_PIN_11;
        __HAL_RCC_GPIOC_CLK_ENABLE();
        HAL_GPIO_Init(GPIOC, &gpio_config);
    }
    else if(this->handler.Instance == UART4){
        gpio_config.Alternate = GPIO_AF8_UART4;
        gpio_config.Pin = GPIO_PIN_0 | GPIO_PIN_1;
        __HAL_RCC_GPIOA_CLK_ENABLE();
        HAL_GPIO_Init(GPIOA, &gpio_config);
    }
    else if(this->handler.Instance == UART5){
        gpio_config.Alternate = GPIO_AF8_UART5;
        gpio_config.Pin = GPIO_PIN_12;
        __HAL_RCC_GPIOC_CLK_ENABLE();
        HAL_GPIO_Init(GPIOC, &gpio_config);
        
        gpio_config.Pin = GPIO_PIN_2;
        __HAL_RCC_GPIOD_CLK_ENABLE();
        HAL_GPIO_Init(GPIOD, &gpio_config);
    }
    else if(this->handler.Instance == USART6){
        gpio_config.Alternate = GPIO_AF8_USART6;
        gpio_config.Pin = GPIO_PIN_7 | GPIO_PIN_6;
        __HAL_RCC_GPIOC_CLK_ENABLE();
        HAL_GPIO_Init(GPIOC, &gpio_config);
    }

    return true;
}
}
}
}

//--------------------------
// interrupt handler
//--------------------------
void USART1_IRQHandler(void)
{
	HAL_UART_IRQHandler(uart_handler1);
}

void USART2_IRQHandler(void)
{
	HAL_UART_IRQHandler(uart_handler2);
}

void USART3_IRQHandler(void)
{
	HAL_UART_IRQHandler(uart_handler3);
}

void UART4_IRQHandler(void)
{
	HAL_UART_IRQHandler(uart_handler4);
}

void UART5_IRQHandler(void)
{
	HAL_UART_IRQHandler(uart_handler5);
}

void USART6_IRQHandler(void)
{
	HAL_UART_IRQHandler(uart_handler6);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *handler)
{
    if(handler->Instance == USART1){
        recv_data1[(*recv_index1)++] = *recv1;
        if(*recv_index1 == MiYALAB::STM32::Serial::SERIAL_RECV_BUFFSIZE) *recv_index1 = 0;
        HAL_UART_Receive_IT(handler, recv1, 1);
    }
    if(handler->Instance == USART2){
        recv_data2[(*recv_index2)++] = *recv1;
        if(*recv_index2 == MiYALAB::STM32::Serial::SERIAL_RECV_BUFFSIZE) *recv_index2 = 0;
        HAL_UART_Receive_IT(handler, recv2, 1);
    }
    if(handler->Instance == USART3){
        
    }
    if(handler->Instance == UART4){
        
    }
    if(handler->Instance == UART5){
        
    }
    if(handler->Instance == USART6){
        
    }
}

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------