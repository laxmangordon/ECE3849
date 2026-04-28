#include "lightSensor.h"
#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/adc.h"

static int ADCAverage[ADCAverageNumber];

void ledInit(){
    adc_init();
    adc_gpio_init(pinLED);
    adc_select_input(0);

    for (int i = 0; i < ADCAverageNumber; i++){
        ADCAverage[i] = 0;
    }
}

int ledADCMeasure(){
    int retVal = (int)adc_read();
    return retVal;
}

int ledADCMeasureAVG(){
    static int idNum = 0;
    static int retVal;

    ADCAverage[idNum] = ledADCMeasure();

    idNum++;

    if (idNum >= ADCAverageNumber){
        idNum = 0;
    }

    for (int i = 0; i < ADCAverageNumber; i++){
        retVal += ADCAverage[i];
    }

    retVal /= ADCAverageNumber;

    return retVal;
}