// MESSAGE BOOTLOADER_CMD PACKING

#define MAVLINK_MSG_ID_BOOTLOADER_CMD 200

typedef struct __mavlink_bootloader_cmd_t
{
 uint32_t session_message_counter; ///< unique session handle negotiated when entering boot mode. Incremented by master with each message. Slave returns the last received and processed message as acknowledgement.
 uint32_t param_address; ///< Command parameter 1 or memory address depending on command
 uint32_t param_length; ///<  Command parameter 2 or transfer length depending on command
 uint8_t target_system; ///< System which should execute the command
 uint8_t target_component; ///< Component which should execute the command, 0 for all components
 uint8_t command; ///< Command ID, as defined by BOOTLOADER_CMD enum.
 uint8_t error_id; ///< Error code in response to previous command or transfer as defined by BOOTLOADER_ERROR enum.
} mavlink_bootloader_cmd_t;

#define MAVLINK_MSG_ID_BOOTLOADER_CMD_LEN 16
#define MAVLINK_MSG_ID_200_LEN 16

#define MAVLINK_MSG_ID_BOOTLOADER_CMD_CRC 224
#define MAVLINK_MSG_ID_200_CRC 224



#define MAVLINK_MESSAGE_INFO_BOOTLOADER_CMD { \
	"BOOTLOADER_CMD", \
	7, \
	{  { "session_message_counter", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_bootloader_cmd_t, session_message_counter) }, \
         { "param_address", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_bootloader_cmd_t, param_address) }, \
         { "param_length", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_bootloader_cmd_t, param_length) }, \
         { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_bootloader_cmd_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 13, offsetof(mavlink_bootloader_cmd_t, target_component) }, \
         { "command", NULL, MAVLINK_TYPE_UINT8_T, 0, 14, offsetof(mavlink_bootloader_cmd_t, command) }, \
         { "error_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 15, offsetof(mavlink_bootloader_cmd_t, error_id) }, \
         } \
}


/**
 * @brief Pack a bootloader_cmd message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System which should execute the command
 * @param target_component Component which should execute the command, 0 for all components
 * @param session_message_counter unique session handle negotiated when entering boot mode. Incremented by master with each message. Slave returns the last received and processed message as acknowledgement.
 * @param command Command ID, as defined by BOOTLOADER_CMD enum.
 * @param error_id Error code in response to previous command or transfer as defined by BOOTLOADER_ERROR enum.
 * @param param_address Command parameter 1 or memory address depending on command
 * @param param_length  Command parameter 2 or transfer length depending on command
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_bootloader_cmd_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t target_system, uint8_t target_component, uint32_t session_message_counter, uint8_t command, uint8_t error_id, uint32_t param_address, uint32_t param_length)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_BOOTLOADER_CMD_LEN];
	_mav_put_uint32_t(buf, 0, session_message_counter);
	_mav_put_uint32_t(buf, 4, param_address);
	_mav_put_uint32_t(buf, 8, param_length);
	_mav_put_uint8_t(buf, 12, target_system);
	_mav_put_uint8_t(buf, 13, target_component);
	_mav_put_uint8_t(buf, 14, command);
	_mav_put_uint8_t(buf, 15, error_id);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_BOOTLOADER_CMD_LEN);
#else
	mavlink_bootloader_cmd_t packet;
	packet.session_message_counter = session_message_counter;
	packet.param_address = param_address;
	packet.param_length = param_length;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.command = command;
	packet.error_id = error_id;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_BOOTLOADER_CMD_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_BOOTLOADER_CMD;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_BOOTLOADER_CMD_LEN, MAVLINK_MSG_ID_BOOTLOADER_CMD_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_BOOTLOADER_CMD_LEN);
#endif
}

/**
 * @brief Pack a bootloader_cmd message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System which should execute the command
 * @param target_component Component which should execute the command, 0 for all components
 * @param session_message_counter unique session handle negotiated when entering boot mode. Incremented by master with each message. Slave returns the last received and processed message as acknowledgement.
 * @param command Command ID, as defined by BOOTLOADER_CMD enum.
 * @param error_id Error code in response to previous command or transfer as defined by BOOTLOADER_ERROR enum.
 * @param param_address Command parameter 1 or memory address depending on command
 * @param param_length  Command parameter 2 or transfer length depending on command
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_bootloader_cmd_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t target_system,uint8_t target_component,uint32_t session_message_counter,uint8_t command,uint8_t error_id,uint32_t param_address,uint32_t param_length)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_BOOTLOADER_CMD_LEN];
	_mav_put_uint32_t(buf, 0, session_message_counter);
	_mav_put_uint32_t(buf, 4, param_address);
	_mav_put_uint32_t(buf, 8, param_length);
	_mav_put_uint8_t(buf, 12, target_system);
	_mav_put_uint8_t(buf, 13, target_component);
	_mav_put_uint8_t(buf, 14, command);
	_mav_put_uint8_t(buf, 15, error_id);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_BOOTLOADER_CMD_LEN);
#else
	mavlink_bootloader_cmd_t packet;
	packet.session_message_counter = session_message_counter;
	packet.param_address = param_address;
	packet.param_length = param_length;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.command = command;
	packet.error_id = error_id;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_BOOTLOADER_CMD_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_BOOTLOADER_CMD;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_BOOTLOADER_CMD_LEN, MAVLINK_MSG_ID_BOOTLOADER_CMD_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_BOOTLOADER_CMD_LEN);
#endif
}

/**
 * @brief Encode a bootloader_cmd struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param bootloader_cmd C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_bootloader_cmd_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_bootloader_cmd_t* bootloader_cmd)
{
	return mavlink_msg_bootloader_cmd_pack(system_id, component_id, msg, bootloader_cmd->target_system, bootloader_cmd->target_component, bootloader_cmd->session_message_counter, bootloader_cmd->command, bootloader_cmd->error_id, bootloader_cmd->param_address, bootloader_cmd->param_length);
}

/**
 * @brief Encode a bootloader_cmd struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param bootloader_cmd C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_bootloader_cmd_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_bootloader_cmd_t* bootloader_cmd)
{
	return mavlink_msg_bootloader_cmd_pack_chan(system_id, component_id, chan, msg, bootloader_cmd->target_system, bootloader_cmd->target_component, bootloader_cmd->session_message_counter, bootloader_cmd->command, bootloader_cmd->error_id, bootloader_cmd->param_address, bootloader_cmd->param_length);
}

/**
 * @brief Send a bootloader_cmd message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System which should execute the command
 * @param target_component Component which should execute the command, 0 for all components
 * @param session_message_counter unique session handle negotiated when entering boot mode. Incremented by master with each message. Slave returns the last received and processed message as acknowledgement.
 * @param command Command ID, as defined by BOOTLOADER_CMD enum.
 * @param error_id Error code in response to previous command or transfer as defined by BOOTLOADER_ERROR enum.
 * @param param_address Command parameter 1 or memory address depending on command
 * @param param_length  Command parameter 2 or transfer length depending on command
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_bootloader_cmd_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint32_t session_message_counter, uint8_t command, uint8_t error_id, uint32_t param_address, uint32_t param_length)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_BOOTLOADER_CMD_LEN];
	_mav_put_uint32_t(buf, 0, session_message_counter);
	_mav_put_uint32_t(buf, 4, param_address);
	_mav_put_uint32_t(buf, 8, param_length);
	_mav_put_uint8_t(buf, 12, target_system);
	_mav_put_uint8_t(buf, 13, target_component);
	_mav_put_uint8_t(buf, 14, command);
	_mav_put_uint8_t(buf, 15, error_id);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BOOTLOADER_CMD, buf, MAVLINK_MSG_ID_BOOTLOADER_CMD_LEN, MAVLINK_MSG_ID_BOOTLOADER_CMD_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BOOTLOADER_CMD, buf, MAVLINK_MSG_ID_BOOTLOADER_CMD_LEN);
#endif
#else
	mavlink_bootloader_cmd_t packet;
	packet.session_message_counter = session_message_counter;
	packet.param_address = param_address;
	packet.param_length = param_length;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.command = command;
	packet.error_id = error_id;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BOOTLOADER_CMD, (const char *)&packet, MAVLINK_MSG_ID_BOOTLOADER_CMD_LEN, MAVLINK_MSG_ID_BOOTLOADER_CMD_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BOOTLOADER_CMD, (const char *)&packet, MAVLINK_MSG_ID_BOOTLOADER_CMD_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_BOOTLOADER_CMD_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_bootloader_cmd_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t target_system, uint8_t target_component, uint32_t session_message_counter, uint8_t command, uint8_t error_id, uint32_t param_address, uint32_t param_length)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint32_t(buf, 0, session_message_counter);
	_mav_put_uint32_t(buf, 4, param_address);
	_mav_put_uint32_t(buf, 8, param_length);
	_mav_put_uint8_t(buf, 12, target_system);
	_mav_put_uint8_t(buf, 13, target_component);
	_mav_put_uint8_t(buf, 14, command);
	_mav_put_uint8_t(buf, 15, error_id);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BOOTLOADER_CMD, buf, MAVLINK_MSG_ID_BOOTLOADER_CMD_LEN, MAVLINK_MSG_ID_BOOTLOADER_CMD_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BOOTLOADER_CMD, buf, MAVLINK_MSG_ID_BOOTLOADER_CMD_LEN);
#endif
#else
	mavlink_bootloader_cmd_t *packet = (mavlink_bootloader_cmd_t *)msgbuf;
	packet->session_message_counter = session_message_counter;
	packet->param_address = param_address;
	packet->param_length = param_length;
	packet->target_system = target_system;
	packet->target_component = target_component;
	packet->command = command;
	packet->error_id = error_id;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BOOTLOADER_CMD, (const char *)packet, MAVLINK_MSG_ID_BOOTLOADER_CMD_LEN, MAVLINK_MSG_ID_BOOTLOADER_CMD_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BOOTLOADER_CMD, (const char *)packet, MAVLINK_MSG_ID_BOOTLOADER_CMD_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE BOOTLOADER_CMD UNPACKING


/**
 * @brief Get field target_system from bootloader_cmd message
 *
 * @return System which should execute the command
 */
static inline uint8_t mavlink_msg_bootloader_cmd_get_target_system(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  12);
}

