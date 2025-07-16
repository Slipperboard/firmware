#ifndef PIN_HPP
#define PIN_HPP

#include "Peripheral.hpp"

template <typename T> class Pin : public Peripheral
{
    public:
    Pin(int number, int mode, T value = T{});
    ~Pin() override;
    int getMode() const;
    int getPinNumber() const;
    virtual T read() const = 0;
    virtual void write(T value) = 0;

    protected:
    int number;
    int mode;
    T value;
};

#endif // PIN_HPP
