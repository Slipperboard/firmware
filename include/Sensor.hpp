#ifndef SENSOR_HPP
#define SENSOR_HPP

#include "Peripheral.hpp"

class Sensor : public Peripheral {
public:
    Sensor();
    ~Sensor() override;
};

#endif // SENSOR_HPP
