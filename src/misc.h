#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

using namespace std;

#define cwd "../"

namespace Hyhy {

    inline string readFileIntoString(const char* filename) {
        std::ifstream fin(filename);
        std::stringstream buff;
        buff << fin.rdbuf();
        return buff.str();
    }

}
