/**
 * \file main.c
 *
 * \brief MavBoot bootloader
 * \author Felix Schill
 */

/**
 * \mainpage MavBoot bootloader
 *
 */

/*
 */

#include <asf.h>
#include "mavboot_config.h"
#include "mavboot.h"
#include "central_data.h"
#include "delay.h"


extern void _goto_app(void);

int main (void)
{
	central_data_t *central_data;

	boardsupport_init();
	central_data=central_data_get_pointer_to_struct();
	central_data->mavlink_stream.msg_available=false;
	int cycles=0;
	while (true) {
		mavlink_stream_receive(&central_data->mavlink_stream);
		if (central_data->mavlink_stream.msg_available)
		 {
			//delay_ms(500);
			mavboot_run(&central_data->mavboot_state, &central_data->mavlink_stream.rec.msg);
			central_data->mavlink_stream.msg_available=false;
			
		}

		cycles++;
		if ((cycles>BOOTLOADER_IDLE_WAIT_TIME)&&(central_data->mavboot_state.state==MAVBOOT_IDLE)) {
			mavboot_start_user_application(BOOTLOADER_USER_APPLICATION_ADDRESS);
			// if this returns there is no program to start (page erased) --> return to bootloader function
			central_data->mavboot_state.state=MAVBOOT_ACTIVE;
		}

	
	}
}
