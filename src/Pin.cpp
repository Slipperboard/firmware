#include "Pin.hpp"

Pin::Pin(PinMode mode, int value) : mode_(mode), value_(value) {}

Pin::~Pin() = default;

void Pin::init() {}

PinMode Pin::getMode() const { return mode_; }

int Pin::getValue() const { return value_; }
