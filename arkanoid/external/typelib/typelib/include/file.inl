namespace typelib {
    namespace file {


inline std::string read(
    const std::string& file,
    const std::string& path
) {
    const std::string source = (path.empty() ? "" : (path + "/")) + file;
    std::ifstream  in( source.c_str() );
#ifdef __DEBUG
    // @todo fine Обернуть все assert'ы библиотеки в #ifdef __DEBUG. Ещё лучше -
    //       переписать через Exception.
    assert( in.is_open() && "File is not found / not open." );
#endif
    std::size_t lineCount = 1;
    std::string line;
    std::string s = "";
    while ( getline( in, line ) ) {
        // @source http://utfcpp.sourceforge.net/
        // check for invalid utf-8 (for a simple yes/no check, there is
        // also utf8::is_valid function)
        const std::string::iterator end_it =
            utf8::find_invalid( line.begin(), line.end() );
        if (end_it != line.end()) {
            std::cerr << "(!) Invalid UTF-8 encoding detected at line " << lineCount << "\n";
            std::cerr << "(!) This part is fine: " << std::string( line.cbegin(), end_it ) << "\n";
            // исправляем
            std::string temp;
            utf8::replace_invalid( line.cbegin(), line.cend(), back_inserter( temp ) );
            line = temp;
        }

        s += line;

        ++lineCount;
    }

    in.close();

    return s;
}




inline bool validUTF8Content(
    const std::string& file,
    const std::string& path
) {
    const std::string source = (path.empty() ? "" : (path + "/")) + file;
    std::ifstream  in( source.c_str() );
#ifdef __DEBUG
    // @todo fine Обернуть все assert'ы библиотеки в #ifdef __DEBUG. Ещё лучше -
    //       переписать через Exception.
    assert( in.is_open() && "File is not found / not open." );
#endif

    std::istreambuf_iterator< char >  it( in.rdbuf() );
    std::istreambuf_iterator< char >  eos;

    return utf8::is_valid( it, eos );
}

    
    
    
template< typename Collection >
inline void listFile(
    Collection*                     r,
    const boost::filesystem::path&  path,
    const std::string&              extension
) {
    namespace fs = boost::filesystem;

    assert( r );

    if ( !fs::exists( path ) ) {
        return;
    }

    const bool withoutExtension = extension.empty();
    const std::string searchExtension =
        ( !extension.empty() && (extension[ 0 ] != '.') )
            ? ("." + extension)
            : extension;
    fs::directory_iterator endItr;
    for (fs::directory_iterator itr( path ); itr != endItr; ++itr) {
        if ( fs::is_regular_file( itr->status() ) ) {
            const std::string ext = itr->path().extension().string();
            if ( withoutExtension || boost::iequals( searchExtension, ext) ) {
                const std::string f = itr->path().filename().string();
                r->insert( f );
            }
        }
    }
}





template< typename Collection >
inline void listFolder(
    Collection*                     r,
    const boost::filesystem::path&  path
) {
    namespace fs = boost::filesystem;

    assert( r );

    if ( !fs::exists( path ) ) {
        return;
    }

    fs::directory_iterator endItr;
    for (fs::directory_iterator itr( path ); itr != endItr; ++itr) {
        if ( fs::is_directory( itr->status() ) ) {
            const std::string f = itr->path().filename().string();
            r->insert( f );
        }
    }
}





inline bool hasFile(
    boost::filesystem::path&        foundPath,
    const boost::filesystem::path&  path,
    const std::string&              searchFile,
    bool                            deep
) {
    namespace fs = boost::filesystem;

    if ( !fs::exists( path ) ) {
        return false;
    }

    fs::directory_iterator endItr;
    for (fs::directory_iterator itr( path ); itr != endItr; ++itr) {
        if ( fs::is_directory( itr->status() ) ) {
            if ( deep && hasFile( foundPath, itr->path(), searchFile, deep ) ) {
                return true;
            }
        } else if (itr->path().leaf() == searchFile) {
            foundPath = itr->path();
            return true;
        }
    }

    return false;
}



    } // file
} // typelib
