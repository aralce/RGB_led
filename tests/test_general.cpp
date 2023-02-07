#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
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
    mock().expectOneCall("PWM_hal->construct")
          .withUnsignedIntParameter("gpio_to_use", RED_PIN);
    mock().expectOneCall("PWM_hal->construct")
          .withUnsignedIntParameter("gpio_to_use", GREEN_PIN);
    mock().expectOneCall("PWM_hal->construct")
          .withUnsignedIntParameter("gpio_to_use", BLUE_PIN);
}

TEST(RGB_LED_instantiation, GIVEN_class_is_not_instantiated_WHEN_instantiate_class_with_array_pins_THEN_init_pwm_on_those_pins_and_set_duty_cycle_to_zero)
{
    CHECK_pwm_are_instantiated();

    const int rgb[3] = {RED_PIN, GREEN_PIN, BLUE_PIN};
    RGB_led led(rgb);
}

TEST(RGB_LED_instantiation, GIVEN_class_is_not_instantiated_WHEN_instantiate_class_with_individual_pins_THEN_init_pwm_on_those_pins_and_set_duty_cycle_to_zero)
{
    CHECK_pwm_are_instantiated();
    RGB_led led(RED_PIN, GREEN_PIN, BLUE_PIN);
}

RGB_led* led = nullptr;
TEST_GROUP(RGB_LED)
{
    void setup()
    {
        mock().disable();
        led = new RGB_led(RED_PIN, GREEN_PIN, BLUE_PIN);
        mock().enable();
    }
    void teardown()
    {
        mock().checkExpectations();
        mock().clear();
        delete led;
    }
};

TEST(RGB_LED, GIVEN_instantiated_class_WHEN_sets_ON_mode_THEN_after_run_pending_task_shows_default_color)
{
    const int default_color[3] = {255, 255, 255};
    
    mock().expectNCalls(3, "PWM_hal->set_duty_cycle")
          .withDoubleParameter("duty_cycle", 100);
    led->set_ON_mode();
    led->run_pending_tasks();
}

TEST(RGB_LED, GIVEN_instantiated_class_WHEN_sets_OFF_mode_THEN_after_runing_pending_tasks_turn_off_LEDs)
{
    mock().expectNCalls(3, "PWM_hal->set_duty_cycle")
          .withDoubleParameter("duty_cycle", 0);

    led->set_OFF_mode();
    led->run_pending_tasks();
}

TEST(RGB_LED, GIVEN_instantiated_class_WHEN_set_colour_rgb_to_255_255_255_THEN_sets_all_PWMs_to_100)
{
    mock().expectNCalls(3, "PWM_hal->set_duty_cycle")
          .withDoubleParameter("duty_cycle", 100);

    const int rgb_color[3] = {255, 255, 255};
    led->set_color(rgb_color);
}

TEST(RGB_LED, GIVEN_instantiated_class_WHEN_set_colour_rgb_to_0_0_0_THEN_sets_all_PWMs_to_0)
{
    mock().expectNCalls(3, "PWM_hal->set_duty_cycle")
          .withDoubleParameter("duty_cycle", 0);

    const int rgb_color[3] = {0, 0 , 0};
    led->set_color(rgb_color);
}

TEST(RGB_LED, GIVEN_instantiated_class_WHEN_set_colour_rgb_to_51_51_51_THEN_sets_all_PWMs_to_20)
{
    mock().expectNCalls(3, "PWM_hal->set_duty_cycle")
          .withDoubleParameter("duty_cycle", 20);
    
    const int rgb_color[3] = {51, 51, 51};
    led->set_color(rgb_color);
}


