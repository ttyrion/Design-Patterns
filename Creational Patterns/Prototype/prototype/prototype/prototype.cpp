// prototype.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <map>

class PrinterProto {
public:
    virtual void Print() = 0;
    static PrinterProto* GetPrinter(std::string type) {
        return printers_[type] == nullptr ? nullptr : printers_[type]->Clone();
    }

    virtual void SetManufacturer(const std::string& name) = 0;
    virtual std::string GetManufacturer() = 0;

protected:
    virtual std::string GetType() = 0;
    //subclass must implement the Clone(), it should know how to copy a subclass object
    virtual PrinterProto *Clone() = 0;
    static void AddPrinterProto(PrinterProto* printer) {
        printers_[printer->GetType()] = printer;
    }

private:
    static std::map<std::string, PrinterProto*> printers_;
};
std::map<std::string, PrinterProto*> PrinterProto::printers_;

class HPPrinter : public PrinterProto {
public:
    void Print() override {
        std::cout << "HP printer, manufactured by " << manufacturer_ << std::endl;
    }

    //The object newly copied may change the its state or properties if required ,such as the manufacture here
    void SetManufacturer(const std::string& name) {
        manufacturer_ = name;
    }

    std::string GetManufacturer() {
        return manufacturer_;
    }

protected:
    std::string GetType() override {
        return "HP";
    }

    PrinterProto *Clone() override {
        return new HPPrinter(manufacturer_);
    }

private:
    HPPrinter() {
        AddPrinterProto(this);
    }

    HPPrinter(const std::string& name) {
        manufacturer_ = name;
    }

    std::string manufacturer_;
    static HPPrinter hp_printer_;
};
//create an static HPPrinter object
//This private and static object 'hp_printer_' is used as the Prototype object
//it will cause a call to the default constructor and then it would be registered as a Prototype
HPPrinter HPPrinter::hp_printer_;

class CanonPrinter : public PrinterProto {
public:
    void Print() override {
        std::cout << "Canon printer, manufactured by " << manufacturer_ << std::endl;
    }

    void SetManufacturer(const std::string& name) {
        manufacturer_ = name;
    }

    std::string GetManufacturer() {
        return manufacturer_;
    }

protected:
    std::string GetType() override {
        return "Canon";
    }

    PrinterProto *Clone() override {
        return new CanonPrinter(manufacturer_);
    }

private:
    CanonPrinter() {
        AddPrinterProto(this);
    }

    CanonPrinter(const std::string& name) {
        manufacturer_ = name;
    }

    std::string manufacturer_;
    static CanonPrinter canon_printer_;
};
CanonPrinter CanonPrinter::canon_printer_;


int main()
{
    PrinterProto* printer = PrinterProto::GetPrinter("Canon");
    if (printer) {
        printer->SetManufacturer("Cannon Japan");
        printer->Print();
    }

    return 0;
}

