// MESSAGE CAN_PACKET PACKING

#define MAVLINK_MSG_ID_CAN_PACKET 180

typedef struct __mavlink_can_packet_t
{
 uint32_t time_boot_ms; ///< Timestamp (milliseconds since system boot)
 uint32_t can_id; ///< CAN arbitration field (11 or 29 bits)
 uint8_t bus_id; ///< identifier of the can bus
 uint8_t frame_type; ///< 0: standard frame; 1: remote frame; 2: error frame, 3: overload frame; Extended: 16: standard frame; 17: remote frame; 18: error frame, 19: overload frame
 uint8_t dlc; ///< data length
 uint8_t values[8]; ///< raw sample values
} mavlink_can_packet_t;

#define MAVLINK_MSG_ID_CAN_PACKET_LEN 19
#define MAVLINK_MSG_ID_180_LEN 19

#define MAVLINK_MSG_ID_CAN_PACKET_CRC 175
#define MAVLINK_MSG_ID_180_CRC 175

#define MAVLINK_MSG_CAN_PACKET_FIELD_VALUES_LEN 8

#define MAVLINK_MESSAGE_INFO_CAN_PACKET { \
	"CAN_PACKET", \
	6, \
	{  { "time_boot_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_can_packet_t, time_boot_ms) }, \
         { "can_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_can_packet_t, can_id) }, \
         { "bus_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_can_packet_t, bus_id) }, \
         { "frame_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 9, offsetof(mavlink_can_packet_t, frame_type) }, \
         { "dlc", NULL, MAVLINK_TYPE_UINT8_T, 0, 10, offsetof(mavlink_can_packet_t, dlc) }, \
         { "values", NULL, MAVLINK_TYPE_UINT8_T, 8, 11, offsetof(mavlink_can_packet_t, values) }, \
         } \
}


