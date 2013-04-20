#pragma once

#include <string>


namespace arkanoid {


/**
* ���������� ����������� �� ������ ������ � ������ ������ �� ���������.
*/
static const size_t COUNT_CONTAINER = 20 + 2;
static const size_t CELL_SIZE = 32;




/**
* ������ ���� ����, �������� �������� ������������� ��������, ���.
*
* # ������ ������ ������� ������� �������, ����� �������� ���������
*   ������ ���-�� ���������.
*/
static const size_t WINDOW_WIDTH  = COUNT_CONTAINER * CELL_SIZE;
static const size_t WINDOW_HEIGHT = WINDOW_WIDTH * 100000 / 161803;




/**
* ���� � ������ � �������� �������.
*/
static const std::string PATH_MEDIA = "media";




/**
* ��������� ��������� ��������� ����, �� / �3.
*/
static const float DENSITY_CAPSULE_PLATFORM = 1000.0f;

static const float DENSITY_SPHERE_RACKET    = 3000.0f;

static const float DENSITY_CUBE_CONTAINER   = 0.0f;
static const float DENSITY_SPHERE_CONTAINER = 0.0f;




/**
* ��� �������.
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
