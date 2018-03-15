// AbstractFactory.cpp : �������̨Ӧ�ó������ڵ㡣
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

//��Ϊ������ࣨ�̳в�Σ��������ǽӿڣ���ϣ�
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

//���ﶼû�йܶ��߳�����µĵ��������߳̿���ͨ��InterlockedExchangeAdd����֤����
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
   ��Abstract Factoryģʽ��
   �ŵ㣺
   1������ʵ����
   factory�����װ�˴���product����Ĺ��̣�����ʹ�����client����ľ���ʵ�ָ��뿪���ͻ��˴����в������ʵ��������֡�
   �ȵȡ�

   ȱ�㣺
   ��չ���󹤳��Ա��������µ�product�����Ǻ����ѵģ���Ҫ�޸�AbstractFactory�Լ������е�subclass��
*/
