#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

extern "C" {
#include "driverlib/fpu.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "Crystalfontz128x128_ST7735.h"
#include "semphr.h"
#include "timers.h"
}

#include "button.h"
#include "pins.h"
#include "joystick.h"
#include "OPT3001.h"

#include "stopwatch.h"
#include "buzzer.h"
#include "joystickTwo.h"
#include "screenMic.h"

enum ScreenID : uint8_t {
    SCREEN_STOPWATCH = 0,
    SCREEN_MIC,
    SCREEN_COUNT
};

#endif /* MAIN_H_ */
