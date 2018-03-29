#include "stdafx.h"
#include "Pipe.h"


Pipe::Pipe()
{
}


Pipe::~Pipe() {
    pipe_.Close();
}

const hPipe& Pipe::GetPipe() const {
    return pipe_;
}

bool Pipe::Create(const int size, const bool inheritable) {
    SECURITY_ATTRIBUTES security;
    memset(&security, 0 , sizeof(SECURITY_ATTRIBUTES));
    security.nLength = sizeof(SECURITY_ATTRIBUTES);
    security.bInheritHandle = inheritable ? TRUE : FALSE;
    BOOL succeed = CreatePipe(&pipe_.read, &pipe_.write, &security, size);
    return succeed == TRUE;
}

std::string Pipe::Read(const int size) {
    char *buffer = new char[size];
    memset(buffer, 0, size);
    DWORD bytes_read = 0;
    BOOL succeed = ReadFile(pipe_.read, buffer, size, &bytes_read, NULL);
    if (succeed) {
        std::string data;
        data.assign(buffer, size);
        return data;
    }

    return "";
}

bool Pipe::Write(const std::string& data) {
    DWORD bytes_written = 0;
    BOOL succeed = WriteFile(pipe_.write, data.c_str(), data.size(), &bytes_written, NULL);

    return succeed == TRUE;
}