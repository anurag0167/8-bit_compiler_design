#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
#include <fstream>
#include <optional>

#include "types.hpp"
#include "token.hpp"

NAMESPACE_BEGIN

struct lexer
{
    static std::vector<token> tokenize(std::ifstream& input_file);
};

NAMESPACE_END

#endif