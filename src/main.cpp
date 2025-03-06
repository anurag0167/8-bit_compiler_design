#include <iostream>
#include <fstream>

#include "lexer/lexer.hpp"

int main()
{
    const char* input_filename = "test_program.sl";
    std::ifstream input_file(input_filename);

    if(!input_file.is_open())
    {
        std::cerr << "Failed to open file `" << input_filename << std::endl;
        exit(-1);
    }

    char c;

    while(input_file.get(c), !input_file.eof())
    {
        std::cout << c;
    }

    input_file.clear();
    std::cout << std::endl;

    input_file.seekg(0, std::ios_base::beg);

    auto tokens = PROJECT_NAMESPACE::lexer::tokenize(input_file);
    
    for(const auto& token : tokens)
    {
        std::cout << token << std::endl;
    }
    


    

}