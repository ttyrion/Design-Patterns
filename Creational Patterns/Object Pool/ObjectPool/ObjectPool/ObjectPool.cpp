// ObjectPool.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <list>

template <typename T>
class ObjectPool {
public:
    static ObjectPool& GetInstance() {
        static ObjectPool pool;
        return pool;
    }

    size_t& GetMaxSize() {
        return max_size;
    }

    //Request和Push非线程安全的
    T* Request() {
        size_t size = objs_.size();
        if (size <= 0) {
            //use the synthesis of Eager and Lazy strategy
            if (size < max_size) {
                return new T();
            }
            else return nullptr;
        }

        T* obj = objs_.back();
        objs_.pop_back();

        return obj;
    }

    void Push(T* obj) {
        obj->Reset();
        objs_.push_back(obj);
    }

private:
    ObjectPool() {
        for (size_t i = 0; i < max_size / 2; ++i) {
            Push(new T());
        }
    }
    ~ObjectPool() {
        for (auto obj : objs_) {
            delete obj;
        }
    }

    ObjectPool(const ObjectPool&) = delete;
    ObjectPool& operator=(const ObjectPool&) = delete;

private:
    std::list<T*> objs_;
    size_t max_size = 4;
};

class A {
public:
    A() {
    }
    ~A() {

    }

    void Reset() {}
};

int main()
{
    ObjectPool<A>& pool = ObjectPool<A>::GetInstance();
    pool.GetMaxSize() = 16;

    A * p = pool.Request();

    pool.Push(p);

    return 0;
}

