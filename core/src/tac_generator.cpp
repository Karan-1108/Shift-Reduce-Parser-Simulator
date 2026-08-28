#include "tac_generator.hpp"

std::string TACGenerator::createTemp() {
    return "t" + std::to_string(tempCount++);
}

void TACGenerator::emit(const std::string& res, const std::string& a1, const std::string& op, const std::string& a2) {
    instructions.push_back({res, a1, op, a2});
}

const std::vector<TACInstruction>& TACGenerator::getInstructions() const {
    return instructions;
}