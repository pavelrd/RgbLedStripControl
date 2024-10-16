#include "io.hpp"
#include "thread.hpp"
#include "wifi.hpp"
#include "database.hpp"
#include "webserver.hpp"
#include "filesystem.hpp"
#include "lednumber.hpp"
#include "debug.hpp"
#include "serial.hpp"
#include "convert.hpp"
#include "delay.hpp"
#include "rgbstrip.hpp"

void onAccessPointStarted();

RgbStrip rgbStrip( IO::D18, IO::D19, 92 );

void setCode( Connection& connection, const char* value );

/**
 *
 * @brief Управление rgb светодиодной лентой по wifi
 *
 *  Идентификатор точки доступа: dlink-r2873
 *  Пароль:                      ad31-gtR7-1290-ewqB
 *  IP адрес интерфейса:         192.168.4.1
 *
 *  При запуске программы в режиме отладки на ПК:
 *
 *  IP адрес интерфейса:         127.0.0.1:12345
 *
 */

void setup()
{

    // Debug::enable();

    Serial::write("Led control program\n");
    Serial::write(" support control 7 leds\n\n");

    Serial::write("SSID:     dlink-r2873\n");
    Serial::write("Password: ad31-gtR7-1290-ewqB\n");
    Serial::write("IP:       192.168.4.1\n\n");

    rgbStrip.init();

    database.init();

    webServer.setFilesytem( filesystem );
    webServer.setDatabase( database );
    webServer.setStackSize( 2500 );

    #if defined(PC_PLATFORM)
        database.add( "IP4_ADDRESS",   "127.0.0.1" );
        database.add( "IP4_PORT",          12345 );
    #else
        database.add( "IP4_ADDRESS", "192.168.4.1" );
        database.add( "IP4_PORT",             80   );
    #endif

    webServer.setPort( database.getIntegerValue("IP4_PORT") );

    webServer.addHandler( "/", "setCode", setCode );

    Wifi::setOnAccessPointStartedHandler( onAccessPointStarted );

    Wifi::setAccessPoint( "dlink-r2873", "ad31-gtR7-1290-ewqB" );

}


/**
 *
 * @brief Обработчик успешного запуска wifi точки доступа
 *    Запускает web сервер.
 */

void onAccessPointStarted()
{

    webServer.start();

}

/**
 *
 * @brief Обработчик установки нового кода
 *
 * @param connection
 * @param value
 *
 */

void setCode( Connection& connection, const char* value )
{

    uint32_t color = Convert::toInteger( value );

    uint32_t correctedColor = color;
    correctedColor         &= 0xFF0000;
    correctedColor         |= ( ( color & 0x00FF00 ) >> 8 ); // XX YY YY
    correctedColor         |= ( ( color & 0x0000FF ) << 8 ); // XX YY YY

    for( int i = 0 ; i < 92; i++ )
    {
        rgbStrip.at( i, correctedColor );
    }

    rgbStrip.update(); // FF0000 красный 00FF00 синий 0000FF зелёный


    Network::sendJsonHeader( connection );
    Network::sendJson( connection, "status", "success", Network::JsonEnd );

}
