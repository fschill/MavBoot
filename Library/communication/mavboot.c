/*
 * \file   mavboot.c
 * 
 * \author Felix Schill
 *   
 * \brief Bootloader protocol handler for Mavlink-based bootloader on AVR32
 *
 * Created: 03/10/2014 02:08:58
 ******************************************************************************/

#include "mavboot.h"
#include "flashc.h"
//#include "error_handler.h"
//#include "delay.h"
#include "avr32_reset_cause.h"
#include "canif.h"

void mavboot_send_processor_information(mavboot_state_t *mavboot_state);
void mavboot_send_command(mavboot_state_t *mavboot_state, uint8_t target_system, uint8_t target_component, uint32_t session_message_counter, uint8_t command, uint8_t error_id, uint32_t param_address, uint32_t param_length);
void mavboot_send_data(mavboot_state_t *mavboot_statem, uint8_t target_system, uint8_t target_component, uint32_t session_message_counter, uint8_t command, uint32_t base_address, uint8_t data_length, const uint8_t *data);

void wdt_set_ctrl(uint32_t ctrl)
{
	AVR32_WDT.ctrl = ctrl | (AVR32_WDT_KEY_VALUE << AVR32_WDT_CTRL_KEY_OFFSET);
	AVR32_WDT.ctrl = ctrl | ((uint32_t) (~AVR32_WDT_KEY_VALUE << AVR32_WDT_CTRL_KEY_OFFSET) & AVR32_WDT_CTRL_KEY_MASK);
}

void mavboot_init(mavboot_state_t *mavboot_state, mavlink_stream_t *mavlink_stream) {
	mavboot_state->state=MAVBOOT_IDLE;
	mavboot_state->mavlink_stream=mavlink_stream;
	mavboot_state->buffer_clean=true;	
	mavboot_send_command(mavboot_state, 255, 0, mavboot_state->msg_counter, BOOT_INITIATE_SESSION | ACK_FLAG, 0, 0, 0);
}



