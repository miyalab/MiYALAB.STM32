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
#include <stdlib.h>
#include <string.h>
#include "USART/Uart.hpp"
#include "USART/Serial.hpp"

//--------------------------
// global values
//--------------------------
namespace MiYALAB{
namespace STM32{
namespace USART{
struct UartReceiveStruct{
    UART_HandleTypeDef *handler;
    uint8_t *data;
    int16_t *index;
} uart_recv[6];
}
}
}

//--------------------------
// method
//--------------------------
namespace MiYALAB{
namespace STM32{
namespace USART{
/**
 * @brief Construct a new Uart Mode:: Uart Mode object
 * 
 * @param instance  USART1(Tx:PA9 , Rx:PA10), 
 *                  USART2(Tx:PA2 , Rx:PA3 ), 
 *                  USART3(Tx:PC10, Rx:PC11), 
 *                  UART4 (Tx:PA0 , Rx:PA1 ), 
 *                  UART5 (Tx:PC12 ,Rx:PD2 ), 
 *                  USART6(Tx:PC6 , Rx:PC7 )
 */
UartMode::UartMode(USART_TypeDef *instance)
{
    this->recv_data = new uint8_t[Serial::SERIAL_RECV_BUFF_SIZE];

    // USARTクロック許可 / 送受信割込み許可
    int index;
    if(instance == USART1){
        index = 0;
        __HAL_RCC_USART1_CLK_ENABLE();
		HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(USART1_IRQn);
    }
    else if(instance == USART2){
        index = 1;
        __HAL_RCC_USART2_CLK_ENABLE();
		HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(USART2_IRQn);
    }
    else if(instance == USART3){
        index = 2;        
        __HAL_RCC_USART3_CLK_ENABLE();
		HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(USART3_IRQn);
    }
    else if(instance == UART4){
        index = 3;
        __HAL_RCC_UART4_CLK_ENABLE();
		HAL_NVIC_SetPriority(UART4_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(UART4_IRQn);
    }
    else if(instance == UART5){
        index = 4;
        __HAL_RCC_UART5_CLK_ENABLE();
		HAL_NVIC_SetPriority(UART5_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(UART5_IRQn);
    }
    else if(instance == USART6){
        index = 5;
        __HAL_RCC_USART6_CLK_ENABLE();
		HAL_NVIC_SetPriority(USART6_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(USART6_IRQn);
    }
    this->handler.Instance = instance;
    uart_recv[index].handler = &this->handler;
    uart_recv[index].index = &this->recv_index;
    uart_recv[index].data = this->recv_data;
}

/**
 * @brief Destroy the Uart Mode:: Uart Mode object
 * 
 */
UartMode::~UartMode()
{
    // UART停止
    HAL_UART_DeInit(&this->handler);
    delete (this->recv_data);

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

/**
 * @brief enable method
 * 
 * @param baudrate baudrate for uart
 * @param length   data length for uart
 * @param stopbits stopbits length for uart 
 * @param parity   parity type for uart
 * @return true 
 * @return false 
 */
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
    this->recv_index = this->read_index = 0;
    return HAL_UART_Receive_IT(&this->handler, &this->recv_data[0], 1) == HAL_OK;
}

/**
 * @brief uart available method
 * 
 * @return int16_t: received data length 
 */
int16_t UartMode::available()
{
    /** 以下のコードと同処理
     * if (this->recv_index > this->read_index) return this->recv_index - this->read_index;
     * else return Serial::SERIAL_RECV_BUFF_SIZE + this->recv_index - this->read_index;
    */
    return (this->recv_index - this->read_index) + (this->recv_index < this->read_index) * Serial::SERIAL_RECV_BUFF_SIZE;
}

/**
 * @brief read method
 * 
 * @return int16_t: received 1 byte data
 */
int16_t UartMode::read()
{
    if(this->recv_index == this->read_index) return -1;
    uint8_t ret = recv_data[read_index++];
    read_index *= read_index < Serial::SERIAL_RECV_BUFF_SIZE;    // read_indexがRECV_BUFF_SIZE以上なら0にする．
    return ret;
}

/**
 * @brief numeric type data transmit to computer by uart
 * 
 * @tparam T: numeric type
 * @param data 
 * @return size_t: transmitted data length
 */
template<typename T> size_t UartMode::print(const T &data)
{
    char str[10] = "";
    sprintf(str, "%d", data);
    size_t length = strlen(str);
    this->transmit((uint8_t*)str, length);
    return length;
}
template<> size_t UartMode::print<char>(const char &data)
{
    this->transmit((uint8_t*)&data, 1);
    return 1;
}
template<> size_t UartMode::print<int32_t>(const int32_t &data)
{
    char str[10] = "";
    sprintf(str, "%ld", data);
    size_t length = strlen(str);
    this->transmit((uint8_t*)str, length);
    return length;
}
template<> size_t UartMode::print<uint32_t>(const uint32_t &data)
{
    char str[10] = "";
    sprintf(str, "%ld", data);
    size_t length = strlen(str);
    this->transmit((uint8_t*)str, length);
    return length;
}
template size_t UartMode::print<int8_t>(const int8_t&);
template size_t UartMode::print<uint8_t>(const uint8_t&);
template size_t UartMode::print<int16_t>(const int16_t&);
template size_t UartMode::print<uint16_t>(const uint16_t&);
template size_t UartMode::print<int>(const int&);
template size_t UartMode::print<unsigned int>(const unsigned int&);

/**
 * @brief string type data transmit to computer by uart
 * 
 * @tparam T: string type
 * @param data 
 * @return size_t: transmitted data length
 */
template<typename T> size_t UartMode::print(const T *data)
{
    size_t length = strlen((char*)data);
    this->transmit((uint8_t*)data, length);
    return length;
}
template size_t UartMode::print<char>(const char*);
template size_t UartMode::print<unsigned char>(const unsigned char*);
template size_t UartMode::print<int8_t>(const int8_t*);

/**
 * @brief binary type data transmit to computer by uart
 * 
 * @tparam T: binary type
 * @param data 
 * @return size_t: transmitted data length
 */
template <typename T> size_t UartMode::write(const T &data)
{
    size_t length = sizeof(T);
    this->transmit((uint8_t*)(&data), length);
    return length;
}
template size_t UartMode::write<char>(const char &);
template size_t UartMode::write<int8_t>(const int8_t &);
template size_t UartMode::write<uint8_t>(const uint8_t &);
template size_t UartMode::write<int16_t>(const int16_t &);
template size_t UartMode::write<uint16_t>(const uint16_t &);
template size_t UartMode::write<int>(const int &);
template size_t UartMode::write<unsigned int>(const unsigned int &);
template size_t UartMode::write<int32_t>(const int32_t &);
template size_t UartMode::write<uint32_t>(const uint32_t &);

/**
 * @brief Initialize gpio for uart.
 * 
 * @return true 
 * @return false 
 */
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
    else return false;
    return true;
}
}
}
}

//--------------------------
// interrupt handler
//--------------------------
void USART1_IRQHandler(void){HAL_UART_IRQHandler(MiYALAB::STM32::USART::uart_recv[0].handler);}
void USART2_IRQHandler(void){HAL_UART_IRQHandler(MiYALAB::STM32::USART::uart_recv[1].handler);}
void USART3_IRQHandler(void){HAL_UART_IRQHandler(MiYALAB::STM32::USART::uart_recv[2].handler);}
void UART4_IRQHandler(void) {HAL_UART_IRQHandler(MiYALAB::STM32::USART::uart_recv[3].handler);}
void UART5_IRQHandler(void) {HAL_UART_IRQHandler(MiYALAB::STM32::USART::uart_recv[4].handler);}
void USART6_IRQHandler(void){HAL_UART_IRQHandler(MiYALAB::STM32::USART::uart_recv[5].handler);}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *handler)
{
    using namespace MiYALAB::STM32::USART;
    int index;
    if(handler->Instance == USART1)      index = 0;
    else if(handler->Instance == USART2) index = 1;
    else if(handler->Instance == USART3) index = 2;
    else if(handler->Instance == UART4)  index = 3;
    else if(handler->Instance == UART5)  index = 4;
    else if(handler->Instance == USART6) index = 5;
    *uart_recv[index].index *= ++(*uart_recv[index].index) < MiYALAB::STM32::Serial::SERIAL_RECV_BUFF_SIZE; // recv_indexを増加させたときにSERIAL_RECV_BUFF_SIZE以上なら0にする
    HAL_UART_Receive_IT(handler, &uart_recv[index].data[*uart_recv[index].index], 1);
}

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
