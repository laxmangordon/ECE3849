#include "finalProjectECE3849.h"

static void vDisplayTask(void *pvParameters);
static void vDisplayBrightnessTask(void *pvParameters);
static void vlightSensorTask(void *pvParameters);
static void vMPU6050Task(void *pvParameters);

int displayBacklightMode = 0;

static TaskHandle_t xMPUTaskNotification = NULL;

void mpu6050INTCallback(uint gpio, uint32_t events){
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    vTaskNotifyGiveFromISR(xMPUTaskNotification, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

int main()
{
    stdio_init_all();

    ledInit();
    displayInit(); //TESTING
    mpu6050_t mpu6050 = mpu6050Init();

    xTaskCreate(vDisplayTask,  "Display",  512, NULL, 1, NULL); //not implemented yet
    xTaskCreate(vDisplayBrightnessTask,  "Brightness",  512, NULL, 1, NULL);
    xTaskCreate(vlightSensorTask,  "LightSensor",  512, NULL, 2, NULL);
    xTaskCreate(vMPU6050Task,  "MPU",  512, &mpu6050, 2, &xMPUTaskNotification);

    vTaskStartScheduler();

    while(1);
}

static void vDisplayTask (void *pvParameters){
    for(;;){
        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

static void vDisplayBrightnessTask(void *pvParameters){
    static int currentPWM = 4094;
    const int lowPWM = 800;
    const int highPWM = 4095;

    for(;;){
        switch (displayBacklightMode){
            case 0:
                if (currentPWM != lowPWM){
                    currentPWM--;
                    pwm_set_gpio_level(pinBacklight, currentPWM);
                    vTaskDelay(pdMS_TO_TICKS(1));
                }
                break;
            case 1:
                if (currentPWM != highPWM){
                    currentPWM++;
                    pwm_set_gpio_level(pinBacklight, currentPWM);
                    vTaskDelay(pdMS_TO_TICKS(1));
                }
                break;
        }
    }
}

static void vlightSensorTask(void *pvParameters){
    for(;;){
        int adcVal = ledADCMeasureAVG();
        if (adcVal < 800){
            displayBacklightMode = 0;
        }
        else if (adcVal >= 800){
            displayBacklightMode = 1;
        }
        printf("%d \n", adcVal);
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

static void vMPU6050Task(void *pvParameters){
    uint32_t notificationProcess;

    mpu6050_t *mpu6050 = pvParameters;

    for(;;){
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        mpu6050_event(mpu6050);

        // Pointers to float vectors with all the results
        mpu6050_vectorf_t *accel = mpu6050_get_accelerometer(mpu6050);
        mpu6050_vectorf_t *gyro = mpu6050_get_gyroscope(mpu6050);

        // Activity struct holding all interrupt flags
        mpu6050_activity_t *activities = mpu6050_read_activities(mpu6050);

        // Rough temperatures as float -- Keep in mind, this is not a temperature sensor!!!
        float tempC = mpu6050_get_temperature_c(mpu6050);
        float tempF = mpu6050_get_temperature_f(mpu6050);

        // Print all the measurements
        printf("Accelerometer: %f, %f, %f - Gyroscope: %f, %f, %f - Temperature: %f°C - Temperature: %f°F\n", accel->x, accel->y, accel->z, gyro->x, gyro->y, gyro->z, tempC, tempF);

        //vTaskDelay(pdMS_TO_TICKS(10));
    }
}