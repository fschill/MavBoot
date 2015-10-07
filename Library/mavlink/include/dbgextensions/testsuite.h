/** @file
 *	@brief MAVLink comm protocol testsuite generated from dbgextensions.xml
 *	@see http://qgroundcontrol.org/mavlink/
 */
#ifndef DBGEXTENSIONS_TESTSUITE_H
#define DBGEXTENSIONS_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL
static void mavlink_test_common(uint8_t, uint8_t, mavlink_message_t *last_msg);
static void mavlink_test_dbgextensions(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_test_common(system_id, component_id, last_msg);
	mavlink_test_dbgextensions(system_id, component_id, last_msg);
}
#endif

#include "../common/testsuite.h"


static void mavlink_test_can_packet(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_can_packet_t packet_in = {
		963497464,963497672,29,96,163,{ 230, 231, 232, 233, 234, 235, 236, 237 }
    };
	mavlink_can_packet_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.time_boot_ms = packet_in.time_boot_ms;
        	packet1.can_id = packet_in.can_id;
        	packet1.bus_id = packet_in.bus_id;
        	packet1.frame_type = packet_in.frame_type;
        	packet1.dlc = packet_in.dlc;
        
        	mav_array_memcpy(packet1.values, packet_in.values, sizeof(uint8_t)*8);
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_can_packet_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_can_packet_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_can_packet_pack(system_id, component_id, &msg , packet1.time_boot_ms , packet1.bus_id , packet1.can_id , packet1.frame_type , packet1.dlc , packet1.values );
	mavlink_msg_can_packet_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_can_packet_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_boot_ms , packet1.bus_id , packet1.can_id , packet1.frame_type , packet1.dlc , packet1.values );
	mavlink_msg_can_packet_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_can_packet_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_can_packet_send(MAVLINK_COMM_1 , packet1.time_boot_ms , packet1.bus_id , packet1.can_id , packet1.frame_type , packet1.dlc , packet1.values );
	mavlink_msg_can_packet_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_raw_data_stream_8(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_raw_data_stream_8_t packet_in = {
		963497464,17,84,151,218,{ 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92 }
    };
	mavlink_raw_data_stream_8_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.time_boot_ms = packet_in.time_boot_ms;
        	packet1.stream_id = packet_in.stream_id;
        	packet1.packets_per_block = packet_in.packets_per_block;
        	packet1.packet_id = packet_in.packet_id;
        	packet1.sample_count = packet_in.sample_count;
        
        	mav_array_memcpy(packet1.values, packet_in.values, sizeof(uint8_t)*64);
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_raw_data_stream_8_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_raw_data_stream_8_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_raw_data_stream_8_pack(system_id, component_id, &msg , packet1.time_boot_ms , packet1.stream_id , packet1.packets_per_block , packet1.packet_id , packet1.sample_count , packet1.values );
	mavlink_msg_raw_data_stream_8_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_raw_data_stream_8_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_boot_ms , packet1.stream_id , packet1.packets_per_block , packet1.packet_id , packet1.sample_count , packet1.values );
	mavlink_msg_raw_data_stream_8_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_raw_data_stream_8_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_raw_data_stream_8_send(MAVLINK_COMM_1 , packet1.time_boot_ms , packet1.stream_id , packet1.packets_per_block , packet1.packet_id , packet1.sample_count , packet1.values );
	mavlink_msg_raw_data_stream_8_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_raw_data_stream_16(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_raw_data_stream_16_t packet_in = {
		963497464,{ 17443, 17444, 17445, 17446, 17447, 17448, 17449, 17450, 17451, 17452, 17453, 17454, 17455, 17456, 17457, 17458, 17459, 17460, 17461, 17462, 17463, 17464, 17465, 17466, 17467, 17468, 17469, 17470, 17471, 17472, 17473, 17474, 17475, 17476, 17477, 17478, 17479, 17480, 17481, 17482, 17483, 17484, 17485, 17486, 17487, 17488, 17489, 17490, 17491, 17492, 17493, 17494, 17495, 17496, 17497, 17498, 17499, 17500, 17501, 17502, 17503, 17504, 17505, 17506 },145,212,23,90
    };
	mavlink_raw_data_stream_16_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.time_boot_ms = packet_in.time_boot_ms;
        	packet1.stream_id = packet_in.stream_id;
        	packet1.packets_per_block = packet_in.packets_per_block;
        	packet1.packet_id = packet_in.packet_id;
        	packet1.sample_count = packet_in.sample_count;
        
        	mav_array_memcpy(packet1.values, packet_in.values, sizeof(int16_t)*64);
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_raw_data_stream_16_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_raw_data_stream_16_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_raw_data_stream_16_pack(system_id, component_id, &msg , packet1.time_boot_ms , packet1.stream_id , packet1.packets_per_block , packet1.packet_id , packet1.sample_count , packet1.values );
	mavlink_msg_raw_data_stream_16_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_raw_data_stream_16_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_boot_ms , packet1.stream_id , packet1.packets_per_block , packet1.packet_id , packet1.sample_count , packet1.values );
	mavlink_msg_raw_data_stream_16_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_raw_data_stream_16_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_raw_data_stream_16_send(MAVLINK_COMM_1 , packet1.time_boot_ms , packet1.stream_id , packet1.packets_per_block , packet1.packet_id , packet1.sample_count , packet1.values );
	mavlink_msg_raw_data_stream_16_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_raw_data_stream_float(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_raw_data_stream_float_t packet_in = {
		963497464,{ 45.0, 46.0, 47.0, 48.0, 49.0, 50.0, 51.0, 52.0, 53.0, 54.0, 55.0, 56.0, 57.0, 58.0, 59.0, 60.0, 61.0, 62.0, 63.0, 64.0, 65.0, 66.0, 67.0, 68.0, 69.0, 70.0, 71.0, 72.0, 73.0, 74.0, 75.0, 76.0 },145,212,23,90
    };
	mavlink_raw_data_stream_float_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.time_boot_ms = packet_in.time_boot_ms;
        	packet1.stream_id = packet_in.stream_id;
        	packet1.packets_per_block = packet_in.packets_per_block;
        	packet1.packet_id = packet_in.packet_id;
        	packet1.sample_count = packet_in.sample_count;
        
        	mav_array_memcpy(packet1.values, packet_in.values, sizeof(float)*32);
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_raw_data_stream_float_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_raw_data_stream_float_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_raw_data_stream_float_pack(system_id, component_id, &msg , packet1.time_boot_ms , packet1.stream_id , packet1.packets_per_block , packet1.packet_id , packet1.sample_count , packet1.values );
	mavlink_msg_raw_data_stream_float_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_raw_data_stream_float_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_boot_ms , packet1.stream_id , packet1.packets_per_block , packet1.packet_id , packet1.sample_count , packet1.values );
	mavlink_msg_raw_data_stream_float_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_raw_data_stream_float_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_raw_data_stream_float_send(MAVLINK_COMM_1 , packet1.time_boot_ms , packet1.stream_id , packet1.packets_per_block , packet1.packet_id , packet1.sample_count , packet1.values );
	mavlink_msg_raw_data_stream_float_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_bootloader_cmd(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_bootloader_cmd_t packet_in = {
		963497464,963497672,963497880,41,108,175,242
    };
	mavlink_bootloader_cmd_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.session_message_counter = packet_in.session_message_counter;
        	packet1.param_address = packet_in.param_address;
        	packet1.param_length = packet_in.param_length;
        	packet1.target_system = packet_in.target_system;
        	packet1.target_component = packet_in.target_component;
        	packet1.command = packet_in.command;
        	packet1.error_id = packet_in.error_id;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_bootloader_cmd_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_bootloader_cmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_bootloader_cmd_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component , packet1.session_message_counter , packet1.command , packet1.error_id , packet1.param_address , packet1.param_length );
	mavlink_msg_bootloader_cmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_bootloader_cmd_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component , packet1.session_message_counter , packet1.command , packet1.error_id , packet1.param_address , packet1.param_length );
	mavlink_msg_bootloader_cmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_bootloader_cmd_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_bootloader_cmd_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component , packet1.session_message_counter , packet1.command , packet1.error_id , packet1.param_address , packet1.param_length );
	mavlink_msg_bootloader_cmd_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_bootloader_data(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_bootloader_data_t packet_in = {
		963497464,963497672,29,96,163,230,{ 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72 }
    };
	mavlink_bootloader_data_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.session_message_counter = packet_in.session_message_counter;
        	packet1.base_address = packet_in.base_address;
        	packet1.target_system = packet_in.target_system;
        	packet1.target_component = packet_in.target_component;
        	packet1.command = packet_in.command;
        	packet1.data_length = packet_in.data_length;
        
        	mav_array_memcpy(packet1.data, packet_in.data, sizeof(uint8_t)*32);
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_bootloader_data_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_bootloader_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_bootloader_data_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component , packet1.session_message_counter , packet1.command , packet1.base_address , packet1.data_length , packet1.data );
	mavlink_msg_bootloader_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_bootloader_data_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component , packet1.session_message_counter , packet1.command , packet1.base_address , packet1.data_length , packet1.data );
	mavlink_msg_bootloader_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_bootloader_data_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_bootloader_data_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component , packet1.session_message_counter , packet1.command , packet1.base_address , packet1.data_length , packet1.data );
	mavlink_msg_bootloader_data_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_dbgextensions(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_test_can_packet(system_id, component_id, last_msg);
	mavlink_test_raw_data_stream_8(system_id, component_id, last_msg);
	mavlink_test_raw_data_stream_16(system_id, component_id, last_msg);
	mavlink_test_raw_data_stream_float(system_id, component_id, last_msg);
	mavlink_test_bootloader_cmd(system_id, component_id, last_msg);
	mavlink_test_bootloader_data(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // DBGEXTENSIONS_TESTSUITE_H
