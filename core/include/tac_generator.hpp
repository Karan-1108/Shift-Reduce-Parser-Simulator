#pragma once
#include <string>
#include <vector>

struct TACInstruction {
    std::string result;
    std::string arg1;
    std::string op;
    std::string arg2;

    std::string toString() const {
        if (op.empty()) return result + " = " + arg1;
        return result + " = " + arg1 + " " + op + " " + arg2;
    }
};

class TACGenerator {
public:
    std::string createTemp();
    void emit(const std::string& res, const std::string& a1, const std::string& op, const std::string& a2);
    const std::vector<TACInstruction>& getInstructions() const;

private:
    int tempCount = 1;
    std::vector<TACInstruction> instructions;
};