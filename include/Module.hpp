#ifndef MODULE_HPP
#define MODULE_HPP

#include "Peripheral.hpp"

class Module : public Peripheral {
public:
    Module();
    ~Module() override;
};

#endif // MODULE_HPP
