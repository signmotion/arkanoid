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
* Для работы с данными в формате JSON.
*
* @use http://cajun-jsonapi.sourceforge.net
*
* @todo ? Добавить упаковку данных http://habrahabr.ru/post/130112
*       См. комментарии о целесообразности такой оптимизации
*       и https://issues.apache.org/jira/browse/COUCHDB-702
*/


namespace typelib {
    namespace json {

/**
* Данные, представленные в виде строки в формате JSON.
*/
typedef std::string  string_t;


/**
* Типы для работы с json-структурой.
* Просто, удобно, эффективно.
*
* @see http://json.org
*
* @todo fine optimize Заменить boost::shared_ptr на std::shared_ptr.
*//* - @todo Ввести новые типы. Использовать их вместо CouchFine::Variant.
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
* На случай, когда внешние модули используют boost::shared_ptr<>.
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


    // На случай, когда внешние модули используют boost::shared_ptr<>.
    inline Variant( boost::shared_ptr< boost::any > a ) :
        std::shared_ptr< boost::any >( a.get(), boost::bind( &_doRelease< boost::any >, a, _1 ) )
    {
    }


    inline Variant( boost::any* a ) : std::shared_ptr< boost::any >( a ) {
    }



    /**
    * @return Распарсенная строка JSON.
    *//* - Заменено на конструктор. См. ниже.
    static inline Variant valueOf( const string_t& s ) {
        Variant v;
        parse( &v, s );
        return v;
    }
    */


    /**
    * Распознаёт строку в формате JSON.
    *
    * #! Если строка не распознана, создаётся неинициализированный объект. После
    *    вызова конструктора обязательно проверяем Variant::undefined().
    *
    * Позволяет писать
    *   Variant json = "{ 'alpha': 0.5 }";
    *
    * Понимает, когда строка содержит не обёрнутый в '{}' объект.
    *
    * Понимает, когда строка содержит однострочные комментарии '//'.
    *   #! Последовательность '//' внутри строк считается комментарием.
    *
    * Понимает, когда вместо двойных кавычек используются одинарные.
    *   Пример:
    *     { 'NaCl': 'FFFFFFFF',  'H2O': '0000FFFF' }
    *   будет воспринято как
    *     { "NaCl": "FFFFFFFF",  "H2O": "0000FFFF" }
    *
    *  @todo Проверяет только "независимые понимания". Добавить комбинации.
    *        Например, есть примечания И вместо стандартных JSON-кавычек
    *        исп. одинарные.
    */
    Variant( const string_t& );




    /**
    * @return true, если Variant не инициализирован json-объектом.
    */
    bool undefined() const;




    /**
    * Доступ к объектам и спискам json-структуры по имени и номеру.
    * Если элемент не найден, возвращает ссылку на пустой Variant().
    *
    * #! При возврате по ссылке меняет содержимое json-объекта, наполняя
    *    его пустыми значениями.
    *
    * @todo fine optimize Метод для удаления пустых значений compact().
    *
    * Примеры:
    *   o["person"]["name"]
    *   coord[ 0u ]
    *   coord[ 1 ]
    *
    * Указание 'u' после цифры требуется по крайней мере для инициализации
    * первого элемента: дальше VC++ 2010 понимает, что за оператор мы хотим
    * вызывать.
    */
    //Variant& operator[]( const std::string& ); - создаёт неоднозначность.
    Variant& operator[]( const char* );
    //const Variant operator[]( const std::string& ) const; - создаёт неоднозначность.
    const Variant operator[]( const char* ) const;
    Variant& operator[]( std::size_t );
    /* - @todo fine Не могут быть константами: поиск дополняет структуру пустыми Variant'ами. Сделать константами левую часть.
    Variant const& operator[]( const char* ) const;
    Variant const& operator[]( const std::size_t ) const;
    */




    /**
    * @return Значение поля объекта или значение по умолчанию, если заданного
    *         поля у объекта нет.
    */
    template< typename T >
    T at( const std::string& field,  T def ) const;




    /**
    * Умеем собирать объекты любого типа.
    */
    template< typename T >
    Variant& operator=( T );



    /**
    * @return true, если объект содержит Object и присутствует
    *         поле с заданным именем.
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
    * @return Распознанная строка JSON.
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
* Умеет приводить структуры к типам coord_t, relCoord_t и пр. с
* помощью static_cast<>().
*/
struct Array : public std::deque< Variant > {

    operator relCoordInt_t () const;

};


typedef std::shared_ptr< Array >  ArrayPtr_t;





struct Object : public std::map< std::string, Variant > {

    /* - Лишнее. Дублирует родителя.
    inline Variant& operator[]( const std::string& k ) {
        return at( k );
    }

    inline Variant const& operator[]( const std::string& k ) const {
        return at( k );
    }
    */


    /**
    * @return Объект содержит указанное поле.
    */
    inline bool has( const std::string& name ) const {
        return (this->find( name ) != this->cend());
    }


    /**
    * @return Объект содержит указанное поле.
    *//* - Нельзя возвращать ссылку внутри объекта или значение по умолчанию.
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
* @return Значение, обёрнутое в Variant.
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
* @return Распарсенная строка JSON.
*
* @alias Variant( jsonString )
*
* #! Для проверки, что содержимое файла было распознано, следует
*    вызвать Variant::undefined().
*/
static inline Variant parse( const string_t& s ) {
    return Variant( s );
}






/**
* @return Загруженная из файла и распарсенная строка JSON.
*
* # Использует возможности Variant().
*
* #! Для проверки, что содержимое файла было распознано, следует
*    вызвать Variant::undefined().
*/
static Variant load( const std::string& file, const std::string& path = "" );





/**
* @return Распарсенная строка JSON. Все значения представлены
*         как std::string.
*//* @todo ...
typedef std::map< std::string, std::string >  variantString_t;
inline variantString_t parseAsString( const string_t& s ) {

    assert( false && "@todo Не реализовано." );

}
*/






/**
* @return Строка JSON, из которой удалены однострочные комментарии '//'.
*
* #! Последовательность '//' внутри строк считается комментарием.
*/
static std::string noComment( const std::string& );






/**
* Преобразует строку JSON в удобный для чтения человеком вид.
*/
static void print( std::ostream& out, const string_t& s );




    } // json
} // typelib







#include "json.inl"
