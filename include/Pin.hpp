#ifndef PIN_HPP
#define PIN_HPP

#include "Peripheral.hpp"

// Enumeration for pin mode
enum class PinMode { Input, Output };

template <typename T> class Pin : public Peripheral
{
    public:
    Pin(int number, PinMode mode, T value = T{});
    ~Pin() override;

    void init() override;
    PinMode getMode() const;
    int getNumber() const;
    virtual T read() const = 0;
    virtual void write(T value) const = 0;

    protected:
    int number;
    PinMode mode;
    mutable T value;
};

#endif // PIN_HPP
