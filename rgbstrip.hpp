#include "io.hpp"

/**
 *
 * @brief Управление светодиодной лентой на контроллере WS2801
 *
 */

class RgbStrip
{

public:

    RgbStrip( IO::PIN _clock, IO::PIN _serialIn, uint8_t _numberOfLeds );

    void init();

    void deinit();

    void write( uint32_t colour );

    void at( uint32_t led, uint32_t color );

    void update();

private:

    IO::PIN  clock;
    IO::PIN  serialIn;
    uint32_t numberOfLeds;
    uint32_t leds[128];

};
