/**
 * @file Pin.cpp
 * @brief Implementation of generic Pin template.
 * @author Fadi Hanna Al-Kass <fadi.h.alkass@gmail.com>
 */

#include "Pin.hpp"
#include <Arduino.h>

template <typename T>
// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
/** Construct a Pin and configure the hardware. */
Pin<T>::Pin(int number, int mode, T value, bool shared) : number(number), mode(mode), value(value), shared(shared)
{
    pinMode(number, mode);
}

/** Destructor. */
template <typename T> Pin<T>::~Pin()
{
}

/** Get the pin mode. */
template <typename T> int Pin<T>::getMode() const
{
    return mode;
}

/** Get the GPIO number. */
template <typename T> int Pin<T>::getPinNumber() const
{
    return number;
}

/** Check whether the pin is shared. */
template <typename T> bool Pin<T>::isShared() const
{
    return shared;
}

// Explicit template instantiations for bool and int
template class Pin<bool>;
template class Pin<int>;
