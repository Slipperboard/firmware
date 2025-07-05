#ifndef PIN_HPP
#define PIN_HPP

#include "Peripheral.hpp"

// Enumeration for pin mode
enum class PinMode { Input, Output };

template <typename T>
class Pin : public Peripheral {
public:
    Pin(PinMode mode, T value = T{}) : mode_(mode), value_(value) {}
    ~Pin() override = default;

    void init() override {}
    PinMode getMode() const { return mode_; }
    T read() const { return value_; }
    void write(T value) {
        if (mode_ == PinMode::Output) {
            value_ = value;
        }
    }

protected:
    PinMode mode_;
    T value_;
};

#endif // PIN_HPP
