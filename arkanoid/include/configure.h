#pragma once

#include <string>


namespace arkanoid {


/**
* Количество контейнеров по ширине уровня и размер ячейки по умолчанию.
*/
static const size_t COUNT_CONTAINER = 20;
static const size_t CELL_SIZE = 32;




/**
* Размер окна игры, согласно которому позиционируем элементы, пкс.
*
* # Ширину сделам кратной размеру спрайта, чтобы спокойно поместить
*   нужное кол-во элементов.
*/
static const size_t WINDOW_WIDTH  = COUNT_CONTAINER * CELL_SIZE;
static const size_t WINDOW_HEIGHT = WINDOW_WIDTH * 100000 / 161803;




/**
* Пути к данным в файловой системе.
*/
static const std::string PATH_MEDIA = "media";




/**
* Массы некоторых элементов игры, кг.
*/
static const float MASS_CAPSULE_PLATFORM = 200.0f;

static const float MASS_SPHERE_RACKET    = 20.0f;

static const float MASS_CUBE_CONTAINER   = 0.0f;
static const float MASS_SPHERE_CONTAINER = 0.0f;




/**
* Для отладки.
*/
#undef ASSERT
#define ASSERT(EXPR)   assert(EXPR);
#define DASSERT(EXPR)  if (!(EXPR)) __debugbreak();


// @see Console
#define CONSOLE  Console::instance()


} // arkanoid
