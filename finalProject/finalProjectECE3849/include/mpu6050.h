#ifndef MPU6050CUS_H
#define MPU6050CUS_H

#include "libs/rpi-pico-mpu6050-master/include/haw/MPU6050.h"

#define I2C_PORT i2c1
#define pinSDA 10
#define pinSCL 11
#define pinINT 12
#define mpuAddress 0x68

extern void mpu6050INTCallback(uint gpio, uint32_t events);

mpu6050_t mpu6050Init();

void getMPUData(mpu6050_t mpu6050);
void processMPUData(mpu6050_t mpu6050);

#endif

