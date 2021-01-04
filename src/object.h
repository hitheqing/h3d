#pragma once

#include <map>
#include <ostream>
#include <string>

#include "console.h"

using string = std::string;

namespace Hyhy {
    class Object {
    public:
        string name;

        Object() {
            id = sid++;
            dic.insert(std::pair<int, Object*>(id, this));
        }

        friend std::ostream& operator<<(std::ostream& os, const Object& obj) {

            return os
                    << "name: " << obj.name
                    << " id: " << obj.id;
        }

        virtual  ~Object() {
            // out_msg(string("dtor:") + std::to_string(id));
        }

        unsigned get_id() const { return id; }

        static void destroy(Object* object);
        static Object* get_object(uint32_t objid);

        friend bool operator==(const Object& lhs, const Object& rhs) {
            return lhs.id == rhs.id;
        }
        friend bool operator!=(const Object& lhs, const Object& rhs) { return !(lhs == rhs); }


        uint32_t id;
        static uint32_t sid;
        static std::map<uint32_t, Object*> dic;
        virtual void on_destroy() {

        }
    private:

    };


}

