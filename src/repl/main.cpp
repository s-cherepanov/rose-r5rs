#include <boost/exception/all.hpp>
#include <boost/format.hpp>
#include <boost/program_options.hpp>

#include <iostream>
#include <stdexcept>
#include <vector>

namespace rose {

void do_repl(std::string const& prompt);
void do_batch(std::string const& input_file);

}   //  namespace rose

static const std::string DEFAULT_REPL_PROMPT("rose[%1%]> ");

int main(int argc, char* argv[]) try {
    using boost::program_options::command_line_parser;
    using boost::program_options::notify;
    using boost::program_options::options_description;
    using boost::program_options::positional_options_description;
    using boost::program_options::store;
    using boost::program_options::value;
    using boost::program_options::variables_map;

    std::string repl_prompt;
    std::vector<std::string> input_files;

    options_description generic_options("Generic command line options");
    generic_options.add_options()
        ("help,h",
         "Show this help message.")

        ("prompt,p",
         value(&repl_prompt)->default_value(DEFAULT_REPL_PROMPT),
         "Set the prompt string of the REPL environment.")
        ;

    options_description hidden_options;
    hidden_options.add_options()
        ("input-file",
         value<std::vector<std::string> >(&input_files),
         "Input source file.")
        ;

    options_description cmdline_options;
    cmdline_options
        .add(generic_options)
        .add(hidden_options);

    positional_options_description positional_options;
    positional_options.add("input-file", 1);

    variables_map cmdline_vars;
    store(
            command_line_parser(argc, argv)
            .options(cmdline_options)
            .positional(positional_options)
            .run(),
            cmdline_vars
    );
    notify(cmdline_vars);

    if (cmdline_vars.count("help")) {
        std::cout << "Usage: rose <script-file> | [options]\n" << std::endl;
        std::cout << generic_options << std::endl;
        return 0;
    }

    cmdline_vars.count("input-file") ?
        rose::do_batch(input_files[0]) :
        rose::do_repl(repl_prompt);

    return 0;
}
catch(boost::exception& e) {
    std::cout
        << "EXCEPTION: "
        << diagnostic_information(e)
        << std::endl;
}
