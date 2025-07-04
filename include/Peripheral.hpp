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

// Generic hardware categories that extend Peripheral. Specific devices will in
// turn derive from one of these classes.
class Module : public Peripheral {};
class Sensor : public Peripheral {};
class Switch : public Peripheral {};
class Button : public Peripheral {};
class Display : public Peripheral {};

#endif // PERIPHERAL_HPP
