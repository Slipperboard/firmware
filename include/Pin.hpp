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
    /**
     * @brief Construct a new Pin.
     *
     * @param number GPIO pin number.
     * @param mode   Pin mode (INPUT/OUTPUT/etc.).
     * @param value  Initial value for the pin.
     * @param shared Whether the pin is shared with other peripherals.
     */
    Pin(int number, int mode, T value = T{}, bool shared = false);

    /** Virtual destructor. */
    ~Pin() override;

    /** @return Configured pin mode. */
    int getMode() const;

    /** @return GPIO pin number. */
    int getPinNumber() const;

    /** @return true if this pin is shared. */
    bool isShared() const;

    /** Read the current value from the pin. */
    virtual T read() const = 0;

    /** Write a value to the pin. */
    virtual void write(T value) = 0;

    protected:
    int number;
    int mode;
    T value;
    bool shared{false};
};

#endif // PIN_HPP
