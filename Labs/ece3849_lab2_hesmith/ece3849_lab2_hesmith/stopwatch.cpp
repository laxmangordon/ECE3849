#include "stopwatch.h"

TickType_t timeKeepLastWake;

volatile bool gRunning;
volatile uint16_t g_ms;
volatile uint8_t  g_sec;
volatile uint8_t  g_min;
volatile uint8_t  g_hr;

MyButton btnStart = {39, 70, 50, 28, "PLAY", false};
MyButton btnReset = {39, 100, 50, 28, "Reset", false};

void ButtonISR(void) {
    GPIOIntClear(BTN_PORT_BASE, BTN_PIN_MASK);

    BaseType_t woken = pdFALSE;
    xSemaphoreGiveFromISR(xBtnSem, &woken);
    portYIELD_FROM_ISR(woken);
}

//button scanning task: scans the user buttons for presses. If pressed, sends Queue data to the buzzer, and either play/pause the timer, or resets the timer.
void buttonTask(void *pvParameters){
    for (;;){
        xSemaphoreTake(xBtnSem, portMAX_DELAY);

        vTaskDelay(pdMS_TO_TICKS(15));

        static uint16_t playPauseBTNSound = 1000;
        static uint16_t ResetBTNSound = 500;

        btnPlayPause.tick();
        btnRestart.tick();

        if (btnPlayPause.wasPressed()){
            xQueueSend(xBuzzerSamples, &playPauseBTNSound, pdMS_TO_TICKS(5)); //play buzzer sound

            btnStart.pressed = true;
            gRunning = !gRunning; //pause/play timer
            btnStart.label = gRunning ? "PAUSE" : "PLAY";
        }
        if (btnPlayPause.wasReleased()){
            btnStart.pressed = false;
        }
        if (btnRestart.wasPressed()){
            xQueueSend(xBuzzerSamples, &ResetBTNSound, pdMS_TO_TICKS(5)); //play buzzer sound

            btnReset.pressed = true;

            //reset timing variables to 0
            g_ms  = 0;
            g_sec = 0;
            g_min = 0;
            g_hr  = 0;
        }
        if (btnRestart.wasReleased()){
            btnReset.pressed = false;
        }
    }
}

//timing task: updates the timing variables and runs every 10ms
void timeTask(void *pvParameters){
    for(;;){
        if (gRunning){
            g_ms += 10;

            if (g_ms >= 1000){
                g_ms = 0;
                g_sec++;
                if (g_sec >= 60){
                    g_sec = 0;
                    g_min++;
                    if (g_min >= 60){
                        g_min = 0;
                        g_hr++;
                        if (g_hr > 99){
                            g_hr = 99;
                        }
                    }
                }
            }
        }
        vTaskDelayUntil(&timeKeepLastWake, pdMS_TO_TICKS(10));
    }
}

void setupButtons(void){
    xBtnSem = xSemaphoreCreateBinary();

    btnPlayPause.begin();
    btnPlayPause.setTickIntervalMs(20);
    btnPlayPause.setDebounceMs(30);

    btnRestart.begin();
    btnRestart.setTickIntervalMs(20);
    btnRestart.setDebounceMs(30);
}
