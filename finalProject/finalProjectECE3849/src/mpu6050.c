#include "mpu6050.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h"
#include "pico/stdlib.h"
#include "libs/rpi-pico-mpu6050-master/include/haw/MPU6050.h"

mpu6050_t mpu6050Init(){
    i2c_init(I2C_PORT, 400000); //400kHz I2C connection

    gpio_init(pinSDA);
    gpio_init(pinSCL);
    gpio_set_function(pinSDA, GPIO_FUNC_I2C);
    gpio_set_function(pinSCL, GPIO_FUNC_I2C);
    gpio_pull_up(pinSDA);
    gpio_pull_up(pinSCL);

    gpio_init(pinINT);
    gpio_set_dir(pinINT, GPIO_IN);
    gpio_pull_down(pinINT);

    mpu6050_t mpu6050 = mpu6050_init(I2C_PORT, mpuAddress);

    if (mpu6050_begin(&mpu6050))
    {
        // Set scale of gyroscope
        mpu6050_set_scale(&mpu6050, MPU6050_SCALE_2000DPS);
        // Set range of accelerometer
        mpu6050_set_range(&mpu6050, MPU6050_RANGE_16G);

        // Enable temperature, gyroscope and accelerometer readings
        mpu6050_set_temperature_measuring(&mpu6050, true);
        mpu6050_set_gyroscope_measuring(&mpu6050, true);
        mpu6050_set_accelerometer_measuring(&mpu6050, true); 
        
        mpu6050_set_int_data_ready(&mpu6050, true);
    }
    else
    {
        for(int i = 0; i < 25; i++)
        {
            printf("Error, Check MPU");
            sleep_ms(500);
        }
    }

    gpio_set_irq_enabled_with_callback(pinINT, GPIO_IRQ_EDGE_RISE, true, &mpu6050INTCallback);

    return mpu6050;
}

void getMPUData(mpu6050_t mpu6050){
    taskENTER_CRITICAL();
    mpu6050_event(&mpu6050);
    taskEXIT_CRITICAL();
}

void processMPUData(mpu6050_t mpu6050){
    mpu6050_vectorf_t *accel = mpu6050_get_accelerometer(&mpu6050);
    mpu6050_vectorf_t *gyro = mpu6050_get_gyroscope(&mpu6050);

    float tempC = mpu6050_get_temperature_c(&mpu6050);

    printf("x: %f, y: %f, z: %f, temp: %f", accel->x, accel->y, accel->z, tempC);
}