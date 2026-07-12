#pragma once
#include <cstdint>
#include <Windows.h>

namespace IL2CPP {
    using MethodInfo = void;

    extern uintptr_t GameAssembly;

    bool Init();
    uintptr_t GetMethodAddr(uintptr_t rva);

    template<typename T>
    T GetMethod(uintptr_t rva) {
        return (T)GetMethodAddr(rva);
    }

    template<typename T>
    T Read(uintptr_t addr) {
        return *(T*)addr;
    }

    template<typename T>
    void Write(uintptr_t addr, T val) {
        *(T*)addr = val;
    }

    uintptr_t FollowPtr(uintptr_t addr);
}
