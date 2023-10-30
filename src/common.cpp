#include "common.hpp"

std::string getFileContentAsString(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::vector<char> getFileContentAsVector(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);  // Open in binary mode

    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return std::vector<char>();  // Return an empty vector
    }

    std::vector<char> content;
    char c;

    while (file.get(c)) {
        content.push_back(c);
    }

    return content;
}


void appendCharacter(char c, std::string filename) {
    // Open the file in binary mode and set the append flag.
    std::ofstream file(filename, std::ios::binary | std::ios::app);

    if (file.is_open()) {
        // Write the character to the file.
        file.write(&c, sizeof(char));

        // Close the file when done.
        file.close();
    } else {
        std::cerr << "Error: Unable to open the file." << std::endl;
    }
}

void emptyFile(std::string filename) {
    // Open the file in binary mode and set the truncate flag.
    std::ofstream file(filename, std::ios::binary | std::ios::trunc);

    if (file.is_open()) {
        // The file is now empty.
        file.close();
    } else {
        std::cerr << "Error: Unable to open the file." << std::endl;
    }
}