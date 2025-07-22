/**
 * @file Pin.cpp
 * @brief Implementation of generic Pin template.
 * @author Fadi Hanna Al-Kass <fadi.h.alkass@gmail.com>
 */

#include "Pin.hpp"
#include <Arduino.h>

template <typename T>
// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
Pin<T>::Pin(int number, int mode, T value, bool isShared) : number(number), mode(mode), value(value), isShared(isShared)
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

template <typename T> bool Pin<T>::getIsShared() const
{
    return isShared;
}

template <typename T> void Pin<T>::setShared(bool shared)
{
    isShared = shared;
}

// Explicit template instantiations for bool and int
template class Pin<bool>;
template class Pin<int>;
