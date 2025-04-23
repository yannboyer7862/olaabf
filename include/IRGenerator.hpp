#ifndef IR_GENERATOR_HPP
#define IR_GENERATOR_HPP

#include <vector>
#include <cstdint>
#include <optional>
#include <string>
#include "Lexer.hpp"

enum class IRInstructionKind {
    IncrementPointer = '>',
    DecrementPointer = '<',
    IncrementByte = '+',
    DecrementByte = '-',
    PrintByte = '.',
    ReadByte = ',',
    JumpIfZero = '[',
    JumpIfNotZero = ']',
};

struct IRInstruction {
    IRInstructionKind kind;
    std::optional<uint8_t> operand;
};

class IRGenerator {
    public:
        IRGenerator() = default;

        std::vector<IRInstruction> GenerateIRFromCode(const std::string& code);
    private:
        Lexer m_lexer;
};

#endif
