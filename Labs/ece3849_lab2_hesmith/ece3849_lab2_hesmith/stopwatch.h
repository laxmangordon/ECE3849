#include "main.h"

#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#define BTN_PORT_BASE GPIO_PORTL_BASE
#define BTN_PIN_MASK  (GPIO_PIN_1 | GPIO_PIN_2)
#define BTN_INT_NUM   INT_GPIOL

void ButtonISR(void);

void timeTask(void *pvParameters);
void buttonTask(void *pvParameters);

void setupButtons(void);

//time variables
extern volatile bool gRunning;
extern volatile uint16_t g_ms;
extern volatile uint8_t  g_sec;
extern volatile uint8_t  g_min;
extern volatile uint8_t  g_hr;

//FreeRTOS task and Queue variables
extern TickType_t timeKeepLastWake;

static SemaphoreHandle_t xBtnSem = NULL;

//physical button definitions
static Button btnPlayPause(S1);     // S1 -> Play/Pause
static Button btnRestart(S2);       // S2 -> Restart

struct MyButton {
    int x, y, w, h;
    const char* label;
    bool pressed;
};

//software button definitions
extern MyButton btnStart;
extern MyButton btnReset;

#endif /* STOPWATCH_H_ */
