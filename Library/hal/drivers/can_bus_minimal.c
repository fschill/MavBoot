/*
 * \file can_bus_minimal.c
 *
 * \brief minimal canbus driver for reduced code size in bootloader
 * 
 * Created: 29/07/2014 15:34:29
 *  Author: Felix Schill 
 */ 

#include "can_bus.h"

#include "conf_can.h"

#include "gpio.h"
#include "scif_uc3c.h"
//#include "delay.h"
#include "buffer.h"

#ifdef CAN0_ENABLED
volatile can_msg_t mob_ram_ch0[NB_MOB_CHANNEL] __attribute__ ((section (".hsb_ram_loc")));

can_stream_data_t *CAN_stream_tx[2], *CAN_stream_rx[2];
#endif

#ifdef CAN1_ENABLED
volatile can_msg_t mob_ram_ch1[NB_MOB_CHANNEL] __attribute__ ((section (".hsb_ram_loc")));
//volatile can_stream_data_t *CAN1_stream_tx, *CAN1_stream_rx;
#endif


// Prototypes:
U8 can_bus_init_hardware(U8 ch,
            U32 can_msg_ram_add,
            U8 operating_mode,
            void (*can_msg_callback_channel) (U8 handle, U8 event));
U8 can_bus_enable_interrupt(U8 ch);
U8 can_bus_tx( U8 ch, U8 handle, U8 dlc, U8 req_type, const can_msg_t *can_msg);
U8 can_bus_rx( U8 ch, U8 handle, U8 req_type, const can_msg_t *can_msg);
void CAN_start_transmission_internal(can_stream_data_t* data);
void can_bus_start_transmission(can_stream_data_t* data);
void CAN_put(can_stream_data_t *data, uint8_t ch);
uint8_t CAN_get(can_stream_data_t *data);
int CAN_bytes_available(can_stream_data_t *data);
int CAN_buffer_empty(can_stream_data_t *data);
void CAN_flush(can_stream_data_t *data);

 

static void inline can_receive_handler(can_channel_t channel, uint8_t handle, can_stream_data_t *can_stream) {
	U8 i;
	can_stream->can_msg.data.u64=((CANIF_mob_get_ptr_data(channel,handle)->data)).u64;
	can_stream->can_msg.id = (CANIF_get_ext_id(channel,handle));
	can_stream->can_mob.dlc = (CANIF_mob_get_dlc(channel,handle));
	// set up next reception
	CANIF_config_rx(channel,handle);
	CANIF_mob_enable(channel,handle);
	CANIF_mob_enable_interrupt(channel,handle);

	// add data to receive stream
	for (i=0; i<can_stream->can_mob.dlc; i++) {
		buffer_put_lossy(&can_stream->byte_buffer, can_stream->can_msg.data.u8[i]);
	}
}


#ifdef CAN0_ENABLED

#if defined (__GNUC__)
__attribute__((__interrupt__))
#elif defined (__ICCAVR32__)
__interrupt
#endif
static void can0_tx_handler(void)
{
	U8 handle;
	handle = CANIF_mob_get_mob_txok(0);
	if (handle != 0x20)
	{
		CANIF_mob_clear_txok_status(0,handle);
		CANIF_mob_clear_status(0,handle); //   and reset MOb status
		// try to send more data if there is any
		CAN_start_transmission_internal(CAN_stream_tx[0]);
	}
}

#if defined (__GNUC__)
__attribute__((__interrupt__))
#elif defined (__ICCAVR32__)
__interrupt
#endif
static void can0_rx_handler(void)
{
	U8 handle;
	handle = CANIF_mob_get_mob_rxok(0) ;
	if (handle != 0x20)
	{
		CANIF_mob_clear_rxok_status(0,handle);
		CANIF_mob_clear_status(0,handle); //   and reset MOb status
		// read out message data :
		can_receive_handler(0, handle, CAN_stream_rx[0]);

	}
}

#if defined (__GNUC__)
__attribute__((__interrupt__))
#elif defined (__ICCAVR32__)
__interrupt
#endif
static void can0_error_handler(void)
{
	CANIF_clr_interrupt_status(0);
	

}

#endif //CAN0_ENABLED


#ifdef CAN1_ENABLED

#if defined (__GNUC__)
__attribute__((__interrupt__))
#elif defined (__ICCAVR32__)
__interrupt
#endif
static void can1_tx_handler(void)
{
	U8 handle;
	handle = CANIF_mob_get_mob_txok(1) ;
	if (handle != 0x20)
	{
		CANIF_mob_clear_txok_status(1,handle);
		CANIF_mob_clear_status(1,handle); //   and reset MOb status
		// try to send more data if there is any
		CAN_start_transmission_internal(CAN_stream_tx[1]);

	}
}

