#pragma once

#include "../configure.h"
#include "other.h"
#include "hash.h"
#include <assert.h>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/functional/hash.hpp>


namespace typelib {

class Name;

}



namespace boost {

// Для работы коллекций boost::unordered_set и пр.
std::size_t hash_value( const typelib::Name& );

} // boost



namespace std {

bool operator==( const std::string&, const typelib::Name& );
std::ostream& operator<<( std::ostream&, const typelib::Name& );

} // std





namespace typelib {


/**
* Название... чего-угодно.
* Хранит названия на разных языках.
* Собранные в рамках одного Name названия выступают в кач-ве псевдонимов.
* Для одного языка может быть указано несколько синонимов.
*/
class Name {
public:
    /**
    * Ссылки.
    */
    typedef std::shared_ptr< Name >  Ptr;
    typedef std::unique_ptr< Name >  UPtr;


public:
    /**
    * Список названий на *одном* языке.
    */
    typedef boost::unordered_set< std::string >  name_t;



    inline Name() {
    }



    /**
    * Конструктор удобен, когда достаточно хранить лишь одно название.
    */
    inline Name( const std::string& name, const typelib::lang_t& lang = typelib::LANG_DEFAULT_TYPELIB ) {
        add( &mList, name, lang );
    }



    virtual inline ~Name() {
    };




    /**
    * @return Нет ни одного названия.
    */
    inline bool empty() const {
        return mList.empty();
    }



    /**
    * @return Ссылка на хранимый список названий.
    */
    inline boost::unordered_map< typelib::lang_t, name_t > const&  list() const {
        return mList;
    }



    /**
    * @return Список названий для конкретного языка. Пустой, если названий нет.
    */
    inline name_t operator[]( const typelib::lang_t& lang ) const {
        assert( (lang.length() == 3)
            && "Необходимо указать язык в стандарте ISO 639-3 (3 символа). http://ru.wikipedia.org/wiki/%D0%9A%D0%BE%D0%B4%D1%8B_%D1%8F%D0%B7%D1%8B%D0%BA%D0%BE%D0%B2" );
        auto ftr = mList.find( lang );
        return (ftr == mList.cend())
            // названий для этого языка может не оказаться
          ? name_t()
          : ftr->second;
    }



    /**
    * Добавляет название для указанного языка. Если название для этого языка уже
    * имеется, ост. без изменений.
    */
    inline void add( const std::string& name, const typelib::lang_t& lang = typelib::LANG_DEFAULT_TYPELIB ) {
        add( &mList, name, lang );
    }



    inline bool operator()( const Name& a ) const {
        return (*this == a);
    }



    inline bool operator==( const Name& a ) const {
        return (boost::hash_value( *this ) == boost::hash_value( a ));
    }



    /**
    * @return Указанное имя найдено среди имён. Просматриваются все языки.
    */
    inline bool operator==( const std::string& name ) const {
        // языки
        for (auto ltr = mList.cbegin(); ltr != mList.cend(); ++ltr) {
            // названия для языка
            auto ftr = ltr->second.find( name );
            if (ftr != ltr->second.cend()) {
                return true;
            }
        }

        return false;
    }




    /**
    * @return Хеш-код первого варианта названия на языка 'lang',
    *         предназначенный для быстрого поиска названий вне зависимости
    *         от кодировки системы.
    *         Исключение, если язык не найден.
    *         Исключение, если для найденного языка нет указанного кол-ва фраз.
    *
    * @info Много времени было потрачено на согласование кодировок C++ и
    *       CouchDB. Побороть так и не удалось. Чтобы обеспечить полноценный
    *       поиск в хранилище по кириллическим названиям, было решено создать
    *       методы на стороне сервера (JavaScript) и здесь (C++), возвращающие
    *       одинаковый код. Конец мученьям! И даже должно работать быстрее.
    *
    * @see typelib::hash::searchHash()
    */
    inline std::string searchHash( const lang_t& lang ) const {
        const name_t nt = ( *this )[ lang ];
        assert( !nt.empty() && "Нет названий для указанного языка." );

        // могут быть пустыми варианты названий
        // @todo fine Предупреждать об этом.
        const std::string& s = *nt.cbegin();

        return typelib::hash::searchHash( s );
    }





protected:
    /**
    * Вспомогательный метод.
    */
    static inline void add(
        boost::unordered_map< typelib::lang_t, name_t >*  l,
        const std::string& name,
        const typelib::lang_t& lang
    ) {
        assert( l && "Ожидается список." );
        assert( !name.empty() && "Название не должно быть пустым." );
        assert( (lang.length() == 3)
            && "Необходимо указать язык в стандарте ISO 639-3 (3 символа). http://ru.wikipedia.org/wiki/%D0%9A%D0%BE%D0%B4%D1%8B_%D1%8F%D0%B7%D1%8B%D0%BA%D0%BE%D0%B2" );
        // если язык есть, он останется без изменений
        auto ri = l->insert( std::make_pair( lang, name_t() ) );
        // название продублировано не будет
        ri.first->second.insert( name );
    }





protected:
    /**
    * Список названий на *разных* языках.
    */
    boost::unordered_map< typelib::lang_t, name_t >  mList;

};



} // typelib






namespace boost {

inline std::size_t hash_value( const typelib::Name& a ) {
    //return boost::hash_value( a.list.cbegin(), a.list.cend() );

    std::size_t seed = 0;
    // языки
    for (auto ltr = a.list().cbegin(); ltr != a.list().cend(); ++ltr) {
        boost::hash_combine( seed, ltr->first );
        // названия для языка
        for (auto ntr = ltr->second.cbegin(); ntr != ltr->second.cend(); ++ntr) {
           boost::hash_combine( seed, *ntr );
        }
    }

    return seed;
}

} // boost






namespace std {

/**
* @see Name::operator==()
*/
inline bool operator==( const std::string& search, const typelib::Name& dest ) {
    return (dest == search);
}




/**
* (!) Сравнене проходит по хеш-значению.
* Метод реализован для использования Name в коллекциях STL.
*/
inline bool operator<( const typelib::Name& a, const typelib::Name& b ) {
    return (boost::hash_value( a ) < boost::hash_value( b ));
}




inline std::ostream& operator<<( std::ostream& out, const typelib::Name& name ) {
    // JSON - cм. соглашение для operator<<() в configure.h
    out << "{ ";
    const int npLang = name.list().size() - 1;
    for (auto ltr = name.list().cbegin(); ltr != name.list().cend(); ++ltr) {
        const typelib::lang_t& lang = ltr->first;
        out << "\"" << lang << "\": [ ";
        const int npName = ltr->second.size() - 1;
        for (auto itr = ltr->second.cbegin(); itr != ltr->second.cend(); ++itr) {
            out << "\"" << *itr << "\"";
            if (std::distance( ltr->second.cbegin(), itr ) < npName) {
                out << ", ";
            }
        }
        out << " ]";
        if (std::distance( name.list().cbegin(), ltr ) < npLang) {
            out << ", ";
        }
    }
    out << " }";

    return out;
}


} // std
