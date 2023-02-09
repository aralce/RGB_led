#include "RGB_led.h"

RGB_led::RGB_led(const uint8_t rgb[3], common_mode mode) {
    RGB_led(rgb[0], rgb[1], rgb[2], mode);
}

RGB_led::RGB_led(uint8_t red_pin, uint8_t green_pin, uint8_t blue_pin, common_mode mode) {
    pwm_red = new PWM_hal(red_pin);
    pwm_green = new PWM_hal(green_pin);
    pwm_blue = new PWM_hal(blue_pin);
    _common_mode = mode;
}

RGB_led::~RGB_led() {
    delete pwm_red;
    delete pwm_green;
    delete pwm_blue;
}

void RGB_led::run_pending_tasks() {
    switch(_mode) {
        case mode::ON:
            turn_on_LEDs();
            break;
        case mode::OFF:
            turn_off_LEDs();
            break;
        case mode::BLINK:
            toggle_LEDs_when_is_time();
            break;
    }
}

void RGB_led::turn_on_LEDs() {
    float pwm_red_value = _pwm_red_value;
    float pwm_green_value = _pwm_green_value;
    float pwm_blue_value = _pwm_blue_value;
    if (_common_mode == common_mode::COMMON_ANODE) {
        pwm_red_value = 100 - _pwm_red_value;
        pwm_green_value = 100 - _pwm_green_value;
        pwm_blue_value = 100 - _pwm_blue_value;
    }
    
    pwm_red->set_duty_cycle(pwm_red_value);
    pwm_green->set_duty_cycle(pwm_green_value);
    pwm_blue->set_duty_cycle(pwm_blue_value);

    is_LED_ON = true;
}

void RGB_led::turn_off_LEDs() {
    float off_value = 0;
    if (_common_mode == common_mode::COMMON_ANODE)
        off_value = 100;

    pwm_red->set_duty_cycle(off_value);
    pwm_green->set_duty_cycle(off_value);
    pwm_blue->set_duty_cycle(off_value);

    is_LED_ON = false;
}

void RGB_led::toggle_LEDs_when_is_time() {
    device = HAL_system_singleton::get_HAL_system_instance();
    if (device->millisecs_since_init() - last_ms_since_toggle_LED >= blink_interval_in_ms/2) {
        last_ms_since_toggle_LED = device->millisecs_since_init();
        if (is_LED_ON)
            turn_off_LEDs();
        else
            turn_on_LEDs();
    }
}

void RGB_led::set_ON_mode() {
    _mode = mode::ON;
}

void RGB_led::set_OFF_mode() {
    _mode = mode::OFF;
}

void RGB_led::set_BLINK_mode(uint32_t interval_in_milliseconds) {
    _mode = mode::BLINK;
    blink_interval_in_ms = interval_in_milliseconds;
}

void RGB_led::set_color(const uint8_t rgb[3]) {
    set_color(rgb[0], rgb[1], rgb[2]);
}

void RGB_led::set_color(uint8_t red, uint8_t green, uint8_t blue) {
    rgb[0] = red;
    rgb[1] = green;
    rgb[2] = blue;

    _pwm_red_value = (100*(float)red)/255;
    _pwm_green_value = (100*(float)green)/255;
    _pwm_blue_value = (100*(float)blue)/255;
}

uint8_t RGB_led::get_red_value() {
    return rgb[0];
}

uint8_t RGB_led::get_green_value() {
    return rgb[1];
}

uint8_t RGB_led::get_blue_value() {
    return rgb[2];
}