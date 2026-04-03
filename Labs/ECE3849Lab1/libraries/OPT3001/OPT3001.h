#ifndef _OPT3001_H_
#define _OPT3001_H_

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// ===== I2C Address (ADDR = GND) =====
#define OPT3001_I2C_ADDRESS     0x44

// ===== Register Map =====
#define OPT3001_REG_RESULT      0x00
#define OPT3001_REG_CONFIG      0x01
#define OPT3001_REG_LOWLIMIT    0x02
#define OPT3001_REG_HIGHLIMIT   0x03
#define OPT3001_REG_MANUFACTURER_ID  0x7E
#define OPT3001_REG_DEVICE_ID   0x7F

// ===== Default Configuration =====
// Automatic range, continuous conversion, 800ms integration
#define OPT3001_DEFAULT_CONFIG  0xC410

// ===== API Prototypes =====
void OPT3001_Init(void);
void OPT3001_WriteRegister(uint8_t reg, uint16_t value);
uint16_t OPT3001_ReadRegister(uint8_t reg);
uint16_t OPT3001_ReadManufacturerID(void);
uint16_t OPT3001_ReadDeviceID(void);
float OPT3001_ReadLux(void);

#ifdef __cplusplus
}
#endif

#endif /* _OPT3001_H_ */
