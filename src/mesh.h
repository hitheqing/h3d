#pragma once

#include <vector>

#include "object.h"
#include "vector3.h"

namespace Hyhy {
    class Mesh {
    public:
        Mesh() {}
        ~Mesh() {}


        std::vector<Hyhy::Vector3>* vertices = nullptr;
        std::vector<unsigned int>* indices = nullptr;
    };

}
