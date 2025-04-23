#include "Lexer.hpp"

Lexer::Lexer() {
    m_positionInCode = 0;
    m_code.resize(0);
}

void Lexer::Fill(const std::string& code) {
    for (char c : code) {
        m_code.push_back(c);
    }
}

bool Lexer::IsValidInstruction(char instruction) {
    std::string validInsts = "><+-.,[]";
    if (validInsts.find(instruction) != std::string::npos)
        return true;
    else
        return false;
}

char Lexer::Next() {
    while (m_positionInCode < m_code.size() && !IsValidInstruction(m_code[m_positionInCode]))
        m_positionInCode++;

    if (m_positionInCode >= m_code.size()) return 0;
    return m_code[m_positionInCode++];
}
