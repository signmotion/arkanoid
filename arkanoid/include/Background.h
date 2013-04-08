#pragma once

#include "configure.h"
#include "structure.h"
#include "PPIncarnate.h"
#include "IRRKIncarnate.h"


namespace arkanoid {


class Background :
    public PPIncarnate,
    public IRRKIncarnate
    // # Фон не является частью физ. мира.
{
public:
    /**
    * Информация о фоне, полученная из файла декларации уровня.
    *
    * @todo fine Сократить конструктор: сейчас часть инфо дублируется.
    */
    const AboutBackground  about;




public:
    Background(
        const std::string&           sprite,
        const typelib::size2Int_t&   needVisualSize,
        const typelib::coord2_t&     coord,
        const AboutBackground&
    );


    virtual ~Background();
};


} // arkanoid
