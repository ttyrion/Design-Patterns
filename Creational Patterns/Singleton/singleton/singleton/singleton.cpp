// singleton.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <mutex>

//std::call_once
class SingletonA {
public:
    static SingletonA& GetInstance() {
        std::call_once(instance_flag_, &SingletonA::init);
        return *instance_;
    }

private:
    //prevent constructor outside
    SingletonA() {}
    ~SingletonA() {}

    //prevent calling copy constructor and assignment operator
    SingletonA(const SingletonA&) = delete;
    SingletonA& operator=(const SingletonA&) = delete;

    static void init() {
        instance_ = new SingletonA();
    }

private:
    static std::once_flag instance_flag_;
    static SingletonA*instance_;
};
std::once_flag SingletonA::instance_flag_;
SingletonA* SingletonA::instance_ = nullptr;

//lock
std::mutex single_mutex_;
class SingletonB {
public:
    static SingletonB& GetInstance() {
        std::lock_guard<std::mutex> auto_lock(single_mutex_);
        if (!instance_) {
            instance_ = new SingletonB();
        }

        return *instance_;
    }

private:
    SingletonB() {}
    ~SingletonB() {}
    SingletonB(const SingletonB&) = delete;
    SingletonB& operator=(const SingletonB&) = delete;

private:
    static std::mutex single_mutex_;
    static SingletonB*instance_;
};
std::mutex SingletonB::single_mutex_;
SingletonB* SingletonB::instance_ = nullptr;

//Meyers Singleton: a static local object
class SingletonC {
public:
    static SingletonC& GetInstance() {
        static SingletonC instance;
        return instance;
    }

private:
    SingletonC() {}
    ~SingletonC() {}
    SingletonC(const SingletonC&) = delete;
    SingletonC& operator=(const SingletonC&) = delete;
};

int main()
{
    //SingletonA& instance_of_A = SingletonA::GetInstance();
    //SingletonB& instance_of_B = SingletonB::GetInstance();
    //SingletonC& instance_of_C = SingletonC::GetInstance();

    return 0;
}

