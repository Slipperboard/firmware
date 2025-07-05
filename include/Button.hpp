#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Peripheral.hpp"

class Button : public Peripheral {
public:
    Button();
    ~Button() override;
};

#endif // BUTTON_HPP
