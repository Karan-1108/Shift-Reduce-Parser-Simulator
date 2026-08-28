#include "lexer.hpp"
#include "slr_parser.hpp"
#include "rd_parser.hpp"
#include <iostream>
#include <chrono>
#include <string>

int main(int argc, char* argv[]) {
    std::string inputStr;

    // Check if an expression was passed as a command-line argument
    if (argc > 1) {
        inputStr = argv[1];
    } else {
        // Interactively prompt user for input
        std::cout << "Enter arithmetic expression: ";
        std::getline(std::cin, inputStr);
    }   

    // Default fallback if input is left empty
    if (inputStr.empty()) {
        inputStr = "a + b * c";
    }

    Lexer lexer(inputStr);
    auto tokens = lexer.tokenize();

    auto startSLR = std::chrono::high_resolution_clock::now();
    SLRParser slrParser;
    bool slrOk = slrParser.parse(tokens);
    auto endSLR = std::chrono::high_resolution_clock::now();
    double slrTime = std::chrono::duration<double, std::milli>(endSLR - startSLR).count();

    RecursiveDescentParser rdParser;
    auto rdMetrics = rdParser.parse(tokens);

    std::cout << "{\n";
    std::cout << "  \"success\": " << (slrOk ? "true" : "false") << ",\n";
    std::cout << "  \"trace\": [\n";
    const auto& trace = slrParser.getTrace();
    for (size_t i = 0; i < trace.size(); ++i) {
        std::cout << "    {\"step\": " << trace[i].step 
                  << ", \"stack\": \"" << trace[i].stackState 
                  << "\", \"buffer\": \"" << trace[i].inputBuffer 
                  << "\", \"action\": \"" << trace[i].action << "\"}"
                  << (i + 1 < trace.size() ? "," : "") << "\n";
    }
    std::cout << "  ],\n";

    std::cout << "  \"symbols\": [\n";
    const auto& symbols = slrParser.getSymbolTable().getSymbols();
    for (size_t i = 0; i < symbols.size(); ++i) {
        std::cout << "    {\"name\": \"" << symbols[i].name 
                  << "\", \"type\": \"" << symbols[i].type 
                  << "\", \"order\": " << symbols[i].firstOccurrenceOrder << "}"
                  << (i + 1 < symbols.size() ? "," : "") << "\n";
    }
    std::cout << "  ],\n";

    std::cout << "  \"tac\": [\n";
    const auto& instructions = slrParser.getTAC().getInstructions();
    for (size_t i = 0; i < instructions.size(); ++i) {
        std::cout << "    \"" << instructions[i].toString() << "\"" << (i + 1 < instructions.size() ? "," : "") << "\n";
    }
    std::cout << "  ],\n";

    std::cout << "  \"benchmark\": {\n";
    std::cout << "    \"slrTimeMs\": " << slrTime << ",\n";
    std::cout << "    \"rdTimeMs\": " << rdMetrics.executionTimeMs << ",\n";
    std::cout << "    \"rdPeakStackDepth\": " << rdMetrics.peakStackDepth << "\n";
    std::cout << "  }\n";
    std::cout << "}\n";

    return 0;
}