#include "pch.h"
#include <stdlib.h>

struct MaybeGameInfo {
    char padding0[80];
    unsigned __int64* ptrToGetDLCCount;          
};
typedef struct MaybeGameInfo MaybeGameInfo;

struct SteamContext {
    unsigned __int64** firstPtrToDummyReturns1;           // Pointer at offset 0
    char padding0[40];     // Padding to ensure ptr2 is at offset 48
    MaybeGameInfo** ptrToPtrToMaybeGameInfo;         // Integer at offset 48
    char padding1[72]; //Padding to offset 128
};
typedef struct SteamContext SteamContext;
int dummyReturns1() {
    return 1;
}

int getGameDLCCount() {
    return 0;
}

void (*dummyFuncPtr)() = &dummyReturns1;
int (*ptrToGetGameDLCCount)() = &getGameDLCCount;
SteamContext steamContext;

// Function definition with proper return value
__declspec(dllexport) SteamContext SteamInternal_ContextInit() {
    MaybeGameInfo* ptrToMaybeGameInfo = (MaybeGameInfo*)malloc(sizeof(MaybeGameInfo));
    ptrToMaybeGameInfo->ptrToGetDLCCount = ptrToGetGameDLCCount;
    steamContext.ptrToPtrToMaybeGameInfo = (MaybeGameInfo**)malloc(sizeof(MaybeGameInfo*));
    *(steamContext.ptrToPtrToMaybeGameInfo) = ptrToMaybeGameInfo;

    unsigned __int64 *ptr3 = &((unsigned __int64)dummyFuncPtr);
    unsigned __int64 ptr2 = (unsigned __int64)ptr3 - 168;
    unsigned __int64* ptr1 = &ptr2;
    steamContext.firstPtrToDummyReturns1 = ptr1;
    return steamContext;          
}


__declspec(dllexport) int SteamAPI_Init() {
    return 1;
}
__declspec(dllexport) int SteamAPI_RestartAppIfNecessary() {
    return 0;
}


__declspec(dllexport) int SteamAPI_GetHSteamPipe() {
    return 1;
}
__declspec(dllexport) int SteamInternal_CreateInterface() {
    return 1;
}
__declspec(dllexport) int SteamAPI_Shutdown() {
    return 1;
}
__declspec(dllexport) int SteamAPI_RunCallbacks() {
    return 1;
}
__declspec(dllexport) int SteamAPI_GetHSteamUser() {
    return 1;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    
    return TRUE;
}

