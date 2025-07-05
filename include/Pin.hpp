#ifndef PIN_HPP
#define PIN_HPP

#include "Peripheral.hpp"

// Enumeration for pin mode
enum class PinMode { Input, Output };

class Pin : public Peripheral {
public:
    Pin(PinMode mode, int value = 0);
    ~Pin() override;

    void init() override;
    PinMode getMode() const;
    int getValue() const;

protected:
    PinMode mode_;
    int value_;
};

#endif // PIN_HPP