void mavboot_run(mavboot_state_t *mavboot_state, mavlink_message_t *received_message) {
	mavlink_bootloader_cmd_t cmd;
	mavlink_bootloader_data_t data;
	uint8_t ack_error_id=0;
	uint32_t checksum=0;
	int i;
	//
	//mavboot_send_command(mavboot_state, 255, 0, mavboot_state->msg_counter, BOOT_INITIATE_SESSION | ACK_FLAG, 0, 0, 0);
	
	switch(mavboot_state->mavlink_stream->rec.msg.msgid) {
	case MAVLINK_MSG_ID_BOOTLOADER_CMD:
		mavlink_msg_bootloader_cmd_decode(received_message, &cmd);
				
		// process discovery messages to all processors:
		if ((cmd.target_system==255) && (cmd.target_component==255)) {
			mavboot_state->msg_counter=cmd.session_message_counter;
			switch (cmd.command) {				
			case BOOT_INITIATE_SESSION: /* Activates bootloader after power-up | */
				mavboot_state->state=MAVBOOT_ACTIVE;
				mavboot_state->current_page_address=0;
				mavboot_state->buffer_clean=true;
				mavboot_send_command(mavboot_state, 255, 0, mavboot_state->msg_counter, BOOT_INITIATE_SESSION | ACK_FLAG, 0, 0, 0);
			break;
			case BOOT_RESET: /* Reset microcontroller | */
				mavboot_send_command(mavboot_state, 255, 0, mavboot_state->msg_counter, BOOT_RESET | ACK_FLAG, 0, 0, 0);
				//delay_ms(100);
				reset_do_soft_reset();
			break;
			case BOOT_STATE_RESET: /* Bootloader returns to default state | */
				mavboot_state->state=MAVBOOT_ACTIVE;
				mavboot_state->current_page_address=0;
				mavboot_state->buffer_clean=true;
				mavboot_send_command(mavboot_state, 255, 0, mavboot_state->msg_counter, BOOT_STATE_RESET | ACK_FLAG, 0, 0, 0);
			break;
			case BOOT_GET_PROCESSOR_INFORMATION: /* Request all processor information. Response: multiple messages with information (see following definitions) | */
				mavboot_state->state=MAVBOOT_ACTIVE;
				mavboot_send_processor_information(mavboot_state);
			break;
			default:
			break;
			}
		}

		if ((cmd.target_system==mavboot_state->mavlink_stream->sysid) && (cmd.target_component==mavboot_state->mavlink_stream->compid)) {
			mavboot_state->msg_counter=cmd.session_message_counter;
			switch (cmd.command) {
			case BOOT_INITIATE_SESSION: /* Activates bootloader after power-up | */
				mavboot_send_command(mavboot_state, 255, 0, mavboot_state->msg_counter, BOOT_INITIATE_SESSION | ACK_FLAG, 0, 0, 0);
				mavboot_state->current_page_address=0;
				mavboot_state->buffer_clean=true;
				mavboot_state->state=MAVBOOT_ACTIVE;
			break;
			case BOOT_RESET: /* Reset microcontroller | */
				mavboot_send_command(mavboot_state, 255, 0, mavboot_state->msg_counter, BOOT_RESET | ACK_FLAG, 0, 0, 0);
				//delay_ms(100);
				reset_do_soft_reset();
			break;
			case BOOT_STATE_RESET: /* Bootloader returns to default state | */
				mavboot_state->state=MAVBOOT_ACTIVE;
				mavboot_state->current_page_address=0;
				mavboot_state->buffer_clean=true;
				mavboot_send_command(mavboot_state, 255, 0, mavboot_state->msg_counter, BOOT_STATE_RESET | ACK_FLAG, 0, 0, 0);
			break;
			case BOOT_GET_PROCESSOR_INFORMATION: /* Request all processor information. Response: multiple messages with information (see following definitions) | */
				mavboot_state->state=MAVBOOT_ACTIVE;
				mavboot_send_processor_information(mavboot_state);
			break;
			case BOOT_START_APPLICATION: /* leaves bootloader and starts user application | */
				mavboot_start_user_application(BOOTLOADER_USER_APPLICATION_ADDRESS);
			break;
			
//			case BOOT_START_AT_ADDRESS: /* start execution at address in param_address | */
//				mavboot_start_user_application(cmd.param_address);
//			break;
			case BOOT_ERASE_FLASH: /* erase flash starting from param_address to param_address+param_length (rounded to pages) | */
				for (i=cmd.param_address/BOOTLOADER_PAGE_SIZE; 
				     i<(cmd.param_length+cmd.param_address)/BOOTLOADER_PAGE_SIZE; i++) {
					flashc_erase_page(i, true);
				}
				mavboot_send_command(mavboot_state, 255, 0, mavboot_state->msg_counter, BOOT_ERASE_FLASH | ACK_FLAG, 0, 0, 0);
			break;
			case BOOT_ERASE_USERPAGE: /* erase user page or internal eeprom | */
				if (flashc_erase_user_page(true)) {
					ack_error_id=0;
				} else ack_error_id=-1;
				mavboot_send_command(mavboot_state, 255, 0, mavboot_state->msg_counter, BOOT_ERASE_USERPAGE | ACK_FLAG, 0, 0, 0);
			break;
			
			case BOOT_START_REPROGRAM: /* initiates flash upload session | */
				mavboot_state->state=MAVBOOT_REPROGRAMMING;
				mavboot_state->buffer_clean=true;
				mavboot_send_command(mavboot_state, 255, 0, mavboot_state->msg_counter, BOOT_START_REPROGRAM | ACK_FLAG, 0, 0, 0);
			break;
			case BOOT_END_REPROGRAM: /* ends flash upload session | */
				mavboot_state->state=MAVBOOT_ACTIVE;
				mavboot_send_command(mavboot_state, 255, 0, mavboot_state->msg_counter, BOOT_END_REPROGRAM | ACK_FLAG, 0, 0, 0);
			break;
			case BOOT_WRITE_BUFFER_TO_FLASH:    /* BOOTLOADER_CMD: write page buffer contents to flash page at given address | */
			case BOOT_WRITE_BUFFER_TO_USERPAGE: /* BOOTLOADER_CMD: write page buffer contents to user page or internal eeprom at relative address | */
				if (mavboot_state->state!=MAVBOOT_REPROGRAMMING) {
					ack_error_id=1;
				} else if ((mavboot_state->current_page_address<BOOTLOADER_FLASH_ADDRESS) || (mavboot_state->current_page_address>BOOTLOADER_FLASH_ADDRESS+BOOTLOADER_FLASH_SIZE-BOOTLOADER_PAGE_SIZE)) {
					ack_error_id=2;
				} else if (mavboot_state->current_page_address!=cmd.param_address) {
					ack_error_id=3;
				} else {
					//int i;
					flashc_memcpy((void*)mavboot_state->current_page_address, &mavboot_state->page_buffer, BOOTLOADER_PAGE_SIZE, true);
					checksum = crc_calculate((uint8_t*)mavboot_state->current_page_address, BOOTLOADER_PAGE_SIZE);
					//for (i=0; i<BOOTLOADER_PAGE_SIZE; i++) {
					//	checksum+=(((uint8_t*)mavboot_state->current_page_address)[i])&0xFF;
					//}
					
					mavboot_state->buffer_clean=true;
					ack_error_id=0;					
				}
				mavboot_send_command(mavboot_state, 255, 0, mavboot_state->msg_counter, BOOT_WRITE_BUFFER_TO_FLASH | ACK_FLAG, ack_error_id, mavboot_state->current_page_address, checksum);				
				
			break;
			case BOOT_READ_MEMORY: /* Request data at given memory address  | */
				mavboot_send_data(mavboot_state, 255, 0, mavboot_state->msg_counter,BOOT_READ_MEMORY|ACK_FLAG, (uint32_t)&cmd.param_address, cmd.param_length, (uint8_t*)cmd.param_address);
			break;
			case BOOT_VERIFY_MEMORY: /* Request crc16 of block at given memory address   */
				checksum = crc_calculate((uint8_t*)cmd.param_address, cmd.param_length);
				mavboot_send_command(mavboot_state, 255, 0, mavboot_state->msg_counter, BOOT_VERIFY_MEMORY | ACK_FLAG, 0, cmd.param_address, checksum);				
			break;
//			case BOOT_READ_FUSES: /* Response: BOOTLOADER_CMD with param_address = fuse bytes | */
//			break;
//			case BOOT_WRITE_FUSES: /* Set fuse bytes to value in param_address | */
//			break;
//			case BOOT_READ_REGISTERS: /* Response: BOOTLOADER_DATA with register dump | */
//			break;
//			case BOOT_READ_STACKPOINTER: /* Response: BOOTLOADER_CMD with stackpointer value in param_address | */
//			break;
//			case BOOT_READ_STACK: /* Response: BOOTLOADER_DATA with stack dump of param_length | */
//			break;
//			case BOOT_DEBUG_PAUSE: /* pause execution and enter debug mode | */
//			break;
//			case BOOT_DEBUG_CONTINUE: /* continue execution | */				
//			break;
			default:
			break;
			}
		}
		break;
	case MAVLINK_MSG_ID_BOOTLOADER_DATA:
		mavlink_msg_bootloader_data_decode(received_message, &data);
		mavboot_state->msg_counter=data.session_message_counter;
		if ((data.target_system==mavboot_state->mavlink_stream->sysid) && (data.target_component==mavboot_state->mavlink_stream->compid)) {
			switch (data.command) {
			case BOOT_WRITE_TO_BUFFER: /* BOOTLOADER_DATA: write data to internal page buffer | */
				// check if address is valid
				if ((data.base_address>=BOOTLOADER_USER_APPLICATION_ADDRESS) && (data.base_address<BOOTLOADER_FLASH_ADDRESS+BOOTLOADER_FLASH_SIZE))  {
					if (mavboot_state->buffer_clean) { // if buffer is unused, initialise buffer base address
						mavboot_state->current_page_address=data.base_address - (data.base_address % BOOTLOADER_PAGE_SIZE);
						mavboot_state->buffer_clean=false;
					}
					if ((data.base_address-mavboot_state->current_page_address >= 0) && (data.base_address-mavboot_state->current_page_address + data.data_length <= BOOTLOADER_PAGE_SIZE)) {
						int i;
						uint32_t checksum = crc_calculate(data.data, data.data_length);
						// copy data
						for (i=0; i<data.data_length; i++) {
							mavboot_state->page_buffer[data.base_address-mavboot_state->current_page_address+i]=data.data[i];
							//checksum+=data.data[i];
						}
						// send acknowledgment
						mavboot_send_command(mavboot_state, 255, 0, mavboot_state->msg_counter, BOOT_WRITE_TO_BUFFER | ACK_FLAG, 0, data.base_address, checksum);
					} else { // base address outside page range
						mavboot_send_command(mavboot_state, 255, 0, mavboot_state->msg_counter, BOOT_WRITE_TO_BUFFER | ACK_FLAG, 2, data.base_address, 0);
					}
				} else { // invalid flash area
					mavboot_send_command(mavboot_state, 255, 0, mavboot_state->msg_counter, BOOT_WRITE_TO_BUFFER | ACK_FLAG, 1, data.base_address, 0);
				}
			break;
			}
		}
	break;
	}	
}


