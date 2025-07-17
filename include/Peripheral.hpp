#ifndef PERIPHERAL_HPP
#define PERIPHERAL_HPP

#include <string>

// Base abstract class for all hardware types. It exposes only the
// lifecycle hook required by the framework.
class Peripheral
{
    public:
    Peripheral() = default;
    virtual ~Peripheral() = default;

    void setUuid(const std::string& id);
    const std::string& getUuid() const;

    private:
    std::string uuid;
};

#endif // PERIPHERAL_HPP
