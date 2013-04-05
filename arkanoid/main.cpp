#include "include/stdafx.h"
#include "include/configure.h"
#include "include/World.h"




void run();




/**
* Переписанная через OpenCL демо-версия MatchN5.
*/
int
main( int argc, char** argv ) {

    using namespace arkanoid;

            
    setlocale( LC_ALL, "Russian" );
    setlocale( LC_NUMERIC, "C" );


    // создаём мир
    int code = 0;
    try {
        run();
        
    } catch ( const Exception& ex ) {
        std::cerr << std::endl << ex.what() << std::endl;
        code = -1;

    } catch ( const std::exception& ex ) {
        std::cerr << std::endl << ex.what() << std::endl;
        code = -2;

    } catch ( const std::string& ex ) {
        std::cerr << std::endl << ex << std::endl;
        code = -100;

    } catch ( const char* const ex ) {
        std::cerr << std::endl << *ex << std::endl;
        code = -200;

    } catch ( ... ) {
        std::cerr << std::endl << "(!) Unknown exception." << std::endl;
        code = -300;
    }

    std::cout << "\n^\n";
    //std::cin.ignore();

    return code;

}; // main()








inline void
run() {

    using namespace arkanoid;

    std::shared_ptr< World >  w = World::valueOf();
    w->go();
}
