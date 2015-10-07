/*******************************************************************************
 * Copyright (c) 2009-2014, MAV'RIC Development Team
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, 
 * this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 * this list of conditions and the following disclaimer in the documentation 
 * and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

/*******************************************************************************
 * \file uart_int.c
 * 
 * \author MAV'RIC Team
 * \author Felix Schill
 *   
 * \brief This file implements the UART communication protocol
 * 
 ******************************************************************************/


#include "uart_int.h"
#include "buffer.h"
#include "gpio.h"
#include "streams.h"
#include "sysclk.h"


void uart_int_start_transmission_dummy(usart_config_t *usart_conf);

static usart_config_t usart_conf[UART_COUNT];

// macro for interrupt handler
#define UART_HANDLER(UID) ISR(uart_handler_##UID, usart_conf[UID].uart_device.IRQ, AVR32_INTC_INTLEV_INT1) {\
	uint8_t c1;\
	int32_t csr = usart_conf[UID].uart_device.uart->csr;\
	if (csr & AVR32_USART_CSR_RXRDY_MASK) {\
		c1 = (uint8_t)usart_conf[UID].uart_device.uart->rhr;\
		if (usart_conf[UID].uart_device.receive_stream != NULL) {\
			usart_conf[UID].uart_device.receive_stream->put(usart_conf[UID].uart_device.receive_stream->data, c1);\
		}\
	}\
	if (csr & AVR32_USART_CSR_TXRDY_MASK) {\
		if (buffer_bytes_available(&(usart_conf[UID].uart_device.transmit_buffer)) > 0) {\
			c1 = buffer_get(&(usart_conf[UID].uart_device.transmit_buffer));\
			usart_conf[UID].uart_device.uart->thr = c1;\
		}\
		if (buffer_bytes_available(&(usart_conf[UID].uart_device.transmit_buffer)) == 0) {\
				usart_conf[UID].uart_device.uart->idr = AVR32_USART_IDR_TXRDY_MASK;\
		}\
	}\
}			
/*
ISR(uart_handler_2, usart_conf[2].uart_device.IRQ, AVR32_INTC_INTLEV_INT1) {\
	uint8_t c1;\
	int32_t csr = usart_conf[2].uart_device.uart->csr;\
	if (csr & AVR32_USART_CSR_RXRDY_MASK) {\
		c1 = (uint8_t)usart_conf[2].uart_device.uart->rhr;\
		if (usart_conf[2].uart_device.receive_stream != NULL) {\
			usart_conf[2].uart_device.receive_stream->put(usart_conf[2].uart_device.receive_stream->data, c1);\
		}\
	}\
	if (csr & AVR32_USART_CSR_TXRDY_MASK) {\
		if (buffer_bytes_available(&(usart_conf[2].uart_device.transmit_buffer)) > 0) {\
			c1 = buffer_get(&(usart_conf[2].uart_device.transmit_buffer));\
			usart_conf[2].uart_device.uart->thr = c1;\
		}\
		if (buffer_bytes_available(&(usart_conf[2].uart_device.transmit_buffer))==0) {\
				usart_conf[2].uart_device.uart->idr = AVR32_USART_IDR_TXRDY_MASK;\
		}\
	}\
}	*/

// define interrupt handlers using above macro
#ifdef UART0
UART_HANDLER(0);
#endif
#ifdef UART1
UART_HANDLER(1);
#endif
#ifdef UART2
UART_HANDLER(2);
#endif
#ifdef UART3
UART_HANDLER(3);
#endif
#ifdef UART4
UART_HANDLER(4);
#endif



///< Function prototype definitions
void register_UART_handler(int32_t UID);
int32_t uart_out_buffer_empty(usart_config_t *usart_conf);

void register_UART_handler(int32_t UID)
{
	switch(UID)
	{
		case 0: 	
			#ifdef UART0
			INTC_register_interrupt( (__int_handler) &uart_handler_0, AVR32_USART0_IRQ, AVR32_INTC_INT1);
			#endif
			break;
		case 1: 
			#ifdef UART1
			INTC_register_interrupt( (__int_handler) &uart_handler_1, usart_conf[1].uart_device.IRQ, AVR32_INTC_INT1);
			#endif
			break;
		case 2: 
			#ifdef UART2
			INTC_register_interrupt( (__int_handler) &uart_handler_2, usart_conf[2].uart_device.IRQ, AVR32_INTC_INT1);
			#endif
			break;
		case 3: 
			#ifdef UART3
			INTC_register_interrupt( (__int_handler) &uart_handler_3, usart_conf[3].uart_device.IRQ, AVR32_INTC_INT1);
			#endif
			break;
		case 4: 
			#ifdef UART4
			INTC_register_interrupt( (__int_handler) &uart_handler_4, usart_conf[4].uart_device.IRQ, AVR32_INTC_INT1);
			#endif
			break;
	}
}

