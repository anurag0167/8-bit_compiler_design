#ifndef TOKEN_HPP
#define TOKEN_HPP

#include "types.hpp"
#include "forward_declaration.hpp"
#include <iostream>
#include <utility>

NAMESPACE_BEGIN

struct token
{
    friend tokenizer_state_machine;

    enum struct enum_token_type
    {
        INT,
        IF,
        ELSE,

        IDENTIFIER,
        NUMBER,

        ASSIGNMENT,
        PLUS,
        MINUS,
        EQUAL,

        SEMICOLON,
        LEFT_PARENTHESES,
        RIGHT_PARENTHESES,

        LEFT_BRACKET,
        RIGHT_BRACKET,

        COMMENT,
        UNKNOWN,
        END_OF_FILE,
    };

    static constexpr std::pair<const char* const, enum_token_type> keywords[] =
    {
        { "int", enum_token_type::INT },

        { "if", enum_token_type::IF },
        { "else", enum_token_type::ELSE },
    };

    static constexpr const std::size_t number_of_keywords = sizeof(keywords) / sizeof(keywords[0]);

    friend std::ostream& operator<<(std::ostream& os, enum_token_type token_type)
    {
        switch(token_type)
        {
            case enum_token_type::INT:
                os << "INT";
                break;

            case enum_token_type::IF:
                os << "IF";
                break;

            case enum_token_type::IDENTIFIER:
                os << "IDENTIFIER";
                break;

            case enum_token_type::NUMBER:
                os << "NUMBER";
                break;

            case enum_token_type::ASSIGNMENT:
                os << "ASSIGNMENT";
                break;

            case enum_token_type::PLUS:
                os << "PLUS";
                break;

            case enum_token_type::MINUS:
                os << "MINUS";
                break;

            case enum_token_type::EQUAL:
                os << "EQUAL";
                break;

            case enum_token_type::SEMICOLON:
                os << "SEMICOLON";
                break;

            case enum_token_type::LEFT_PARENTHESES:
                os << "LEFT_PARENTHESES";
                break;

            case enum_token_type::RIGHT_PARENTHESES:
                os << "RIGHT_PARENTHESES";
                break;

            case enum_token_type::LEFT_BRACKET:
                os << "LEFT_BRACKET";
                break;

            case enum_token_type::RIGHT_BRACKET:
                os << "RIGHT_BRACKET";
                break;

            case enum_token_type::COMMENT:
                os << "COMMENT";
                break;

            case enum_token_type::UNKNOWN:
                os << "UNKNOWN";
                break;

            case enum_token_type::END_OF_FILE:
                os << "END_OF_FILE";
                break;

            default:
                os << "INVALID_TOKEN_TYPE";
                break;
        }

        return os;
    }

    friend std::ostream& operator<<(std::ostream& os, const token& token)
    {
        os << "token { type: " << token.m_token_type << ", text: " << token.m_text << ", line_number: " << token.m_line_number << ", column_number: " << token.m_column_number << std::endl;
        return os;
    }

    token(i32 line_number, i32 column_number) :
        m_line_number { line_number },
        m_column_number { column_number }
    {}

    token(enum_token_type token_type, i32 line_number, i32 column_number) :
        m_token_type { token_type },
        m_line_number { line_number },
        m_column_number { column_number }
    {}

    enum_token_type get_type()
    {
        return m_token_type;
    }

    void set_type(enum_token_type token_type)
    {
        m_token_type = token_type;
    }

    void append_character(char c)
    {
        m_text.push_back(c);
    }

    void remove_last_character()
    {
        m_text.pop_back();
    }

private:
    enum_token_type m_token_type;
    std::string m_text;

    i32 m_line_number;
    i32 m_column_number;
};

NAMESPACE_END

#endif