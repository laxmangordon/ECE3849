#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#define pinLED 26

#define ADCAverageNumber 100 //std. of 0.1

void ledInit();

int ledADCMeasure();
int ledADCMeasureAVG();

static int ADCAverage[ADCAverageNumber];

#endif