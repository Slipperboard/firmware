#include "Pin.hpp"
#include <Arduino.h>

template <typename T>
// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
Pin<T>::Pin(int number, int mode, T value) : number(number), mode(mode), value(value)
{
    pinMode(number, mode);
}

template <typename T> Pin<T>::~Pin()
{
}

template <typename T> int Pin<T>::getMode() const
{
    return mode;
}

template <typename T> int Pin<T>::getPinNumber() const
{
    return number;
}

// Explicit template instantiations for bool and int
template class Pin<bool>;
template class Pin<int>;