void uart_int_set_usart_conf(int32_t UID, usart_config_t usart_config)
{
	usart_conf[UID] = usart_config;
}

void uart_int_init(int32_t UID) {
	if ((usart_conf[UID].mode&UART_IN) > 0)
	{
		gpio_enable_module_pin(usart_conf[UID].rx_pin_map.pin, usart_conf[UID].rx_pin_map.function); 
	}
	
	if ((usart_conf[UID].mode&UART_OUT) > 0)
	{
		gpio_enable_module_pin(usart_conf[UID].tx_pin_map.pin, usart_conf[UID].tx_pin_map.function); 
	}

	usart_init_rs232( usart_conf[UID].uart_device.uart, &(usart_conf[UID].options), sysclk_get_cpu_hz()); 
	//usart_write_line(usart_conf[UID].uart_device.uart, "UART initialised\r\n");
	
	register_UART_handler(UID);
	
	buffer_init(&(usart_conf[UID].uart_device.transmit_buffer));
	//buffer_init(&(usart_conf[UID].uart_device.receive_buffer));
	
	if (((usart_conf[UID].mode)&UART_IN) > 0)
	{
		usart_conf[UID].uart_device.uart->ier = AVR32_USART_IER_RXRDY_MASK;
	}
	
	//if (usart_conf[UID].mode&UART_OUT > 0)
	//{
		//usart_conf[UID].uart_device.uart->ier = AVR32_USART_IER_TXRDY_MASK;
	//}
} 

usart_config_t *uart_int_get_uart_handle(int32_t UID) 
{
	return &usart_conf[UID];
}
/*
int8_t  uart_int_get_byte(usart_config_t *usart_conf) 
{
	return buffer_get(&(usart_conf->uart_device.receive_buffer));
}

int32_t uart_int_bytes_available(usart_config_t *usart_conf) 
{
	return buffer_bytes_available(&(usart_conf->uart_device.receive_buffer));
}
*/
void uart_int_start_transmission_dummy(usart_config_t *usart_conf) {
	
}
void uart_int_send_byte(usart_config_t *usart_conf, uint8_t data) 
{
//	usart_write_line(usart_conf->uart_device.uart, "\ns");
	while (buffer_put(&(usart_conf->uart_device.transmit_buffer), data) < 0);
	if ((buffer_bytes_available(&(usart_conf->uart_device.transmit_buffer)) >= 1))//&&
//	  (usart_conf->uart_device.uart->csr & AVR32_USART_CSR_TXRDY_MASK)) 
	{ // if there is exactly one byte in the buffer (this one...), and transmitter ready
		 // kick-start transmission
//		usart_conf->uart_device.uart->thr='c';//buffer_get(&(usart_conf->uart_device.transmit_buffer));
		usart_conf->uart_device.uart->ier = AVR32_USART_IER_TXRDY_MASK;
	}		
}

void uart_int_flush(usart_config_t *usart_conf) 
{
	usart_conf->uart_device.uart->ier = AVR32_USART_IER_TXRDY_MASK;
	while (!buffer_empty(&(usart_conf->uart_device.transmit_buffer)));
}

int32_t uart_out_buffer_empty(usart_config_t *usart_conf) 
{
	return buffer_empty(&(usart_conf->uart_device.transmit_buffer));
}

void uart_int_register_write_stream(usart_config_t *usart_conf, byte_stream_t *stream) 
{
	stream->get = NULL;
	//stream->get = &uart_int_get_byte;
	stream->put = (int8_t(*)(stream_data_t*, uint8_t))&uart_int_send_byte;			// Here we need to explicitly cast the function to match the prototype
	stream->flush = (void(*)(stream_data_t*))&uart_int_flush;						// stream->get and stream->put expect stream_data_t* as first argument
	stream->buffer_empty = (bool(*)(stream_data_t*))&uart_out_buffer_empty;			// but buffer_get and buffer_put take buffer_t* as first argument
	stream->start_transmission = (void(*)(stream_data_t*))&uart_int_start_transmission_dummy;
	stream->data = usart_conf;
}

