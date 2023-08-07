#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include <mocks/HAL_system_singleton.h>
#include <RGB_led.h>

TEST_GROUP(RGB_LED_instantiation)
{
    void teardown()
    {
        mock().checkExpectations();
        mock().clear();
    }
};

#define RED_PIN 33
#define GREEN_PIN 32
#define BLUE_PIN 2

void CHECK_pwm_are_instantiated() {
    mock().expectOneCall("HAL_PWM->construct")
          .withUnsignedIntParameter("gpio_to_use", RED_PIN);
    mock().expectOneCall("HAL_PWM->construct")
          .withUnsignedIntParameter("gpio_to_use", GREEN_PIN);
    mock().expectOneCall("HAL_PWM->construct")
          .withUnsignedIntParameter("gpio_to_use", BLUE_PIN);
}

TEST(RGB_LED_instantiation, GIVEN_class_is_not_instantiated_WHEN_instantiate_class_with_array_pins_THEN_init_pwm_on_those_pins_and_set_duty_cycle_to_zero)
{
    CHECK_pwm_are_instantiated();

    const uint8_t rgb[3] = {RED_PIN, GREEN_PIN, BLUE_PIN};
    RGB_led led(rgb, common_mode::COMMON_CATHODE);
}

TEST(RGB_LED_instantiation, GIVEN_class_is_not_instantiated_WHEN_instantiate_class_with_individual_pins_THEN_init_pwm_on_those_pins_and_set_duty_cycle_to_zero)
{
    CHECK_pwm_are_instantiated();
    RGB_led led(RED_PIN, GREEN_PIN, BLUE_PIN, common_mode::COMMON_CATHODE);
}

RGB_led* led = nullptr;
HAL_system_api* device;

TEST_GROUP(RGB_LED)
{
    void setup()
    {
        mock().disable();
        led = new RGB_led(RED_PIN, GREEN_PIN, BLUE_PIN, common_mode::COMMON_CATHODE);
        mock().enable();
        device = HAL_system_singleton::get_HAL_system_instance();
    }
    void teardown()
    {
        mock().checkExpectations();
        mock().clear();
        delete led;
        HAL_system_singleton::clear_all_instances();
    }
};

void CHECK_LEDs_color(uint8_t red, uint8_t green, uint8_t blue);

TEST(RGB_LED, default_color_is_255_255_255)
{
    CHECK_LEDs_color(255,255,255);
}

void CHECK_PWM_set_duty_calls_for_RGB(float duty_cycle);

TEST(RGB_LED, default_mode_is_OFF)
{
    CHECK_PWM_set_duty_calls_for_RGB(0);
    led->run_pending_tasks();
}

TEST(RGB_LED, when_set_ON_mode_without_set_color_THEN_set_pwm_duty_to_100_on_all_colors)
{
    led->set_ON_mode();
    
    CHECK_PWM_set_duty_calls_for_RGB(100);
    led->run_pending_tasks();
}

TEST(RGB_LED, GIVEN_instantiated_class_WHEN_sets_ON_mode_THEN_after_run_pending_task_shows_default_color)
{
    CHECK_PWM_set_duty_calls_for_RGB(100);
    led->set_ON_mode();
    led->run_pending_tasks();
}

TEST(RGB_LED, GIVEN_instantiated_class_WHEN_sets_OFF_mode_THEN_after_runing_pending_tasks_turn_off_LEDs)
{
    CHECK_PWM_set_duty_calls_for_RGB(0);
    led->set_ON_mode();
    led->set_OFF_mode();
    led->run_pending_tasks();
}

TEST(RGB_LED, GIVEN_instantiated_class_WHEN_set_colour_rgb_to_255_255_255_THEN_sets_colors)
{
    const uint8_t rgb_color[3] = {255, 255, 255};
    led->set_color(rgb_color);
    CHECK_LEDs_color(255,255,255);
}

TEST(RGB_LED, GIVEN_instantiated_class_WHEN_set_colour_rgb_to_0_0_0_THEN_sets_colors)
{
    const uint8_t rgb_color[3] = {0, 0 , 0};
    led->set_color(rgb_color);
    CHECK_LEDs_color(0,0,0);
}

void CHECK_LEDs_color(uint8_t red, uint8_t green, uint8_t blue) {
    CHECK_EQUAL(red, led->get_red_value());
    CHECK_EQUAL(green, led->get_green_value());
    CHECK_EQUAL(blue, led->get_blue_value());
}

TEST(RGB_LED, GIVEN_instantiated_class_WHEN_set_colour_rgb_to_51_51_51_and_set_ON_mode_THEN_sets_all_PWMs_to_20)
{
    const uint8_t rgb_color[3] = {51, 51, 51};
    led->set_color(rgb_color);
    led->set_ON_mode();

    CHECK_PWM_set_duty_calls_for_RGB(20);
    led->run_pending_tasks();
}

TEST(RGB_LED, GIVEN_instantiated_class_WHEN_set_color_rgb_to_255_255_255_and_set_ON_mode_THEN_sets_all_PWMs_to_100)
{
    const uint8_t rgb_color[3] = {255, 255, 255};
    led->set_color(rgb_color);
    led->set_ON_mode();

    CHECK_PWM_set_duty_calls_for_RGB(100);
    led->run_pending_tasks();
}

#define milliseconds
TEST(RGB_LED, GIVEN_instantiated_class_WHEN_set_BLINK_mode_with_500_ms_interval_THEN_sets_PWMs_each_250ms)
{
    device->set_milliseconds_since_init(0 milliseconds);
    uint32_t INTERVAL_OF_500_MS = 500;
    led->set_BLINK_mode(INTERVAL_OF_500_MS);

    device->set_milliseconds_since_init(250 milliseconds);
    CHECK_PWM_set_duty_calls_for_RGB(100);
    led->run_pending_tasks();

    device->set_milliseconds_since_init(500 milliseconds);
    CHECK_PWM_set_duty_calls_for_RGB(0);
    led->run_pending_tasks();
}

TEST(RGB_LED, GIVEN_instantiated_on_common_anode_WHEN_set_ON_mode_without_set_color_THEN_set_pwm_duty_to_0_on_all_colors)
{
    delete led;
    mock().disable();
    led = new RGB_led(RED_PIN, GREEN_PIN, BLUE_PIN, common_mode::COMMON_ANODE);
    mock().enable();

    CHECK_PWM_set_duty_calls_for_RGB(0);
    led->set_ON_mode();
    led->run_pending_tasks();
}

TEST(RGB_LED, GIVEN_instantiated_on_common_anode_WHEN_set_OFF_mode_THEN_set_pwm_duty_to_100_on_all_colors)
{
    delete led;
    mock().disable();
    led = new RGB_led(RED_PIN, GREEN_PIN, BLUE_PIN, common_mode::COMMON_ANODE);
    mock().enable();

    CHECK_PWM_set_duty_calls_for_RGB(100);
    led->set_OFF_mode();
    led->run_pending_tasks();
}

void CHECK_PWM_set_duty_calls_for_RGB(float duty_cycle) {
    mock().expectNCalls(3, "HAL_PWM->set_duty_cycle")
          .withDoubleParameter("duty_cycle", duty_cycle);
}