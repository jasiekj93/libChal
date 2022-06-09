#include "MockHal.hpp"

clock_t Mock::Hal::Clock = 0;
time_t Mock::Hal::Time = 0;
Chal::IStream * Mock::Hal::Stream = nullptr;