#if defined (__GNUC__)
__attribute__((__interrupt__))
#elif defined (__ICCAVR32__)
__interrupt
#endif
static void can1_rx_handler(void)
{
	U8 handle;
	handle = CANIF_mob_get_mob_rxok(1) ;
	if (handle != 0x20)
	{
		CANIF_mob_clear_rxok_status(1,handle);
		CANIF_mob_clear_status(1,handle); //   and reset MOb status

		// read out message data :
		can_receive_handler(1, handle, CAN_stream_rx[1]);

	}
}

#if defined (__GNUC__)
__attribute__((__interrupt__))
#elif defined (__ICCAVR32__)
__interrupt
#endif
static void can1_error_handler(void)
{

	CANIF_clr_interrupt_status(1);
}

#endif //CAN0_ENABLED

U8 can_bus_enable_interrupt(U8 ch)
{
	if ((ch > 1))
	return  CAN_CMD_REFUSED;

#ifdef CAN0_ENABLED

	if (ch==0)
	{
		INTC_register_interrupt(&can0_tx_handler, AVR32_CANIF_TXOK_IRQ_0, CAN0_INT_TX_LEVEL);
		INTC_register_interrupt(&can0_rx_handler, AVR32_CANIF_RXOK_IRQ_0, CAN0_INT_RX_LEVEL);
		INTC_register_interrupt(&can0_error_handler, AVR32_CANIF_BUS_OFF_IRQ_0, CAN0_INT_BOFF_LEVEL);
		INTC_register_interrupt(&can0_error_handler, AVR32_CANIF_ERROR_IRQ_0, CAN0_INT_ERR_LEVEL);
		INTC_register_interrupt(&can0_error_handler, AVR32_CANIF_WAKE_UP_IRQ_0, CAN0_INT_WAKE_UP_LEVEL);
		CANIF_enable_interrupt(ch);
	}
#endif
#ifdef CAN1_ENABLED
	
	if (ch == 1)
	{
		INTC_register_interrupt(&can1_tx_handler, AVR32_CANIF_TXOK_IRQ_1, CAN1_INT_TX_LEVEL);
		INTC_register_interrupt(&can1_rx_handler, AVR32_CANIF_RXOK_IRQ_1, CAN1_INT_RX_LEVEL);
		INTC_register_interrupt(&can1_error_handler, AVR32_CANIF_BUS_OFF_IRQ_1, CAN1_INT_BOFF_LEVEL);
		INTC_register_interrupt(&can1_error_handler, AVR32_CANIF_ERROR_IRQ_1, CAN1_INT_ERR_LEVEL);
		INTC_register_interrupt(&can1_error_handler, AVR32_CANIF_WAKE_UP_IRQ_1, CAN1_INT_WAKE_UP_LEVEL);
		CANIF_enable_interrupt(ch);
	}
#endif

	return  CAN_CMD_ACCEPTED;
}


U8 can_bus_init_hardware(U8 ch,
            U32 can_msg_ram_add,
            U8 operating_mode,
            void (*can_msg_callback_channel) (U8 handle, U8 event))
{
   if ( ch > 1)
         return  CAN_CMD_REFUSED;

   // Initialize CAN channel
   CANIF_set_reset(ch);
   while(CANIF_channel_enable_status(ch));
   CANIF_clr_reset(ch);

   CANIF_set_ram_add(ch,(unsigned long) can_msg_ram_add);
   if ((CANIF_bit_timing(ch))==0) return (0);
   switch(operating_mode)
   {
    case CANIF_CHANNEL_MODE_NORMAL:
      CANIF_set_channel_mode(ch,0);
      CANIF_clr_overrun_mode(ch);
      break;
//    case CANIF_CHANNEL_MODE_LISTENING:
//      CANIF_set_channel_mode(ch,1);
//      CANIF_set_overrun_mode(ch);
//      break;
//    case CANIF_CHANNEL_MODE_LOOPBACK:
//      CANIF_set_channel_mode(ch,2);
//      CANIF_clr_overrun_mode(ch);
//      break;
   }
   canif_clear_all_mob(ch,NB_MOB_CHANNEL);
   CANIF_enable(ch);

/* 
 * The maximum delay time to wait is the time to transmit 128-bits 
 * (CAN extended frame at baudrate speed configured by the user).
 * - 10x bits number of previous undetected message,
 * - 128x bits MAX length,
 * - 3x bits of interframe.
 */
#define DELAY_HZ         (BAUDRATE_HZ/141.0)   /*Compute Maximum delay time*/
#define DELAY            (1000000 / DELAY_HZ)  /*Compute Delay in µs*/
//   delay_us(DELAY);
	
   while ((!CANIF_channel_enable_status(ch)));//&&(i<10000)) i++; 
   //if (i>=10000){
   //         return CAN_CMD_REFUSED;
   //}

	can_bus_enable_interrupt(ch);

   return CAN_CMD_ACCEPTED;
}


