// MESSAGE BOOTLOADER_DATA PACKING

#define MAVLINK_MSG_ID_BOOTLOADER_DATA 201

typedef struct __mavlink_bootloader_data_t
{
 uint32_t session_message_counter; ///< unique session handle negotiated when entering boot mode. Incremented by master with each message. Slave returns the last received and processed message as acknowledgement.
 uint32_t base_address; ///< 32bit memory base address to write to / read from. 
 uint8_t target_system; ///< System which should execute the command
 uint8_t target_component; ///< Component which should execute the command, 0 for all components
 uint8_t command; ///< Command ID, as defined by BOOTLOADER_CMD enum.
 uint8_t data_length; ///< length of data block (number of valid bytes in data)
 uint8_t data[32]; ///< raw data for memory transfer
} mavlink_bootloader_data_t;

#define MAVLINK_MSG_ID_BOOTLOADER_DATA_LEN 44
#define MAVLINK_MSG_ID_201_LEN 44

#define MAVLINK_MSG_ID_BOOTLOADER_DATA_CRC 147
#define MAVLINK_MSG_ID_201_CRC 147

#define MAVLINK_MSG_BOOTLOADER_DATA_FIELD_DATA_LEN 32

#define MAVLINK_MESSAGE_INFO_BOOTLOADER_DATA { \
	"BOOTLOADER_DATA", \
	7, \
	{  { "session_message_counter", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_bootloader_data_t, session_message_counter) }, \
         { "base_address", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_bootloader_data_t, base_address) }, \
         { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_bootloader_data_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 9, offsetof(mavlink_bootloader_data_t, target_component) }, \
         { "command", NULL, MAVLINK_TYPE_UINT8_T, 0, 10, offsetof(mavlink_bootloader_data_t, command) }, \
         { "data_length", NULL, MAVLINK_TYPE_UINT8_T, 0, 11, offsetof(mavlink_bootloader_data_t, data_length) }, \
         { "data", NULL, MAVLINK_TYPE_UINT8_T, 32, 12, offsetof(mavlink_bootloader_data_t, data) }, \
         } \
}


