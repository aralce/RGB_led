#pragma once
#include "HAL_system_api.h"

class HAL_system_singleton {
public:
    static HAL_system_api* get_HAL_system_instance();
    static void clear_all_instances();

    HAL_system_singleton() = delete;
    HAL_system_singleton(const HAL_system_singleton&) = delete;
    HAL_system_singleton(HAL_system_singleton&&) = delete;
    HAL_system_singleton& operator=(const HAL_system_singleton&) = delete;
    HAL_system_singleton& operator=(HAL_system_singleton&&) = delete;

private:
    static HAL_system_api* hal_system_instance;
};