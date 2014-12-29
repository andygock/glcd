/**
	\file STM32F4.h
	\author Andy Gock (modified for STM32F4xx by Moreto)
	\brief Functions specific to STM32 F4 ARM Cortex-M4 devices.
 */

/*
	Copyright (c) 2012, Andy Gock

	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:
		* Redistributions of source code must retain the above copyright
		  notice, this list of conditions and the following disclaimer.
		* Redistributions in binary form must reproduce the above copyright
		  notice, this list of conditions and the following disclaimer in the
		  documentation and/or other materials provided with the distribution.
		* Neither the name of Andy Gock nor the
		  names of its contributors may be used to endorse or promote products
		  derived from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL ANDY GOCK BE LIABLE FOR ANY
	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef STM32F4XX_H_
#define STM32F4XX_H_

#if defined(GLCD_DEVICE_STM32F4XX)

#include <stm32f4xx.h>


/* SPIx Communication boards Interface */
#define SPIx                           SPI3
#define SPIx_CLK                       RCC_APB1Periph_SPI3
#define SPIx_CLK_INIT                  RCC_APB1PeriphClockCmd
#define SPIx_PRESCALLER				   SPI_BaudRatePrescaler_8

#define SPIx_SCK_PIN                   GPIO_Pin_3
#define SPIx_SCK_GPIO_PORT             GPIOB
#define SPIx_SCK_GPIO_CLK              RCC_AHB1Periph_GPIOB
#define SPIx_SCK_SOURCE                GPIO_PinSource3
#define SPIx_SCK_AF                    GPIO_AF_SPI3

#if 0 // Not using MISO pin for this LCD.
#define SPIx_MISO_PIN                  GPIO_Pin_4
#define SPIx_MISO_GPIO_PORT            GPIOB
#define SPIx_MISO_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define SPIx_MISO_SOURCE               GPIO_PinSource4
#define SPIx_MISO_AF                   GPIO_AF_SPI3
#endif

#define SPIx_MOSI_PIN                  GPIO_Pin_5
#define SPIx_MOSI_GPIO_PORT            GPIOB
#define SPIx_MOSI_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define SPIx_MOSI_SOURCE               GPIO_PinSource5
#define SPIx_MOSI_AF                   GPIO_AF_SPI3

/* Backlight config */
/* Comment the following line if you just want to use an
 * ON and OFF backlight (no brightness control) */
#define USE_TIMER_PWM
//define BACKLIGHT_INVERT_OUT	// Uncoment if your backlight turn on with a low value.
#define LCD_LED_PIN					GPIO_Pin_15 // Should be and TIMx_CHx pin.
#define LCD_LED_PORT				GPIOA
#define LCD_LED_GPIO_RCC			RCC_AHB1Periph_GPIOA
#ifdef USE_TIMER_PWM
  #define LCD_LED_PinSource			GPIO_PinSource15
  #define LCD_TIM					TIM2
  #define LCD_AF					GPIO_AF_TIM2
  #define LCD_TIM_OCInit			TIM_OC1Init
  #define LCD_TIM_OCPreload			TIM_OC1PreloadConfig
  #define LCD_TIM_RCC				RCC_APB1Periph_TIM2
  #define LCD_TIM_PeriphClockCmd	RCC_APB1PeriphClockCmd
  #define LCD_TIM_SetCompare		TIM_SetCompare1
  #define LCD_TIM_Sys_Prescaller	1 // Nucleo board TIM2 clock is the same of systemcoreclock
#endif



#define CONTROLLER_SPI_SS_PORT  GPIOB
#define CONTROLLER_SPI_SS_PIN   GPIO_Pin_8
#define CONTROLLER_SPI_SS_RCC	RCC_AHB1Periph_GPIOB
#define CONTROLLER_SPI_DC_PORT  GPIOB
#define CONTROLLER_SPI_DC_PIN   GPIO_Pin_4
#define CONTROLLER_SPI_DC_RCC	RCC_AHB1Periph_GPIOB
#define CONTROLLER_SPI_RST_PORT GPIOB
#define CONTROLLER_SPI_RST_PIN  GPIO_Pin_9
#define CONTROLLER_SPI_RST_RCC	RCC_AHB1Periph_GPIOB


#define GLCD_SELECT()     GPIO_ResetBits(CONTROLLER_SPI_SS_PORT,CONTROLLER_SPI_SS_PIN)
#define GLCD_DESELECT()   GPIO_SetBits(CONTROLLER_SPI_SS_PORT,CONTROLLER_SPI_SS_PIN)
#define GLCD_A0_LOW()     GPIO_ResetBits(CONTROLLER_SPI_DC_PORT,CONTROLLER_SPI_DC_PIN)
#define GLCD_A0_HIGH()    GPIO_SetBits(CONTROLLER_SPI_DC_PORT,CONTROLLER_SPI_DC_PIN)
#define GLCD_RESET_LOW()  GPIO_ResetBits(CONTROLLER_SPI_RST_PORT,CONTROLLER_SPI_RST_PIN)
#define GLCD_RESET_HIGH() GPIO_SetBits(CONTROLLER_SPI_RST_PORT,CONTROLLER_SPI_RST_PIN)

/* RTOS delay function
 * Enable the following define to use a RTOS.
 * Update the call to the millisecond delay with the one of
 * your RTOS and add the includes in STM32F4.c  */
#define GLCD_USE_RTOS

#ifdef GLCD_USE_RTOS
  #define GLCD_RTOS_DELAY_FCN 		DelayTask(ms);
#endif
/* Function prototypes: */
void glcd_enable_backlight(FunctionalState state);
#ifdef USE_TIMER_PWM
void glcd_change_backlight(uint8_t value);
#endif
#else
	#error "Controller not supported by STM32F4XX"
#endif

#endif
