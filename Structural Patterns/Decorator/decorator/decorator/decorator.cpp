// decorator.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

/*
    注意这里的关系： is-a or has-a
*/

// 1. "lowest common denominator"
class Widget {
public:
    virtual void Draw() = 0;
};

//2. "the Core class"
class TextField : public Widget {
public:
    TextField(int w, int h) {
        width = w;
        height = h;
    }

    void Draw() override {
        std::cout << "TextField: w=" << width << " h=" << height << std::endl;
    }

private:
    int width = 0;
    int height = 0;
};

//3. "the Decorator base class - 2nd level base class"
class Decorator : public Widget
{
public:
    Decorator(Widget *w)
    {
        wid = w;
    }

    void Draw() override
    {
        wid->Draw(); // Delegation
    }

private:
    Widget *wid = nullptr; //the reference to the core object, "has a" relationship
};

//4. "those Decorator subclasses"
class BorderDecorator : public Decorator
{
public:
    //Optional embellishment 1 
    BorderDecorator(Widget *w) : Decorator(w) {}

    void Draw() {
        //Delegate to base class and add extra stuff
        Decorator::Draw();
        std::cout << "BorderDecorator" << std::endl;
    }
};

class ScrollDecorator : public Decorator
{
public:
    //Optional embellishment 2
    ScrollDecorator(Widget *w) : Decorator(w) {}

    void Draw()
    {
        //Delegate to base class and add extra stuff
        Decorator::Draw();
        std::cout << "ScrollDecorator" << std::endl;
    }
};


int main()
{
    Widget* wig =  new BorderDecorator(new ScrollDecorator(new TextField(3,4)));
    wig->Draw();

    return 0;
}

