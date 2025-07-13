#include "Pin.hpp"

template <typename T> Pin<T>::Pin(int pinNumber, PinMode mode, T value) : pinNumber(pinNumber), mode(mode), value(value)
{
}

template <typename T> Pin<T>::~Pin() = default;

// GCOVR_EXCL_START
template <typename T> void Pin<T>::init()
{
}
// GCOVR_EXCL_STOP

template <typename T> PinMode Pin<T>::getMode() const
{
    return mode;
}

template <typename T> int Pin<T>::getPinNumber() const
{
    return pinNumber;
}

// Explicit template instantiations for bool and int
template class Pin<bool>;
template class Pin<int>;
