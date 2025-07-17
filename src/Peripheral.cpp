#include "Peripheral.hpp"
#include <string>

void Peripheral::setUuid(const std::string& id)
{
    uuid = id;
}

const std::string& Peripheral::getUuid() const
{
    return uuid;
}
