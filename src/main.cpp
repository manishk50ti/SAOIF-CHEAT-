#include "../kiero/kiero.h"

#include <Windows.h>
#include <d3d11.h>
#include <cstdio>
#include <conio.h>

#include "game.h"
#include "features.h"

typedef long(__stdcall* Present)(IDXGISwapChain*, UINT, UINT);
static Present oPresent = NULL;

long __stdcall hkPresent11(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
    static bool init = false;
    if (!init) {
        Game::Init();
        init = true;
        printf("[SAOIF] Present hooked, Game::Init() done\n");
    }

    auto& f = Features::Get();
    f.RefreshAddresses();
    f.ApplyAll();

    return oPresent(pSwapChain, SyncInterval, Flags);
}

static void ToggleFeature(int index) {
    auto& f = Features::Get();
    switch (index) {
    case 0: f.Toggle(0); break;
    case 1: f.Toggle(1); break;
    case 2: f.Toggle(2); break;
    case 3: f.Toggle(3); break;
    case 4: f.Toggle(4); break;
    case 5: f.Toggle(5); break;
    case 6: f.Toggle(6); break;
    case 7: f.Toggle(7); break;
    case 8: f.Toggle(8); break;
    case 9: f.Toggle(9); break;
    }
}

void RunConsoleMenu() {
    bool visible = true;
    bool running = true;

    while (running) {
        if (visible) {
            Features::Get().ConsoleMenu();
        }

        int ch = _getch();
        

        if (ch == 27 || ch == 'q' || ch == 'Q') {
            running = false;
            continue;
        }

        if (ch == 'r' || ch == 'R') {
            Features::Get().RefreshAddresses();
            continue;
        }

        if (ch == 224) {
            ch = _getch();
            if (ch == 82) visible = !visible;
            continue;
        }

        if (ch >= '0' && ch <= '9') {
            int idx = (ch == '0') ? 9 : (ch - '1');
            
            ToggleFeature(idx);
            continue;
        }

        if (ch == '+' || ch == '=') {
            Features::Get().AdjustValue(1);
            continue;
        }
        if (ch == '-' || ch == '_') {
            Features::Get().AdjustValue(-1);
            continue;
        }

        printf("[dbg] unhandled key: 0x%02X ('%c')\n", ch, (ch >= 32 && ch < 127) ? ch : '?');
        printf("Press any key to continue...\n");
        _getch();
    }
}

DWORD WINAPI MainThread(LPVOID) {
    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    freopen_s((FILE**)stderr, "CONOUT$", "w", stderr);
    SetConsoleTitleA("SAOIF CHEAT | SLA:CHTS");

    printf("[SAOIF] Waiting for GameAssembly.dll...\n");
    while (!GetModuleHandleA("GameAssembly.dll")) Sleep(100);
    printf("[SAOIF] GameAssembly.dll found\n");

    for (int tries = 0; tries < 10; ++tries) {
        printf("[SAOIF] kiero init attempt %d...\n", tries + 1);
        kiero::Status::Enum status = kiero::init(kiero::RenderType::D3D11);
        if (status == kiero::Status::Success) {
            status = kiero::bind(8, (void**)&oPresent, hkPresent11);
            if (status == kiero::Status::Success) {
                printf("[SAOIF] Present hooked! Entering console menu...\n");
                RunConsoleMenu();
                printf("[SAOIF] Console menu ended.\n");
                return 1;
            }
        }
        Sleep(1000);
    }

    printf("[SAOIF] FAILED to hook Present after 10 tries.\n");
    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID) {
    DisableThreadLibraryCalls(hInstance);
    switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
        CreateThread(NULL, 0, MainThread, NULL, 0, NULL);
        break;
    case DLL_PROCESS_DETACH:
        kiero::shutdown();
        break;
    }
    return TRUE;
}
