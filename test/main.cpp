#define BOOST_TEST_NO_MAIN
#define BOOST_TEST_ALTERNATIVE_INIT_API

#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <boost/program_options.hpp>
#include <boost/test/included/unit_test.hpp>

using namespace boost::filesystem;
using namespace boost::program_options;

bool init_function() {
    return true;
}

int main( int argc, char* argv[] ) {
    std::string working_dir;

    options_description cmdline_desc( "Available command line options" );
    cmdline_desc.add_options()
        ( "working-dir,w",
          value( &working_dir ),
          "Specify the working direcotory." )
        ;

    variables_map cmdline_vm;
    store( parse_command_line( argc, argv, cmdline_desc ), cmdline_vm );
    notify( cmdline_vm );

    if( cmdline_vm.count( "working-dir" ) ) {
        current_path( path( working_dir ) );
    }

    return boost::unit_test::unit_test_main( &init_function, argc, argv );
}
