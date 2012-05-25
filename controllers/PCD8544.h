/**
   \file PCD8544.c
   \brief Functions relating to PCD8544 LCD Controller (Nokia 5110 LCD).
   \author Andy Gock
 */ 


#ifndef PCD8544_H_
#define PCD8544_H_

// instruction set bit masks
#define PCD8544_NOP 0

// function set commands
#define PCD8544_FUNCTION_SET          (1<<5)
#define PCD8544_POWER_DOWN            (1<<2)
#define PCD8544_HORIZONTAL_ADDRESSING 0
#define PCD8544_VERTICAL_ADDRESSING   (1<<1)
#define PCD8544_EXTENDED_INSTRUCTION  (1<<0)

// H=0 (basic instruction set)
#define PCD8544_DISPLAY_CONTROL  (1<<3)
#define PCD8544_DISPLAY_BLANK    0x0
#define PCD8544_DISPLAY_NORMAL   (1<<2)
#define PCD8544_DISPLAY_ALL_ON   (1<<0)
#define PCD8544_DISPLAY_INVERTED (1<<2|1<<0)

#define PCD8544_SET_Y_ADDRESS       0x40
#define PCD8544_SET_X_ADDRESS       0x80

// H=1 (extended instruction set)
#define PCD8544_SET_TEMP (1<<2)
#define PCD8544_TEMPCO_0 0b00
#define PCD8544_TEMPCO_1 0b01
#define PCD8544_TEMPCO_2 0b10
#define PCD8544_TEMPCO_3 0b11

#define PCD8544_SET_BIAS (1<<4)
#define PCD8544_SET_VOP  (1<<7)

//
#define PCD8544_MAX_BANKS 6
#define PCD8544_MAX_COLS  84

#endif /* PCD8544_H_ */