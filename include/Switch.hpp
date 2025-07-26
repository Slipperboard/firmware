#ifndef SWITCH_HPP
#define SWITCH_HPP

/**
 * @file Switch.hpp
 * @brief Simple on/off switch abstraction.
 * @author Fadi Hanna Al-Kass <fadi.h.alkass@gmail.com>
 */

#include "Peripheral.hpp"

class Switch : public Peripheral
{
    public:
    /** Construct the switch. */
    Switch();

    /** Virtual destructor. */
    ~Switch() override;
};

#endif // SWITCH_HPP
