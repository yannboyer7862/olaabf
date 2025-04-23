#ifndef LEXER_HPP
#define LEXER_HPP

#include <cstdint>
#include <string>
#include <vector>

class Lexer {
    public:
        Lexer();

        void Fill(const std::string& code);
        char Next();
    private:
        bool IsValidInstruction(char instruction);

        uint64_t m_positionInCode;
        std::vector<char> m_code;
};

#endif
