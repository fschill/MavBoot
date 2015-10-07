/*
 * boardsupport.h
 *
 * Created: 20/03/2013 12:14:04
 *  Author: sfx
 */ 


#ifndef BOARDSUPPORT_H_
#define BOARDSUPPORT_H_

#include "conf_board.h"
#include "conf_mavlink.h"
#include "uart_int.h"
#include "can_bus.h"

#include "time_keeper.h"
#include "delay.h"
#include "leds.h"
#include "i2c_driver_int.h"
#include "streams.h"
#include "uart_int.h"
#include "print_util.h"

#include "bmp085.h"
#include "mavlink_stream.h"
#include "coord_conventions.h"
#include "onboard_parameters.h"
#include "remote.h"
#include "remote_telemetry.h"

enum { ENABLE_6V, ENABLE_GYRO, POWER_CONTROL_PINS_COUNT};

#define ENABLE_6V_PIN   AVR32_PIN_PA04
#define ENABLE_GYRO_PIN  AVR32_PIN_PD23


typedef struct power_control_t {
	int32_t gpio_pin;
	float pin_control;
	char *name;
} power_control_t;

typedef struct board_control_t {
	power_control_t power_control[POWER_CONTROL_PINS_COUNT];
	
} board_control_t;

void initialise_board(void);

void init_pps_timer(void);

task_return_t update_control_pins(task_argument_t* arg);

void boardcontrol_register_parameters(onboard_parameters_t * onboard_parameters);

static inline board_control_t board_control_conf(void) {
	board_control_t board_control = {
		.power_control  = {
			{.gpio_pin = ENABLE_6V_PIN ,  .pin_control = 1.0, .name="EN_6V"},
			{.gpio_pin = ENABLE_GYRO_PIN ,  .pin_control = 1.0, .name="EN_GYRO"},
		},
	};
	return board_control;
}