U8 can_bus_tx( U8 ch,
U8 handle,
U8 dlc,
U8 req_type,
const can_msg_t *can_msg)
{
	if ((ch > 1) ||
	(handle > (NB_MOB_CHANNEL-1)) ||
	(dlc > 8))
	return  CAN_CMD_REFUSED;

	if (can_msg->ide_bit){
		CANIF_set_ext_id(ch,
		handle,
		can_msg->id);

		CANIF_set_ext_idmask(ch,
		handle,
		can_msg->id_mask);
	}
	else 
	{
		CANIF_set_std_id(ch,
		handle,
		can_msg->id);
		CANIF_set_std_idmask(ch,
		handle,
		can_msg->id_mask);
	}
	CANIF_mob_clr_dlc(ch,handle);
	CANIF_mob_set_dlc(ch,handle,dlc);
//	if (req_type == CAN_REMOTE_FRAME){
//		CANIF_set_rtr(ch,handle);
//		CANIF_set_rtrmask(ch,handle);
//		CANIF_mob_set_automode(ch,handle);
//	}
	CANIF_set_data(ch,handle,((can_msg_t *)can_msg)->data.u64);
	CANIF_config_tx(ch,handle);
	CANIF_mob_enable(ch,handle);
	#ifdef CAN_LIB_UNDER_INTERRUPT
	CANIF_mob_enable_interrupt(ch,handle);
	#endif
	return CAN_CMD_ACCEPTED;
}

U8 can_bus_rx( U8 ch,
U8 handle,
U8 req_type,
const can_msg_t *can_msg)
{
	if ((ch > 1) ||
	(handle > (NB_MOB_CHANNEL-1)))
	return  CAN_CMD_REFUSED;
	if (can_msg->ide_bit){
		CANIF_set_ext_id(ch,
		handle,
		can_msg->id);
		CANIF_set_ext_idmask(ch,
		handle,
		can_msg->id_mask);
	}
	else {
		CANIF_set_std_id(ch,
		handle,
		can_msg->id);
		CANIF_set_std_idmask(ch,
		handle,
		can_msg->id_mask);
	}
//	if (req_type == CAN_REMOTE_FRAME){
//		CANIF_set_rtr(ch,handle);
//		CANIF_set_rtrmask(ch,handle);
//		CANIF_mob_set_automode(ch,handle);
//		CANIF_set_data(ch,handle,((can_msg_t *)can_msg)->data.u64);
//	}
	CANIF_config_rx(ch,handle);
	CANIF_mob_enable(ch,handle);

	CANIF_mob_enable_interrupt(ch,handle);

	return CAN_CMD_ACCEPTED;
}



void can_bus_init(int channel, can_stream_config_t config) {

	// Setup the generic clock for CAN
	scif_gc_setup(AVR32_SCIF_GCLK_CANIF,
					CAN_GCLK_SOURCE,
					CAN_GCLK_DIV_MODE,
					CAN_GCLK_DIV);
	// Now enable the generic clock
	scif_gc_enable(AVR32_SCIF_GCLK_CANIF);
	 
	// Assign GPIO to CAN. 
	gpio_enable_module_pin(config.can_rx_map.pin, config.can_rx_map.function);
	gpio_enable_module_pin(config.can_tx_map.pin, config.can_tx_map.function);

	// activate control pins for CAN transceiver
	//gpio_configure_pin(config.can_shutdown_pin, GPIO_DIR_OUTPUT | GPIO_INIT_LOW); // CAN0 shutdown line
	//gpio_configure_pin(config.can_standby_pin, GPIO_DIR_OUTPUT | GPIO_INIT_LOW); // CAN0 standby line

	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[config.can_shutdown_pin >> 5];
	gpio_port->ovrc = 1 << (config.can_shutdown_pin & 0x1F);
	gpio_port->oders = 1 << (config.can_shutdown_pin & 0x1F);

	gpio_port = &AVR32_GPIO.port[config.can_standby_pin >> 5];
	gpio_port->ovrc = 1 << (config.can_standby_pin & 0x1F);
	gpio_port->oders = 1 << (config.can_standby_pin & 0x1F);

	// Initialize channel 0 
	can_bus_init_hardware(channel, ((uint32_t)&mob_ram_ch0[channel]), CANIF_CHANNEL_MODE_NORMAL, NULL);

	CAN_stream_rx[channel]=NULL;
	CAN_stream_tx[channel]=NULL;
	
}


