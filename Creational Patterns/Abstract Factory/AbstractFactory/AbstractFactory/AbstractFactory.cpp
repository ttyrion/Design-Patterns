// AbstractFactory.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>

enum CarType {
    MINI,BUS
};

enum Location {
    CHINA,AMERICA
};

//作为抽象基类（继承层次），而不是接口（组合）
class Car {
public:
    Car(CarType model, Location location) {
        this->model_ = model;
        this->location_ = location;
    }
    ~Car() {
        std::cout << "Car model="<<model_<<",location="<<location_<<" Deconstructed." << std::endl;
    }

    virtual void Whistle() = 0;
    
protected:
    CarType model_ = CarType::MINI;
    Location location_ = Location::CHINA;
};

class MiniCar : public Car {
public:
    MiniCar(Location location):Car(CarType::MINI, location){        
    }

    ~MiniCar() {
        std::cout << "MiniCar model=" << model_ << ",location=" << location_ << " Deconstructed." << std::endl;
    }

    void Whistle() {
        std::cout << "di...di..." << std::endl;
    }
};

class Bus : public Car {
public:
    Bus(Location location): Car(CarType::BUS, location){        
    }

    ~Bus() {
        std::cout << "Bus model=" << model_ << ",location=" << location_ << " Deconstructed." << std::endl;
    }

    void Whistle() {
        std::cout << "boom...boom..." << std::endl;
    }
};

class Factory {
public:
    Factory() {}
    virtual ~Factory() {
        std::cout << "Factory Deconstructed." << std::endl;
    }

    virtual Car* MakeCar(CarType type) = 0;
    virtual void Release() = 0;
};

//这里都没有管多线程情况下的单例，多线程可以通过InterlockedExchangeAdd来保证单例
class ChinaFactory : public Factory {
public:
    static Factory* GetInstance() {
        if (!factory_) {
            factory_ = new ChinaFactory();
        }

        return factory_;
    }

    Car* MakeCar(CarType type) {
        Car* car = nullptr;
        switch (type)
        {
        case MINI:
            car = new MiniCar(Location::CHINA);
            break;
        case BUS:
            car = new Bus(Location::CHINA);
            break;
        default:
            break;
        }
        cars_.push_back(car);

        return car;
    }

    void Release() {
        if (factory_) {
            delete factory_;
        }
    }

private:
    ChinaFactory() {};
    ~ChinaFactory() {
        std::cout << "ChinaFactory Deconstructed." << std::endl;
        for (auto car: cars_) {
            if (car) {
                delete car;
            }
        }
    }

    static ChinaFactory* factory_;
    std::vector<Car*> cars_;
};
ChinaFactory* ChinaFactory::factory_ = nullptr;

class AmericaFactory : public Factory {
public:
    static Factory* GetInstance() {
        if (!factory_) {
            factory_ = new AmericaFactory();
        }

        return factory_;
    }

    Car* MakeCar(CarType type) {
        Car* car = nullptr;
        switch (type)
        {
        case MINI:
            car = new MiniCar(Location::AMERICA);
            break;
        case BUS:
            car = new Bus(Location::AMERICA);
            break;
        default:
            break;
        }
        cars_.push_back(car);

        return car;
    }

    void Release() {
        if (factory_) {
            delete factory_;
        }
    }

private:
    AmericaFactory() {};
    ~AmericaFactory() {
        std::cout << "AmericaFactory Deconstructed." << std::endl;
        for (auto car : cars_) {
            if (car) {
                delete car;
            }
        }
    }

    static AmericaFactory* factory_;
    std::vector<Car*> cars_;
};
AmericaFactory* AmericaFactory::factory_ = nullptr;

int main()
{
#define CHINA

    Factory* factory = nullptr;
#ifdef CHINA
    factory = ChinaFactory::GetInstance();
#else 
    factory = AmericaFactory::GetInstance();
#endif

    Car* car = factory->MakeCar(CarType::MINI);
    car->Whistle();
    factory->Release();

    return 0;
}

/*
   【Abstract Factory模式】
   优点：
   1、隔离实体类
   factory对象封装了创建product对象的过程，它把使用类的client和类的具体实现隔离开。客户端代码中不会出现实现类的名字。
   等等。

   缺点：
   扩展抽象工厂以便能生产新的product对象，是很困难的：需要修改AbstractFactory以及它所有的subclass。
*/
