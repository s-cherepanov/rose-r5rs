#include "load_file.hpp"
#include "rose/r5rs_lexer.hpp"

#include <boost/test/unit_test.hpp>

namespace lex = boost::spirit::lex;
namespace qi = boost::spirit::qi;
namespace mpl = boost::mpl;

BOOST_AUTO_TEST_SUITE( r5rs_lexer_test_suite )

struct r5rs_fixture {
    typedef
        lex::lexertl::token<
            std::string::iterator,
            mpl::vector<>
        >
        token_type;

    typedef
        lex::lexertl::actor_lexer<token_type>
        lexer_type;

    typedef
        rose::r5rs_tokens<lexer_type>
        r5rs_tokens;

    typedef
        r5rs_tokens::iterator_type
        token_iterator_type;

    rose::r5rs_tokens<lexer_type> tokens;

    r5rs_fixture() {
    }

    ~r5rs_fixture() {
    }

};  //  struct r5rs_fixture

BOOST_FIXTURE_TEST_CASE( r5rs_lexer, r5rs_fixture ) {
    std::string str( load_file( "r5rs_lexer_test.input" ) );
    std::string::iterator first = str.begin();
    std::string::iterator last = str.end();
    bool result = tokenize( first, last, tokens );

    BOOST_CHECK( result == true );
    BOOST_CHECK( first == last );
}

BOOST_AUTO_TEST_SUITE_END()
