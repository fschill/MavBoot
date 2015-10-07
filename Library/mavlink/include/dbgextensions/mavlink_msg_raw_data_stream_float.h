// MESSAGE RAW_DATA_STREAM_FLOAT PACKING

#define MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT 183

typedef struct __mavlink_raw_data_stream_float_t
{
 uint32_t time_boot_ms; ///< Timestamp (milliseconds since system boot)
 float values[32]; ///< raw sample values
 uint8_t stream_id; ///< Stream ID
 uint8_t packets_per_block; ///< Number of packets per block (0 if continuous stream)
 uint8_t packet_id; ///< packet counter
 uint8_t sample_count; ///< Number of valid samples in this packet
} mavlink_raw_data_stream_float_t;

#define MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT_LEN 136
#define MAVLINK_MSG_ID_183_LEN 136

#define MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT_CRC 138
#define MAVLINK_MSG_ID_183_CRC 138

#define MAVLINK_MSG_RAW_DATA_STREAM_FLOAT_FIELD_VALUES_LEN 32

#define MAVLINK_MESSAGE_INFO_RAW_DATA_STREAM_FLOAT { \
	"RAW_DATA_STREAM_FLOAT", \
	6, \
	{  { "time_boot_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_raw_data_stream_float_t, time_boot_ms) }, \
         { "values", NULL, MAVLINK_TYPE_FLOAT, 32, 4, offsetof(mavlink_raw_data_stream_float_t, values) }, \
         { "stream_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 132, offsetof(mavlink_raw_data_stream_float_t, stream_id) }, \
         { "packets_per_block", NULL, MAVLINK_TYPE_UINT8_T, 0, 133, offsetof(mavlink_raw_data_stream_float_t, packets_per_block) }, \
         { "packet_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 134, offsetof(mavlink_raw_data_stream_float_t, packet_id) }, \
         { "sample_count", NULL, MAVLINK_TYPE_UINT8_T, 0, 135, offsetof(mavlink_raw_data_stream_float_t, sample_count) }, \
         } \
}


/**
 * @brief Pack a raw_data_stream_float message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_boot_ms Timestamp (milliseconds since system boot)
 * @param stream_id Stream ID
 * @param packets_per_block Number of packets per block (0 if continuous stream)
 * @param packet_id packet counter
 * @param sample_count Number of valid samples in this packet
 * @param values raw sample values
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_raw_data_stream_float_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint32_t time_boot_ms, uint8_t stream_id, uint8_t packets_per_block, uint8_t packet_id, uint8_t sample_count, const float *values)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT_LEN];
	_mav_put_uint32_t(buf, 0, time_boot_ms);
	_mav_put_uint8_t(buf, 132, stream_id);
	_mav_put_uint8_t(buf, 133, packets_per_block);
	_mav_put_uint8_t(buf, 134, packet_id);
	_mav_put_uint8_t(buf, 135, sample_count);
	_mav_put_float_array(buf, 4, values, 32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT_LEN);
#else
	mavlink_raw_data_stream_float_t packet;
	packet.time_boot_ms = time_boot_ms;
	packet.stream_id = stream_id;
	packet.packets_per_block = packets_per_block;
	packet.packet_id = packet_id;
	packet.sample_count = sample_count;
	mav_array_memcpy(packet.values, values, sizeof(float)*32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT_LEN, MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT_LEN);
#endif
}

/**
 * @brief Pack a raw_data_stream_float message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_boot_ms Timestamp (milliseconds since system boot)
 * @param stream_id Stream ID
 * @param packets_per_block Number of packets per block (0 if continuous stream)
 * @param packet_id packet counter
 * @param sample_count Number of valid samples in this packet
 * @param values raw sample values
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_raw_data_stream_float_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint32_t time_boot_ms,uint8_t stream_id,uint8_t packets_per_block,uint8_t packet_id,uint8_t sample_count,const float *values)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT_LEN];
	_mav_put_uint32_t(buf, 0, time_boot_ms);
	_mav_put_uint8_t(buf, 132, stream_id);
	_mav_put_uint8_t(buf, 133, packets_per_block);
	_mav_put_uint8_t(buf, 134, packet_id);
	_mav_put_uint8_t(buf, 135, sample_count);
	_mav_put_float_array(buf, 4, values, 32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT_LEN);
#else
	mavlink_raw_data_stream_float_t packet;
	packet.time_boot_ms = time_boot_ms;
	packet.stream_id = stream_id;
	packet.packets_per_block = packets_per_block;
	packet.packet_id = packet_id;
	packet.sample_count = sample_count;
	mav_array_memcpy(packet.values, values, sizeof(float)*32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT_LEN, MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT_LEN);
#endif
}

/**
 * @brief Encode a raw_data_stream_float struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param raw_data_stream_float C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_raw_data_stream_float_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_raw_data_stream_float_t* raw_data_stream_float)
{
	return mavlink_msg_raw_data_stream_float_pack(system_id, component_id, msg, raw_data_stream_float->time_boot_ms, raw_data_stream_float->stream_id, raw_data_stream_float->packets_per_block, raw_data_stream_float->packet_id, raw_data_stream_float->sample_count, raw_data_stream_float->values);
}

/**
 * @brief Encode a raw_data_stream_float struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param raw_data_stream_float C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_raw_data_stream_float_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_raw_data_stream_float_t* raw_data_stream_float)
{
	return mavlink_msg_raw_data_stream_float_pack_chan(system_id, component_id, chan, msg, raw_data_stream_float->time_boot_ms, raw_data_stream_float->stream_id, raw_data_stream_float->packets_per_block, raw_data_stream_float->packet_id, raw_data_stream_float->sample_count, raw_data_stream_float->values);
}

/**
 * @brief Send a raw_data_stream_float message
 * @param chan MAVLink channel to send the message
 *
 * @param time_boot_ms Timestamp (milliseconds since system boot)
 * @param stream_id Stream ID
 * @param packets_per_block Number of packets per block (0 if continuous stream)
 * @param packet_id packet counter
 * @param sample_count Number of valid samples in this packet
 * @param values raw sample values
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_raw_data_stream_float_send(mavlink_channel_t chan, uint32_t time_boot_ms, uint8_t stream_id, uint8_t packets_per_block, uint8_t packet_id, uint8_t sample_count, const float *values)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT_LEN];
	_mav_put_uint32_t(buf, 0, time_boot_ms);
	_mav_put_uint8_t(buf, 132, stream_id);
	_mav_put_uint8_t(buf, 133, packets_per_block);
	_mav_put_uint8_t(buf, 134, packet_id);
	_mav_put_uint8_t(buf, 135, sample_count);
	_mav_put_float_array(buf, 4, values, 32);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT, buf, MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT_LEN, MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT, buf, MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT_LEN);
#endif
#else
	mavlink_raw_data_stream_float_t packet;
	packet.time_boot_ms = time_boot_ms;
	packet.stream_id = stream_id;
	packet.packets_per_block = packets_per_block;
	packet.packet_id = packet_id;
	packet.sample_count = sample_count;
	mav_array_memcpy(packet.values, values, sizeof(float)*32);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT, (const char *)&packet, MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT_LEN, MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT, (const char *)&packet, MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_raw_data_stream_float_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t time_boot_ms, uint8_t stream_id, uint8_t packets_per_block, uint8_t packet_id, uint8_t sample_count, const float *values)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint32_t(buf, 0, time_boot_ms);
	_mav_put_uint8_t(buf, 132, stream_id);
	_mav_put_uint8_t(buf, 133, packets_per_block);
	_mav_put_uint8_t(buf, 134, packet_id);
	_mav_put_uint8_t(buf, 135, sample_count);
	_mav_put_float_array(buf, 4, values, 32);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT, buf, MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT_LEN, MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT, buf, MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT_LEN);
#endif
#else
	mavlink_raw_data_stream_float_t *packet = (mavlink_raw_data_stream_float_t *)msgbuf;
	packet->time_boot_ms = time_boot_ms;
	packet->stream_id = stream_id;
	packet->packets_per_block = packets_per_block;
	packet->packet_id = packet_id;
	packet->sample_count = sample_count;
	mav_array_memcpy(packet->values, values, sizeof(float)*32);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT, (const char *)packet, MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT_LEN, MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT, (const char *)packet, MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE RAW_DATA_STREAM_FLOAT UNPACKING


/**
 * @brief Get field time_boot_ms from raw_data_stream_float message
 *
 * @return Timestamp (milliseconds since system boot)
 */
static inline uint32_t mavlink_msg_raw_data_stream_float_get_time_boot_ms(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field stream_id from raw_data_stream_float message
 *
 * @return Stream ID
 */
static inline uint8_t mavlink_msg_raw_data_stream_float_get_stream_id(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  132);
}

/**
 * @brief Get field packets_per_block from raw_data_stream_float message
 *
 * @return Number of packets per block (0 if continuous stream)
 */
static inline uint8_t mavlink_msg_raw_data_stream_float_get_packets_per_block(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  133);
}

/**
 * @brief Get field packet_id from raw_data_stream_float message
 *
 * @return packet counter
 */
static inline uint8_t mavlink_msg_raw_data_stream_float_get_packet_id(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  134);
}