void CAN_start_transmission_internal(can_stream_data_t* data) {
	int i=0;
	
	while ((buffer_bytes_available(&data->byte_buffer)>0) && i<8) {
		data->can_msg.data.u8[i]=buffer_get(&data->byte_buffer);
		i++;
	}
	if (i==0) { // nothing left to transmit
		data->transmission_active=false;
		return;
	}
	/*
	if (data->can_channel==0) {
		can_bus_init(data->can_channel, ((uint32_t)&mob_ram_ch0[0]), CANIF_CHANNEL_MODE_NORMAL, can_callback0);
	} else {
		can_bus_init(data->can_channel, ((uint32_t)&mob_ram_ch1[0]), CANIF_CHANNEL_MODE_NORMAL, can_callback1);
	}
	*/
	data->can_mob.handle=CAN_TX_MOB;
	data->can_mob.dlc=i;
	data->can_msg.id=data->id;
	data->can_msg.id_mask = data->id_mask;
	data->can_mob.req_type=CAN_DATA_FRAME;
	data->transmission_active=true;
	can_bus_tx(data->can_channel,
	       data->can_mob.handle,
	       data->can_mob.dlc,
	       data->can_mob.req_type,
	       data->can_mob.can_msg);
}

void can_bus_start_transmission(can_stream_data_t* data) {
	if (data->transmission_active==false) 
		CAN_start_transmission_internal(data);
} 


void CAN_put(can_stream_data_t *data, uint8_t ch) {
	buffer_put_lossy(&data->byte_buffer, ch);
}

uint8_t CAN_get(can_stream_data_t *data) {
	return buffer_get(&data->byte_buffer);
}


int CAN_bytes_available(can_stream_data_t *data) {
	return buffer_bytes_available(&data->byte_buffer);
}

int CAN_buffer_empty(can_stream_data_t *data) {
	return buffer_empty(&data->byte_buffer);
}


void CAN_flush(can_stream_data_t *data) {
	can_bus_start_transmission(data);
	while (CAN_bytes_available(data)>0);
}

void can_bus_register_write_stream(can_stream_data_t *data, byte_stream_t *stream, can_channel_t channel, can_id_t id, can_id_t id_mask) {
	data->can_channel=channel;

	CAN_stream_tx[data->can_channel]=data;
	
	data->can_mob.can_msg=&data->can_msg;
	
	data->id=id;
	data->id_mask=id_mask;
	data->transmission_active=false;
	
	buffer_init(&data->byte_buffer);
	
	data->can_mob.handle = CAN_TX_MOB;

	stream->get=NULL;
	//stream->get=&uart_int_get_byte;
	stream->put=(int8_t(*)(stream_data_t*, uint8_t))&CAN_put;
	stream->flush=(void(*)(stream_data_t*))&CAN_flush;
	stream->bytes_available=(int(*)(stream_data_t*))&CAN_bytes_available;
	stream->buffer_empty=(bool(*)(stream_data_t*))&CAN_buffer_empty;
	stream->start_transmission=(void(*)(stream_data_t*))can_bus_start_transmission;
	stream->data=data;
}

void can_bus_register_read_stream(can_stream_data_t *data, byte_stream_t *stream, can_channel_t channel, can_id_t id, can_id_t id_mask) {
	data->can_channel=channel;

	CAN_stream_rx[data->can_channel]=data;

	data->can_mob.can_msg=&data->can_msg;
	buffer_init(&data->byte_buffer);
	data->can_mob.req_type=CAN_DATA_FRAME;
	data->can_mob.dlc=2;
	data->can_mob.status=CAN_STATUS_NOT_COMPLETED;
	
	data->can_mob.handle =CAN_RX_MOB; // allocate a MOB for the receive channel

	data->id=id;
	data->id_mask=id_mask;

	stream->get=(uint8_t(*)(stream_data_t*))&CAN_get;
	//stream->get=&uart_int_get_byte;
	stream->put=NULL;
	stream->flush=NULL;
	stream->bytes_available=(int(*)(stream_data_t*))&CAN_bytes_available;
	stream->buffer_empty=(bool(*)(stream_data_t*))&CAN_buffer_empty;
	stream->start_transmission=NULL;
	stream->data=data;
	
	
	// initiate reception mode using two MOBs for double-buffering:
	data->can_mob.handle =CAN_RX_MOB; // allocate a MOB for the receive channel
	can_bus_rx(data->can_channel, data->can_mob.handle, data->can_mob.req_type, &data->can_msg);
	data->can_mob.handle =CAN_RX_MOB+1; // allocate a MOB for the receive channel
	can_bus_rx(data->can_channel, data->can_mob.handle, data->can_mob.req_type, &data->can_msg);
	
}
