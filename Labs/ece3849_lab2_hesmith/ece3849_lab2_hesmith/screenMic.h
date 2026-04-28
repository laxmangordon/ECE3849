#include "main.h"

#ifndef SCREENMIC_H_
#define SCREENMIC_H_

extern void MicTask(void *pvParams);

static void microphoneSetup(void);
static uint16_t Mic_Read(void);
static void MicSampleCb(TimerHandle_t xTimer);
extern void ScreenMic_Init(void);

#define WINDOW_SIZE 128

#define MIC_ADC_BASE      ADC0_BASE
#define MIC_ADC_SEQ       3
#define MIC_ADC_CHANNEL   ADC_CTL_CH8

extern TimerHandle_t xMicTimer;
extern SemaphoreHandle_t xMicReadySem;
static uint16_t gMicSamples[WINDOW_SIZE];
extern volatile uint16_t gMicIndex;
extern volatile float gMicLevel;
extern volatile float gMicDb;


#endif /* SCREENMIC_H_ */
