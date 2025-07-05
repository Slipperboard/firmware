#include "Pin.hpp"

template <typename T>
Pin<T>::Pin(PinMode mode, T value) : mode_(mode), value_(value) {}

template <typename T>
Pin<T>::~Pin() = default;

template <typename T>
void Pin<T>::init() {}

template <typename T>
PinMode Pin<T>::getMode() const { return mode_; }

template <typename T>
T Pin<T>::read() const { return value_; }

template <typename T>
void Pin<T>::write(T value) {
    if (mode_ == PinMode::Output) {
        value_ = value;
    }
}

// Explicit template instantiations for bool and int
template class Pin<bool>;
template class Pin<int>;

