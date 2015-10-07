/*
 * boardsupport.c
 *
 * Created: 20/03/2013 12:14:18
 *  Author: sfx
 */ 

#include "asv_mavric_board.h"
#include "sysclk.h"
#include "sleep.h"
#include "analog_monitor.h"
#include "sleepmgr.h"
#include "onboard_parameters.h"
#include "central_data.h"
#include "tc.h"
#include "can_bus.h"
#include "mavlink_stream.h"
#include "mavlink_communication.h"

#include "lsm330dlc.h"
#include "hmc5883l.h"
#include "debugtools.h"

void initialise_board(void) {
		int i;
		central_data_t *central_data=central_data_get_pointer_to_struct();
		
		irq_initialize_vectors();
		cpu_irq_enable();
		Disable_global_interrupt();
			
		// Initialize the sleep manager
		sleepmgr_init();
		sysclk_init();
		INTC_init_interrupts();

		delay_init(sysclk_get_cpu_hz());
		time_keeper_init();
		
//		time_keeper_init_synchronisation();

		init_LEDs();
		switch_LED(1, LED_ON);
		switch_LED(0, LED_ON);

		pwm_servos_init(true);
		
		// set up UART for main telemetry
		uart_int_set_usart_conf(0, asv_xbee_uart_conf());
		uart_int_init(0);
		uart_int_register_write_stream(uart_int_get_uart_handle(0), &central_data->xbee_out_stream);
		
		//init_UART_DMA(0);
		//register_write_stream_dma(get_UART_handle(0), &central_data->xbee_out_stream);
		buffer_make_buffered_stream(&(central_data->xbee_in_buffer), &(central_data->xbee_in_stream));
		uart_int_register_read_stream(uart_int_get_uart_handle(0), &(central_data->xbee_in_stream));

		uart_int_set_usart_conf(4, asv_debug_uart_conf());
		uart_int_init(4);
		uart_int_register_write_stream(uart_int_get_uart_handle(4), &central_data->wired_out_stream);
		
		//init_UART_DMA(0);
		//register_write_stream_dma(get_UART_handle(0), &central_data->wired_out_stream);
		buffer_make_buffered_stream(&(central_data->wired_in_buffer), &(central_data->wired_in_stream));
		uart_int_register_read_stream(uart_int_get_uart_handle(4), &(central_data->wired_in_stream));

		// set up UART for GPS
		uart_int_set_usart_conf(3, asv_gps_uart_conf());
		uart_int_init(3);
		uart_int_register_write_stream(uart_int_get_uart_handle(3), &central_data->gps_out_stream);		
		buffer_make_buffered_stream(&(central_data->gps_in_buffer), &(central_data->gps_in_stream));
		uart_int_register_read_stream(uart_int_get_uart_handle(3), &(central_data->gps_in_stream));

		
		multistream_init(&central_data->multi_telemetry_down_stream);
		multistream_init(&central_data->multi_telemetry_up_stream);

		multistream_add_stream(&central_data->multi_telemetry_down_stream, &central_data->wired_out_stream);
		multistream_add_stream(&central_data->multi_telemetry_down_stream, &central_data->xbee_out_stream);

		multistream_add_stream(&central_data->multi_telemetry_up_stream, &central_data->wired_in_stream);
		multistream_add_stream(&central_data->multi_telemetry_up_stream, &central_data->xbee_in_stream);
		
		/*
		can_bus_init(1, asv_can1_conf());
		can_bus_register_write_stream(&central_data->ext_can_out_stream_data, &central_data->ext_can_out_stream, 1, MAVLINK_COMPONENT_ID, 0x3ff);
		can_bus_register_read_stream(&central_data->ext_can_in_stream_data, &central_data->ext_can_in_stream, 1, MAVLINK_COMPONENT_ID, 0x00);
		*/
		
		// set telemetry stream for mavlink
		//central_data->telemetry_down_stream=&(central_data->xbee_out_stream);
		//central_data->telemetry_up_stream  =&(central_data->xbee_in_stream);
		//central_data->telemetry_down_stream=&(central_data->wired_out_stream);
		//central_data->telemetry_up_stream  =&(central_data->wired_in_stream);
		central_data->telemetry_down_stream= multistream_get_stream(&central_data->multi_telemetry_down_stream);
		central_data->telemetry_up_stream  = multistream_get_stream(&central_data->multi_telemetry_up_stream);
		
		central_data->debug_out_stream=&central_data->wired_out_stream;
		central_data->debug_in_stream=&central_data->wired_in_stream;
		//central_data->debug_out_stream = &central_data->xbee_out_stream;
		//central_data->debug_in_stream  = &central_data->xbee_in_stream;
		
		print_util_dbg_print_init(central_data->debug_out_stream);

		// init error handler as plain text until mavlink is configured
		error_handler_init_plaintext(central_data->debug_out_stream);

		// init mavlink
		// Init mavlink communication
		mavlink_communication_conf_t mavlink_config = 
		{	
			.scheduler_config =
			{
				.max_task_count = 30,
				.schedule_strategy = ROUND_ROBIN,
				.debug = true
			},
			.mavlink_stream_config = 
			{
				.rx_stream   = central_data->telemetry_up_stream,
				.tx_stream   = central_data->telemetry_down_stream,
				.sysid       = MAVLINK_SYS_ID,
				.compid      = MAVLINK_COMPONENT_ID,
				.use_dma     = false
			},
			.message_handler_config = 
			{
				.max_msg_callback_count = 20,
				.max_cmd_callback_count = 20,
				.debug                  = true
			},
			.onboard_parameters_config =
			{
				.max_param_count = MAX_ONBOARD_PARAM_COUNT,
				.debug           = true
			}
		};
		mavlink_communication_init(&central_data->mavlink_communication, &mavlink_config);


		/*mavlink_communication_conf_t ext_mavlink_config =
		{
			.scheduler_config =
			{
				.max_task_count = 3,
				.schedule_strategy = ROUND_ROBIN,
				.debug = true
			},
			.mavlink_stream_config =
			{
				.rx_stream   = &central_data->ext_can_in_stream,
				.tx_stream   = &central_data->ext_can_out_stream,
				.sysid       = MAVLINK_SYS_ID,
				.compid      = MAVLINK_COMPONENT_ID,
				.use_dma     = false
			},
			.message_handler_config =
			{
				.max_msg_callback_count = 5,
				.max_cmd_callback_count = 2,
				.debug                  = true
			},
			.onboard_parameters_config =
			{
				.max_param_count = 5,
				.debug           = true
			}
		};
		mavlink_communication_init(&central_data->ext_mavlink_communication, &ext_mavlink_config);*/

		//error_handler_init_plaintext(central_data->debug_out_stream);
		error_handler_init_mavlink(&central_data->mavlink_communication.mavlink_stream);
		error_handler_set_debug_level(DEBUG_2);
		ERROR(MSG, INFO, "setting debug level to 2");
		DBG_MSG(DEBUG_0, "debug message level 0\n");

		
		init_analog_monitor(&central_data->analog_monitor);
		
		central_data->board_control = board_control_conf();
		// initialise power control pins defined in conf_board:
		for (i=0; i<(POWER_CONTROL_PINS_COUNT); i++) {
			gpio_configure_pin(central_data->board_control.power_control[i].gpio_pin, GPIO_DIR_OUTPUT);
		}
		update_control_pins(NULL);
		// wait 100ms to allow power rails to stabilise
		delay_ms(100); 
		
		// initialise power control pins defined in conf_board:

		// init imu & compass
		
		// init imu & compass
		i2c_driver_init(I2C0);

		delay_ms(100); 
		lsm330dlc_init();
		DBG_MSG(DEBUG_0, "LSM330 initialised");
		delay_ms(300);
		
		hmc5883l_init_slow();
		DBG_MSG(DEBUG_0, "HMC5883 initialised");
		delay_ms(100);
		
		// RC receiver initialization
		spektrum_satellite_init(&(central_data->remote.sat), asv_spektrum_uart_conf());
		// Init remote
		remote_init(&central_data->remote, asv_remote_conf());
		
//		Init_DAC(0);
//		DAC_set_value(0);
		Enable_global_interrupt();
		delay_ms(50);
		run_analog_monitor();
		//save_stack_trace();
		delay_ms(100);
}

