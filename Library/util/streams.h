/*
 * streams.h
 *
 * Created: 07/06/2012 21:07:26
 *  Author: sfx
 */


#ifndef STREAMS_H_
#define STREAMS_H_
#include "compiler.h"


typedef void* stream_data_t;


typedef struct byte_stream_t {
	uint8_t (*get)(stream_data_t *data);					   // get a byte from the stream
	int8_t  (*put)(stream_data_t *data, uint8_t element);   // put a byte into the stream. Depending on implementation this may or may not block
	void    (*flush)(stream_data_t *data);                  // initiate transmission and wait for it to finish (blocking)
	void    (*start_transmission)(stream_data_t *data);     // initiate transmission (non-blocking)
	bool     (*buffer_empty)(stream_data_t *data);          // returns true if the stream is empty
	int     (*bytes_available)(stream_data_t *data);        // returns how many bytes can be retrieved from the stream
	void    (*clear_stream)(stream_data_t *data);           // clears the stream buffer (buffer_empty will return true after this)
	volatile stream_data_t data;                            // abstract data object, used by the above methods (implementation specific type)
} byte_stream_t;



#endif
