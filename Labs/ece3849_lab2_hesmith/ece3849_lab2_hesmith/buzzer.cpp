#include "buzzer.h"

QueueHandle_t xBuzzerSamples;

void setupBuzzer(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0));
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));

    GPIOPinConfigure(GPIO_PF1_M0PWM1);
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1);
    PWMClockSet(PWM0_BASE, PWM_SYSCLK_DIV_64);
}

static void BuzzerBeepOn(uint32_t freq_hz){
    if (freq_hz == 0) return;

    uint32_t pwmClock = gSysClk / 64;
    uint32_t period = pwmClock / freq_hz;

    PWMGenConfigure(BUZZER_PWM_BASE, BUZZER_GEN, PWM_GEN_MODE_DOWN);
    PWMGenPeriodSet(BUZZER_PWM_BASE, BUZZER_GEN, period);
    PWMPulseWidthSet(BUZZER_PWM_BASE, BUZZER_OUTNUM, period / 2);
    PWMOutputState(BUZZER_PWM_BASE, BUZZER_OUTBIT, true);
    PWMGenEnable(BUZZER_PWM_BASE, BUZZER_GEN);
}

static void BuzzerBeepOff(){
    PWMOutputState(BUZZER_PWM_BASE, BUZZER_OUTBIT, false);
}

//buzzer task: operates only on receiving Queue data. Turns the buzzer on at the received tone for 50ms ,then off, and goes back to wait.
void buzzerTask (void *pvParameters){
    for (;;){
        uint16_t tone;

        if (xQueueReceive(xBuzzerSamples, &tone, portMAX_DELAY) == pdTRUE){ //receives Queue data and assigns it to the 'tone' variable.
            BuzzerBeepOn(tone);

            vTaskDelay(pdMS_TO_TICKS(50));

            BuzzerBeepOff();
        }
    }
}
