#ifndef PERIPHERAL_HPP
#define PERIPHERAL_HPP

// Base abstract class for all hardware types. It exposes only the
// lifecycle hook required by the framework.
class Peripheral {
public:
    Peripheral() = default;
    virtual ~Peripheral() = default;

    // Derived classes must implement their own initialization logic.
    virtual void init() = 0;
};

#endif // PERIPHERAL_HPP
