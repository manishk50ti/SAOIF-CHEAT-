#include "il2cp.h"

namespace IL2CPP {
    uintptr_t GameAssembly = 0;

    bool Init() {
        GameAssembly = (uintptr_t)GetModuleHandleA("GameAssembly.dll");
        return GameAssembly != 0;
    }

    uintptr_t GetMethodAddr(uintptr_t rva) {
        return GameAssembly + rva;
    }

    uintptr_t FollowPtr(uintptr_t addr) {
        if (!addr) return 0;
        return *(uintptr_t*)addr;
    }
}
