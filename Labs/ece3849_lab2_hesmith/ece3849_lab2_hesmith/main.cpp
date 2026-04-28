#include "main.h"

volatile uint8_t gCurrentScreen = SCREEN_STOPWATCH;

static void initializeDisplay(tContext &context);
static void drawStopwatchScreen(tContext &context, bool running);
static void DrawHeader(tContext &gContext);
static void drawButton(tContext &context, const MyButton &btn);

//update display task: draws the display UI and time numbers in HH:MM:SS:MS format
void displayTask (void *pvParameters){
    for (;;){
        tContext sContext;
        initializeDisplay(sContext);

        for (;;){
            drawStopwatchScreen(sContext, gRunning);

            #ifdef GrFlush
                GrFlush(&sContext);
            #endif

            vTaskDelay(pdMS_TO_TICKS(100));
        }
    }
}

int main(void){
    volatile bool gRunning = false;
    volatile uint16_t g_ms = 0;
    volatile uint8_t  g_sec = 0;
    volatile uint8_t  g_min = 0;
    volatile uint8_t  g_hr = 0;

    IntMasterDisable(); //disable ISRs.

    FPUEnable();
    FPULazyStackingEnable();

    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    gSysClk = SysCtlClockFreqSet(SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480, 120000000);

    (void)gSysClk;

    setupBuzzer();
    setupButtons();

    IntMasterEnable(); //enable ISRs.

    GPIOIntRegister(BTN_PORT_BASE, ButtonISR);
    GPIOIntTypeSet(BTN_PORT_BASE, BTN_PIN_MASK, GPIO_BOTH_EDGES);
    GPIOIntEnable(BTN_PORT_BASE, BTN_PIN_MASK);
    IntEnable(BTN_INT_NUM);
    ScreenMic_Init();

    timeKeepLastWake = xTaskGetTickCount();

    //create buzzer Queue
    xBuzzerSamples = xQueueCreate(16, sizeof(int16_t));

    if (xBuzzerSamples == NULL) while (1){}

    //Create the required system tasks
    xTaskCreate(buzzerTask, "buzzer", 512, NULL, 1, NULL);
    xTaskCreate(displayTask, "displayUpdate", 512, NULL, 1, NULL);
    xTaskCreate(MicTask, "micUpdate", 512, NULL, 2, NULL);
    xTaskCreate(JoystickTask, "joystickScan", 512, NULL, 2, NULL);
    xTaskCreate(buttonTask, "buttonScan", 512, NULL, 2, NULL);
    xTaskCreate(timeTask, "timeKeep", 512, NULL, 3, NULL);

    vTaskStartScheduler(); //start the FreeRTOS scheduler

    while (1);
}

static void initializeDisplay(tContext &context){
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
    GrContextInit(&context, &g_sCrystalfontz128x128);
    GrContextFontSet(&context, &g_sFontFixed6x8);

    tRectangle full = {0, 0, 127, 127};
    GrContextForegroundSet(&context, ClrBlack);
    GrRectFill(&context, &full);
}