static inline usart_config_t asv_debug_uart_conf(void) {
	usart_config_t usart_conf =
	{   .mode=UART_IN_OUT,
		.uart_device.uart=(avr32_usart_t*)&AVR32_USART4,
		.uart_device.IRQ=AVR32_USART4_IRQ,
		.uart_device.DMA_channel=UART0_DMA_CH_TRANSMIT,
		.uart_device.DMA_IRQ=UART0_DMA_IRQ,
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

static inline usart_config_t asv_xbee_uart_conf(void) {
	usart_config_t usart_conf =
	{   .mode=UART_IN_OUT,
		.uart_device.uart=(avr32_usart_t*)&AVR32_USART0, 
		.uart_device.IRQ=AVR32_USART0_IRQ,
		.uart_device.DMA_channel=UART0_DMA_CH_TRANSMIT,
		.uart_device.DMA_IRQ=UART0_DMA_IRQ,
		.uart_device.receive_stream=NULL,
		.options={
			.baudrate     = 57600,
			.charlength   = 8,
			.paritytype   = USART_NO_PARITY,
			.stopbits     = USART_1_STOPBIT,
			.channelmode  = USART_NORMAL_CHMODE },
		.rx_pin_map= {AVR32_USART0_RXD_0_0_PIN, AVR32_USART0_RXD_0_0_FUNCTION},
		.tx_pin_map= {AVR32_USART0_TXD_0_0_PIN, AVR32_USART0_TXD_0_0_FUNCTION}
	};
	return usart_conf;
};

static inline usart_config_t asv_gps_uart_conf(void) {
	usart_config_t usart_conf =
	{   .mode=UART_IN_OUT,
		.uart_device.uart=(avr32_usart_t*)&AVR32_USART3,
		.uart_device.IRQ=AVR32_USART3_IRQ,
		.uart_device.DMA_channel=UART3_DMA_CH_TRANSMIT,
		.uart_device.DMA_IRQ=UART3_DMA_IRQ,
		.uart_device.receive_stream=NULL,
		.options={
			.baudrate     = 9600,
			.charlength   = 8,
			.paritytype   = USART_NO_PARITY,
			.stopbits     = USART_1_STOPBIT,
			.channelmode  = USART_NORMAL_CHMODE },
			//.rx_pin_map= {AVR32_USART3_RXD_2_PIN, AVR32_USART3_RXD_2_FUNCTION},
			//.tx_pin_map= {AVR32_USART3_TXD_2_PIN, AVR32_USART3_TXD_2_FUNCTION}
			.rx_pin_map= {AVR32_USART3_RXD_0_0_PIN, AVR32_USART3_RXD_0_0_FUNCTION},
			.tx_pin_map= {AVR32_USART3_TXD_0_0_PIN, AVR32_USART3_TXD_0_0_FUNCTION}
	};
	return usart_conf;
};

static inline usart_config_t asv_spektrum_uart_conf(void) {
	static const usart_config_t usart_default_config_spektrum =
	{
		.mode						= UART_IN_OUT,
		.uart_device.uart			= (avr32_usart_t *)&AVR32_USART1,
		.uart_device.IRQ			= AVR32_USART1_IRQ,
		.uart_device.receive_stream	= NULL,
		.options					=
		{
			.baudrate				= 115200,
			.charlength				= 8,
			.paritytype				= USART_NO_PARITY,
			.stopbits				= USART_1_STOPBIT,
			.channelmode			= USART_NORMAL_CHMODE 
		},
		.rx_pin_map					= { AVR32_USART1_RXD_0_1_PIN, AVR32_USART1_RXD_0_1_FUNCTION },
		.tx_pin_map					= { AVR32_USART1_TXD_0_1_PIN, AVR32_USART1_TXD_0_1_FUNCTION }
	};
	return usart_default_config_spektrum;
}

static inline remote_conf_t asv_remote_conf(void) {
	remote_conf_t remote_default_config =
	{
		.type = REMOTE_TURNIGY,
		.mode_config =
		{
			.safety_channel = CHANNEL_GEAR,
			.safety_mode =
			{
				.byte = MAV_MODE_ATTITUDE_CONTROL,
				// .flags =
				// {
				// .MANUAL = MANUAL_ON,
				// }
			},
			.mode_switch_channel = CHANNEL_FLAPS,
			.mode_switch_up =
			{
				.byte = MAV_MODE_VELOCITY_CONTROL
				// .flags =
				// {
				// .MANUAL = MANUAL_ON,
				// .STABILISE = STABILISE_ON,
				// }
			},
			.mode_switch_middle =
			{
				.byte = MAV_MODE_POSITION_HOLD,
				// .flags =
				// {
				// .MANUAL = MANUAL_ON,
				// .GUIDED = GUIDED_ON,
				// }
			},
			.mode_switch_down =
			{
				.byte = MAV_MODE_GPS_NAVIGATION
				// .flags =
				// {
				// .AUTO = AUTO_ON,
				// }
			},
			.use_custom_switch = true,//false,
			.custom_switch_channel = CHANNEL_AUX1,
			.use_test_switch = false,
			.test_switch_channel = CHANNEL_AUX2,
			.use_disable_remote_mode_switch = false,
			.test_switch_channel = CHANNEL_AUX2,
		},
	};
	return remote_default_config;
}

static inline can_stream_config_t asv_can1_conf(void) {
	can_stream_config_t can_conf = {
		.can_rx_map = {AVR32_CANIF_RXLINE_1_4_PIN, AVR32_CANIF_RXLINE_1_4_FUNCTION}, 
		.can_tx_map = {AVR32_CANIF_TXLINE_1_4_PIN, AVR32_CANIF_TXLINE_1_4_FUNCTION}, 
		.can_shutdown_pin = AVR32_PIN_PC17, 
		.can_standby_pin  = AVR32_PIN_PC12
	};
	return can_conf;
}

#endif /* BOARDSUPPORT_H_ */