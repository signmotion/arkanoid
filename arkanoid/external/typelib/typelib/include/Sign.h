#pragma once

#include "../configure.h"
#include <assert.h>
#include <memory>
#include <string>
#include <boost/algorithm/string/predicate.hpp>
//#include <boost/algorithm/string/classification.hpp>
#include <boost/functional/hash.hpp>



namespace typelib {

template< std::size_t N = 30 > class Sign;

}




namespace boost {

// ��� ������ ��������� boost::unordered_set � ��.
std::size_t hash_value( const typelib::Sign<>& a );

} // boost




namespace std {

std::ostream& operator<<( std::ostream&, const typelib::Sign<>& );

} // std





namespace typelib {


/**
* �����.
* ������������ ��� ����������� ������������� �������� �� ����� ����.
* �� ����� �������� �� ����� ��� N �������� (�� ���������� std::string
* ��� �������� ����� � ����� ���������).
*
* ��������������� ����. �������� ��� �����:
*   . ������
*   # ���� ������� (�����)
*   @ ��������
* ��� ����� ������������ � ���-�� �������� ��� ������������ ��������� �����.
*/
template< std::size_t N >
class Sign {
public:
    /**
    * ������.
    */
    typedef std::shared_ptr< Sign >  Ptr;
    typedef std::unique_ptr< Sign >  UPtr;


public:

    inline Sign() {
        std::memset( &mName[0], '\0', (N + 1) );
    }



    explicit inline Sign( const std::string& name ) {
        assert( !name.empty() && "����� �� ������ ���� ������." );
        assert( (name.length() <= N) && "����� �� ������ ��������� ����� N ��������." );
        assert( !( boost::contains( name, " " ) || boost::contains( name, "\t" ) || boost::contains( name, "\n" ) )
            && "����� �� ����� ���� ���������� �������� � �� ������ ��������� ��." );

        // �������� ������, �� ������� �������� �� ����� ���������� ������
        std::memcpy( &mName[0], name.c_str(), N );
        mName[N] = '\0';
    }




    /**
    * @return ������������ ����� �������� �����.
    */
    static inline std::size_t maxLength() {
        return N;
    }



    /**
    * @return ������� ����� �������� �����.
    */
    inline std::size_t length() const {
        return std::strlen( name() );
    }



    inline char const* name() const {
        return &mName[0];
    }


    inline void name( const std::string& s ) {
        // �������� ������, ������, �� ������� �������� �� ����� ���������� ������
        std::memcpy( &mName[0], name.c_str(), N );
        /* - ��� ������� � ������������.
        mName[N] = '\0';
        */
    }



    /**
    * @return ������ �����.
    */
    inline bool empty() const {
        return (*this == SPACE());
    }


    
    inline char operator[]( std::size_t i ) const {
        return mName[i];
    }

    
    inline char& operator[]( std::size_t i ) {
        return mName[i];
    }

    

    inline Sign<>& operator=( const std::string& s ) {
        assert( (s.length() <= N) && "����� �� ������ ��������� ����� N ��������." );
        std::memcpy( &mName[0], name.c_str(), N );
        mName[ s.length ] = '\0';
        return *this;
    }


    /**
    * �������������� ������ � std::string.
    */
    inline const std::string operator()() const {
        return static_cast< std::string >( mName );
    }



    inline bool operator==( const Sign<>& b ) const {
        return (strcmp( &mName[0], b.name() ) == 0);
    }



    inline bool operator==( const std::string& b ) const {
        return (*this == Sign<>( b ));
    }



    inline bool operator==( const char* b ) const {
        return (*this == static_cast< std::string >( b ));
    }



    inline bool operator!=( const Sign<>& b ) const {
        return (strcmp( &mName[0], b.name() ) != 0);
    }



    inline bool operator!=( const std::string& b ) const {
        return (*this != Sign<>( b ));
    }



    inline bool operator!=( const char* b ) const {
        return (*this != static_cast< std::string >( b ));
    }



    inline bool operator>( const Sign<>& b ) const {
        return (strcmp( &mName[0], b.name() ) > 0);
    }

    

    inline bool operator<( const Sign<>& b ) const {
        return (strcmp( &mName[0], b.name() ) < 0);
    }
    



    /**
    * ������� (����� �� ���������).
    */
    //const static Sign<> SPACE;
    static inline Sign<>  SPACE() {
        //return Sign<>( "." );
        // @tip http://rsdn.ru/forum/cpp.applied/4771369.flat.aspx
        static const Sign<> r( "." );
        return r;
    }




private:
    /**
    * �������� �����.
    *
    * @todo optimize? ������������� ������.
    */
    char mName[N + 1];
    

    friend std::size_t boost::hash_value( const typelib::Sign<>& );

};




} // typelib







namespace boost {

inline std::size_t hash_value( const typelib::Sign<>& s ) {

    std::size_t seed = 0;
    for (std::size_t i = 0; s.mName[i] != '\0'; ++i) {
        hash_combine( seed, s.mName[i] );
    }

    return seed;
}

} // boost







namespace std {


inline std::ostream& operator<<( std::ostream& out, const typelib::Sign<>& s ) {
    out << "\"" << s.name() << "\"";
    return out;
}


} // std
