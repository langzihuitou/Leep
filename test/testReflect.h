//
// Created by Admin on 2023/8/29.
//
#pragma once

#include "../include/Reflectable.h"
#include "../include/ClassFactory.h"

#include <iostream>

class Derived1 : public Reflectable {
public:
    void DealData()override
    {
        std::cout<<"Derived1"<<std::endl;
    }
};
REGISTER_CLASS(Derived1)

class Derived2 : public Reflectable {
public:
    void DealData()override
    {
        std::cout<<"Derived2\n";
    }
};
REGISTER_CLASS(Derived2)

void testReflect_01();