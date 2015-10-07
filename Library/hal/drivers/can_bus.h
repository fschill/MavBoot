/*
 * \file can_bus.h
 *
 * \brief CAN bus driver for AVR32 with stream interface
 * 
 * Created: 29/07/2014 15:34:29
 *  Author: Felix Schill 
 */ 


#ifndef CAN_BUS_H_
#define CAN_BUS_H_

#include "canif.h"
#include "streams.h"
#include "buffer.h"
#include "common_types.h"

typedef enum {CAN_CHANNEL_0=0, CAN_CHANNEL_1=1} can_channel_t;

typedef U32 can_id_t;

typedef struct{
	U8 handle;
	can_msg_t *can_msg;
	U8 dlc;
	U8 req_type;
	U8 status;
}can_bus_mob_t;

typedef void (*can_callback_t)(can_bus_mob_t *msg_mob);


typedef struct can_stream_config_t {
	gpio_module_map_t can_rx_map;
	gpio_module_map_t can_tx_map;
	gpio_pin_t can_shutdown_pin;
	gpio_pin_t can_standby_pin;
} can_stream_config_t ;

typedef struct can_stream_data_t {
	can_channel_t can_channel;
	can_bus_mob_t can_mob;
	can_msg_t can_msg;
	buffer_t byte_buffer;
	can_id_t   id          : 32;
	can_id_t   id_mask     : 32;
	bool transmission_active;
	can_callback_t packet_callback;
} can_stream_data_t;


void can_bus_init(int channel, can_stream_config_t config);

void can_bus_start_transmission(can_stream_data_t* data);
void can_bus_register_write_stream(can_stream_data_t *data, byte_stream_t *stream, can_channel_t channel, can_id_t id, can_id_t id_mask);
void can_bus_register_read_stream(can_stream_data_t *data, byte_stream_t *stream, can_channel_t channel, can_id_t id, can_id_t id_mask);

void can_bus_register_packet_receive_callback(can_stream_data_t *data, can_callback_t *callback);

#define CAN_TX_MOB 0
#define CAN_RX_MOB 8
// ----------
//! This constant is used as return value for "can_cmd" function.
#define CAN_CMD_REFUSED          0xFF
// ----------
//!This constant is used as return value for "can_cmd" function.
#define CAN_CMD_ACCEPTED         0x00
// ----------
//! This constant is used as return value for "can_get_status" function.
#define CAN_STATUS_COMPLETED     0x00
// ----------
//! This constant is used as return value for "can_get_status" function.
#define CAN_STATUS_NOT_COMPLETED 0x01
// ----------
//! This constant is used as return value for "can_get_status" function.
#define CAN_STATUS_ERROR         0x02
// ----------
//! This constant is used as return value for "can_get_status" function.
#define CAN_STATUS_WAKEUP        0x03
// ----------
//! This constant is used as return value for "can_get_status" function.
#define CAN_STATUS_BUSOFF        0x04
// ----------
//! This constant is used for MOB Allocation status
#define CAN_MOB_NOT_ALLOCATED    0xFF
// ----------
//! This constant is used for MOB Initialization request
#define CAN_DATA_FRAME              0
//! This constant is used for MOB Initialization request
#define CAN_REMOTE_FRAME           1


#endif /* CAN_BUS_H_ */