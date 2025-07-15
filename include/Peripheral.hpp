#ifndef PERIPHERAL_HPP
#define PERIPHERAL_HPP
// GCOVR_EXCL_START

// Base abstract class for all hardware types. It exposes only the
// lifecycle hook required by the framework.
class Peripheral
{
    public:
    Peripheral() = default;
    virtual ~Peripheral() = default;
};

// GCOVR_EXCL_STOP

#endif // PERIPHERAL_HPP
