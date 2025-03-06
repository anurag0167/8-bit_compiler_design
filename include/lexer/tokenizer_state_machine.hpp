#ifndef TOKENIZER_STATE_MACHINE_HPP
#define TOKENIZER_STATE_MACHINE_HPP

#include <fstream>
#include <ios>
#include <optional>
#include <cstring>

#include "token.hpp"

NAMESPACE_BEGIN

struct tokenizer_state_machine
{
    static constexpr const char EOF_CHARACTER = EOF;

    enum struct enum_state
    {
        NONE,
        START,
        NUMBER,
        IDENTIFIER_OR_KEYWORD,
        EQUAL_OR_ASSIGNMENT,
    };

    static bool is_digit(char c)
    {
        return '0' <= c && c <= '9';
    }

    static bool is_letter(char c)
    {
        return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z');
    }

    static bool is_alphanumeric(char c)
    {
        return is_letter(c) || is_digit(c);
    }

    bool is_assignment()
    {
        const char* text = m_token.m_text.c_str();
        return !strcmp("==", text);
    }
    
    std::optional<token::enum_token_type> get_keyword()
    {
        std::cout << "get_keyword!!!!!!" << std::endl;
        const char* text = m_token.m_text.c_str();

        for(size_t i = 0; i < token::number_of_keywords; i++)
        {
            if(!strcmp(m_keywords[i].first, text))
            {
                std::cout << "index: " << i << std::endl;
                return m_keywords[i].second;
            }
        }

        return std::nullopt;
    }

    char get_character()
    {
        char c;
        m_input_file.get(c);
        
        if(m_input_file.eof())
        {
            c = EOF_CHARACTER;            
        }

        (std::cout << "get_character: " << c << " ").flush();

        m_token.append_character(c);
        return c;
    }

    void unget_character()
    {
        m_token.remove_last_character();

        if(!m_input_file.eof())
        {                
            m_input_file.seekg(-1, std::ios_base::cur);
        }
        else
        {
            m_input_file.clear();
        }
    }
    
    void state_start()
    {
        std::cout << "start" << std::endl;
        char c = get_character();

        if(c == EOF_CHARACTER)
        {
            state_end_of_file();
        }
        else if(is_digit(c))
        {
            state_number();
        }
        else if(is_letter(c))
        {
            state_identifier_or_keyword();
        }
        else if(c == '_')
        {
            state_identifier_or_keyword();
        }
        else if(c == '=')
        {
            state_equal_or_assignment();
        }
        else if(c == '+')
        {
            state_plus();
        }
        else if(c == '-')
        {
            state_minus();
        }
        else if(c == ';')
        {
            state_semicolon();
        }
        else if(c == '{')
        {
            state_left_parentheses();
        }
        else if(c == '}')
        {
            state_right_parentheses();
        }
        else if(c == '(')
        {
            state_left_bracket();
        }
        else if(c == ')')
        {
            state_right_bracket();
        }
        else if(c == '/')
        {
            state_comment_or_divides();
        }
        else
        {
            state_unknown();
        }
    }

    void state_number()
    {
        m_token.set_type(token::enum_token_type::NUMBER);
        m_last_state = enum_state::NUMBER;

        char c = get_character();

        if(!is_digit(c))
        {
            state_end();
        }
    }

    void state_identifier_or_keyword()
    {
        char c = get_character();
        m_last_state = enum_state::IDENTIFIER_OR_KEYWORD;

        if(!is_alphanumeric(c))
        {
            state_end();
            return;
        }

        state_identifier_or_keyword();
    }

    void state_plus()
    {
        m_token.set_type(token::enum_token_type::PLUS);
    }

    void state_minus()
    {
        m_token.set_type(token::enum_token_type::MINUS);
    }

    void state_equal_or_assignment()
    {
        char c = get_character();
        m_last_state = enum_state::EQUAL_OR_ASSIGNMENT;

        if(c == '=')
        {
            m_token.set_type(token::enum_token_type::EQUAL);
            state_end();
        }
        else
        {
            m_token.set_type(token::enum_token_type::ASSIGNMENT);
            state_end();
        }
    }

    void state_semicolon()
    {
        m_token.set_type(token::enum_token_type::SEMICOLON);
    }

    void state_left_parentheses()
    {
        m_token.set_type(token::enum_token_type::LEFT_PARENTHESES);
    }

    void state_right_parentheses()
    {
        m_token.set_type(token::enum_token_type::RIGHT_PARENTHESES);
    }

    void state_left_bracket()
    {
        m_token.set_type(token::enum_token_type::LEFT_BRACKET);
    }

    void state_right_bracket()
    {
        m_token.set_type(token::enum_token_type::RIGHT_BRACKET);
    }

    void state_comment_or_divides()
    {
        std::cout << "state_comment_or_divides" << std::endl;
        char c = get_character();

        if(c == '/')
        {
            state_comment();
        }
        else
        {
            state_end();
        }
    }

    void state_comment()
    {
        std::cout << "state_comment" << std::endl;
        m_token.set_type(token::enum_token_type::COMMENT);

        char c = get_character();

        if(c == '\n' || c == EOF_CHARACTER)
        {
            state_end();
        }
        else
        {
            state_comment();
        }
    }

    void state_unknown()
    {
        m_token.set_type(token::enum_token_type::UNKNOWN);
    }

    void state_end_of_file()
    {
        m_token.set_type(token::enum_token_type::END_OF_FILE);
        state_end();
    }

    void state_end()
    {
        std::cout << "state_end" << std::endl;
        unget_character();

        std::cout << "last_state: " << static_cast<int>(m_last_state) << std::endl;

        switch(m_last_state)
        {
            case enum_state::IDENTIFIER_OR_KEYWORD:
            {
                std::cout << "IDENTIFIER_OR_KEYWORD" << std::endl;
                auto optional_keyword = get_keyword();

                if(optional_keyword.has_value())
                {
                    m_token.set_type(optional_keyword.value());
                }
                else
                {
                    m_token.set_type(token::enum_token_type::IDENTIFIER);
                }

                break;
            }
            
            case enum_state::EQUAL_OR_ASSIGNMENT:
                if(is_assignment())
                {
                    m_token.set_type(token::enum_token_type::ASSIGNMENT);
                }
                else
                {
                    m_token.set_type(token::enum_token_type::EQUAL);
                }

                break;
        }

    }

    tokenizer_state_machine(std::ifstream& input_file, const i32 line_number, i32& column_number, const std::pair<const char* const, token::enum_token_type>(&keywords)[token::number_of_keywords]) :
        m_token { line_number, column_number },
        m_input_file { input_file },
        m_keywords { keywords },
        m_column_number { column_number }
    {
        state_start();
    }

    token get_token()
    {
        return m_token;
    }

private:
    token m_token;
    std::ifstream& m_input_file;
    enum_state m_last_state { enum_state::NONE };

    const std::pair<const char* const, token::enum_token_type>(&m_keywords) [token::number_of_keywords];

    i32& m_column_number;
};

NAMESPACE_END

#endif
