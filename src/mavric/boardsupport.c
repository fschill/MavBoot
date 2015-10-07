
/*******************************************************************************
 * \file boardsupport.c  
 * 
 * \author Felix Schill
 *   
 * \brief Initialization of all hardware related elements (communication lines, 
 * sensors devices, etc) for MavBoot on MAVRIC autopilot board
 *
 ******************************************************************************/


#include "boardsupport.h"
#include "uart_int.h"
#include "sysclk.h"
#include "buffer.h"
#include "gpio.h"
//#include "stdio_usb.h"

#include "can_bus.h"

#include "central_data.h"

buffer_t wired_in_buffer;				///< The console incoming buffer


void boardsupport_init(void) 
{
	central_data_t *central_data;
	irq_initialize_vectors();
	cpu_irq_enable();
	Disable_global_interrupt();
		
	sysclk_init();

	//delay_init(sysclk_get_cpu_hz());
		
	INTC_init_interrupts();

	central_data=central_data_get_pointer_to_struct();
	
	#ifdef TELEMETRY_USE_UART
		uart_int_set_usart_conf(TELEMETRY_UART_INDEX, asv_debug_uart_conf());
		//uart configuration
		uart_int_init(TELEMETRY_UART_INDEX);
		uart_int_register_write_stream(uart_int_get_uart_handle(TELEMETRY_UART_INDEX), &(central_data->wired_out_stream));
		// Registering streams
		buffer_make_buffered_stream_lossy(&(wired_in_buffer), &(central_data->wired_in_stream));
		uart_int_register_read_stream(uart_int_get_uart_handle(TELEMETRY_UART_INDEX), &(central_data->wired_in_stream));
		central_data->debug_in_stream=&central_data->wired_in_stream;
		central_data->debug_out_stream=&central_data->wired_out_stream;

	#endif
		
	central_data_init();

	Enable_global_interrupt();

}
