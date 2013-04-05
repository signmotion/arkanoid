#pragma once

/**
* Генератор случайных чисел.
*/

#include <ctime>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>


namespace typelib {


template< typename Number, typename GT = boost::mt19937 >
class Random {
public:
    /**
    * Ссылки.
    */
    typedef std::shared_ptr< Random >  Ptr;
    typedef std::unique_ptr< Random >  UPtr;


    const Number a;
    const Number b;

    const std::size_t seed;


    inline Random(
        Number a,
        Number b,
        std::size_t seed  // = static_cast< std::size_t >( std::time( nullptr ) )
    ) :
        a( a ),
        b( b ),
        seed( seed ),
        generator( seed ),
        gInt(
            generator,
            dInt_t( static_cast< int >( a ), static_cast< int >( b ) )
        )
    {
        assert( (a < b) && "Не верный диапазон инициализации." );
    }



    /**
    * @return След. случайное число.
    */
    inline Number next() {
        return static_cast< Number >( gInt() );
    }



private:
    typedef boost::uniform_int< int >  dInt_t;
    typedef boost::variate_generator< GT&, dInt_t >  gInt_t;



private:
    GT      generator;
    gInt_t  gInt;
};






/**
* @see template< typename Number, typename GT = boost::mt19937 > class Random
*/
template< typename GT >
class Random< float, GT > {
public:
    /**
    * Ссылки.
    */
    typedef std::shared_ptr< Random >  Ptr;
    typedef std::unique_ptr< Random >  UPtr;


    const float a;
    const float b;

    const std::size_t seed;


    inline Random(
        float a,
        float b,
        std::size_t seed  // = static_cast< std::size_t >( std::time( nullptr ) )
    ) :
        a( a ),
        b( b ),
        seed( seed ),
        generator( seed ),
        gReal( generator,  dReal_t( a, b ) )
    {
        assert( (a < b) && "Не верный диапазон инициализации." );
    }



    inline float next() {
        return gReal();
    }



private:
    typedef boost::uniform_real< float >  dReal_t;
    typedef boost::variate_generator< GT&, dReal_t >  gReal_t;



private:
    GT       generator;
    gReal_t  gReal;
};






/**
* @see template< typename Number, typename GT = boost::mt19937 > class Random
*/
template< typename GT >
class Random< double, GT > {
public:
    /**
    * Ссылки.
    */
    typedef std::shared_ptr< Random >  Ptr;
    typedef std::unique_ptr< Random >  UPtr;


    const double a;
    const double b;

    const std::size_t seed;


    inline Random(
        double a,
        double b,
        std::size_t seed  // = static_cast< std::size_t >( std::time( nullptr ) )
    ) :
        a( a ),
        b( b ),
        seed( seed ),
        generator( seed ),
        gReal( generator,  dReal_t( a, b ) )
    {
        assert( (a < b) && "Не верный диапазон инициализации." );
    }



    inline double next() {
        return gReal();
    }



private:
    typedef boost::uniform_real< double >  dReal_t;
    typedef boost::variate_generator< GT&, dReal_t >  gReal_t;



private:
    GT       generator;
    gReal_t  gReal;
};


} // typelib
