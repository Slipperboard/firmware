#ifndef HAL_HPP
#define HAL_HPP

// Base abstract class for all hardware types. It exposes only the
// lifecycle hook required by the framework.
class HAL {
public:
    HAL() = default;
    virtual ~HAL() = default;

    // Derived classes must implement their own initialization logic.
    virtual void init() = 0;
};

// Generic hardware categories that extend HAL. Specific devices will in
// turn derive from one of these classes.
class Module : public HAL {};
class Sensor : public HAL {};
class Switch : public HAL {};
class Button : public HAL {};
class Display : public HAL {};

#endif // HAL_HPP
