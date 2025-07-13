#ifndef PIN_HPP
#define PIN_HPP

#include "Peripheral.hpp"

// Enumeration for pin mode
enum class PinMode { Input, Output };

template <typename T> class Pin : public Peripheral
{
    public:
    Pin(int pinNumber, PinMode mode, T value = T{});
    ~Pin() override;

    void init() override;
    PinMode getMode() const;
    int getPinNumber() const;
    virtual T read() const = 0;
    virtual void write(T value) = 0;

    protected:
    int pinNumber;
    PinMode mode;
    T value;
};

#endif // PIN_HPP
