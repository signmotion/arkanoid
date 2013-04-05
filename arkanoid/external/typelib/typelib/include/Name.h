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

// ��� ������ ��������� boost::unordered_set � ��.
std::size_t hash_value( const typelib::Name& );

} // boost



namespace std {

bool operator==( const std::string&, const typelib::Name& );
std::ostream& operator<<( std::ostream&, const typelib::Name& );

} // std





namespace typelib {


/**
* ��������... ����-������.
* ������ �������� �� ������ ������.
* ��������� � ������ ������ Name �������� ��������� � ���-�� �����������.
* ��� ������ ����� ����� ���� ������� ��������� ���������.
*/
class Name {
public:
    /**
    * ������.
    */
    typedef std::shared_ptr< Name >  Ptr;
    typedef std::unique_ptr< Name >  UPtr;


public:
    /**
    * ������ �������� �� *�����* �����.
    */
    typedef boost::unordered_set< std::string >  name_t;



    inline Name() {
    }



    /**
    * ����������� ������, ����� ���������� ������� ���� ���� ��������.
    */
    inline Name( const std::string& name, const typelib::lang_t& lang = typelib::LANG_DEFAULT_TYPELIB ) {
        add( &mList, name, lang );
    }



    virtual inline ~Name() {
    };




    /**
    * @return ��� �� ������ ��������.
    */
    inline bool empty() const {
        return mList.empty();
    }



    /**
    * @return ������ �� �������� ������ ��������.
    */
    inline boost::unordered_map< typelib::lang_t, name_t > const&  list() const {
        return mList;
    }



    /**
    * @return ������ �������� ��� ����������� �����. ������, ���� �������� ���.
    */
    inline name_t operator[]( const typelib::lang_t& lang ) const {
        assert( (lang.length() == 3)
            && "���������� ������� ���� � ��������� ISO 639-3 (3 �������). http://ru.wikipedia.org/wiki/%D0%9A%D0%BE%D0%B4%D1%8B_%D1%8F%D0%B7%D1%8B%D0%BA%D0%BE%D0%B2" );
        auto ftr = mList.find( lang );
        return (ftr == mList.cend())
            // �������� ��� ����� ����� ����� �� ���������
          ? name_t()
          : ftr->second;
    }



    /**
    * ��������� �������� ��� ���������� �����. ���� �������� ��� ����� ����� ���
    * �������, ���. ��� ���������.
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
    * @return ��������� ��� ������� ����� ���. ��������������� ��� �����.
    */
    inline bool operator==( const std::string& name ) const {
        // �����
        for (auto ltr = mList.cbegin(); ltr != mList.cend(); ++ltr) {
            // �������� ��� �����
            auto ftr = ltr->second.find( name );
            if (ftr != ltr->second.cend()) {
                return true;
            }
        }

        return false;
    }




    /**
    * @return ���-��� ������� �������� �������� �� ����� 'lang',
    *         ��������������� ��� �������� ������ �������� ��� �����������
    *         �� ��������� �������.
    *         ����������, ���� ���� �� ������.
    *         ����������, ���� ��� ���������� ����� ��� ���������� ���-�� ����.
    *
    * @info ����� ������� ���� ��������� �� ������������ ��������� C++ �
    *       CouchDB. �������� ��� � �� �������. ����� ���������� �����������
    *       ����� � ��������� �� ������������� ���������, ���� ������ �������
    *       ������ �� ������� ������� (JavaScript) � ����� (C++), ������������
    *       ���������� ���. ����� ��������! � ���� ������ �������� �������.
    *
    * @see typelib::hash::searchHash()
    */
    inline std::string searchHash( const lang_t& lang ) const {
        const name_t nt = ( *this )[ lang ];
        assert( !nt.empty() && "��� �������� ��� ���������� �����." );

        // ����� ���� ������� �������� ��������
        // @todo fine ������������� �� ����.
        const std::string& s = *nt.cbegin();

        return typelib::hash::searchHash( s );
    }





protected:
    /**
    * ��������������� �����.
    */
    static inline void add(
        boost::unordered_map< typelib::lang_t, name_t >*  l,
        const std::string& name,
        const typelib::lang_t& lang
    ) {
        assert( l && "��������� ������." );
        assert( !name.empty() && "�������� �� ������ ���� ������." );
        assert( (lang.length() == 3)
            && "���������� ������� ���� � ��������� ISO 639-3 (3 �������). http://ru.wikipedia.org/wiki/%D0%9A%D0%BE%D0%B4%D1%8B_%D1%8F%D0%B7%D1%8B%D0%BA%D0%BE%D0%B2" );
        // ���� ���� ����, �� ��������� ��� ���������
        auto ri = l->insert( std::make_pair( lang, name_t() ) );
        // �������� �������������� �� �����
        ri.first->second.insert( name );
    }





protected:
    /**
    * ������ �������� �� *������* ������.
    */
    boost::unordered_map< typelib::lang_t, name_t >  mList;

};



} // typelib






namespace boost {

inline std::size_t hash_value( const typelib::Name& a ) {
    //return boost::hash_value( a.list.cbegin(), a.list.cend() );

    std::size_t seed = 0;
    // �����
    for (auto ltr = a.list().cbegin(); ltr != a.list().cend(); ++ltr) {
        boost::hash_combine( seed, ltr->first );
        // �������� ��� �����
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
* (!) �������� �������� �� ���-��������.
* ����� ���������� ��� ������������� Name � ���������� STL.
*/
inline bool operator<( const typelib::Name& a, const typelib::Name& b ) {
    return (boost::hash_value( a ) < boost::hash_value( b ));
}




inline std::ostream& operator<<( std::ostream& out, const typelib::Name& name ) {
    // JSON - c�. ���������� ��� operator<<() � configure.h
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