// **** internal private functions ****

void mavboot_send_command(mavboot_state_t *mavboot_state, uint8_t target_system, uint8_t target_component, uint32_t session_message_counter, uint8_t command, uint8_t error_id, uint32_t param_address, uint32_t param_length) {
	mavlink_message_t cmd;
	mavlink_msg_bootloader_cmd_pack(mavboot_state->mavlink_stream->sysid, mavboot_state->mavlink_stream->compid, &cmd, target_system, target_component, session_message_counter, command, error_id, param_address, param_length);
	mavlink_stream_send(mavboot_state->mavlink_stream, &cmd);
	//bytestream_flush(mavlink_stream->tx);
	//mavboot_state->mavlink_stream->tx->flush(mavboot_state->mavlink_stream->tx->data);
}

void mavboot_send_data(mavboot_state_t *mavboot_state, uint8_t target_system, uint8_t target_component, uint32_t session_message_counter, uint8_t command, uint32_t base_address, uint8_t data_length, const uint8_t *data) {
	mavlink_message_t data_msg;
	mavlink_msg_bootloader_data_pack(mavboot_state->mavlink_stream->sysid, mavboot_state->mavlink_stream->compid, &data_msg, target_system, target_component, session_message_counter, command, base_address, data_length, data);
	mavlink_stream_send(mavboot_state->mavlink_stream, &data_msg);
	//bytestream_flush(mavlink_stream->tx);
	//mavboot_state->mavlink_stream->tx->flush(mavboot_state->mavlink_stream->tx->data);
}



