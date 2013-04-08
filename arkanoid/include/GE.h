#pragma once

#include "configure.h"
#include "structure.h"


namespace arkanoid {


/**
* Класс для связывания игровых элементов.
* Если движок (физики, графики, логики, ...) должен знать о других
* игровых элементах, он обязан наследоваться от этого класса.
*/
class GE {
public:
    /**
    * Метка этого элемента и то, во что он превращается (например, после
    * разрушения).
    *
    * # Если элемент не должен быть доступен по метке, значение метки = 0.
    */
    const sign_t  sign;
    const sign_t  next;



public:
    GE( sign_t sign, sign_t next );


    virtual ~GE();
};


} // arkanoid
