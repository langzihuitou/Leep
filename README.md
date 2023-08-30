# Leap
每日更新内容：
2023.8.26
 C++ 实现线程池步骤：
创建任务队列：使用队列数据结构来存储待执行的任务。任务可以是函数指针、函数对象或lambda表达式。
创建线程池类：定义一个线程池类，其中包括以下成员变量：
线程池的大小，即要创建的线程数量
任务队列，用于存储待执行的任务
互斥量，用于在多线程环境下对任务队列进行同步
条件变量，用于线程间的通信和任务调度
初始化线程池：在线程池类的构造函数中，创建指定数量的工作线程，并让它们等待任务的到来。
提交任务：在线程池类中定义一个成员函数，用于向任务队列提交任务。该函数需要将任务添加到任务队列中，并通知等待中的工作线程来执行任务。
执行任务：每个工作线程在一个循环中等待任务的到来。当有任务可执行时，线程从任务队列中取出任务并执行。
销毁线程池：在线程池类的析构函数中，需要将每个工作线程都加入到任务队列中，以便线程可以退出循环并销毁。
2023.8.27
数据的序列化与反序列化
序列化与反序列化的对象包括：基本类型，STL 中的容器，自定义类
2023.8.28
1.设计单列模板类
2.结构化CMakeLists.txt
2023.8.29
利用简单的反射工厂模式，它允许在运行时根据类名动态创建类的实例，它可以解决C++不支持反射问题
代码中的REGISTER_CLASS宏用于注册一个类到工厂中，Register函数用于注册一个类名和对应的实例创建函数。Create函数根据类名在工厂中查找对应的实例创建函数并执行，返回创建的实例。
这样，通过使用反射工厂，可以实现在编译时无法确定具体类类型的情况下，通过字符串类名来创建实例对象的功能。
需要注意的是，这段代码使用了C++11的特性，如lambda函数和变长模板参数。它依赖于标准库中的map和function等容器和函数模板。