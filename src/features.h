#pragma once
#include <cstdint>

class Features {
public:
    static Features& Get();

    void ApplyAll();
    void RefreshAddresses();

    void ConsoleMenu();
    bool IsPlayerFound() const { return m_playerBase != 0; }

    void Toggle(int index);
    void AdjustValue(int delta);

private:
    Features() = default;

    uintptr_t m_playerBase = 0;
    uintptr_t m_playerParam = 0;

    bool m_bGodMode       = false;
    bool m_bInfSP         = false;
    bool m_bSpeedHack     = false;
    bool m_bJumpHack      = false;
    bool m_bCustomWalk    = false;
    bool m_bCustomRun     = false;
    bool m_bCustomDash    = false;
    bool m_bOneHitKill    = false;
    bool m_bNoCooldown    = false;
    bool m_bRemoveDebuff  = false;
    bool m_bNoClip        = false;

    float m_fSpeedMult    = 2.0f;
    float m_fJumpMult     = 2.0f;
    float m_fWalkSpeed    = 5.0f;
    float m_fRunSpeed     = 10.0f;
    float m_fDashSpeed    = 15.0f;
    int   m_lastFloatIdx  = -1;

    void ApplyGodMode();
    void ApplyInfSP();
    void ApplySpeedHack();
    void ApplyJumpHack();
    void ApplyCustomWalk();
    void ApplyCustomRun();
    void ApplyCustomDash();
    void ApplyNoCooldown();
    void ApplyRemoveDebuff();
    void ApplyNoClip();
};
