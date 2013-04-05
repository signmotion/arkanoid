#pragma once

#include "../configure.h"
#include "../external/utfcpp/utf8.h"
#include <string>
#include <set>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>



/**
* Методы для работы с файловой системой.
*/


namespace typelib {
    namespace file {


/**
* @return Прочитанное в строку содержимое файла.
*
* #! Не работает корректно с файлами в формате UTF-8. @todo
*/
std::string read(
    const std::string& file,
    const std::string& path = ""
);




/**
* @return Содержимое файла - текст в формате UTF8.
*/
bool validUTF8Content(
    const std::string& file,
    const std::string& path = ""
);




/**
* @return Набор файлов из указанной папки файловой системы.
*
* @param extension  Если указано, будут отобраны файлы только с заданным
*                   расширением.
*/
template< typename Collection >
void listFile(
    Collection*                     r,
    const boost::filesystem::path&  path,
    const std::string&              extension = ""
);





/**
* @return Набор папок из указанной папки файловой системы.
*/
template< typename Collection >
void listFolder(
    Collection*                     r,
    const boost::filesystem::path&  path
);





/**
* @return Признак, что файл по указанному пути существует. Поиск ведётся
*         по папкам.
*
* @param foundPath  Путь, где найден файл.
* @param deep       Просматривать вложенные папки.
*/
bool hasFile(
    boost::filesystem::path&        foundPath,
    const boost::filesystem::path&  path,
    const std::string&              searchFile,
    bool                            deep
);



    } // file
} // typelib







#include "file.inl"
