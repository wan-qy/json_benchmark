//
// Copyright (C) 2013 Mateusz Loskot <mateusz@loskot.net>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "json_benchmark.hpp"
#include <ciere/json/value.hpp>
#include <ciere/json/io.hpp>
namespace jb = jsonbench;
namespace cj = ciere::json;
int main()
{
    try
    {
        //auto const jsons = jb::get_one_json_per_line();
        auto const jsons = jb::get_json();
        auto const marks = jb::benchmark(jsons, [](std::string const& s) {
            cj::value jv;
            bool parsed = cj::construct(s, jv);
#ifdef JSON_BENCHMARK_DUMP_PARSED_JSON
            std::cout << jv << std::endl;
#endif
            return parsed && jv.type() != cj::null_type;
        });

        jb::print_result(std::cout << "spirit: ", marks);
        return EXIT_SUCCESS;
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() <<std::endl;
    }
    return EXIT_FAILURE;
}