/**
 * @brief Get field target_component from bootloader_cmd message
 *
 * @return Component which should execute the command, 0 for all components
 */
static inline uint8_t mavlink_msg_bootloader_cmd_get_target_component(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  13);
}

/**
 * @brief Get field session_message_counter from bootloader_cmd message
 *
 * @return unique session handle negotiated when entering boot mode. Incremented by master with each message. Slave returns the last received and processed message as acknowledgement.
 */
static inline uint32_t mavlink_msg_bootloader_cmd_get_session_message_counter(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field command from bootloader_cmd message
 *
 * @return Command ID, as defined by BOOTLOADER_CMD enum.
 */
static inline uint8_t mavlink_msg_bootloader_cmd_get_command(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  14);
}

/**
 * @brief Get field error_id from bootloader_cmd message
 *
 * @return Error code in response to previous command or transfer as defined by BOOTLOADER_ERROR enum.
 */
static inline uint8_t mavlink_msg_bootloader_cmd_get_error_id(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  15);
}

/**
 * @brief Get field param_address from bootloader_cmd message
 *
 * @return Command parameter 1 or memory address depending on command
 */
static inline uint32_t mavlink_msg_bootloader_cmd_get_param_address(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  4);
}

/**
 * @brief Get field param_length from bootloader_cmd message
 *
 * @return  Command parameter 2 or transfer length depending on command
 */
