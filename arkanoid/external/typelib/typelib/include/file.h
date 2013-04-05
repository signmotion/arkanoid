#pragma once

#include "../configure.h"
#include "../external/utfcpp/utf8.h"
#include <string>
#include <set>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>



/**
* ������ ��� ������ � �������� ��������.
*/


namespace typelib {
    namespace file {


/**
* @return ����������� � ������ ���������� �����.
*
* #! �� �������� ��������� � ������� � ������� UTF-8. @todo
*/
std::string read(
    const std::string& file,
    const std::string& path = ""
);




/**
* @return ���������� ����� - ����� � ������� UTF8.
*/
bool validUTF8Content(
    const std::string& file,
    const std::string& path = ""
);




/**
* @return ����� ������ �� ��������� ����� �������� �������.
*
* @param extension  ���� �������, ����� �������� ����� ������ � ��������
*                   �����������.
*/
template< typename Collection >
void listFile(
    Collection*                     r,
    const boost::filesystem::path&  path,
    const std::string&              extension = ""
);





/**
* @return ����� ����� �� ��������� ����� �������� �������.
*/
template< typename Collection >
void listFolder(
    Collection*                     r,
    const boost::filesystem::path&  path
);





/**
* @return �������, ��� ���� �� ���������� ���� ����������. ����� ������
*         �� ������.
*
* @param foundPath  ����, ��� ������ ����.
* @param deep       ������������� ��������� �����.
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
