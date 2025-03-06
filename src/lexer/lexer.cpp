
#include "lexer/lexer.hpp"
#include "lexer/tokenizer_state_machine.hpp"
#include <ios>

NAMESPACE_BEGIN

std::vector<token> lexer::tokenize(std::ifstream& input_file)
{
    std::vector<token> tokens;
    i32 line_number = 1, column_number = 0;

    auto is_whitespace = [] (char c) -> bool
    {
        return (c == ' ' || c == '\t');
    };
    
    auto is_newline = [] (char c) -> bool
    {
        return (c == '\n');
    };

    auto get_next_token = [&] () -> token
    {
        char c = tokenizer_state_machine::EOF_CHARACTER;

        while(true)
        {
            input_file.get(c);
            std::cout << "c: " << c << std::endl;
            std::cout << "fail_status: " << input_file.fail() << std::endl;

            if(input_file.eof())
            {
                std::cout << "gadha eof reached" << std::endl;
                break;
            }

            if(is_newline(c))
            {
                line_number++;
                column_number = 0;
                continue;
            }
            
            column_number++;

            if(!is_whitespace(c))
            {
                break;
            }
        }

        if(!input_file.eof())
        {
            input_file.seekg(-1, std::ios_base::cur); 
        }
        else
        {
            input_file.clear();
        }

        tokenizer_state_machine tokenizer(input_file, line_number, column_number, token::keywords);
        return tokenizer.get_token();
    };

    while(tokens.empty() || tokens.back().get_type() != token::enum_token_type::END_OF_FILE)
    {
        auto token = get_next_token();
        std::cout << "loop!" << std::endl;
        std::cout << token << std::endl;
        tokens.push_back(token);
    }

    return tokens;
}

NAMESPACE_END