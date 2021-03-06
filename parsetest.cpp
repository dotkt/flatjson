
#include "flatjson.hpp"

#include <iostream>
#include <fstream>
#include <chrono>

#include <cassert>

std::string read_file(const char *fname) {
    std::ifstream file(fname);
    assert(file.good());

    std::string str(
        (std::istreambuf_iterator<char>(file))
        ,std::istreambuf_iterator<char>())
    ;
    return str;
}

int main(int argc, char **argv) {
	if ( argc != 2 ) {
		std::cout << "parsetest <filename.json>" << std::endl;

		return EXIT_FAILURE;
	}

	const char *fname = argv[1];
	std::string body = read_file(fname);

	auto t1 = std::chrono::high_resolution_clock::now();
	
	flatjson::fdyjson json(body.c_str());
	if ( !json.valid() ) {
	    std::cout << "parse error: " << json.error() << std::endl;

	    return EXIT_FAILURE;
	}

	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

	std::cout << "tokens: " << json.tokens() << ", parse time: " << duration << " ms" << std::endl;

	return EXIT_SUCCESS;
}