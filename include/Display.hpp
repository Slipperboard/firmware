#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "Peripheral.hpp"

class Display : public Peripheral {
public:
    Display(int width, int height);
    ~Display() override;

    int getWidth() const;
    int getHeight() const;
    virtual bool isInitialized() const = 0;

protected:
    int width;
    int height;
};

#endif // DISPLAY_HPP
