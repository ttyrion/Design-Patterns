// server.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Pipe.h"
#include <string>
#include <iostream>

int main()
{
    Pipe read_pipe;
    read_pipe.Create(1024, true);
    Pipe write_pipe;
    write_pipe.Create(1024, true);
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));    

    si.cb = sizeof(STARTUPINFO);
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdInput = write_pipe.GetPipe().read;
    si.hStdOutput = read_pipe.GetPipe().write;
    si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    
    WCHAR child[] = L"client.exe";

    if (CreateProcess(
        NULL,           // No module name (use command line)
        child,  // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        TRUE,           // Set handle inheritance to TRUE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi)            // Pointer to PROCESS_INFORMATION structure
        )
    {
        // CreateProcess successfully
        std::string msg("[server] hello...");
        write_pipe.Write(msg);
        std::cout << "send " << msg << std::endl;

        std::string data = read_pipe.Read(1024);
        std::cout << "receive " << data.c_str() << std::endl;

        msg = "quit";
        write_pipe.Write(msg);
        std::cout << "send " << msg << std::endl;

        data = read_pipe.Read(1024);
        std::cout << "receive " << data.c_str() << std::endl;
    }
    else {
        std::cout << "create client failed." << std::endl;
    }

    return 0;
}

