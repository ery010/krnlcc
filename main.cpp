#include <iostream>
#include <fstream>   // For reading files
#include <sstream>   // For string manipulation
#include <vector>
#include <iomanip>   // For clean console output
#include "src/lexer.h"

int main(int argc, char* argv[]) {
    // 1. Ensure a file was provided
    if (argc < 2) {
        std::cerr << "Usage: krnlcc <filename.krnl>" << std::endl;
        return 1;
    }

    // 2. Open and read the source file
    std::string filename = argv[1];
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();

    // 3. Initialize the Lexer
    Lexer lexer(source);

    std::cout << "--- Tokenizing: " << filename << " ---" << std::endl;
    std::cout << std::left << std::setw(10) << "Line:Col" 
              << std::setw(15) << "Type" 
              << "Text" << std::endl;
    std::cout << "------------------------------------------" << std::endl;

    // 4. Token loop
    try {
        while (true) {
            Token t = lexer.next();
            
            // Print token info in a nice table format
            std::cout << std::left << t.line << ":" << std::setw(7) << t.col 
                      << std::setw(15) << token_kind_str(t.kind) 
                      << "[" << t.text << "]" << std::endl;

            if (t.kind == TokenKind::EOF_TOKEN) break;
        }
    } catch (const std::exception& e) {
        // This catches the 'unexpected character' errors from your lex_symbol logic
        std::cerr << "\nLEXER ERROR: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "------------------------------------------" << std::endl;
    std::cout << "Lexing complete." << std::endl;

    return 0;
}