/**
 * @brief Pack a bootloader_data message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System which should execute the command
 * @param target_component Component which should execute the command, 0 for all components
 * @param session_message_counter unique session handle negotiated when entering boot mode. Incremented by master with each message. Slave returns the last received and processed message as acknowledgement.
 * @param command Command ID, as defined by BOOTLOADER_CMD enum.
 * @param base_address 32bit memory base address to write to / read from. 
 * @param data_length length of data block (number of valid bytes in data)
 * @param data raw data for memory transfer
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_bootloader_data_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t target_system, uint8_t target_component, uint32_t session_message_counter, uint8_t command, uint32_t base_address, uint8_t data_length, const uint8_t *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_BOOTLOADER_DATA_LEN];
	_mav_put_uint32_t(buf, 0, session_message_counter);
	_mav_put_uint32_t(buf, 4, base_address);
	_mav_put_uint8_t(buf, 8, target_system);
	_mav_put_uint8_t(buf, 9, target_component);
	_mav_put_uint8_t(buf, 10, command);
	_mav_put_uint8_t(buf, 11, data_length);
	_mav_put_uint8_t_array(buf, 12, data, 32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_BOOTLOADER_DATA_LEN);
#else
	mavlink_bootloader_data_t packet;
	packet.session_message_counter = session_message_counter;
	packet.base_address = base_address;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.command = command;
	packet.data_length = data_length;
	mav_array_memcpy(packet.data, data, sizeof(uint8_t)*32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_BOOTLOADER_DATA_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_BOOTLOADER_DATA;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_BOOTLOADER_DATA_LEN, MAVLINK_MSG_ID_BOOTLOADER_DATA_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_BOOTLOADER_DATA_LEN);
#endif
}

/**
 * @brief Pack a bootloader_data message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System which should execute the command
 * @param target_component Component which should execute the command, 0 for all components
 * @param session_message_counter unique session handle negotiated when entering boot mode. Incremented by master with each message. Slave returns the last received and processed message as acknowledgement.
 * @param command Command ID, as defined by BOOTLOADER_CMD enum.
 * @param base_address 32bit memory base address to write to / read from. 
 * @param data_length length of data block (number of valid bytes in data)
 * @param data raw data for memory transfer
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_bootloader_data_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t target_system,uint8_t target_component,uint32_t session_message_counter,uint8_t command,uint32_t base_address,uint8_t data_length,const uint8_t *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_BOOTLOADER_DATA_LEN];
	_mav_put_uint32_t(buf, 0, session_message_counter);
	_mav_put_uint32_t(buf, 4, base_address);
	_mav_put_uint8_t(buf, 8, target_system);
	_mav_put_uint8_t(buf, 9, target_component);
	_mav_put_uint8_t(buf, 10, command);
	_mav_put_uint8_t(buf, 11, data_length);
	_mav_put_uint8_t_array(buf, 12, data, 32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_BOOTLOADER_DATA_LEN);
#else
	mavlink_bootloader_data_t packet;
	packet.session_message_counter = session_message_counter;
	packet.base_address = base_address;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.command = command;
	packet.data_length = data_length;
	mav_array_memcpy(packet.data, data, sizeof(uint8_t)*32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_BOOTLOADER_DATA_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_BOOTLOADER_DATA;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_BOOTLOADER_DATA_LEN, MAVLINK_MSG_ID_BOOTLOADER_DATA_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_BOOTLOADER_DATA_LEN);
#endif
}

/**
 * @brief Encode a bootloader_data struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param bootloader_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_bootloader_data_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_bootloader_data_t* bootloader_data)
{
	return mavlink_msg_bootloader_data_pack(system_id, component_id, msg, bootloader_data->target_system, bootloader_data->target_component, bootloader_data->session_message_counter, bootloader_data->command, bootloader_data->base_address, bootloader_data->data_length, bootloader_data->data);
}

/**
 * @brief Encode a bootloader_data struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param bootloader_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_bootloader_data_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_bootloader_data_t* bootloader_data)
{
	return mavlink_msg_bootloader_data_pack_chan(system_id, component_id, chan, msg, bootloader_data->target_system, bootloader_data->target_component, bootloader_data->session_message_counter, bootloader_data->command, bootloader_data->base_address, bootloader_data->data_length, bootloader_data->data);
}

/**
 * @brief Send a bootloader_data message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System which should execute the command
 * @param target_component Component which should execute the command, 0 for all components
 * @param session_message_counter unique session handle negotiated when entering boot mode. Incremented by master with each message. Slave returns the last received and processed message as acknowledgement.
 * @param command Command ID, as defined by BOOTLOADER_CMD enum.
 * @param base_address 32bit memory base address to write to / read from. 
 * @param data_length length of data block (number of valid bytes in data)
 * @param data raw data for memory transfer
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_bootloader_data_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint32_t session_message_counter, uint8_t command, uint32_t base_address, uint8_t data_length, const uint8_t *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_BOOTLOADER_DATA_LEN];
	_mav_put_uint32_t(buf, 0, session_message_counter);
	_mav_put_uint32_t(buf, 4, base_address);
	_mav_put_uint8_t(buf, 8, target_system);
	_mav_put_uint8_t(buf, 9, target_component);
	_mav_put_uint8_t(buf, 10, command);
	_mav_put_uint8_t(buf, 11, data_length);
	_mav_put_uint8_t_array(buf, 12, data, 32);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BOOTLOADER_DATA, buf, MAVLINK_MSG_ID_BOOTLOADER_DATA_LEN, MAVLINK_MSG_ID_BOOTLOADER_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BOOTLOADER_DATA, buf, MAVLINK_MSG_ID_BOOTLOADER_DATA_LEN);
#endif
#else
	mavlink_bootloader_data_t packet;
	packet.session_message_counter = session_message_counter;
	packet.base_address = base_address;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.command = command;
	packet.data_length = data_length;
	mav_array_memcpy(packet.data, data, sizeof(uint8_t)*32);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BOOTLOADER_DATA, (const char *)&packet, MAVLINK_MSG_ID_BOOTLOADER_DATA_LEN, MAVLINK_MSG_ID_BOOTLOADER_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BOOTLOADER_DATA, (const char *)&packet, MAVLINK_MSG_ID_BOOTLOADER_DATA_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_BOOTLOADER_DATA_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_bootloader_data_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t target_system, uint8_t target_component, uint32_t session_message_counter, uint8_t command, uint32_t base_address, uint8_t data_length, const uint8_t *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint32_t(buf, 0, session_message_counter);
	_mav_put_uint32_t(buf, 4, base_address);
	_mav_put_uint8_t(buf, 8, target_system);
	_mav_put_uint8_t(buf, 9, target_component);
	_mav_put_uint8_t(buf, 10, command);
	_mav_put_uint8_t(buf, 11, data_length);
	_mav_put_uint8_t_array(buf, 12, data, 32);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BOOTLOADER_DATA, buf, MAVLINK_MSG_ID_BOOTLOADER_DATA_LEN, MAVLINK_MSG_ID_BOOTLOADER_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BOOTLOADER_DATA, buf, MAVLINK_MSG_ID_BOOTLOADER_DATA_LEN);
#endif
#else
	mavlink_bootloader_data_t *packet = (mavlink_bootloader_data_t *)msgbuf;
	packet->session_message_counter = session_message_counter;
	packet->base_address = base_address;
	packet->target_system = target_system;
	packet->target_component = target_component;
	packet->command = command;
	packet->data_length = data_length;
	mav_array_memcpy(packet->data, data, sizeof(uint8_t)*32);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BOOTLOADER_DATA, (const char *)packet, MAVLINK_MSG_ID_BOOTLOADER_DATA_LEN, MAVLINK_MSG_ID_BOOTLOADER_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BOOTLOADER_DATA, (const char *)packet, MAVLINK_MSG_ID_BOOTLOADER_DATA_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE BOOTLOADER_DATA UNPACKING


/**
 * @brief Get field target_system from bootloader_data message
 *
 * @return System which should execute the command
 */
