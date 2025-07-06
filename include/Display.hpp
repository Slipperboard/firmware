#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "Peripheral.hpp"
#include <cstddef>
#include <cstdint>

class Display : public Peripheral {
public:
    Display(int width, int height);
    ~Display() override;

    int getWidth() const;
    int getHeight() const;
    virtual bool isInitialized() const = 0;
    virtual void drawBytes(int x, int y, const uint8_t* data, std::size_t len) = 0;
    // Returns the byte stored in the display's buffer at the given coordinates.
    // This helper is primarily used in unit tests to verify drawBytes.
    virtual uint8_t readByte(int x, int y) const = 0;

protected:
    int width;
    int height;
};

#endif // DISPLAY_HPP
