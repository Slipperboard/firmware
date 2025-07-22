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
    Pin(int number, int mode, T value = T{}, bool isShared = false);
    ~Pin() override;
    int getMode() const;
    int getPinNumber() const;
    bool getIsShared() const;
    void setShared(bool shared);
    virtual T read() const = 0;
    virtual void write(T value) = 0;

    protected:
    int number;
    int mode;
    T value;
    bool isShared;
};

#endif // PIN_HPP
