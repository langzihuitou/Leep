//
// Created by Admin on 2023/8/29.
//

#ifndef COMTOOLS_CLASSFACTORY_H
#define COMTOOLS_CLASSFACTORY_H

#include <string>
#include <functional>
#include <map>
#include "Reflectable.h"
// 定义一个宏来简化代码
#define REGISTER_CLASS(classname)                                                        \
    class classname##RegisterHelper {                                                    \
    public:                                                                              \
        classname##RegisterHelper() {                                                    \
            ClassFactory::Register<classname>(#classname, []{ return new classname; });  \
        }                                                                                \
};                                                                                       \
static classname##RegisterHelper g_##classname##RegisterHelper;

class ClassFactory {
public:
    template<typename T>
    static void Register(std::string name, std::function<T*()> creator);

    static Reflectable* Create(std::string name);

private:
    static std::map<std::string, std::function<Reflectable*()>> &GetMap() {
        static std::map<std::string, std::function<Reflectable*()>> map;
        return map;
    }
};
// 模板函数的实现必须与声明位于同一文件中，或者需要在实现的文件底部包含函数模板的声明。
template<typename T>
void ClassFactory::Register(std::string name, std::function<T*()> creator) {
    GetMap()[name] = creator;
}

#endif //COMTOOLS_CLASSFACTORY_H
