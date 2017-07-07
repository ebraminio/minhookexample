// Just changed https://www.codeproject.com/Articles/44326/MinHook-The-Minimalistic-x-x-API-Hooking-Libra a bit
#include <windows.h>
#include "MinHook.h"

typedef DWORD (WINAPI *GETSYSCOLOR)(int);

// Pointer for calling original GetSysColor.
GETSYSCOLOR fpGetSysColor = NULL;

// Detour function which overrides GetSysColor.
int WINAPI DetourGetSysColor(int nIndex) {
    return 0xA0A0A0;
}

int main() {
    // Initialize MinHook.
    if (MH_Initialize() != MH_OK) {
        return 1;
    }

    // Create a hook for MessageBoxW, in disabled state.
    if (MH_CreateHook((LPVOID) &GetSysColor, (LPVOID) &DetourGetSysColor, 
        reinterpret_cast<LPVOID*>(&fpGetSysColor)) != MH_OK) {
        return 1;
    }

    // or you can use the new helper function like this.
    // if (MH_CreateHookApiEx(L"user32", "MessageBoxW", &DetourMessageBoxW, &fpMessageBoxW) != MH_OK) {
    //    return 1;
    // }

    MessageBoxW(NULL, L"You shouldn't see me if I'm hooked", L"Not hooked", MB_OK);
    
    // Enable the hook for MessageBoxW.
    if (MH_EnableHook((LPVOID) &GetSysColor) != MH_OK) {
        return 1;
    }

    // Expected to tell "Hooked!".
    MessageBoxW(NULL, L"You shouldn't see me if I'm hooked", L"Hooked", MB_OK);

    // Disable the hook for MessageBoxW.
    if (MH_DisableHook((LPVOID) &GetSysColor) != MH_OK) {
        return 1;
    }

    // Uninitialize MinHook.
    if (MH_Uninitialize() != MH_OK) {
        return 1;
    }

    return 0;
}
