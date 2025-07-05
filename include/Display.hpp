#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "Peripheral.hpp"

class Display : public Peripheral {
public:
    Display(int width, int height);
    ~Display() override;

    int getWidth() const;
    int getHeight() const;
    bool isInitialized() const;

protected:
    bool initialized;
    int width;
    int height;
};

#endif // DISPLAY_HPP
