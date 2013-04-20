#pragma once

#include <string>


namespace arkanoid {


/**
* Количество контейнеров по ширине уровня и размер ячейки по умолчанию.
*/
static const size_t COUNT_CONTAINER = 20 + 2;
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
* Плотности некоторых элементов игры, кг / м3.
*/
static const float DENSITY_CAPSULE_PLATFORM = 1000.0f;

static const float DENSITY_SPHERE_RACKET    = 3000.0f;

static const float DENSITY_CUBE_CONTAINER   = 0.0f;
static const float DENSITY_SPHERE_CONTAINER = 0.0f;




/**
* Для отладки.
*/
#ifdef _DEBUG
#define ASSERT(EXPR)   assert(EXPR);
#define DASSERT(EXPR)  if (!(EXPR)) __debugbreak();

#define QUOTE_(WHAT)      #WHAT
#define QUOTE(WHAT)       QUOTE_(WHAT)
#define DBG(format, ...)  printf("%s: "format, __FILE__":"QUOTE(__LINE__), ## __VA_ARGS__)

#define CONSOLE  Console::instance()

#else
#define ASSERT(EXPR)      ((void)0)
#define DASSERT(EXPR)     ((void)0)
#define DBG(format, ...)  ((void)0)
#define CONSOLE           ((void)0)

#endif


} // arkanoid
