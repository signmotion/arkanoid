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
#define ASSERT(EXPR)   assert(EXPR);
#define DASSERT(EXPR)  if (!(EXPR)) __debugbreak();
#define NOT_USED(x)    ((void)(x))


// @see Console
#define CONSOLE  Console::instance()


} // arkanoid
