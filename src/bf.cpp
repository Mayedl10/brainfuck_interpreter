#include "common.hpp"

void raiseError(int errorCode, std::string message) {
    std::cerr << "\n[brainfuck runtime error] (BF" << errorCode << "): " << message << std::endl; 
}

enum errorCodes : int {
    BF_MEMPTR_OUT_OF_RANGE,
    BF_OVERFLOW,
    BF_INVALID_INSTRUCTION
};

int interpret(std::string code, config cfg) {
    std::vector<char> memory(cfg.memsize);
    int memPtr = 0;
    int ispt = 0;

    int loopLevel;
    int codesize = code.size();

    std::vector<char> fileInput;
    if (!(cfg.get_input_from_console)) {
        fileInput = getFileContentAsVector("bfinput");
    }

    emptyFile("bfout");

    unsigned int fileInputIndex = 0;

    while (ispt < codesize) {

        switch (code[ispt])
        {
        case '>':
            
            memPtr++;

            if ((memPtr >= cfg.memsize) && !(cfg.wrap_tape)) {
                if (cfg.continue_on_error) {
                    memPtr--;

                } else {
                    raiseError(errorCodes::BF_MEMPTR_OUT_OF_RANGE, "Memory pointer exceeded memory size after executing '>'.");
                    return 1;
                }

            } else if (memPtr >= cfg.memsize) {
                memPtr = 0;
            }

            break;

        case '<':

            memPtr--;

            if ((memPtr < 0) && !(cfg.wrap_tape)) {
                if (cfg.continue_on_error) {
                    memPtr++;

                } else {
                    raiseError(errorCodes::BF_MEMPTR_OUT_OF_RANGE, "Memory pointer was set to a negative number after executing '<'.");
                    return 1;
                }

            } else if (memPtr < 0) {
                memPtr = cfg.memsize-1;
            }

            break;

        case '+':

            if (cfg.allow_overflow) {
                memory[memPtr]++;

            } else {
                if ((memory[memPtr] == '\255') && (cfg.continue_on_error)) {
                    // do nothing
                } else if (memory[memPtr] == '\255') {
                    raiseError(errorCodes::BF_OVERFLOW, "Memory at position " + std::to_string(memPtr) + " exceeded 255 after evecuting '+'.");
                    return 1;
                }
            }

            break;

        case '-':

            if (cfg.allow_overflow) {
                memory[memPtr]--;

            } else {
                if ((memory[memPtr] == '\0') && (cfg.continue_on_error)) {
                    // do nothing
                } else if (memory[memPtr] == '\0') {
                    raiseError(errorCodes::BF_OVERFLOW, "Memory at position " + std::to_string(memPtr) + " went below 0 after evecuting '-'.");
                    return 1;
                }
            }

            break;

        case '.':
            if (cfg.output_to_console) {
                std::cout << memory[memPtr];
            } else {
                appendCharacter(memory[memPtr], "bfout");
            }

            break;

        case ',':

            if (cfg.get_input_from_console) {
                std::string tempStr = "";
                std::cin >> tempStr;
                memory[memPtr] = tempStr[0];

            } else {
                if (fileInputIndex >= fileInput.size()) {
                    memory[memPtr] = cfg.file_read_default_char;

                } else {
                    memory[memPtr] = fileInput[fileInputIndex];
                    fileInputIndex++;
                }

            }

            break;

        case '[':

            if (memory[memPtr] == 0) {
                loopLevel = 1;
                while (loopLevel > 0) {
                    ispt++;
                    if (code[ispt] == '[') {
                        loopLevel++;

                    } else if (code[ispt] == ']') {
                        loopLevel--;
                    }
                }
            }

            break;

        case ']':

            if (memory[memPtr]) {
                loopLevel = 1;
                while (loopLevel > 0) {
                    ispt--;
                    if (code[ispt] == '[') {
                        loopLevel--;

                    } else if (code[ispt] == ']') {
                        loopLevel++;
                    }
                }
            }

            break;
        
        default:

            if (!(cfg.ignore_invalid)) {
                raiseError(errorCodes::BF_INVALID_INSTRUCTION, "Invalid instruction '" + std::to_string(code[ispt]) + "'.");
                return 1;
            }

            break;
        }
    ispt++;

    }

    return 0;

};


int main(int argc, char* argv[]) {
    config cfg = readConfigFile("bfconfig");

    std::string code = getFileContentAsString(argv[1]);

    interpret(
        code,
        cfg
    );

    std::cout << "\n\nPress enter to close this window." << std::endl;
    std::cin.get();
    return 0;
}