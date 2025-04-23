#include "IRInterpreter.hpp"
#include "IRGenerator.hpp"
#include <memory>
#include <iostream>

IRInterpreter::IRInterpreter() {
    m_memory.fill(0);
    m_program.resize(0);

    m_instructionPointer = 0;
    m_memoryPointer = 0;
}

void IRInterpreter::LoadIR(const std::vector<IRInstruction> program) {
    m_program = program;
}

void IRInterpreter::Interpret() {
    const std::size_t PRG_LEN = m_program.size();

    std::vector<uint64_t> stack;
    // Silly hack because we aren't allowed to use PRG_LEN for std::array.
    std::unique_ptr<uint64_t[]> targets = std::make_unique<uint64_t[]>(PRG_LEN);


    // Precomputing the jump.
    // NOTE : ARRAY VS HASHMAP, ARRAY wins, about 2 times the HASHMAP performance.
    for (std::size_t i = 0, j; i < PRG_LEN; i++) {
        if (m_program[i].kind == IRInstructionKind::JumpIfZero) {
            stack.push_back(i);
        } else if (m_program[i].kind == IRInstructionKind::JumpIfNotZero) {
            if (stack.empty()) {
                throw std::runtime_error("[ERROR] Unmatched ']' at byte " + std::to_string(i + 1));
            } else {
                j = stack.back();
                stack.pop_back();
                targets[i] = j;
                targets[j] = i;
            }
        }
    }

    while (m_instructionPointer < PRG_LEN) {
        IRInstruction irInst = m_program[m_instructionPointer];

        switch (irInst.kind) {
            case IRInstructionKind::IncrementPointer: m_memoryPointer += irInst.operand.value(); break;
            case IRInstructionKind::DecrementPointer: m_memoryPointer -= irInst.operand.value(); break;
            case IRInstructionKind::IncrementByte: m_memory[m_memoryPointer] += irInst.operand.value(); break;
            case IRInstructionKind::DecrementByte: m_memory[m_memoryPointer] -= irInst.operand.value(); break;
            case IRInstructionKind::PrintByte:
                {
                    char byteAsChar = static_cast<char>(m_memory[m_memoryPointer]);
                    for (uint8_t i = 0; i < irInst.operand.value(); i++) {
                        std::cout << byteAsChar;
                        std::cout.flush();
                    }
                }
                break;
            case IRInstructionKind::ReadByte:
                {
                    char inputByte;
                    std::cin >> inputByte;
                    std::cin.clear();

                    m_memory[m_memoryPointer] = static_cast<uint8_t>(inputByte);
                }
                break;
            case IRInstructionKind::JumpIfZero:
                if (m_memory[m_memoryPointer] == 0)
                    m_instructionPointer = targets[m_instructionPointer];
                break;
            case IRInstructionKind::JumpIfNotZero:
                if (m_memory[m_memoryPointer] != 0)
                    m_instructionPointer = targets[m_instructionPointer];
            break;
        }

        m_instructionPointer++;
    }
}
