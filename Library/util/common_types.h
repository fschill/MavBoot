/**
 * Common library-wide type definitions
 * 
 * Author: Felix Schill
 * 2014
 */

#ifndef COMMON_TYPES_H_
#define COMMON_TYPES_H_

typedef struct {
	uint32_t pin;      /**< Module pin. */
	uint32_t function; /**< Module function. */
} gpio_module_map_t;

typedef uint32_t gpio_pin_t;

// future-proof time types
typedef int64_t time_milliseconds_t;
typedef int64_t time_microseconds_t;

// shorter time definitions to save memory
typedef int32_t time_span_microseconds_t;
typedef int32_t time_span_milliseconds_t;


typedef double seconds_t;

typedef struct time_reference_t {
	int16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hours, minutes, seconds;
	uint32_t micros;
} time_reference_t;


#endif