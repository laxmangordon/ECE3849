#include "OPT3001.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/pin_map.h"

// =========================================================
//  I2C0 on PB2 (SCL) / PB3 (SDA)
// =========================================================
static void I2C0_Init(void)
{
    // Enable I2C0 and GPIO Port B
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_I2C0));

    // Configure PB2/PB3 for I2C0
    GPIOPinConfigure(GPIO_PB2_I2C0SCL);
    GPIOPinConfigure(GPIO_PB3_I2C0SDA);
    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
    GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);

    // Initialize I2C0 Master at 400kHz
    I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), true);
    I2CMasterEnable(I2C0_BASE);
}

// =========================================================
//  Low-level helper: write 16-bit value to a register
// =========================================================
static void I2C0_Write16(uint8_t slaveAddr, uint8_t reg, uint16_t data)
{
    I2CMasterSlaveAddrSet(I2C0_BASE, slaveAddr, false);
    I2CMasterDataPut(I2C0_BASE, reg);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    while(I2CMasterBusy(I2C0_BASE));

    I2CMasterDataPut(I2C0_BASE, (data >> 8) & 0xFF);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
    while(I2CMasterBusy(I2C0_BASE));

    I2CMasterDataPut(I2C0_BASE, data & 0xFF);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
    while(I2CMasterBusy(I2C0_BASE));
}

// =========================================================
//  Low-level helper: read 16-bit value from a register
// =========================================================
static uint16_t I2C0_Read16(uint8_t slaveAddr, uint8_t reg)
{
    uint8_t msb, lsb;

    // Send register address
    I2CMasterSlaveAddrSet(I2C0_BASE, slaveAddr, false);
    I2CMasterDataPut(I2C0_BASE, reg);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);
    while(I2CMasterBusy(I2C0_BASE));

    // Restart as read
    I2CMasterSlaveAddrSet(I2C0_BASE, slaveAddr, true);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);
    while(I2CMasterBusy(I2C0_BASE));
    msb = I2CMasterDataGet(I2C0_BASE);

    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
    while(I2CMasterBusy(I2C0_BASE));
    lsb = I2CMasterDataGet(I2C0_BASE);

    return ((uint16_t)msb << 8) | lsb;
}

// =========================================================
//  OPT3001 API implementation
// =========================================================
void OPT3001_Init(void)
{
    I2C0_Init();
    OPT3001_WriteRegister(OPT3001_REG_CONFIG, OPT3001_DEFAULT_CONFIG);
}

void OPT3001_WriteRegister(uint8_t reg, uint16_t value)
{
    I2C0_Write16(OPT3001_I2C_ADDRESS, reg, value);
}

uint16_t OPT3001_ReadRegister(uint8_t reg)
{
    return I2C0_Read16(OPT3001_I2C_ADDRESS, reg);
}

uint16_t OPT3001_ReadManufacturerID(void)
{
    return OPT3001_ReadRegister(OPT3001_REG_MANUFACTURER_ID);
}

uint16_t OPT3001_ReadDeviceID(void)
{
    return OPT3001_ReadRegister(OPT3001_REG_DEVICE_ID);
}

float OPT3001_ReadLux(void)
{
    uint16_t raw = OPT3001_ReadRegister(OPT3001_REG_RESULT);
    uint16_t exponent = (raw >> 12) & 0xF;
    uint16_t mantissa = raw & 0x0FFF;
    return 0.01f * (1 << exponent) * mantissa;
}