void init_pps_timer() {
	
	avr32_tc_t *pps_timer= (avr32_tc_t*)&AVR32_TC0;
	tc_waveform_opt_t wave_opt0={0};
	tc_waveform_opt_t wave_opt1={0};

	wave_opt0.channel=0;
	wave_opt0.acpc=1;   // set output A at max value (RC)
	wave_opt0.acpa=2;   // clear output A at compare match (RA)
	wave_opt0.wavsel=2; // up mode with automatic trigger at RC compare
	wave_opt0.enetrg=1; // enable external trigger (from GPS PPS signal)
	wave_opt0.eevt=0;   // TIOB as external trigger
	wave_opt0.eevtedg=1;// external trigger rising edge
	wave_opt0.tcclks=2; // select timer clock 3 (PBC/8)


	wave_opt1.channel=1;
	wave_opt1.acpc=1;   // set output A at max value (RC)
	wave_opt1.acpa=2;   // clear output A at compare match (RA)
	wave_opt1.wavsel=2; // up mode with automatic trigger at RC compare
	wave_opt1.enetrg=1; // enable external trigger (from GPS PPS signal)
	wave_opt1.eevt=0;   // TIOB as external trigger
	wave_opt1.eevtedg=1;// external trigger rising edge
	wave_opt1.tcclks=6; // select timer clock XC1 (connected to output of channel 0)
	
	tc_init_waveform(pps_timer, &wave_opt0);
	tc_init_waveform(pps_timer, &wave_opt1);
	
	// set up registers to count ticks to 1 millisecond (channel 0) and 1000 milliseconds (channel 1)
	tc_write_ra(pps_timer, 0, sysclk_get_cpu_hz()/8/2000);
	tc_write_rc(pps_timer, 0, sysclk_get_cpu_hz()/8/1000);
	tc_write_ra(pps_timer, 1, 500);
	tc_write_rc(pps_timer, 1, 1000);
	pps_timer->bmr= 2<< 2; // choose TIOA0 as input for XC1
	
	// activate TC0 A0 output pin for test point
	gpio_enable_module_pin(AVR32_TC0_A0_0_0_PIN, AVR32_TC0_A0_0_0_FUNCTION);
	gpio_enable_module_pin(AVR32_TC0_B0_0_0_PIN, AVR32_TC0_B0_0_0_FUNCTION);

	// activate TC0 A1 output pin
	gpio_enable_module_pin(AVR32_TC0_B1_0_0_PIN, AVR32_TC0_B1_0_0_FUNCTION);
	gpio_enable_module_pin(AVR32_TC0_A1_0_0_PIN, AVR32_TC0_A1_FUNCTION);
	
	tc_start(pps_timer, 0);
	tc_start(pps_timer, 1);
}

void boardcontrol_register_parameters(onboard_parameters_t * onboard_parameters) {
	central_data_t *central_data=central_data_get_pointer_to_struct();
	int i;
	for (i=0; i<POWER_CONTROL_PINS_COUNT; i++) {
		onboard_parameters_add_parameter_float(onboard_parameters, &central_data->board_control.power_control[i].pin_control, central_data->board_control.power_control[i].name);
	}
}

task_return_t update_control_pins(task_argument_t* arg) {
	int pin;
	central_data_t *central_data=central_data_get_pointer_to_struct();
	
	for (pin=0; pin<POWER_CONTROL_PINS_COUNT; pin++) { 
		if (central_data->board_control.power_control[pin].pin_control==0.0f) {
			gpio_set_pin_low(central_data->board_control.power_control[pin].gpio_pin);
		} else {
			gpio_set_pin_high(central_data->board_control.power_control[pin].gpio_pin);
		}
	}
	return TASK_RUN_SUCCESS;
}