/**
 * @brief Pack a can_packet message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_boot_ms Timestamp (milliseconds since system boot)
 * @param bus_id identifier of the can bus
 * @param can_id CAN arbitration field (11 or 29 bits)
 * @param frame_type 0: standard frame; 1: remote frame; 2: error frame, 3: overload frame; Extended: 16: standard frame; 17: remote frame; 18: error frame, 19: overload frame
 * @param dlc data length
 * @param values raw sample values
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_can_packet_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint32_t time_boot_ms, uint8_t bus_id, uint32_t can_id, uint8_t frame_type, uint8_t dlc, const uint8_t *values)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_CAN_PACKET_LEN];
	_mav_put_uint32_t(buf, 0, time_boot_ms);
	_mav_put_uint32_t(buf, 4, can_id);
	_mav_put_uint8_t(buf, 8, bus_id);
	_mav_put_uint8_t(buf, 9, frame_type);
	_mav_put_uint8_t(buf, 10, dlc);
	_mav_put_uint8_t_array(buf, 11, values, 8);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CAN_PACKET_LEN);
#else
	mavlink_can_packet_t packet;
	packet.time_boot_ms = time_boot_ms;
	packet.can_id = can_id;
	packet.bus_id = bus_id;
	packet.frame_type = frame_type;
	packet.dlc = dlc;
	mav_array_memcpy(packet.values, values, sizeof(uint8_t)*8);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CAN_PACKET_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_CAN_PACKET;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_CAN_PACKET_LEN, MAVLINK_MSG_ID_CAN_PACKET_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_CAN_PACKET_LEN);
#endif
}

/**
 * @brief Pack a can_packet message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_boot_ms Timestamp (milliseconds since system boot)
 * @param bus_id identifier of the can bus
 * @param can_id CAN arbitration field (11 or 29 bits)
 * @param frame_type 0: standard frame; 1: remote frame; 2: error frame, 3: overload frame; Extended: 16: standard frame; 17: remote frame; 18: error frame, 19: overload frame
 * @param dlc data length
 * @param values raw sample values
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_can_packet_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint32_t time_boot_ms,uint8_t bus_id,uint32_t can_id,uint8_t frame_type,uint8_t dlc,const uint8_t *values)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_CAN_PACKET_LEN];
	_mav_put_uint32_t(buf, 0, time_boot_ms);
	_mav_put_uint32_t(buf, 4, can_id);
	_mav_put_uint8_t(buf, 8, bus_id);
	_mav_put_uint8_t(buf, 9, frame_type);
	_mav_put_uint8_t(buf, 10, dlc);
	_mav_put_uint8_t_array(buf, 11, values, 8);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CAN_PACKET_LEN);
#else
	mavlink_can_packet_t packet;
	packet.time_boot_ms = time_boot_ms;
	packet.can_id = can_id;
	packet.bus_id = bus_id;
	packet.frame_type = frame_type;
	packet.dlc = dlc;
	mav_array_memcpy(packet.values, values, sizeof(uint8_t)*8);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CAN_PACKET_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_CAN_PACKET;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_CAN_PACKET_LEN, MAVLINK_MSG_ID_CAN_PACKET_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_CAN_PACKET_LEN);
#endif
}

/**
 * @brief Encode a can_packet struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param can_packet C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_can_packet_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_can_packet_t* can_packet)
{
	return mavlink_msg_can_packet_pack(system_id, component_id, msg, can_packet->time_boot_ms, can_packet->bus_id, can_packet->can_id, can_packet->frame_type, can_packet->dlc, can_packet->values);
}

/**
 * @brief Encode a can_packet struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param can_packet C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_can_packet_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_can_packet_t* can_packet)
{
	return mavlink_msg_can_packet_pack_chan(system_id, component_id, chan, msg, can_packet->time_boot_ms, can_packet->bus_id, can_packet->can_id, can_packet->frame_type, can_packet->dlc, can_packet->values);
}

/**
 * @brief Send a can_packet message
 * @param chan MAVLink channel to send the message
 *
 * @param time_boot_ms Timestamp (milliseconds since system boot)
 * @param bus_id identifier of the can bus
 * @param can_id CAN arbitration field (11 or 29 bits)
 * @param frame_type 0: standard frame; 1: remote frame; 2: error frame, 3: overload frame; Extended: 16: standard frame; 17: remote frame; 18: error frame, 19: overload frame
 * @param dlc data length
 * @param values raw sample values
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_can_packet_send(mavlink_channel_t chan, uint32_t time_boot_ms, uint8_t bus_id, uint32_t can_id, uint8_t frame_type, uint8_t dlc, const uint8_t *values)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_CAN_PACKET_LEN];
	_mav_put_uint32_t(buf, 0, time_boot_ms);
	_mav_put_uint32_t(buf, 4, can_id);
	_mav_put_uint8_t(buf, 8, bus_id);
	_mav_put_uint8_t(buf, 9, frame_type);
	_mav_put_uint8_t(buf, 10, dlc);
	_mav_put_uint8_t_array(buf, 11, values, 8);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CAN_PACKET, buf, MAVLINK_MSG_ID_CAN_PACKET_LEN, MAVLINK_MSG_ID_CAN_PACKET_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CAN_PACKET, buf, MAVLINK_MSG_ID_CAN_PACKET_LEN);
#endif
#else
	mavlink_can_packet_t packet;
	packet.time_boot_ms = time_boot_ms;
	packet.can_id = can_id;
	packet.bus_id = bus_id;
	packet.frame_type = frame_type;
	packet.dlc = dlc;
	mav_array_memcpy(packet.values, values, sizeof(uint8_t)*8);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CAN_PACKET, (const char *)&packet, MAVLINK_MSG_ID_CAN_PACKET_LEN, MAVLINK_MSG_ID_CAN_PACKET_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CAN_PACKET, (const char *)&packet, MAVLINK_MSG_ID_CAN_PACKET_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_CAN_PACKET_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_can_packet_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t time_boot_ms, uint8_t bus_id, uint32_t can_id, uint8_t frame_type, uint8_t dlc, const uint8_t *values)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint32_t(buf, 0, time_boot_ms);
	_mav_put_uint32_t(buf, 4, can_id);
	_mav_put_uint8_t(buf, 8, bus_id);
	_mav_put_uint8_t(buf, 9, frame_type);
	_mav_put_uint8_t(buf, 10, dlc);
	_mav_put_uint8_t_array(buf, 11, values, 8);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CAN_PACKET, buf, MAVLINK_MSG_ID_CAN_PACKET_LEN, MAVLINK_MSG_ID_CAN_PACKET_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CAN_PACKET, buf, MAVLINK_MSG_ID_CAN_PACKET_LEN);
#endif
#else
	mavlink_can_packet_t *packet = (mavlink_can_packet_t *)msgbuf;
	packet->time_boot_ms = time_boot_ms;
	packet->can_id = can_id;
	packet->bus_id = bus_id;
	packet->frame_type = frame_type;
	packet->dlc = dlc;
	mav_array_memcpy(packet->values, values, sizeof(uint8_t)*8);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CAN_PACKET, (const char *)packet, MAVLINK_MSG_ID_CAN_PACKET_LEN, MAVLINK_MSG_ID_CAN_PACKET_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CAN_PACKET, (const char *)packet, MAVLINK_MSG_ID_CAN_PACKET_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE CAN_PACKET UNPACKING


/**
 * @brief Get field time_boot_ms from can_packet message
 *
 * @return Timestamp (milliseconds since system boot)
 */
