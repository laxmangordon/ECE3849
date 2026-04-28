#include "lightSensor.h"
#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/adc.h"

void ledInit(){
    adc_init();
    adc_gpio_init(pinLED);
    adc_select_input(0);
}

int ledADCMeasure(){
    int retVal = (int)adc_read();
    return retVal;
}