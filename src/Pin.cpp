#include "Pin.hpp"

template <typename T> Pin<T>::Pin(PinMode mode, T value) : mode(mode), value(value)
{
}

template <typename T> Pin<T>::~Pin() = default;

template <typename T> void Pin<T>::init()
{
}

template <typename T> PinMode Pin<T>::getMode() const
{
    return mode;
}

// Explicit template instantiations for bool and int
template class Pin<bool>;
template class Pin<int>;
