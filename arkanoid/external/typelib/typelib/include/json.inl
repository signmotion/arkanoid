namespace typelib {
    namespace json {


inline Variant::Variant( const string_t& s ) : std::shared_ptr< boost::any >() {
    try {
        // идеальный JSON-объект
        parse( this, s );

    } catch ( const ::json::Exception& ) {
        // Понимаем, когда строка содержит не обёрнутый в '{}' объект
        // плюс однострочные комментарии '//'
        try {
            const ::std::string ps = "{" + noComment( s ) + "}";
            parse( this, ps );

        } catch ( const ::json::Exception& ) {
            // Понимаем, когда строка содержит примечания
            try {
                const ::std::string ps = noComment( s );
                assert( !(ps.empty() && !s.empty())
                    && "После удаления комментариев получили пустое содержание." );
                parse( this, ps );

            } catch ( const ::json::Exception& ) {
                // Понимаем когда вместо двойных кавычек используются одинарные
                try {
                    ::std::string ps = s;
                    ::std::replace( ps.begin(), ps.end(), '\'', '"' );
                    parse( this, ps );

                } catch ( const ::json::Exception& ex ) {
                    // И, когда варианты выше не подошли, понимаем, что
                    // придётся оставить объект неинициализированным.
                    std::cerr << "(!) " << std::endl << ex.what() << std::endl;
                    throw ex;
                }
            }
        }
    }

}

        
        
        
inline bool Variant::undefined() const {
    return this->_Get() ? false : true;
}




inline Variant& Variant::operator[]( const char* k ) {
    // ключ - строка, значит этот json-элемент - Object
    
    // создаём, если объекта нет
    if ( this->undefined() ) {
        *this = cjv( Object() );
    }

    Object& o = boost::any_cast< Object& >( **this );
    auto ftr = o.find( k );
    if (ftr == o.cend()) {
        ftr = o.insert( std::make_pair( k, Variant() ) ).first;
    }

    return ftr->second;
}




inline const Variant  Variant::operator[]( const char* k ) const {
    // этот элемент существует?
    if ( this->undefined() ) {
        return Variant();
    }

    if ( (*this)->type() != typeid( Object ) ) {
        return Variant();
    }

    Object& o = boost::any_cast< Object& >( **this );
    auto ftr = o.find( k );

    return (ftr == o.cend()) ? Variant() : ftr->second;
}




inline Variant& Variant::operator[]( std::size_t i ) {
    // ключ - число, значит этот json-элемент - Array
    
    // создаём, если списка нет
    if ( this->undefined() ) {
        *this = cjv( Array() );
    }

    Array& a = boost::any_cast< Array& >( **this );
    /* - @todo fine См. прим. к operator[]( const char*& )
    */
    // доращиваем список до требуемого кол-ва
    for (std::size_t q = a.size(); q <= i; ++q) {
        a.push_back( Variant() );
    }

    return a.at( i );
}





template< typename T >
inline T Variant::at( const std::string& field,  T def = T() ) const {
    const Variant v = ( *this )[ field.c_str() ];
    return v.undefined() ? def : static_cast< T >( v );
}





template< typename T >
inline Variant& Variant::operator=( T v ) {
    *this = cjv( v );
    return *this;
}






inline bool Variant::has( const std::string& field ) const {
    if ( this->undefined() ) {
        return false;
    }

    if ( (*this)->type() != typeid( Object ) ) {
        return false;
    }

    return boost::any_cast< Object >( **this ).has( field );
}





inline Variant::operator Array () const {
    if ( this->undefined() ) {
        return Array();
    }

#ifdef _DEBUG
    const std::string& typeName = (*this)->type().name();
#endif

    assert( ( (*this)->type() == typeid( Array ) )
        && "Элемент является другим типом и не может быть приведён к типу Array." );

    return boost::any_cast< Array >( **this );
}




inline Variant::operator Object () const {
    if ( this->undefined() ) {
        return Object();
    }

#ifdef _DEBUG
    const std::string& typeName = (*this)->type().name();
#endif

    assert( ( (*this)->type() == typeid( Object ) )
        && "Элемент является другим типом и не может быть приведён к типу Object." );

    return boost::any_cast< Object >( **this );
}





inline Variant::operator bool () const {
    if ( this->undefined() ) {
        return false;
    }

    const auto& type = (*this)->type();

#ifdef _DEBUG
    const std::string& typeName = type.name();
#endif

    if (type == typeid( bool ) ) {
        return boost::any_cast< bool >( **this );

    } else if (type == typeid( int ) ) {
        return (boost::any_cast< int >( **this ) != 0);

    } else if (type == typeid( std::size_t ) ) {
        return (boost::any_cast< std::size_t >( **this ) != 0);

    } else if (type == typeid( long ) ) {
        return (boost::any_cast< long >( **this ) != 0);

    } else if (type == typeid( unsigned long ) ) {
        return (boost::any_cast< unsigned long >( **this ) != 0);

    } else if (type == typeid( char ) ) {
        return (boost::any_cast< char >( **this ) != 0);

    } else if (type == typeid( unsigned char ) ) {
        return (boost::any_cast< unsigned char >( **this ) != 0);

    } else if (type == typeid( double ) ) {
        return !empty( boost::any_cast< double >( **this ) );

    } else if (type == typeid( float ) ) {
        return !empty( boost::any_cast< float >( **this ) );

    }

    assert( false && "Элемент является другим типом и не может быть приведён к типу bool." );
    return false;
}




inline Variant::operator std::string () const {
    if ( this->undefined() ) {
        return "";
    }

    const auto& type = (*this)->type();

#ifdef _DEBUG
    const std::string& typeName = type.name();
#endif

    if (type == typeid( std::string ) ) {
        return boost::any_cast< std::string >( **this );

    } else if (type == typeid( const char* ) ) {
        return static_cast< std::string >( boost::any_cast< const char* >( **this ) );

    } else if (type == typeid( double ) ) {
        std::ostringstream ss;
        ss << std::fixed << boost::any_cast< double >( **this );
        return ss.str();

    } else if (type == typeid( int ) ) {
        std::ostringstream ss;
        ss << boost::any_cast< int >( **this );
        return ss.str();

    } else if (type == typeid( std::size_t ) ) {
        std::ostringstream ss;
        ss << boost::any_cast< std::size_t >( **this );
        return ss.str();

    } else if (type == typeid( long ) ) {
        std::ostringstream ss;
        ss << boost::any_cast< long >( **this );
        return ss.str();

    } else if (type == typeid( unsigned long ) ) {
        std::ostringstream ss;
        ss << boost::any_cast< unsigned long >( **this );
        return ss.str();

    } else if (type == typeid( bool ) ) {
        return boost::any_cast< bool >( **this ) ? "true" : "false";

    } else if (type == typeid( char ) ) {
        std::ostringstream ss;
        ss << boost::any_cast< char >( **this );
        return ss.str();

    } else if (type == typeid( unsigned char ) ) {
        std::ostringstream ss;
        ss << boost::any_cast< unsigned char >( **this );
        return ss.str();

    } else if (type == typeid( float ) ) {
        std::ostringstream ss;
        ss << std::fixed << boost::any_cast< float >( **this );
        return ss.str();

    }

    assert( false && "Элемент является другим типом и не может быть приведён к типу std::string." );
    return "";
}




inline Variant::operator int () const {
    if ( this->undefined() ) {
        return 0;
    }

    const auto& type = (*this)->type();

#ifdef _DEBUG
    const std::string& typeName = type.name();
#endif

    if (type == typeid( double ) ) {
        return static_cast< int >( boost::any_cast< double >( **this ) );

    } else if (type == typeid( int ) ) {
        return boost::any_cast< int >( **this );

    } else if (type == typeid( std::size_t ) ) {
        return boost::any_cast< std::size_t >( **this );

    } else if (type == typeid( std::size_t ) ) {
        return boost::any_cast< std::size_t >( **this );

    } else if (type == typeid( long ) ) {
        return static_cast< int >( boost::any_cast< long >( **this ) );

    } else if (type == typeid( unsigned long ) ) {
        return static_cast< int >( boost::any_cast< unsigned long >( **this ) );

    } else if (type == typeid( bool ) ) {
        return boost::any_cast< bool >( **this ) ? 1 : 0;

    } else if (type == typeid( char ) ) {
        return static_cast< int >( boost::any_cast< char >( **this ) );

    } else if (type == typeid( unsigned char ) ) {
        return static_cast< int >( boost::any_cast< unsigned char >( **this ) );

    } else if (type == typeid( float ) ) {
        return static_cast< int >( boost::any_cast< float >( **this ) );

    }

    assert( false && "Элемент является другим типом и не может быть приведён к типу int." );
    return 0;
}




inline Variant::operator std::size_t () const {
    if ( this->undefined() ) {
        return 0;
    }

    const auto& type = (*this)->type();

#ifdef _DEBUG
    const std::string& typeName = type.name();
#endif

    // чаще всего получаем значения 'double' - идут первыми
    if (type == typeid( double ) ) {
        return static_cast< std::size_t >( boost::any_cast< double >( **this ) );

    } else if (type == typeid( int ) ) {
        return static_cast< std::size_t >( boost::any_cast< int >( **this ) );

    } else if (type == typeid( std::size_t ) ) {
        return boost::any_cast< std::size_t >( **this );

    } else if (type == typeid( long ) ) {
        return static_cast< std::size_t >( boost::any_cast< long >( **this ) );

    } else if (type == typeid( unsigned long ) ) {
        return static_cast< std::size_t >( boost::any_cast< unsigned long >( **this ) );

    } else if (type == typeid( bool ) ) {
        return boost::any_cast< bool >( **this ) ? 1 : 0;

    } else if (type == typeid( char ) ) {
        return static_cast< std::size_t >( boost::any_cast< char >( **this ) );

    } else if (type == typeid( unsigned char ) ) {
        return static_cast< std::size_t >( boost::any_cast< unsigned char >( **this ) );

    } else if (type == typeid( float ) ) {
        return static_cast< std::size_t >( boost::any_cast< float >( **this ) );

    }

    assert( false && "Элемент является другим типом и не может быть приведён к типу std::size_t." );
    return 0;
}





inline Variant::operator float () const {
    if ( this->undefined() ) {
        return 0.0f;
    }

    const auto& type = (*this)->type();

#ifdef _DEBUG
    const std::string& typeName = type.name();
#endif

    if (type == typeid( double ) ) {
        return static_cast< float >( boost::any_cast< double >( **this ) );

    } else if (type == typeid( int ) ) {
        return static_cast< float >( boost::any_cast< int >( **this ) );

    } else if (type == typeid( std::size_t ) ) {
        return static_cast< float >( boost::any_cast< std::size_t >( **this ) );

    } else if (type == typeid( long ) ) {
        return static_cast< float >( boost::any_cast< long >( **this ) );

    } else if (type == typeid( unsigned long ) ) {
        return static_cast< float >( boost::any_cast< unsigned long >( **this ) );

    } else if (type == typeid( bool ) ) {
        return boost::any_cast< bool >( **this ) ? 1.0f : 0.0f;

    } else if (type == typeid( char ) ) {
        return static_cast< float >( boost::any_cast< char >( **this ) );

    } else if (type == typeid( unsigned char ) ) {
        return static_cast< float >( boost::any_cast< unsigned char >( **this ) );

    } else if (type == typeid( float ) ) {
        return boost::any_cast< float >( **this );

    }

    assert( false && "Элемент является другим типом и не может быть приведён к типу float." );
    return 0;
}





inline Variant::operator relCoordInt_t () const {
    if ( this->undefined() ) {
        return relCoordInt_t::ZERO();
    }

    const auto& type = (*this)->type();

#ifdef _DEBUG
    const std::string& typeName = type.name();
#endif

    if (type == typeid( typelib::json::Array ) ) {
        auto a = static_cast< typelib::json::Array >( *this );
        return static_cast< relCoordInt_t >( a );
    }

    assert( false && "Элемент является другим типом и не может быть приведён к типу relCoordInt_t." );
    return relCoordInt_t::ZERO();
}






inline Array::operator relCoordInt_t () const {
#ifdef _DEBUG
    const std::size_t n = size();
#endif

    assert( (size() == 4)
        && "Для приведения к типу relCoordInt_t необходимо 4 элемента: родитель и 3 координаты." );

    const auto& parent = static_cast< std::string >( at( 0 ) );
    const auto& x = static_cast< int >( at( 1 ) );
    const auto& y = static_cast< int >( at( 2 ) );
    const auto& z = static_cast< int >( at( 3 ) );

    return relCoordInt_t( parent, x, y, z );
}










inline void Variant::parse( Variant* v, const string_t& s ) {

    // @see external/cajun/test.cpp
    std::istringstream iss( s );
    ::json::UnknownElement e;
    try {
        ::json::Reader::Read( e, iss );

    } catch ( const ::json::Reader::ParseException& ex ) {
#if _DEBUG
        std::cerr << "json::ParseException: " << ex.what()
            << ", Line / offset: " << (ex.m_locTokenBegin.m_nLine + 1)
            << '/' << (ex.m_locTokenBegin.m_nLineOffset + 1)
        << std::endl << std::endl;
        //assert( false && "Ошибка при анализе JSON-строки." );
#endif
        throw ex;
    }

    Variant::get( v, e );
}





template< typename ElementTypeT >
inline void Variant::get( Variant* v, const ElementTypeT& e ) {
   assert( v );
   v->get( e );
   //  значение 'e' получено в 'v'
}




inline void Variant::get( const ::json::Array& array ) {
    Array a;
    for (auto itr = array.Begin(); itr != array.End(); ++itr) {
        Variant v;
        get( &v, *itr );
        a.push_back( v );
    }
    *this = cjv( a );
}




inline void Variant::get( const ::json::Object& object ) {
    Object o;
    for (auto itr = object.Begin(); itr != object.End(); ++itr) {
        Variant v;
        get( &v, itr->element );
        o[ itr->name ] = v;
    }
    *this = cjv( o );
}




inline void Variant::get( const ::json::Number& number ) {
    *this = cjv( number.Value() );
}




inline void Variant::get( const ::json::Boolean& boolean ) {
    *this = cjv( boolean.Value() );
}




inline void Variant::get( const ::json::String& str ) {
    *this = cjv( str.Value() );
}




inline void Variant::get( const ::json::Null& ) {
    *this = cjv( nullptr );
}




inline void Variant::get( const ::json::UnknownElement& unknown ) {
   unknown.Accept( *this );
}




inline void Variant::Visit( const ::json::Array& array )      { get( array ); }

inline void Variant::Visit( const ::json::Object& object )    { get( object ); }

inline void Variant::Visit( const ::json::Number& number )    { get( number ); }

inline void Variant::Visit( const ::json::String& string )    { get( string ); }

inline void Variant::Visit( const ::json::Boolean& boolean )  { get( boolean ); }

inline void Variant::Visit( const ::json::Null& null )        { get( null ); }





inline Variant load( const std::string& file, const std::string& path ) {

    // загружаем файл
    const std::string source = (path.empty() ? "" : (path + "/")) + file;
    std::ifstream  in( source.c_str() );
    assert( in.is_open() && "File is not found / not open." );
    //in.exceptions( std::ifstream::failbit | std::ifstream::badbit );
    std::string ts;
    std::string s = "";
    try {
        while ( std::getline( in, ts ) ) {
            s += ts + "\n";
        }
    } catch ( const std::ifstream::failure& ex ) {
          std::cerr << "Exception happened: " << ex.what() << "\n"
              << "Error bits are: "
              << "\nfailbit: " << in.fail() 
              << "\neofbit: " << in.eof()
              << "\nbadbit: " << in.bad() <<
          std::endl;
    }
    in.close();

    // возвращаем объект
    return Variant( s );
}





inline std::string noComment( const std::string& s ) {
    // @source http://ostermiller.org/findcomment.html
    //static const std::regex pattern ( "(/\\*([^*]|[\r\n]|(\\*+([^*/]|[\r\n])))*\\*+/)|(//.*)" );
    static const std::regex pattern ( "(//.*)" );
    return std::regex_replace( s, pattern, std::string( "" ) );
}




inline void print( std::ostream& out, const string_t& s ) {
    // @see external/cajun/test.cpp
    std::istringstream iss( s );
    ::json::Object obj;
    try {
        ::json::Reader::Read( obj, iss );

    } catch ( const ::json::Reader::ParseException& ex ) {
        out << "(!) json::ParseException: " << ex.what()
            << ", Line / offset: " << (ex.m_locTokenBegin.m_nLine + 1)
            << '/' << (ex.m_locTokenBegin.m_nLineOffset + 1)
        << std::endl << std::endl;
        assert( false && "Ошибка при анализе JSON-строки." );
    }

    // Напечатаем результат, и, чтобы не нарушать код сторонней библиотеки:
    // перед выводом в 'out':
    //   - заменим табуляцию на 2 пробела
    //   - заменим "\u" (так уж работает Cajun) на 'u'
    std::ostringstream oss;
    ::json::Writer::Write( obj, oss );
    const std::string t = boost::replace_all_copy( oss.str(), "\t", "  " );
    out << boost::replace_all_copy( t, "\\u", "u" );
}



    } // json
} // typelib
