#ifndef SENSOR_HPP
#define SENSOR_HPP

/**
 * @file Sensor.hpp
 * @brief Generic sensor interface abstraction.
 * @author Fadi Hanna Al-Kass <fadi.h.alkass@gmail.com>
 */

#include "Peripheral.hpp"

class Sensor : public Peripheral
{
    public:
    Sensor();
    ~Sensor() override;
};

#endif // SENSOR_HPP
