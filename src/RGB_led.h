#pragma once

#ifdef IS_RUNNING_TESTS
    #include <mocks/HAL_PWM_api.h>
    #include <mocks/HAL_system_singleton.h>
#else
    #include <HAL_API/HAL_PWM/HAL_PWM_api.h>
    #include <HAL_API/HAL_system/HAL_system_singleton.h>
#endif

enum class common_mode {COMMON_CATHODE, COMMON_ANODE};

#define COLOR_RED 255,0,0
#define COLOR_GREEN 0,255,0
#define COLOR_BLUE 0,0,255
#define COLOR_YELLOW 255,255,0
#define COLOR_PURPLE 255,0,255
#define COLOR_BLUE_SKY 0,255,255
#define COLOR_WHITE 255,255,255 

class RGB_led {
public:
    RGB_led(const uint8_t rgb[3], common_mode mode);
    RGB_led(uint8_t red_pin, uint8_t green_pin, uint8_t blue_pin, common_mode mode);
    ~RGB_led();

    void set_ON_mode();
    void set_OFF_mode();
    void set_BLINK_mode(uint32_t interval_in_milliseconds);

    void set_color(const uint8_t rgb[3]);
    void set_color(uint8_t red, uint8_t green, uint8_t blue);

    uint8_t get_red_value();
    uint8_t get_green_value();
    uint8_t get_blue_value();

    void run_pending_tasks();

private:
    HAL_system_api* device;
    
    PWM_hal* pwm_red = nullptr;
    PWM_hal* pwm_green = nullptr;
    PWM_hal* pwm_blue = nullptr;

    uint8_t rgb[3] = {255, 255, 255};
    float _pwm_red_value = 100;
    float _pwm_green_value = 100;
    float _pwm_blue_value = 100;

    uint32_t blink_interval_in_ms;
    uint32_t last_ms_since_toggle_LED = 0;

    enum class mode {ON, OFF, BLINK};
    mode _mode = mode::OFF;

    common_mode _common_mode;

    bool is_LED_ON = false;

    void turn_on_LEDs();
    void turn_off_LEDs();
    void toggle_LEDs_when_is_time();
};