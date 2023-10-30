#ifndef COMMON_HPP
#define COMMON_HPP

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct config {
    int memsize;
    bool wrap_tape;
    bool allow_overflow;
    char file_read_default_char;
    bool get_input_from_console;
    bool output_to_console;
    bool continue_on_error;
    bool ignore_invalid;
};

config readConfigFile(std::string file);

std::string getFileContentAsString(const std::string& filename);
std::vector<char> getFileContentAsVector(const std::string& filename);
void appendCharacter(char c, std::string filename);
void emptyFile(std::string filename);


template<typename T1, typename T2>
struct customPair {
    T1 first;
    T2 second;

    customPair(T1 x, T2 y) : first(x), second(y) {}
    customPair() {}

    auto operator[] (int index) {
        if (index == 0) {
            return first;

        } else if (index == 1) {
            return second;

        } else {
            throw std::out_of_range("Cannot index 'customPair' with a value other than 0 or 1. Index provided: " + index);
        }
    }
};


#endif