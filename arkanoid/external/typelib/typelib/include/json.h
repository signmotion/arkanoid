#pragma once

#include "../configure.h"
#include "coord.h"
#include "../external/cajun/json/reader.h"
#include "../external/cajun/json/writer.h"
#include "../external/cajun/json/elements.h"
#include "../external/cajun/json/visitor.h"
#include <sstream>
#include <assert.h>
#include <string>
#include <deque>
#include <fstream>
#include <regex>
#include <boost/algorithm/string/replace.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/any.hpp>
#include <boost/bind.hpp>


/**
* ��� ������ � ������� � ������� JSON.
*
* @use http://cajun-jsonapi.sourceforge.net
*
* @todo ? �������� �������� ������ http://habrahabr.ru/post/130112
*       ��. ����������� � ���������������� ����� �����������
*       � https://issues.apache.org/jira/browse/COUCHDB-702
*/


namespace typelib {
    namespace json {

/**
* ������, �������������� � ���� ������ � ������� JSON.
*/
typedef std::string  string_t;


/**
* ���� ��� ������ � json-����������.
* ������, ������, ����������.
*
* @see http://json.org
*
* @todo fine optimize �������� boost::shared_ptr �� std::shared_ptr.
*//* - @todo ������ ����� ����. ������������ �� ������ CouchFine::Variant.
typedef boost::shared_ptr< boost::any >     variant_t;
typedef std::deque< variant_t >             array_t;
typedef std::map< std::string, variant_t >  object_t;
*/
struct Variant;
struct Array;
struct Object;


template< typename T > static Variant cjv( T value );
template< typename T > static Variant createVariant( T value );



/**
* �� ������, ����� ������� ������ ���������� boost::shared_ptr<>.
*
* @source http://stackoverflow.com/questions/6326757/conversion-from-boostshared-ptr-to-stdshared-ptr
*/
template<typename T>
inline void _doRelease( typename boost::shared_ptr< T > const&, T* ) {
}



struct Variant :
    public std::shared_ptr< boost::any >,
    private ::json::ConstVisitor
{
    inline Variant() : std::shared_ptr< boost::any >() {
    }


    inline Variant( std::shared_ptr< boost::any > a ) : std::shared_ptr< boost::any >( a ) {
    }


    // �� ������, ����� ������� ������ ���������� boost::shared_ptr<>.
    inline Variant( boost::shared_ptr< boost::any > a ) :
        std::shared_ptr< boost::any >( a.get(), boost::bind( &_doRelease< boost::any >, a, _1 ) )
    {
    }


    inline Variant( boost::any* a ) : std::shared_ptr< boost::any >( a ) {
    }



    /**
    * @return ������������ ������ JSON.
    *//* - �������� �� �����������. ��. ����.
    static inline Variant valueOf( const string_t& s ) {
        Variant v;
        parse( &v, s );
        return v;
    }
    */


    /**
    * ��������� ������ � ������� JSON.
    *
    * #! ���� ������ �� ����������, �������� �������������������� ������. �����
    *    ������ ������������ ����������� ��������� Variant::undefined().
    *
    * ��������� ������
    *   Variant json = "{ 'alpha': 0.5 }";
    *
    * ��������, ����� ������ �������� �� �������� � '{}' ������.
    *
    * ��������, ����� ������ �������� ������������ ����������� '//'.
    *   #! ������������������ '//' ������ ����� ��������� ������������.
    *
    * ��������, ����� ������ ������� ������� ������������ ���������.
    *   ������:
    *     { 'NaCl': 'FFFFFFFF',  'H2O': '0000FFFF' }
    *   ����� ���������� ���
    *     { "NaCl": "FFFFFFFF",  "H2O": "0000FFFF" }
    *
    *  @todo ��������� ������ "����������� ���������". �������� ����������.
    *        ��������, ���� ���������� � ������ ����������� JSON-�������
    *        ���. ���������.
    */
    Variant( const string_t& );




    /**
    * @return true, ���� Variant �� ��������������� json-��������.
    */
    bool undefined() const;




    /**
    * ������ � �������� � ������� json-��������� �� ����� � ������.
    * ���� ������� �� ������, ���������� ������ �� ������ Variant().
    *
    * #! ��� �������� �� ������ ������ ���������� json-�������, ��������
    *    ��� ������� ����������.
    *
    * @todo fine optimize ����� ��� �������� ������ �������� compact().
    *
    * �������:
    *   o["person"]["name"]
    *   coord[ 0u ]
    *   coord[ 1 ]
    *
    * �������� 'u' ����� ����� ��������� �� ������� ���� ��� �������������
    * ������� ��������: ������ VC++ 2010 ��������, ��� �� �������� �� �����
    * ��������.
    */
    //Variant& operator[]( const std::string& ); - ������ ���������������.
    Variant& operator[]( const char* );
    //const Variant operator[]( const std::string& ) const; - ������ ���������������.
    const Variant operator[]( const char* ) const;
    Variant& operator[]( std::size_t );
    /* - @todo fine �� ����� ���� �����������: ����� ��������� ��������� ������� Variant'���. ������� ����������� ����� �����.
    Variant const& operator[]( const char* ) const;
    Variant const& operator[]( const std::size_t ) const;
    */




    /**
    * @return �������� ���� ������� ��� �������� �� ���������, ���� ���������
    *         ���� � ������� ���.
    */
    template< typename T >
    T at( const std::string& field,  T def ) const;




    /**
    * ����� �������� ������� ������ ����.
    */
    template< typename T >
    Variant& operator=( T );



    /**
    * @return true, ���� ������ �������� Object � ������������
    *         ���� � �������� ������.
    */
    bool has( const std::string& field ) const;


    operator Array () const;

    operator Object () const;

    operator bool () const;

    operator std::string () const;

    operator int () const;

    operator std::size_t () const;

    operator float () const;

    operator relCoordInt_t () const;



    static const Variant ZERO();



private:
    /**
    * @return ������������ ������ JSON.
    *
    * @throw ::json::Exception
    */
    static void parse( Variant*, const string_t& );

    //static void parse( Variant* v, const ::json::UnknownElement& b );
    //static void parse( Variant* v, const ::json::Object& b );


    template< typename ElementTypeT >
    static void get( Variant*, const ElementTypeT& );

    void get( const ::json::Object& );
    void get( const ::json::Array& );
    void get( const ::json::String& );
    void get( const ::json::Number& );
    void get( const ::json::Boolean& );
    void get( const ::json::Null& );
    void get( const ::json::UnknownElement& );

    virtual void Visit( const ::json::Array& );
    virtual void Visit( const ::json::Object& );
    virtual void Visit( const ::json::Number& );
    virtual void Visit( const ::json::String& );
    virtual void Visit( const ::json::Boolean& );
    virtual void Visit( const ::json::Null& );

};





/**
* ����� ��������� ��������� � ����� coord_t, relCoord_t � ��. �
* ������� static_cast<>().
*/
struct Array : public std::deque< Variant > {

