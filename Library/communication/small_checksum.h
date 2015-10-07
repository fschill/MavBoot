/**
 * \file small_checksum.h
 *
 * \brief non-static version of CRC16 checksum for mavlink to reduce code size for bootloader
 * 
 */
 
 
#ifdef __cplusplus
extern "C" {
#endif

#ifndef _CHECKSUM_H_
#define _CHECKSUM_H_


/**
 *
 *  CALCULATE THE CHECKSUM
 *
 */

#define X25_INIT_CRC 0xffff
#define X25_VALIDATE_CRC 0xf0b8

#ifndef HAVE_CRC_ACCUMULATE
/**
 * @brief Accumulate the X.25 CRC by adding one char at a time.
 *
 * The checksum function adds the hash of one char at a time to the
 * 16 bit checksum (uint16_t).
 *
 * @param data new char to hash
 * @param crcAccum the already accumulated checksum
 **/
void crc_accumulate(uint8_t data, uint16_t *crcAccum);
#endif


/**
 * @brief Initiliaze the buffer for the X.25 CRC
 *
 * @param crcAccum the 16 bit X.25 CRC
 */
void crc_init(uint16_t* crcAccum);

/**
 * @brief Calculates the X.25 checksum on a byte buffer
 *
 * @param  pBuffer buffer containing the byte array to hash
 * @param  length  length of the byte array
 * @return the checksum over the buffer bytes
 **/
uint16_t crc_calculate(const uint8_t* pBuffer, uint16_t length);

/**
 * @brief Accumulate the X.25 CRC by adding an array of bytes
 *
 * The checksum function adds the hash of one char at a time to the
 * 16 bit checksum (uint16_t).
 *
 * @param data new bytes to hash
 * @param crcAccum the already accumulated checksum
 **/
void crc_accumulate_buffer(uint16_t *crcAccum, const char *pBuffer, uint16_t length);


#endif /* _CHECKSUM_H_ */

#ifdef __cplusplus
}
#endif