static inline uint32_t mavlink_msg_bootloader_cmd_get_param_length(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Decode a bootloader_cmd message into a struct
 *
 * @param msg The message to decode
 * @param bootloader_cmd C-struct to decode the message contents into
 */
static inline void mavlink_msg_bootloader_cmd_decode(const mavlink_message_t* msg, mavlink_bootloader_cmd_t* bootloader_cmd)
{
#if MAVLINK_NEED_BYTE_SWAP
	bootloader_cmd->session_message_counter = mavlink_msg_bootloader_cmd_get_session_message_counter(msg);
	bootloader_cmd->param_address = mavlink_msg_bootloader_cmd_get_param_address(msg);
	bootloader_cmd->param_length = mavlink_msg_bootloader_cmd_get_param_length(msg);
	bootloader_cmd->target_system = mavlink_msg_bootloader_cmd_get_target_system(msg);
	bootloader_cmd->target_component = mavlink_msg_bootloader_cmd_get_target_component(msg);
	bootloader_cmd->command = mavlink_msg_bootloader_cmd_get_command(msg);
	bootloader_cmd->error_id = mavlink_msg_bootloader_cmd_get_error_id(msg);
#else
	memcpy(bootloader_cmd, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_BOOTLOADER_CMD_LEN);
#endif
}
