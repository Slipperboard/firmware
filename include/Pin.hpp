#ifndef PIN_HPP
#define PIN_HPP

/**
 * @file Pin.hpp
 * @brief Generic I/O pin template used by specific pin classes.
 * @author Fadi Hanna Al-Kass <fadi.h.alkass@gmail.com>
 */

#include <Arduino.h>
#include "Peripheral.hpp"

template <typename T> class Pin : public Peripheral
{
    public:
    Pin(int number, int mode, T value = T{}, bool shared = false);
    ~Pin() override;
    int getMode() const;
    int getPinNumber() const;
    bool isShared() const;
    virtual T read() const = 0;
    virtual void write(T value) = 0;

    protected:
    int number;
    int mode;
    T value;
    bool shared{false};
};

#endif // PIN_HPP
