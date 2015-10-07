/**
 * \file
 *
 * \brief User board configuration template
 *
 */

#ifndef CONF_BOARD_H
#define CONF_BOARD_H
#include "gpio.h"

#include "compiler.h"
#define BOARD USER_BOARD


// desired system clock
#define SYSCLK_FREQUENCY 64000000UL
#define BOARD_PLL0_DIVIDER 1

// configuration of the crystal mounted on the board

//#define BOARD_OSC0_HZ           10000000
//#define BOARD_OSC0_STARTUP_US   2000
//#define BOARD_OSC0_IS_XTAL      true
/*
#define BOARD_OSC32_HZ          32768
#define BOARD_OSC32_STARTUP_US  71000
#define BOARD_OSC32_IS_XTAL     true
*/

#define NUMBER_OF_LEDS 0

static const uint8_t LED_GPIO_PINS[]={};


#define UART_USE_DMA 0

#endif // CONF_BOARD_H
