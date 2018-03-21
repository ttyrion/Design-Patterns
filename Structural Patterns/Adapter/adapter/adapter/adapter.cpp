// adapter.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

//the system that would reuse something legacy(LegacyRectangle here)
class Shape {
public:
    virtual void Draw() = 0;
};

class Circle : public Shape {
public:
    void Draw() override {
        std::cout << "Circle Draw." <<std::endl;
    }
};

void DrawSomething(Shape& shape) {
    shape.Draw();
}

//Legacy component of an existing system
typedef int Coordinate;
typedef int Dimension;
class LegacyRectangle
{
public:
    //LegacyRectangle has an interface 'oldDraw', but no 'Draw' which DrawSomething() needs
    void oldDraw() {
        std::cout << "LegacyRectangle Draw." << std::endl;
    }
};

//Adapter pattern
class RectangleAdapter : public Shape, private LegacyRectangle {
public:
    void Draw() override {
        oldDraw();
    }
};

int main()
{
    Circle c;
    DrawSomething(c);

    //这个adapter类把新的接口（想复用遗留代码的系统中已存在的接口）映射到了遗留的实现上
    RectangleAdapter rectangle;
    DrawSomething(rectangle);

    return 0;
}

