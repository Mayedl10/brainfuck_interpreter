#include "common.hpp"

static std::vector<std::string> split(std::string raw, char c) {
    std::vector<std::string> ret = {};

    std::string temp = "";

    for (char ch: raw) {
        if (ch == c) {
            ret.push_back(temp);
            temp = "";
        } else {
            temp += ch;
        }
    }
    ret.push_back(temp);
    return ret;
}

static int where (std::vector<customPair<std::string, int>> data, std::string key) {
    for (auto y: data) {
        if (y.first == key) {
            return y.second;
        }
    }
    std::cerr << "INVALID KEY IN BRAINFUCK CONFIGURATION FILE: " << key << std::endl;
    return -1;
}

config readConfigFile(std::string file) {
    auto raw = getFileContentAsString(file);
    auto lines = split(raw, '\n');
    std::vector<customPair<std::string, int>> retData = {};
    config ret;

    for (auto line : lines) {
        auto temp = split(line, ':');
        retData.push_back({
            temp[0],
            std::stoi(temp[1])
        });
    }

    ret.memsize = where(retData, "memsize");
    ret.wrap_tape = where(retData, "wrap-tape");
    ret.allow_overflow = where(retData, "allow-overflow");
    ret.file_read_default_char = where(retData, "file-read-default-char");
    ret.get_input_from_console = where(retData, "get-input-from-console");
    ret.output_to_console = where(retData, "output-to-console");
    ret.continue_on_error = where(retData, "continue-on-error");
    ret.ignore_invalid = where(retData, "ignore-invalid");

    return ret;
}