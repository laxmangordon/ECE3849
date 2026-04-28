#include "main.h"

#ifndef BUZZER_H_
#define BUZZER_H_

//used for setting up the buzzer
#define BUZZER_PWM_BASE    PWM0_BASE
#define BUZZER_GEN         PWM_GEN_0
#define BUZZER_OUTNUM      PWM_OUT_1
#define BUZZER_OUTBIT      PWM_OUT_1_BIT

extern QueueHandle_t xBuzzerSamples;

extern void buzzerTask (void *pvParameters);
extern void setupBuzzer();

static void BuzzerBeepOn(uint32_t freq_hz);
static void BuzzerBeepOff();

uint32_t gSysClk;

#endif /* BUZZER_H_ */
