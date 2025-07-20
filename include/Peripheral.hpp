#ifndef PERIPHERAL_HPP
#define PERIPHERAL_HPP

/**
 * @file Peripheral.hpp
 * @brief Base class for all hardware components.
 * @author Fadi Hanna Al-Kass <fadi.h.alkass@gmail.com>
 */

// Base abstract class for all hardware types. It exposes only the
// lifecycle hook required by the framework.
class Peripheral
{
    public:
    Peripheral() = default;
    virtual ~Peripheral() = default;
};

#endif // PERIPHERAL_HPP
