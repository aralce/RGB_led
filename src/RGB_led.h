#ifdef IS_RUNNING_TESTS
    #include <mocks/HAL_PWM_api.h>
#else
    #include "HAL_for_platformio/HAL_API/HAL_PWM/HAL_PWM_api.h"
#endif

class RGB_led {
public:
    RGB_led(const int rgb[3]) {
        RGB_led(rgb[0], rgb[1], rgb[2]);
    }
    RGB_led(int red_pin, int green_pin, int blue_pin) {
        pwm_red = new PWM_hal(red_pin);
        pwm_green = new PWM_hal(green_pin);
        pwm_blue = new PWM_hal(blue_pin);
    }

    ~RGB_led() {
        delete pwm_red;
        delete pwm_green;
        delete pwm_blue;
    }

    void set_ON_mode() {
        _mode = mode::ON;
    }

    void set_OFF_mode() {
        _mode = mode::OFF;
    }

    void run_pending_tasks() {
        pwm_red->set_duty_cycle(100);
        pwm_green->set_duty_cycle(100);
        pwm_blue->set_duty_cycle(100);
    }

    void set_color(const int rgb[3]) {
        set_color(rgb[0], rgb[1], rgb[2]);
    }

    void set_color(int red, int green, int blue) {
        float pwm_red_value = (100*(float)red)/255;
        pwm_red->set_duty_cycle(pwm_red_value);
        
        float pwm_green_value = (100*(float)red)/255;
        pwm_green->set_duty_cycle(pwm_green_value);
        
        float pwm_blue_value = (100*(float)red)/255;
        pwm_blue->set_duty_cycle(pwm_blue_value);
    }



private:
    PWM_hal* pwm_red = nullptr;
    PWM_hal* pwm_green = nullptr;
    PWM_hal* pwm_blue = nullptr;

    enum class mode {ON, OFF};
    mode _mode = mode::OFF;
};