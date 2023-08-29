//
// Created by Admin on 2023/8/29.
//
#include "../include/ClassFactory.h"



Reflectable* ClassFactory::Create(std::string name) {
    auto& map = GetMap();
    auto it = map.find(name);
    if (it != map.end()) {
        return it->second();
    }
    return nullptr;
}