void uart_int_register_read_stream(usart_config_t *usart_conf,  byte_stream_t *stream) 
{
	usart_conf->uart_device.receive_stream = stream;
}


#if UART_USE_DMA == 1

#include "pdca.h"

// macro for UART interrupt handler in DMA mode
// (clears transmit buffer, resets transmit_in_progress flag and disables PDCA)
#define UART_DMA_INTERRUPT(UID) ISR(uart_handler_dma_##UID, usart_conf[UID].uart_device.DMA_IRQ, AVR32_INTC_INTLEV_INT1) {\
	buffer_clear((buffer_t*)(&usart_conf[UID].uart_device.transmit_buffer));\
	usart_conf[UID].uart_device.transmit_in_progress=false;\
	pdca_get_transfer_status(usart_conf[UID].uart_device.DMA_channel);\
	pdca_disable_interrupt_transfer_complete(usart_conf[UID].uart_device.DMA_channel); \
	pdca_disable_interrupt_transfer_error(usart_conf[UID].uart_device.DMA_channel); \
	pdca_disable(usart_conf[UID].uart_device.DMA_channel);\
}

// define interrupt handlers using above macro
UART_DMA_INTERRUPT(0);
UART_DMA_INTERRUPT(1);
UART_DMA_INTERRUPT(2);
UART_DMA_INTERRUPT(3);
UART_DMA_INTERRUPT(4);



/** Initialisation of a UART device in DMA mode, according to settings in conf_usart_serial.h */

usart_config_t *uart_int_init_dma(int UID) {
	pdca_channel_options_t UART_TX_OPTIONS =
	{
		.addr = 0,                                // memory address
		.pid = AVR32_PDCA_PID_USART0_TX,          // select peripheral - transmitting to UART
		.size = 0,                               // transfer counter
		.r_addr = NULL,                           // next memory address
		.r_size = 0,                              // next transfer counter
		.transfer_size = PDCA_TRANSFER_SIZE_BYTE  // select size of the transfer
	};

	if ((usart_conf[UID].mode&UART_IN) >0)  gpio_enable_module_pin(usart_conf[UID].rx_pin_map.pin, usart_conf[UID].rx_pin_map.function);
	if ((usart_conf[UID].mode&UART_OUT)>0)  gpio_enable_module_pin(usart_conf[UID].tx_pin_map.pin, usart_conf[UID].tx_pin_map.function);

	usart_init_rs232( usart_conf[UID].uart_device.uart, (const usart_options_t*)&(usart_conf[UID].options), sysclk_get_cpu_hz());

	buffer_init((buffer_t*)&usart_conf[UID].uart_device.transmit_buffer);
	register_UART_handler(UID);
	buffer_init((buffer_t*)&usart_conf[UID].uart_device.transmit_buffer);

	// enable receive interrupt if specified
	if ((usart_conf[UID].mode&UART_IN) >0) usart_conf[UID].uart_device.uart->ier=AVR32_USART_IER_RXRDY_MASK;
	// disable transmit interrupt
	usart_conf[UID].uart_device.uart->idr=AVR32_USART_IER_TXRDY_MASK;

	usart_conf[UID].uart_device.transmit_in_progress=false;
	
	// Register PDCA IRQ interrupt.
	switch(UID) {
		case 0: 	
					INTC_register_interrupt( (__int_handler) &uart_handler_dma_0, usart_conf[0].uart_device.DMA_IRQ, AVR32_INTC_INT1); 
					UART_TX_OPTIONS.pid=AVR32_PDCA_PID_USART0_TX;
		break;
		case 1: 	INTC_register_interrupt( (__int_handler) &uart_handler_dma_1, usart_conf[1].uart_device.DMA_IRQ, AVR32_INTC_INT1);
					UART_TX_OPTIONS.pid=AVR32_PDCA_PID_USART1_TX;
		break;
		case 2: 	INTC_register_interrupt( (__int_handler) &uart_handler_dma_2, usart_conf[2].uart_device.DMA_IRQ, AVR32_INTC_INT1); 
					UART_TX_OPTIONS.pid=AVR32_PDCA_PID_USART2_TX;
		break;
		case 3: 	INTC_register_interrupt( (__int_handler) &uart_handler_dma_3, usart_conf[3].uart_device.DMA_IRQ, AVR32_INTC_INT1); 
					UART_TX_OPTIONS.pid=AVR32_PDCA_PID_USART3_TX;
		break;
		case 4: 	INTC_register_interrupt( (__int_handler) &uart_handler_dma_4, usart_conf[4].uart_device.DMA_IRQ, AVR32_INTC_INT1); 
					UART_TX_OPTIONS.pid=AVR32_PDCA_PID_USART4_TX;
		break;
	}
	
	pdca_init_channel(usart_conf[UID].uart_device.DMA_channel, &UART_TX_OPTIONS); // init PDCA channel with options.
	return (usart_config_t *)&usart_conf[UID];
}


