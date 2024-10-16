#include "rgbstrip.hpp"

/**
 *
 * @brief RgbStrip::RgbStrip
 *
 * @param _clock    вывод к контроллера который подключен к проводу CK(clock) ленты
 * @param _serialIn вывод к контроллера который подключен к проводу SI(serial input) ленты
 *
 * @param _numberOfLeds количество светодиодов в ленте
 *
 */

RgbStrip::RgbStrip( IO::PIN _clock, IO::PIN _serialIn, uint8_t _numberOfLeds )
{
    clock        = _clock;
    serialIn     = _serialIn;
    numberOfLeds = _numberOfLeds;
}

/**
 *
 * @brief Инициализация, метод вызывается один раз перед использованием ленты
 *
 */

void RgbStrip::init()
{

    IO::use( clock );
    IO::use( serialIn );

    IO::out( clock );
    IO::out( serialIn );

    IO::low(clock);
    IO::low(serialIn);

}

/**
 *
 * @brief Деинициализация, метод вызывается после окончания использования ленты
 *
 */

void RgbStrip::deinit()
{

    IO::in( clock );
    IO::in( serialIn );

    IO::unuse( clock );
    IO::unuse( serialIn );

}

/**
 *
 * @brief Записать цвет
 *
 * @param colour
 *
 */

void RgbStrip::write( uint32_t colour )
{

   // portMUX_TYPE myMutex = portMUX_INITIALIZER_UNLOCKED;

    for( int i = 0 ; i < 24; i++ )
    {
        if( colour & 0x00800000 )
        {
            IO::high(serialIn);
        }
        else
        {
            IO::low(serialIn);
        }
        colour <<= 1;
        IO::high(clock);
        IO::low(clock);
    }



}

/**
 * @brief RgbStrip::at
 * @param led
 * @param color
 */

void RgbStrip::at( uint32_t led, uint32_t color )
{
    if( ( numberOfLeds != 0 ) && ( led <= ( numberOfLeds - 1 ) ) )
    {
        leds[led] = color;
    }
}

/**
 * @brief RgbStrip::update
 */

void RgbStrip::update()
{
    for( uint32_t i = 0 ; i < numberOfLeds; i++ )
    {
        write( leds[i] );
    }
}
