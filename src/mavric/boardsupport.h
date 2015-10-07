
/*******************************************************************************
 * \file boardsupport.h
 * 
 * \author Felix Schill
 *   
 * \brief Initialization of all hardware related elements (communication lines, 
 * sensors devices, etc) for MavBoot on MAVRIC autopilot board
 *
 ******************************************************************************/


#ifndef BOARDSUPPORT_H_
#define BOARDSUPPORT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "uart_int.h"
#include "can_bus.h"

#define TELEMETRY_UART_INDEX UART4
#define TELEMETRY_USE_UART

//#define TELEMETRY_USE_XBEE

//#define TELEMETRY_USE_CAN0


static inline usart_config_t asv_debug_uart_conf(void) {
	usart_config_t usart_conf =
	{   .mode=UART_IN_OUT,
		.uart_device.uart=(avr32_usart_t*)&AVR32_USART4,
		.uart_device.IRQ=AVR32_USART4_IRQ,
		.uart_device.receive_stream=NULL,
		.options={
			.baudrate     = 115200,
			.charlength   = 8,
			.paritytype   = USART_NO_PARITY,
			.stopbits     = USART_1_STOPBIT,
			.channelmode  = USART_NORMAL_CHMODE },
			.rx_pin_map= {AVR32_USART4_RXD_2_PIN, AVR32_USART4_RXD_2_FUNCTION},
			.tx_pin_map= {AVR32_USART4_TXD_2_PIN, AVR32_USART4_TXD_2_FUNCTION}
	};
	return usart_conf;
};



/**
 * \brief	Initialize the hardware related elements (communication lines, sensors devices, etc)
 *
 * \param	central_data		The pointer to the structure where all central data is stored
 */
void boardsupport_init(void);

#ifdef __cplusplus
}
#endif

#endif /* BOARDSUPPORT_H_ */