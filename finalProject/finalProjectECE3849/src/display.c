#include "display.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

void displayInit(){

    gpio_set_function(pinBacklight, GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(pinBacklight);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.0f);

    pwm_init(slice_num, &config, true);

    pwm_set_wrap(slice_num, 4095);


    /*gpio_init(pinRS);
    gpio_init(pinE);
    gpio_init(pinD4);
    gpio_init(pinD5);
    gpio_init(pinD6);
    gpio_init(pinD7);
    
    gpio_set_dir(pinRS, 1);
    gpio_set_dir(pinE, 1);
    gpio_set_dir(pinD4, 1);
    gpio_set_dir(pinD5, 1);
    gpio_set_dir(pinD6, 1);
    gpio_set_dir(pinD7, 1);
    
    gpio_put(pinRS, 0);
    gpio_put(pinE, 0);
    gpio_put(pinD4, 0);
    gpio_put(pinD5, 0);
    gpio_put(pinD6, 0);
    gpio_put(pinD7, 0);
//=============================
    
    sleep_ms(40);
//Set 4 bit mode
    gpio_put(pinRS, 0);
    gpio_put(pinD4, 0);
    gpio_put(pinD5, 1);
    gpio_put(pinD6, 0);
    gpio_put(pinD7, 0);

    sleep_ms(1);
    gpio_put(pinE, 1);
    sleep_ms(1);
    gpio_put(pinE, 0);
    sleep_ms(2);
//Clear Display
    gpio_put(pinRS, 0);
    gpio_put(pinD4, 0);
    gpio_put(pinD5, 0);
    gpio_put(pinD6, 0);
    gpio_put(pinD7, 0);

    sleep_ms(1);
    gpio_put(pinE, 1);
    sleep_ms(1);
    gpio_put(pinE, 0);
    sleep_ms(2);

    gpio_put(pinRS, 0);
    gpio_put(pinD4, 1);
    gpio_put(pinD5, 0);
    gpio_put(pinD6, 0);
    gpio_put(pinD7, 0);

    sleep_ms(1);
    gpio_put(pinE, 1);
    sleep_ms(1);
    gpio_put(pinE, 0);
    sleep_ms(2);
//Return home
    gpio_put(pinRS, 0);
    gpio_put(pinD4, 0);
    gpio_put(pinD5, 0);
    gpio_put(pinD6, 0);
    gpio_put(pinD7, 0);

    sleep_ms(1);
    gpio_put(pinE, 1);
    sleep_ms(1);
    gpio_put(pinE, 0);
    sleep_ms(2);

    gpio_put(pinRS, 0);
    gpio_put(pinD4, 0);
    gpio_put(pinD5, 1);
    gpio_put(pinD6, 0);
    gpio_put(pinD7, 0);

    sleep_ms(1);
    gpio_put(pinE, 1);
    sleep_ms(1);
    gpio_put(pinE, 0);
    sleep_ms(2);
//Disp: On, Cursur: Off
    gpio_put(pinRS, 0);
    gpio_put(pinD4, 0);
    gpio_put(pinD5, 0);
    gpio_put(pinD6, 0);
    gpio_put(pinD7, 0);

    sleep_ms(1);
    gpio_put(pinE, 1);
    sleep_ms(1);
    gpio_put(pinE, 0);
    sleep_ms(2);

    gpio_put(pinRS, 0);
    gpio_put(pinD4, 0);
    gpio_put(pinD5, 0);
    gpio_put(pinD6, 1);
    gpio_put(pinD7, 1);

    sleep_ms(1);
    gpio_put(pinE, 1);
    sleep_ms(1);
    gpio_put(pinE, 0);
    sleep_ms(2);
//TEST: H
    gpio_put(pinRS, 1);
    gpio_put(pinD4, 0);
    gpio_put(pinD5, 0);
    gpio_put(pinD6, 1);
    gpio_put(pinD7, 0);

    sleep_ms(1);
    gpio_put(pinE, 1);
    sleep_ms(1);
    gpio_put(pinE, 0);
    sleep_ms(2);

    gpio_put(pinRS, 1);
    gpio_put(pinD4, 0);
    gpio_put(pinD5, 0);
    gpio_put(pinD6, 0);
    gpio_put(pinD7, 1);

    sleep_ms(1);
    gpio_put(pinE, 1);
    sleep_ms(1);
    gpio_put(pinE, 0);
    sleep_ms(2);*/
}
