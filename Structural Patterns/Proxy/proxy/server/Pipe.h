#pragma once
#include <Windows.h>
#include <string>

struct hPipe {
    void Close() {
        if (read) {
            ::CloseHandle(read);
        }

        if (write) {
            ::CloseHandle(write);
        }
    }

    HANDLE read = NULL;
    HANDLE write = NULL;
};

class Pipe
{
public:
    Pipe();
    ~Pipe();
    const hPipe& GetPipe() const;

    //Asynchronous (overlapped) read and write operations are not supported by anonymous pipes. 
    bool Create(const int size, const bool inheritable);
    std::string Read(const int size);
    bool Write(const std::string& data);

private:
    hPipe pipe_;
};

