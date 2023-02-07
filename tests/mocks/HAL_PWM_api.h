#pragma once
#include <cstdint>
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#define DEFAULT_PWM_CHANNEL 0
#define DEFAULT_PWM_FREQUENCY 500E3

#define DEFAULT_PWM_RESOLUTION 10
#define MAX_VALUE_FOR_DEFAULT_PWM_RESOLUTION 1024

class PWM_hal {
public:
    PWM_hal(uint8_t gpio_to_use) {
        mock().actualCall("PWM_hal->construct")
              .withUnsignedIntParameter("gpio_to_use", gpio_to_use);
    }

    void set_duty_cycle(float duty_cycle) {
        mock().actualCall("PWM_hal->set_duty_cycle")
              .withDoubleParameter("duty_cycle", duty_cycle);
    }
};