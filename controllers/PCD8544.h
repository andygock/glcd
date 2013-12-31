/**
 * \file PCD8544.h
 * \brief Constants relating to PCD8544 LCD Controller (Nokia 5110 LCD).
 * \author Andy Gock
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

#ifndef PCD8544_H_
#define PCD8544_H_

/**
 * \name Function set commands
 * @{
 */
#define PCD8544_NOP 0
#define PCD8544_FUNCTION_SET          (1<<5)
#define PCD8544_POWER_DOWN            (1<<2)
#define PCD8544_HORIZONTAL_ADDRESSING 0
#define PCD8544_VERTICAL_ADDRESSING   (1<<1)
#define PCD8544_EXTENDED_INSTRUCTION  (1<<0)
/**@}*/

/**
 * \name Basic instruction set (H=0)
 * @{
 */
#define PCD8544_DISPLAY_CONTROL  (1<<3)
#define PCD8544_DISPLAY_BLANK    0x0
#define PCD8544_DISPLAY_NORMAL   (1<<2)
#define PCD8544_DISPLAY_ALL_ON   (1<<0)
#define PCD8544_DISPLAY_INVERTED (1<<2|1<<0)
#define PCD8544_SET_Y_ADDRESS       0x40
#define PCD8544_SET_X_ADDRESS       0x80
/**@}*/

/**
 * \name Extended instruction set (H=1)
 * @{
 */
#define PCD8544_SET_TEMP (1<<2)
#define PCD8544_TEMPCO_0 0b00
#define PCD8544_TEMPCO_1 0b01
#define PCD8544_TEMPCO_2 0b10
#define PCD8544_TEMPCO_3 0b11

/** \todo Check if these instructions are from this group */
#define PCD8544_SET_BIAS (1<<4)
#define PCD8544_SET_VOP  (1<<7)
/**@}*/

#define PCD8544_MAX_BANKS 6
#define PCD8544_MAX_COLS  84

/** Init PCD8544 controller / display */
void glcd_PCD8544_init(void);

#endif /* PCD8544_H_ */