/**
 * @brief Get field sample_count from raw_data_stream_float message
 *
 * @return Number of valid samples in this packet
 */
static inline uint8_t mavlink_msg_raw_data_stream_float_get_sample_count(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  135);
}

/**
 * @brief Get field values from raw_data_stream_float message
 *
 * @return raw sample values
 */
static inline uint16_t mavlink_msg_raw_data_stream_float_get_values(const mavlink_message_t* msg, float *values)
{
	return _MAV_RETURN_float_array(msg, values, 32,  4);
}

/**
 * @brief Decode a raw_data_stream_float message into a struct
 *
 * @param msg The message to decode
 * @param raw_data_stream_float C-struct to decode the message contents into
 */
static inline void mavlink_msg_raw_data_stream_float_decode(const mavlink_message_t* msg, mavlink_raw_data_stream_float_t* raw_data_stream_float)
{
#if MAVLINK_NEED_BYTE_SWAP
	raw_data_stream_float->time_boot_ms = mavlink_msg_raw_data_stream_float_get_time_boot_ms(msg);
	mavlink_msg_raw_data_stream_float_get_values(msg, raw_data_stream_float->values);
	raw_data_stream_float->stream_id = mavlink_msg_raw_data_stream_float_get_stream_id(msg);
	raw_data_stream_float->packets_per_block = mavlink_msg_raw_data_stream_float_get_packets_per_block(msg);
	raw_data_stream_float->packet_id = mavlink_msg_raw_data_stream_float_get_packet_id(msg);
	raw_data_stream_float->sample_count = mavlink_msg_raw_data_stream_float_get_sample_count(msg);
#else
	memcpy(raw_data_stream_float, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_RAW_DATA_STREAM_FLOAT_LEN);
#endif
}
