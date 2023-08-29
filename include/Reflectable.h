//
// Created by Admin on 2023/8/29.
//

#ifndef COMTOOLS_REFLECTABLE_H
#define COMTOOLS_REFLECTABLE_H

#include <iostream>
#include <string>

class Reflectable  {
public:
    virtual void DealData()  = 0;
    virtual ~Reflectable () {}
};
#endif //COMTOOLS_REFLECTABLE_H
