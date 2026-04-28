#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#define pinLED 26

#define ADCAverageNumber 16

void ledInit();

int ledADCMeasure();
int ledADCMeasureAVG();

static int ADCAverage[ADCAverageNumber];

#endif