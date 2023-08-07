#pragma once
#include <cstdint>
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#define DEFAULT_PWM_CHANNEL 0
#define DEFAULT_PWM_FREQUENCY 500E3

#define DEFAULT_PWM_RESOLUTION 10
#define MAX_VALUE_FOR_DEFAULT_PWM_RESOLUTION 1024

class HAL_PWM {
public:
    HAL_PWM(uint8_t gpio_to_use, uint8_t channel = DEFAULT_PWM_CHANNEL) {
        mock().actualCall("HAL_PWM->construct")
              .withUnsignedIntParameter("gpio_to_use", gpio_to_use);
    }

    void set_duty_cycle(float duty_cycle) {
        mock().actualCall("HAL_PWM->set_duty_cycle")
              .withDoubleParameter("duty_cycle", duty_cycle);
    }
};