static inline uint32_t mavlink_msg_can_packet_get_time_boot_ms(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field bus_id from can_packet message
 *
 * @return identifier of the can bus
 */
static inline uint8_t mavlink_msg_can_packet_get_bus_id(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  8);
}

/**
 * @brief Get field can_id from can_packet message
 *
 * @return CAN arbitration field (11 or 29 bits)
 */
static inline uint32_t mavlink_msg_can_packet_get_can_id(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  4);
}

/**
 * @brief Get field frame_type from can_packet message
 *
 * @return 0: standard frame; 1: remote frame; 2: error frame, 3: overload frame; Extended: 16: standard frame; 17: remote frame; 18: error frame, 19: overload frame
 */
static inline uint8_t mavlink_msg_can_packet_get_frame_type(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  9);
}

/**
 * @brief Get field dlc from can_packet message
 *
 * @return data length
 */
static inline uint8_t mavlink_msg_can_packet_get_dlc(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  10);
}

/**
 * @brief Get field values from can_packet message
 *
 * @return raw sample values
 */
static inline uint16_t mavlink_msg_can_packet_get_values(const mavlink_message_t* msg, uint8_t *values)
{
	return _MAV_RETURN_uint8_t_array(msg, values, 8,  11);
}

/**
 * @brief Decode a can_packet message into a struct
 *
 * @param msg The message to decode
 * @param can_packet C-struct to decode the message contents into
 */
static inline void mavlink_msg_can_packet_decode(const mavlink_message_t* msg, mavlink_can_packet_t* can_packet)
{
#if MAVLINK_NEED_BYTE_SWAP
	can_packet->time_boot_ms = mavlink_msg_can_packet_get_time_boot_ms(msg);
	can_packet->can_id = mavlink_msg_can_packet_get_can_id(msg);
	can_packet->bus_id = mavlink_msg_can_packet_get_bus_id(msg);
	can_packet->frame_type = mavlink_msg_can_packet_get_frame_type(msg);
	can_packet->dlc = mavlink_msg_can_packet_get_dlc(msg);
	mavlink_msg_can_packet_get_values(msg, can_packet->values);
#else
	memcpy(can_packet, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_CAN_PACKET_LEN);
#endif
}