static void drawStopwatchScreen(tContext &context, bool running){
    uint8_t hours = g_hr;
    uint8_t minutes = g_min;
    uint8_t seconds = g_sec;
    uint16_t milseconds = g_ms;

    tRectangle rectFull = {0, 0, 127, 127};
    GrContextForegroundSet(&context, ClrBlack);
    GrRectFill(&context, &rectFull);

    DrawHeader(context);

    switch (gCurrentScreen){
        case SCREEN_STOPWATCH:
            char timeSTR[20];

            GrContextForegroundSet(&context, ClrCyan);
            GrStringDrawCentered(&context, "STOPWATCH", -1, 64, 30, false);

            snprintf(timeSTR, sizeof(timeSTR), "%02u : %02u : %02u : %02u", hours, minutes, seconds, milseconds);

            if (running){
                GrContextForegroundSet(&context, ClrGreen);
                GrStringDrawCentered(&context, "Running", -1, 64, 45, false);

                GrContextForegroundSet(&context, ClrYellow);
                GrStringDrawCentered(&context, timeSTR, -1, 64, 60, false);
            }
            else{
                GrContextForegroundSet(&context, ClrRed);
                GrStringDrawCentered(&context, "Stopped", -1, 64, 45, false);

                GrContextForegroundSet(&context, ClrOlive);
                GrStringDrawCentered(&context, timeSTR, -1, 64, 60, false);
            }
            drawButton(context, btnStart);
            drawButton(context, btnReset);

            break;
        case SCREEN_MIC:
            char dBSTR[10];
            static int yGain = 50;
            static int maxGreen = 120 - (yGain * 0.4);
            static int maxYellow = maxGreen - (yGain * 0.75);

            snprintf(dBSTR, sizeof(dBSTR), "%.2f dB", gMicDb);

            GrStringDrawCentered(&context, dBSTR, -1, 30, 120, false);

            if (gMicLevel <= 0.4){
                tRectangle micLevelGreen = {100, 120, 150, (short)(120 - (yGain * gMicLevel))};
                GrContextForegroundSet(&context, ClrGreen);
                GrRectFill(&context, &micLevelGreen);
            }
            if ((gMicLevel > 0.4) && (gMicLevel <= 0.75)){
                tRectangle micLevelGreen = {100, 120, 150, (short)(maxGreen)};
                GrContextForegroundSet(&context, ClrGreen);
                GrRectFill(&context, &micLevelGreen);

                tRectangle micLevelYellow = {100, maxGreen, 150, (short)(maxGreen - (yGain * gMicLevel))};
                GrContextForegroundSet(&context, ClrYellow);
                GrRectFill(&context, &micLevelYellow);
            }
            if ((gMicLevel > 0.75) && (gMicLevel <= 1.0)){
                tRectangle micLevelGreen = {100, 120, 150,(short)(maxGreen)};
                GrContextForegroundSet(&context, ClrGreen);
                GrRectFill(&context, &micLevelGreen);

                tRectangle micLevelYellow = {100, maxGreen, 150, (short)(maxYellow)};
                GrContextForegroundSet(&context, ClrYellow);
                GrRectFill(&context, &micLevelYellow);

                tRectangle micLevelRed = {100, maxYellow, 150, (short)(maxYellow - (yGain * gMicLevel))};
                GrContextForegroundSet(&context, ClrRed);
                GrRectFill(&context, &micLevelRed);
            }

            break;
    }
}

static void DrawHeader(tContext &gContext) {
    tRectangle header = {0, 0, 127, 20};
    GrContextForegroundSet(&gContext, ClrDarkBlue);
    GrRectFill(&gContext, &header);

    GrContextForegroundSet(&gContext, ClrYellow);
    GrStringDraw(&gContext, "<", -1, 4, 6, false);
    GrStringDraw(&gContext, ">", -1, 118, 6, false);

    GrContextForegroundSet(&gContext, ClrWhite);
    GrStringDrawCentered(&gContext, "TESTING", -1, 64, 7, false);
}

static void drawButton(tContext &context, const MyButton &btn){
    uint16_t bgColor = btn.pressed ? ClrBlack : ClrGray;
    uint16_t textColor = btn.pressed ? ClrWhite : ClrBlack;

    tRectangle rect = {btn.x, btn.y, btn.x + btn.w - 1, btn.y + btn.h - 1};
    GrContextForegroundSet(&context, bgColor);
    GrRectFill(&context, &rect);

    GrContextForegroundSet(&context, ClrBlack);
    GrRectDraw(&context, &rect);

    GrContextForegroundSet(&context, textColor);
    GrStringDrawCentered(&context, btn.label, -1, btn.x + btn.w / 2, btn.y + btn.h / 2, false);
}
