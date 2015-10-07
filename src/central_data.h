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
 * \file central_data.h
 * 
 * \author MAV'RIC Team
 *   
 * \brief Place where the central data is stored and initialized
 *
 ******************************************************************************/


#ifndef CENTRAL_DATA_H_
#define CENTRAL_DATA_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "boardsupport.h"
#include "mavboot_config.h"
#include "streams.h"
#include "buffer.h"

#include "mavlink_stream.h"
#include "can_bus.h"
#include "mavboot.h"
// TODO : update documentation

/**
 * \brief The central data structure
 */
typedef struct  {
	mavlink_stream_t mavlink_stream;
	can_stream_data_t can_out_stream_data, can_in_stream_data;
	byte_stream_t can_out_stream, can_in_stream;
	byte_stream_t wired_in_stream, wired_out_stream;
	// aliases
	byte_stream_t *telemetry_down_stream;						///< The pointer to the downcoming telemetry byte stream
	byte_stream_t *telemetry_up_stream;							///< The pointer to the upcoming telemetry byte stream
	byte_stream_t *debug_out_stream;							///< The pointer to the outgoing debug byte stream
	byte_stream_t *debug_in_stream;								///< The pointer to the incoming debug byte stream
	
	mavboot_state_t mavboot_state;
	
} central_data_t;


/**
 * \brief	Initialization of the central data structure
 */
void central_data_init(void);


/**
 * \brief	Get a pointer to the central data
 *
 * \return	A pointer to the structure central data
*/
central_data_t* central_data_get_pointer_to_struct(void);

#ifdef __cplusplus
}
#endif

#endif /* CENTRAL_DATA_H_ */
