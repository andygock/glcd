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

#if defined(GLCD_DEVICE_STM32F4XX)

/* Includes from CMSIS and Peripheral Library */
#include "devices\STM32F4.h"
#include "stm32f4xx_spi.h"

/* Includes from GLCD */
#include "glcd.h"

/* Includes for RTOS */
#ifdef GLCD_USE_RTOS
  #include "BRTOS.h"
#endif

void delay_ms(uint32_t ms);

//#define BACKLIGHT_INVERT	// Uncomment if LED backlight turn on with low value

void glcd_init(void)
{

	/* Initialisation for PCD8544 controller */

	/* Declare GPIO and SPI init structures */
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;
	
	/* Configuring CS, DC (A0) and RST pin */
	/* Peripheral clock init. */
	RCC_AHB1PeriphClockCmd(CONTROLLER_SPI_DC_RCC | CONTROLLER_SPI_SS_RCC | \
			CONTROLLER_SPI_RST_RCC, ENABLE);
	/* CS pin */
	GPIO_InitStructure.GPIO_Pin   = CONTROLLER_SPI_SS_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(CONTROLLER_SPI_SS_PORT, &GPIO_InitStructure);

	/* DC (A0) pin */
	GPIO_InitStructure.GPIO_Pin = CONTROLLER_SPI_DC_PIN;
	GPIO_Init(CONTROLLER_SPI_DC_PORT, &GPIO_InitStructure);

	/* RST pin */
	GPIO_InitStructure.GPIO_Pin = CONTROLLER_SPI_RST_PIN;
	GPIO_Init(CONTROLLER_SPI_RST_PORT, &GPIO_InitStructure);

	/* Make sure chip is de-selected by default */
	GLCD_DESELECT();

	/*
	 * Configuring SPI:
	 */
	/* Enable the SPI clock */
	SPIx_CLK_INIT(SPIx_CLK, ENABLE);
	/* Enable SPI GPIO clocks */
	RCC_AHB1PeriphClockCmd(SPIx_SCK_GPIO_CLK | SPIx_MOSI_GPIO_CLK, ENABLE);
	/* Connect SPI pins to the corresponding alternate function */
	GPIO_PinAFConfig(SPIx_SCK_GPIO_PORT, SPIx_SCK_SOURCE, SPIx_SCK_AF);
	GPIO_PinAFConfig(SPIx_MOSI_GPIO_PORT, SPIx_MOSI_SOURCE, SPIx_MOSI_AF);
//	GPIO_PinAFConfig(SPIx_MISO_GPIO_PORT, SPIx_MISO_SOURCE, SPIx_MISO_AF);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;

	/* SPI SCK pin configuration */
	GPIO_InitStructure.GPIO_Pin = SPIx_SCK_PIN;
	GPIO_Init(SPIx_SCK_GPIO_PORT, &GPIO_InitStructure);
	/* SPI  MOSI pin configuration */
	GPIO_InitStructure.GPIO_Pin =  SPIx_MOSI_PIN;
	GPIO_Init(SPIx_MOSI_GPIO_PORT, &GPIO_InitStructure);
#if 0
	GPIO_InitStructure.GPIO_Pin =  SPIx_MISO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_Init(SPIx_MISO_GPIO_PORT, &GPIO_InitStructure);
#endif
	/* SPI configuration */
	SPI_I2S_DeInit(SPIx);
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	/* Clock set to 8MHz */
	SPI_InitStructure.SPI_BaudRatePrescaler = SPIx_PRESCALLER;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_Init(SPIx, &SPI_InitStructure);
	/* Enable the SPI peripheral */
	SPI_Cmd(SPIx, ENABLE);

	glcd_select_screen((uint8_t *)&glcd_buffer,&glcd_bbox);

	RCC_AHB1PeriphClockCmd(LCD_LED_GPIO_RCC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LCD_LED_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_Init(LCD_LED_PORT, &GPIO_InitStructure);


#if defined(GLCD_CONTROLLER_PCD8544)
	/* Initialisation sequence of controller */

	glcd_PCD8544_init();
	glcd_clear();

#elif defined(GLCD_CONTROLLER_ST7565R)
	glcd_reset();
	glcd_enable_backlight(ENABLE);
	glcd_ST7565R_init();

#else
	#error "Controller not supported by STM32F0xx"
#endif

}

/* Change backlight led state ENABLE or DISABLE*/
void glcd_enable_backlight(FunctionalState state)
{

#ifdef USE_TIMER_PWM
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	uint16_t PrescalerValue = 0;
	/* Init LED backlight pin*/
	GPIO_InitStructure.GPIO_Pin = LCD_LED_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

	if (state == ENABLE){

		/* Compute the prescaler value
		 * This formula yelds the prescaller for a frequency of 100Hz with
		 * 255 steps (period) */
		PrescalerValue = (uint16_t) (((SystemCoreClock /LCD_TIM_Sys_Prescaller) / 255)/100) - 1;

		/* Init LED pin as Alternated Function: */
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_Init(LCD_LED_PORT, &GPIO_InitStructure);

		/* Connect TIM2 pins to AF */
		GPIO_PinAFConfig(LCD_LED_PORT, LCD_LED_PinSource, LCD_AF);

		/* TIM clock enable */
		LCD_TIM_PeriphClockCmd(LCD_TIM_RCC, ENABLE);

		/* Time base configuration: 100Hz period with 255 steps */
		TIM_TimeBaseStructure.TIM_Period = 254;
		TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
		TIM_TimeBaseStructure.TIM_ClockDivision = 0;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(LCD_TIM, &TIM_TimeBaseStructure);

		/* PWM1 Mode configuration: Channel3 */
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse = 128; // Initial value (half)
#ifdef BACKLIGHT_INVERT_OUT
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
#else
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
#endif
		LCD_TIM_OCInit(LCD_TIM, &TIM_OCInitStructure);
		LCD_TIM_OCPreload(LCD_TIM, TIM_OCPreload_Enable);

		TIM_ARRPreloadConfig(LCD_TIM, ENABLE);

		/* TIM3 enable counter */
		TIM_Cmd(LCD_TIM, ENABLE);

	}
	/* If DISABLE: Disable timer and turn off led */
	else{
		// DeInit LED pin as Alternated Function:
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_Init(LCD_LED_PORT, &GPIO_InitStructure);
		/* TIM clock disable */
		TIM_Cmd(LCD_TIM, DISABLE);
		LCD_TIM_PeriphClockCmd(LCD_TIM_RCC, DISABLE);
#ifdef BACKLIGHT_INVERT_OUT
		GPIO_SetBits(LCD_LED_PORT,LCD_LED_PIN);
#else
		// Turn off LED backlight
		GPIO_ResetBits(LCD_LED_PORT,LCD_LED_PIN);
	}
#endif
#else // if not defined USE_TIMER_PWM
	if (state == ENABLE){
	#ifdef BACKLIGHT_INVERT_OUT
		GPIO_ResetBits(LCD_LED_PORT,LCD_LED_PIN);
	#else
		GPIO_SetBits(LCD_LED_PORT,LCD_LED_PIN);
	#endif
	}else{
	#ifdef BACKLIGHT_INVERT_OUT
		GPIO_SetBits(LCD_LED_PORT,LCD_LED_PIN);
	#else
		GPIO_ResetBits(LCD_LED_PORT,LCD_LED_PIN);
	#endif
	}
#endif
}

#ifdef USE_TIMER_PWM
/* Change PWM duty cycle (brightness).
 * values between 0 and 255 */
void glcd_change_backlight(uint8_t value){

	LCD_TIM_SetCompare(LCD_TIM,value);
}
#endif

void glcd_spi_write(uint8_t c)
{
	//uint8_t temp;

	GLCD_SELECT();
	/*!< Loop while DR register in not emplty */
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);

	SPI_I2S_SendData(SPIx, (uint16_t) c);
	
	/* Wait until entire byte has been read (which we discard anyway) */
	while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY) != RESET);

	//temp = SPI_I2S_ReceiveData(SPIx);

	GLCD_DESELECT();
}

void glcd_reset(void)
{
	/* Toggle RST low to reset. Minimum pulse 100ns on datasheet. */
	GLCD_SELECT();
	GLCD_RESET_LOW();


	delay_ms(GLCD_RESET_TIME);
	//DelayTask(GLCD_RESET_TIME);
	GLCD_RESET_HIGH();
	GLCD_DESELECT();
}

void delay_ms(uint32_t ms){

#ifndef GLCD_USE_RTOS
	uint32_t count = 0;
	uint32_t ms_counter = 0;
	do{
		count = 0;
		const uint32_t utime = 100000;
		do{
			count++;
		}
		while (count < utime);
		ms_counter++;
	}while(ms_counter < ms);
#else
	GLCD_RTOS_DELAY_FCN // Call the delay function defined in the header file.
#endif
}


#endif
