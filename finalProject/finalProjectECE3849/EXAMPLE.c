/*#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define I2C_PORT i2c0
#define SDA_PIN 4
#define SCL_PIN 5
#define SLAVE_ADDR 0x3C  // Example: SSD1306 OLED

int main() {
    stdio_init_all();

    // Initialize I2C at 100 kHz
    i2c_init(I2C_PORT, 100 * 1000);

    // Configure GPIO pins for I2C
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    // Wait a bit before starting
    sleep_ms(500);

    // --- Start condition ---
    // Send slave address with write bit (0)
    // This is low-level: you must write address << 1
    uint8_t address_byte = (SLAVE_ADDR << 1) | 0;
    while (i2c_get_write_available(I2C_PORT) == 0) tight_loop_contents();
    i2c_write_byte_raw(I2C_PORT, address_byte);

    // Example: send a command byte (0x00)
    while (i2c_get_write_available(I2C_PORT) == 0) tight_loop_contents();
    i2c_write_byte_raw(I2C_PORT, 0x00);

    // Example: send data byte (0xAF)
    while (i2c_get_write_available(I2C_PORT) == 0) tight_loop_contents();
    i2c_write_byte_raw(I2C_PORT, 0xAF);

    // --- Stop condition ---
    // In raw mode, you must manually trigger STOP by ending the transfer
    // The Pico SDK does this automatically in higher-level APIs,
    // but here you would typically set the STOP bit in the hardware registers.
    // For simplicity, we'll just finish here.

    while (true) {
        tight_loop_contents();
    }
}
*/