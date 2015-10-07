/*
 * \file   mavboot.h
 * 
 * \author Felix Schill
 *   
 * \brief Bootloader protocol handler for Mavlink-based bootloader on AVR32
 *
 * Created: 03/10/2014 02:08:58
 ******************************************************************************/


#ifndef MAVBOOT_H_
#define MAVBOOT_H_

#define BOOTLOADER_PAGE_SIZE AVR32_FLASH_PAGE_SIZE

#define BOOTLOADER_FLASH_ADDRESS AVR32_FLASH_ADDRESS
#define BOOTLOADER_FLASH_SIZE AVR32_FLASH_SIZE

#define BOOTLOADER_RAM_ADDRESS AVR32_CPU_RAM_ADDRESS
#define BOOTLOADER_RAM_SIZE AVR32_CPU_RAM_SIZE

#define BOOTLOADER_USERPAGE_ADDRESS AVR32_FLASHC_USER_PAGE_ADDRESS
#define BOOTLOADER_USERPAGE_SIZE AVR32_FLASHC_USER_PAGE_SIZE

#define BOOTLOADER_SIZE 8192
#define BOOTLOADER_USER_APPLICATION_ADDRESS (BOOTLOADER_FLASH_ADDRESS+BOOTLOADER_SIZE)

#define BOOTLOADER_MODULE_NAME "TestBoard"

#define PROCESSOR_ID_ADDRESS 0x80800204

#include "mavlink_stream.h"

typedef enum {MAVBOOT_IDLE, MAVBOOT_ACTIVE, MAVBOOT_REPROGRAMMING} mavboot_internal_state_t;

typedef struct {
	mavlink_stream_t *mavlink_stream;
	mavboot_internal_state_t state;
	int32_t msg_counter;
	uint8_t page_buffer[BOOTLOADER_PAGE_SIZE];
	uint32_t current_page_address;
	bool buffer_clean;
	
} mavboot_state_t;

void mavboot_init(mavboot_state_t *mavboot_state, mavlink_stream_t *mavlink_stream);

void mavboot_run(mavboot_state_t *mavboot_state, mavlink_message_t *received_message);

void system_reset(void);

extern void mavboot_start_user_application(unsigned long ulAddress);

void wdt_set_ctrl(uint32_t ctrl);


#endif /* MAVBOOT_H_ */