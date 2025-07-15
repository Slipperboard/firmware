#include "Pin.hpp"

template <typename T> Pin<T>::Pin(int number, PinMode mode, T value) : number(number), mode(mode), value(value)
{
}

template <typename T> Pin<T>::~Pin() = default;

template <typename T> PinMode Pin<T>::getMode() const
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
