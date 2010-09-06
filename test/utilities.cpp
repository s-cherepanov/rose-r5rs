#include "rose/exception.hpp"

#include <algorithm>
#include <fstream>
#include <iterator>

using namespace rose;

std::string load_file(std::string const& filename) {
    std::ifstream in(filename.c_str());

    if (!in.is_open()) {
        BOOST_THROW_EXCEPTION(
                file_not_found()
                << boost::errinfo_file_name(filename));
    }

    in.unsetf(std::ios::skipws);
    return std::string(
            std::istreambuf_iterator<char>(in.rdbuf()),
            std::istreambuf_iterator<char>());
}

