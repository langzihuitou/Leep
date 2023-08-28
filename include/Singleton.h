//
// Created by Admin on 2023/8/28.
//

#ifndef COMTOOLS_SINGLETON_H
#define COMTOOLS_SINGLETON_H

// 懒汉式单例
template <typename T>
class Singleton
{
public:
    static T *instance()
    {
        if (m_instance == nullptr)  // 如果实例指针为空，则创建实例
            m_instance = new T();
        return m_instance;
    }

private:
    Singleton() {}  // 私有的构造函数，确保无法通过外部调用构造函数创建实例
    Singleton(const Singleton<T> &);  // 禁止拷贝构造函数
    Singleton<T> &operator=(const Singleton<T> &);  // 禁止赋值操作符重载
    ~Singleton() {}  // 私有的析构函数，确保无法通过外部调用析构函数删除实例

private:
    static T *m_instance;  // 静态指针成员变量，用于存储实例的指针
};

template <typename T>
T * Singleton<T>::m_instance = NULL;
#endif //COMTOOLS_SINGLETON_H
