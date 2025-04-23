#ifndef IR_INTERPRETER_HPP
#define IR_INTERPRETER_HPP

#include <vector>
#include <cstdint>
#include <array>
#include "IRGenerator.hpp"

class IRInterpreter {
    public:
        IRInterpreter();

        void LoadIR(const std::vector<IRInstruction> program);
        void Interpret();
    private:
        static constexpr uint32_t TOTAL_MEMORY_CELLS = 100000;

        std::array<uint8_t, TOTAL_MEMORY_CELLS> m_memory;
        std::vector<IRInstruction> m_program;

        uint64_t m_instructionPointer;
        uint64_t m_memoryPointer;
};

#endif
