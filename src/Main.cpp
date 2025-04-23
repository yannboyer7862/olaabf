#include <iostream>
#include <cstdlib>
#include <fstream>
#include "IRGenerator.hpp"
#include "IRInterpreter.hpp"

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::cerr << "[ERROR] No program provided !\n";
        std::cerr << "[INFO] Usage : ./olaabf program.bf\n";
        return EXIT_FAILURE;
    }

    std::string programPath = std::string(argv[1]);

    std::ifstream programFile(programPath);

    if (!programFile.is_open()) {
        std::cerr << "[ERROR] Unable to open the provided file !\n";
        return EXIT_FAILURE;
    }

    std::string programBuffer;
    char ch;
    while (programFile.good()) {
        programFile.get(ch);
        programBuffer.push_back(ch);
    }

    programFile.close();

    IRGenerator irGenerator;
    IRInterpreter irInterpreter;

    try {
        const std::vector<IRInstruction> program = irGenerator.GenerateIRFromCode(programBuffer);
        irInterpreter.LoadIR(program);
        irInterpreter.Interpret();
    } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
