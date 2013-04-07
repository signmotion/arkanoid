#pragma once

#include "configure.h"


namespace arkanoid {


class World;
class ManagerSprite;


/**
* Объект, зарегистрированный в визуальном движке.
* # В качестве виз. движка используется Phrophecy.
*
* @see http://twilight3d.com
*/
class PPIncarnate {
public:
    const std::string          sprite;
    const typelib::size2Int_t  originalVisualSize;
    const typelib::size2Int_t  needVisualSize;




protected:
    /**
    * Если 'needVisualSize' не указан, будет взят оригинальный размер спрайта.
    */
    PPIncarnate(
        const std::string&           sprite,
        const typelib::coord2Int_t&  vc,
        const typelib::size2Int_t&   needVisualSize = typelib::size2Int_t::ZERO()
    );


    virtual ~PPIncarnate();




public:
    /**
    * Отображает спрайт для элемента. Показ отложен.
    */
    virtual void draw( prcore::Bitmap& context ) const;




    /**
    * @return Координаты образа.
    *
    * # Названа с приставкой, чтобы проще получать доступ из элементов игры.
    */
    template< typename T >
    inline void visualCoord( T x, T y ) {
        visualCoord( typelib::coord2Int_t( x, y ) );
    };


    inline const typelib::coord2Int_t&  visualCoord() const {
        return mCoord;
    };


    inline typelib::coord2Int_t&  visualCoord() {
        return mCoord;
    };


    inline void visualCoord( const typelib::coord2Int_t& c ) {
        mCoord = c;
    };




    /**
    * @return Угол поворота элемента в градусах.
    */
    template< typename T >
    inline void visualRotation( T a ) {
        mRotation = static_cast< float >( a );
    };


    template< typename T >
    inline T visualRotation() const {
        return static_cast< T >( mRotation );
    };


    inline float visualRotation() const {
        return mRotation;
    };




    /**
    * @return Прозрачность элемента [0.0; 1.0].
    */
    template< typename T >
    inline void visualAlpha( T a ) {
        mAlpha = static_cast< float >( a );
    };


    inline float visualAlpha() const {
        return mAlpha;
    };




    /**
    * @return Размер спрайта.
    */
    static typelib::size2Int_t  sizeSprite( const std::string&  sprite );




    /**
    * @return Координаты для позиционирования спрайта по центру.
    */
    static typelib::coord2Int_t  centerSprite( const std::string&  sprite );




private:
    typelib::coord2Int_t  mCoord;
    float                 mRotation;
    float                 mAlpha;




protected:
    static std::unique_ptr< ManagerSprite >  mManagerSprite;
};



} // arkanoid
