#include "object.h"

namespace Hyhy {
    void Hyhy::Object::destroy(Object* object) {
        if (dic.at(object->get_id()) != nullptr) {
            object->on_destroy();
            dic.erase(object->get_id());
        }
    }

    Object* Object::get_object(uint32_t objid) {
        auto iter = dic.find(objid);
        if (iter != dic.end()) {
            return iter->second;
        }

        return nullptr;
    }

    uint32_t Object::sid;
    std::map<uint32_t, Object*> Object::dic;
}