static inline uint8_t mavlink_msg_bootloader_data_get_target_system(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  8);
}

/**
 * @brief Get field target_component from bootloader_data message
 *
 * @return Component which should execute the command, 0 for all components
 */
static inline uint8_t mavlink_msg_bootloader_data_get_target_component(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  9);
}

/**
 * @brief Get field session_message_counter from bootloader_data message
 *
 * @return unique session handle negotiated when entering boot mode. Incremented by master with each message. Slave returns the last received and processed message as acknowledgement.
 */
static inline uint32_t mavlink_msg_bootloader_data_get_session_message_counter(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field command from bootloader_data message
 *
 * @return Command ID, as defined by BOOTLOADER_CMD enum.
 */
static inline uint8_t mavlink_msg_bootloader_data_get_command(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  10);
}

/**
 * @brief Get field base_address from bootloader_data message
 *
 * @return 32bit memory base address to write to / read from. 
 */
static inline uint32_t mavlink_msg_bootloader_data_get_base_address(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  4);
}

/**
 * @brief Get field data_length from bootloader_data message
 *
 * @return length of data block (number of valid bytes in data)
 */
static inline uint8_t mavlink_msg_bootloader_data_get_data_length(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  11);
}

/**
 * @brief Get field data from bootloader_data message
 *
 * @return raw data for memory transfer
 */
static inline uint16_t mavlink_msg_bootloader_data_get_data(const mavlink_message_t* msg, uint8_t *data)
{
	return _MAV_RETURN_uint8_t_array(msg, data, 32,  12);
}

/**
 * @brief Decode a bootloader_data message into a struct
 *
 * @param msg The message to decode
 * @param bootloader_data C-struct to decode the message contents into
 */
static inline void mavlink_msg_bootloader_data_decode(const mavlink_message_t* msg, mavlink_bootloader_data_t* bootloader_data)
{
#if MAVLINK_NEED_BYTE_SWAP
	bootloader_data->session_message_counter = mavlink_msg_bootloader_data_get_session_message_counter(msg);
	bootloader_data->base_address = mavlink_msg_bootloader_data_get_base_address(msg);
	bootloader_data->target_system = mavlink_msg_bootloader_data_get_target_system(msg);
	bootloader_data->target_component = mavlink_msg_bootloader_data_get_target_component(msg);
	bootloader_data->command = mavlink_msg_bootloader_data_get_command(msg);
	bootloader_data->data_length = mavlink_msg_bootloader_data_get_data_length(msg);
	mavlink_msg_bootloader_data_get_data(msg, bootloader_data->data);
#else
	memcpy(bootloader_data, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_BOOTLOADER_DATA_LEN);
#endif
}
