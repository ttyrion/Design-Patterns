// client.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <string>
#include <iostream>

int main()
{
    HANDLE hReadPipe = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hWritePipe = GetStdHandle(STD_OUTPUT_HANDLE);

    const int buffer_size = 1024;
    char *buffer = new char[buffer_size];
    while (true) {
        memset(buffer, 0, buffer_size);
        DWORD bytes_read = 0;
        BOOL succeed = ::ReadFile(hReadPipe, buffer, buffer_size, &bytes_read, NULL);
        if (succeed) {
            std::string data(buffer, bytes_read);
            if (data == "quit") {
                std::string response("[client]: quit");
                DWORD bytes_written = 0;
                WriteFile(hWritePipe, response.c_str(), response.size(), &bytes_written, NULL);
                break;
            }

            std::string response("[client]: ");
            response.append(data);
            DWORD bytes_written = 0;
            BOOL succeed = WriteFile(hWritePipe, response.c_str(), response.size(), &bytes_written, NULL);
            if (!succeed) {
                break;
            }
        }
        else break;
    }

    return 0;
}

