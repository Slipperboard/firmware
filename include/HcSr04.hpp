#ifndef HC_SR04_HPP
#define HC_SR04_HPP

#include "DigitalPin.hpp"
#include "Module.hpp"

struct __attribute__((packed)) DistanceReading {
    float centimeters;
    float meters;
    float inches;
};

class HcSr04 : public Module
{
    public:
    HcSr04(DigitalPin &trigger, DigitalPin &echo);
    ~HcSr04() override = default;

    void init() override;
    DistanceReading readDistance() const;

    private:
    DigitalPin &triggerPin;
    DigitalPin &echoPin;
    bool initialized = false;
};

#endif // HC_SR04_HPP
