#ifndef TESTC_JSONREADER_H
#define TESTC_JSONREADER_H

#include <fstream>
#include "libs/json.hpp"

using json = nlohmann::json;

class JsonReader {
public:
    static bool exists(const std::string& path) {
        std::ifstream f(path.c_str());
        return f.good();
    }

    static bool exists(const char* path) {
        std::ifstream f(path);
        return f.good();
    }

    static json get(const std::string& path) {
        std::ifstream file(path);
        json j;
        file >> j;
        file.close();
        return j;
    }

    static json get(const char* path) {
        std::ifstream file(path);
        json j;
        file >> j;
        file.close();
        return j;
    }
private:
};

#endif //TESTC_JSONREADER_H