void mavboot_send_processor_information(mavboot_state_t *mavboot_state) {
	//char boardstring[32]=BOOTLOADER_MODULE_NAME;
	uint8_t processor_id[32];
	memset(&processor_id, 0, 32);
	memcpy(&processor_id, (void *)PROCESSOR_ID_ADDRESS, 15);

	//DBG_MSG(DEBUG_0, "Sending processor info");
	
	//mavboot_send_data(mavboot_state, 255, 0, mavboot_state->msg_counter, BOOT_BOARD_NAME | ACK_FLAG, 0, sizeof(BOOTLOADER_MODULE_NAME), (uint8_t*)&boardstring);
	mavboot_send_data(mavboot_state, 255, 0, mavboot_state->msg_counter, BOOT_PROCESSOR_ID | ACK_FLAG, 0, 15, (uint8_t*)&processor_id);
	mavboot_send_command(mavboot_state, 255, 0, mavboot_state->msg_counter, BOOT_PROCESSOR_MODEL | ACK_FLAG, 0, Get_debug_register(0), 0);
	mavboot_send_command(mavboot_state, 255, 0, mavboot_state->msg_counter, BOOT_PAGE_SIZE | ACK_FLAG, 0, BOOTLOADER_PAGE_SIZE, 0);
	mavboot_send_command(mavboot_state, 255, 0, mavboot_state->msg_counter, BOOT_FLASH_ADDRESS | ACK_FLAG, 0, BOOTLOADER_FLASH_ADDRESS, BOOTLOADER_FLASH_SIZE);
	mavboot_send_command(mavboot_state, 255, 0, mavboot_state->msg_counter, BOOT_RAM_ADDRESS | ACK_FLAG, 0, BOOTLOADER_RAM_ADDRESS, BOOTLOADER_RAM_SIZE);
	mavboot_send_command(mavboot_state, 255, 0, mavboot_state->msg_counter, BOOT_USERPAGE_ADDRESS | ACK_FLAG, 0, BOOTLOADER_USERPAGE_ADDRESS, BOOTLOADER_USERPAGE_SIZE);
	mavboot_send_command(mavboot_state, 255, 0, mavboot_state->msg_counter, BOOT_PROTECTED_BOOT_AREA | ACK_FLAG, 0, BOOTLOADER_USER_APPLICATION_ADDRESS, BOOTLOADER_SIZE);

}

//extern void _goto_app(void);
void mavboot_start_user_application(unsigned long ulAddress) {
	// don't start program if flash page is erased
	if (flashc_quick_page_read((BOOTLOADER_USER_APPLICATION_ADDRESS-BOOTLOADER_FLASH_ADDRESS)/BOOTLOADER_PAGE_SIZE)) {
		return;
	}
	//sysclk_set_source(SYSCLK_SRC_RC8M);
	// program watchdog to issue reset	
	wdt_set_ctrl(AVR32_WDT_EN_MASK | AVR32_WDT_DAR_MASK |AVR32_WDT_CEN_MASK);
    //while (1);
	//wdt_reset_mcu();
	//Disable_global_interrupt();
	//CANIF_disable_interrupt(0);
	//sysclk_set_source(SYSCLK_SRC_RCSYS);
	//pll_disable(0);
	//_goto_app();	
}