/************************************************************************/
/* non-blocking operation to append a byte to the uart send buffer      */
/* for DMA mode. This will only append to the buffer - transmission has */
/* to be started separately.									        */
/************************************************************************/

short uart_dma_send_byte(usart_config_t *usart_conf, char data) {
	short ret=buffer_put(&(usart_conf->uart_device.transmit_buffer), data);
	return ret;
}

/*************************************************************************/
/* Start UART transmission in DMA mode. Everything in the buffer will    */
/* be sent. Data should not be added to the buffer until the transfer is */
/* complete (buffer empty) or it will be lost.                           */
/*************************************************************************/
void uart_dma_start_transmission(usart_config_t *usart_conf) {
	if (usart_conf->uart_device.transmit_in_progress) return;
	//if (pdca_get_load_size(usart_conf->uart_device.DMA_channel)>0) return;
	int transfersize=buffer_bytes_available( &usart_conf->uart_device.transmit_buffer);
	if (transfersize==0) {
		return;
	}

	pdca_disable(usart_conf->uart_device.DMA_channel);
	pdca_load_channel(usart_conf->uart_device.DMA_channel,  
	                  (void *)((void *) usart_conf->uart_device.transmit_buffer.Buffer), 
	                  transfersize );
	pdca_get_transfer_status(usart_conf->uart_device.DMA_channel);
	// Enable pdca interrupt for complete transfer and errors, to reset buffer
	pdca_enable_interrupt_transfer_complete(usart_conf->uart_device.DMA_channel);
	pdca_enable_interrupt_transfer_error(usart_conf->uart_device.DMA_channel);
	usart_conf->uart_device.transmit_in_progress=true;
	// start the transfer.
	pdca_enable(usart_conf->uart_device.DMA_channel);

}

void uart_dma_flush(usart_config_t *usart_conf) {
	uart_dma_start_transmission(usart_conf);
	while (usart_conf->uart_device.transmit_in_progress);
}


bool uart_dma_out_buffer_empty(usart_config_t *usart_conf) {
	// extra check in case the DMA is stuck in an invalid state (can happen when pausing during Debugging session)
	// If the flag indicates there is a transfer happening, but the DMA is at rest, clear the buffer and reset the flag.
	if ((!usart_conf->uart_device.transmit_in_progress) || ((usart_conf->uart_device.transmit_in_progress) && (pdca_get_load_size(usart_conf->uart_device.DMA_channel)==0))) {
		buffer_clear(&(usart_conf->uart_device.transmit_buffer));
		usart_conf->uart_device.transmit_in_progress=false;
	}
	return  buffer_empty(&(usart_conf->uart_device.transmit_buffer));
}

void uart_int_register_write_stream_dma(usart_config_t *usart_conf, byte_stream_t *stream) {
	stream->get=NULL;
	//stream->get=&uart_int_get_byte;
	stream->put=(int8_t(*)(stream_data_t*, uint8_t))&uart_dma_send_byte;
	stream->flush=(void(*)(stream_data_t*))&uart_dma_flush;
	stream->start_transmission= (void(*)(stream_data_t*))&uart_dma_start_transmission;
	stream->buffer_empty=(bool(*)(stream_data_t*))&uart_dma_out_buffer_empty;
	stream->data=usart_conf;
	buffer_clear(&usart_conf->uart_device.transmit_buffer);
}
#endif