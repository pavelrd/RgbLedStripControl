import "C:/MicrocontrollerLibrary/sources/build/PC.qbs"           as pcProgram

// ------- Выбор платформы, должна быть раскомментирована одна из этих строк,
//           в зависимости от того под какую платформу требуется компиляция и прошивка программы

// import "C:/MicrocontrollerLibrary/sources/build/K1986.qbs"       as microcontrollerProgram

// import "C:/MicrocontrollerLibrary/sources/build/SAM4E.qbs"       as microcontrollerProgram

// import "C:/MicrocontrollerLibrary/sources/build/ESP8266.qbs"     as microcontrollerProgram

import "C:/MicrocontrollerLibrary/sources/build/ESP32.qbs"       as microcontrollerProgram

// import "C:/MicrocontrollerLibrary/sources/build/Raspberrypi.qbs" as microcontrollerProgram

// -------

Project
{

    name: "Program"

    // ------- Подключение необходимых файлов
    //          из библиотеки файлов web интерфейса

    pcProgram
    {
        
        // Сборка под pc, ничего не надо, все по-умолчанию
        
        Group
        {
            name     : "Common web interface"
            prefix   : "C:/MicrocontrollerLibrary/sources/web/common"
            files    : [
                        "/scripts/jquery.min.js"
                        ]
            fileTags : [ "web" ]
        }
    }
	
    // Раскомментировать, чтобы собрать программу под микроконтроллер
    microcontrollerProgram
    {

        // Сборка под микроконтроллер, все по-умолчанию

        // Порт, только для ESP8266 и ESP32

        property string port : "COM4"
        
        Group
        {
            name     : "Common web interface"
            prefix   : "C:/MicrocontrollerLibrary/sources/web/common"
            files    : [
                        "/scripts/jquery.min.js"
                        ]
            fileTags : [ "web" ]
        }
        
    }

}