    operator relCoordInt_t () const;

};


typedef std::shared_ptr< Array >  ArrayPtr_t;





struct Object : public std::map< std::string, Variant > {

    /* - ������. ��������� ��������.
    inline Variant& operator[]( const std::string& k ) {
        return at( k );
    }

    inline Variant const& operator[]( const std::string& k ) const {
        return at( k );
    }
    */


    /**
    * @return ������ �������� ��������� ����.
    */
    inline bool has( const std::string& name ) const {
        return (this->find( name ) != this->cend());
    }


    /**
    * @return ������ �������� ��������� ����.
    *//* - ������ ���������� ������ ������ ������� ��� �������� �� ���������.
    template< typename T >
    inline T const& at( const std::string& name, const T& defaultValue ) const {
        const auto ftr = find( name );
        return (ftr == this->cend())
            ? defaultValue ...
    }
    */
};


typedef std::shared_ptr< Object >  ObjectPtr_t;






/**
* @return ��������, �������� � Variant.
*
* @alias createVariant()
*/
template< typename T >
static inline Variant cjv( T value ) {
    return Variant( new boost::any( value ) );
}


// @alias cjv()
template< typename T >
static inline Variant createVariant( T value ) {
    return cjv( value );
}






/**
* @return ������������ ������ JSON.
*
* @alias Variant( jsonString )
*
* #! ��� ��������, ��� ���������� ����� ���� ����������, �������
*    ������� Variant::undefined().
*/
static inline Variant parse( const string_t& s ) {
    return Variant( s );
}






/**
* @return ����������� �� ����� � ������������ ������ JSON.
*
* # ���������� ����������� Variant().
*
* #! ��� ��������, ��� ���������� ����� ���� ����������, �������
*    ������� Variant::undefined().
*/
static Variant load( const std::string& file, const std::string& path = "" );





/**
* @return ������������ ������ JSON. ��� �������� ������������
*         ��� std::string.
*//* @todo ...
typedef std::map< std::string, std::string >  variantString_t;
inline variantString_t parseAsString( const string_t& s ) {

    assert( false && "@todo �� �����������." );

}
*/






/**
* @return ������ JSON, �� ������� ������� ������������ ����������� '//'.
*
* #! ������������������ '//' ������ ����� ��������� ������������.
*/
static std::string noComment( const std::string& );






/**
* ����������� ������ JSON � ������� ��� ������ ��������� ���.
*/
static void print( std::ostream& out, const string_t& s );




    } // json
} // typelib







#include "json.inl"
