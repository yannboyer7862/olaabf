#include "IRGenerator.hpp"
#include <stdexcept>

std::vector<IRInstruction> IRGenerator::GenerateIRFromCode(const std::string& code) {
    m_lexer.Fill(code);

    char c = m_lexer.Next();

    std::vector<IRInstruction> tempProgram;

    while (c) {
        IRInstruction irInst;
        switch (c) {
            case '>':
            case '<':
            case '+':
            case '-':
            case '.':
                {
                    char s = m_lexer.Next();
                    uint8_t streak = 1;

                    while (c == s) {
                        // 255 because there is incrementation below and it will become 256 thus overflowing.
                        if (streak == 255) {
                            throw std::runtime_error("[ERROR] Streak optimization is limited to 255 instructions at once !");
                        }
                        s = m_lexer.Next();
                        streak++;
                    }

                    irInst = IRInstruction { static_cast<IRInstructionKind>(c), streak };

                    c = s;
                }
                break;
            case ',':
            case '[':
            case ']':
                {
                    irInst = IRInstruction { static_cast<IRInstructionKind>(c), {} };

                    c = m_lexer.Next();
                }
                break;
            default: continue;
        }

        tempProgram.push_back(irInst);
    }

    return tempProgram;
}
