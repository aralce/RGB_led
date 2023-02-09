#pragma once
#include <cstdint>

class HAL_system_api {
public:
    uint32_t millisecs_since_init() {
        return _millisecs_since_init;
    }
    
    void set_milliseconds_since_init(uint32_t milliseconds) {
        _millisecs_since_init = milliseconds;
    }

private:
    uint32_t _millisecs_since_init = 0;
};