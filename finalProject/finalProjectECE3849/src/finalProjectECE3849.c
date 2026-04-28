#include "finalProjectECE3849.h"

static void vDisplayTask(void *pvParameters);
static void vDisplayBrightnessTask(void *pvParameters);
static void vlightSensorTask(void *pvParameters);
static void vMPU6050Task(void *pvParameters);

int displayBacklightMode = 0;

int main()
{
    stdio_init_all();

    ledInit();
    displayInit(); //TESTING

    xTaskCreate(vDisplayTask,  "Display",  512, NULL, 1, NULL); //not implemented yet
    xTaskCreate(vDisplayBrightnessTask,  "Brightness",  512, NULL, 1, NULL);
    xTaskCreate(vlightSensorTask,  "LightSensor",  512, NULL, 2, NULL);
    xTaskCreate(vMPU6050Task,  "MPU",  512, NULL, 2, NULL);

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
        if (adcVal < 760){
            displayBacklightMode = 0;
        }
        else if (adcVal >= 760){
            displayBacklightMode = 1;
        }
        printf("%d \n", adcVal);
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

static void vMPU6050Task(void *pvParameters){

}