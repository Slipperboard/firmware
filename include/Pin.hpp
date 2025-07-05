#ifndef PIN_HPP
#define PIN_HPP

#include "Peripheral.hpp"

// Enumeration for pin mode
enum class PinMode { Input, Output };

template <typename T>
class Pin : public Peripheral {
public:
    Pin(PinMode mode, T value = T{});
    ~Pin() override;

    void init() override;
    PinMode getMode() const;
    virtual T read() const = 0;
    virtual void write(T value) = 0;

protected:
    PinMode mode_;
    T value_;
};

#endif // PIN_HPP
