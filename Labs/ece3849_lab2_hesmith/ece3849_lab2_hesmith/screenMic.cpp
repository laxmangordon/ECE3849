#include "screenMic.h"

TimerHandle_t xMicTimer = NULL;
SemaphoreHandle_t xMicReadySem = NULL;

volatile uint16_t gMicIndex = 0;

volatile float gMicLevel;
volatile float gMicDb;

void MicTask(void *pvParams)
{
    for (;;) {
        //static float micSamplesCOPY[WINDOW_SIZE];
        float samplesSum = 0.0;
        static float meanSquare;
        static float RMS;
        static float ARef = 0.25;
        static float dB;
        static float level;

        xSemaphoreTake(xMicReadySem, portMAX_DELAY);

        for (int i = 0; i < WINDOW_SIZE; i++){
            float temp = (((float)gMicSamples[i] / 4095.0) - 0.5);
            //micSamplesCOPY[i] = temp * temp;
            samplesSum += temp * temp;
        }

        meanSquare = (1.0 / (float)WINDOW_SIZE) * samplesSum;

        RMS = sqrt(meanSquare);

        dB = 20 * log10(RMS / ARef);

        if (dB > 0){
            dB = 0;
        }
        if (dB < -60){
            dB = -60;
        }

        level = (dB + 60.0) / 60.0;

        gMicLevel = level;
        gMicDb = dB;
    }
}

static void microphoneSetup(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_5);

    ADCSequenceConfigure(MIC_ADC_BASE, MIC_ADC_SEQ, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(MIC_ADC_BASE, MIC_ADC_SEQ, 0, MIC_ADC_CHANNEL | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceEnable(MIC_ADC_BASE, MIC_ADC_SEQ);
    ADCIntClear(MIC_ADC_BASE, MIC_ADC_SEQ);
}

static uint16_t Mic_Read(void){
    uint32_t value;

    ADCProcessorTrigger(MIC_ADC_BASE, MIC_ADC_SEQ);
    while (!ADCIntStatus(MIC_ADC_BASE, MIC_ADC_SEQ, false)) {}
    ADCIntClear(MIC_ADC_BASE, MIC_ADC_SEQ);
    ADCSequenceDataGet(MIC_ADC_BASE, MIC_ADC_SEQ, &value);

    return (uint16_t)value;
}

static void MicSampleCb(TimerHandle_t xTimer)
{
    (void)xTimer;

    gMicSamples[gMicIndex++] = Mic_Read();

    if (gMicIndex >= WINDOW_SIZE) {
        gMicIndex = 0;
        xSemaphoreGive(xMicReadySem);
    }
}

void ScreenMic_Init(void)
{
    microphoneSetup();

    xMicReadySem = xSemaphoreCreateBinary();
    xMicTimer = xTimerCreate("mic", pdMS_TO_TICKS(1), pdTRUE, NULL, MicSampleCb);

    xTimerStart(xMicTimer, 0);
}
