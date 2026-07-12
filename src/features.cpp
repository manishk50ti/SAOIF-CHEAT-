#include "features.h"
#include "game.h"
#include <cstdio>
#include <conio.h>

Features& Features::Get() {
    static Features instance;
    return instance;
}

void Features::RefreshAddresses() {
    m_playerBase = Game::GetControlPlayer();
    if (m_playerBase) {
        m_playerParam = Game::GetPlayerParameterDirect(m_playerBase);
    } else {
        m_playerParam = 0;
    }
}

void Features::ApplyGodMode() {
    if (!m_playerParam) return;
    int64_t maxHp = Game::ReadMaxHp_Direct(m_playerParam);
    Game::WriteHp_Direct(m_playerParam, maxHp);
    Game::WriteHpRate_Direct(m_playerParam, 100);
}

void Features::ApplyInfSP() {
    if (!m_playerParam) return;
    int32_t maxSp = Game::ReadMaxSp_Direct(m_playerParam);
    Game::WriteSp_Direct(m_playerParam, (float)maxSp);
}

void Features::ApplySpeedHack() {
    if (!m_playerBase) return;
    uintptr_t base = m_playerBase;
    IL2CPP::Write<float>(base + Game::Offset::CharacterBase::m_moveSpeed, 3.5f * m_fSpeedMult);
}

void Features::ApplyJumpHack() {
    if (!m_playerBase) return;
    uintptr_t jumpField = m_playerBase + Game::Offset::PlayerBase::JumpHeight;
    float baseJump = 1.0f;
    IL2CPP::Write<float>(jumpField, baseJump * m_fJumpMult);
}

void Features::ApplyCustomWalk() {
    if (!m_playerBase) return;
    IL2CPP::Write<float>(m_playerBase + Game::Offset::CharacterBase::m_walkSpeed, m_fWalkSpeed);
}

void Features::ApplyCustomRun() {
    if (!m_playerBase) return;
    IL2CPP::Write<float>(m_playerBase + Game::Offset::CharacterBase::m_runSpeed, m_fRunSpeed);
}

void Features::ApplyCustomDash() {
    if (!m_playerBase) return;
    IL2CPP::Write<float>(m_playerBase + Game::Offset::CharacterBase::m_dashSpeed, m_fDashSpeed);
}

void Features::ApplyNoCooldown() {
    if (!m_playerBase) return;
    IL2CPP::Write<float>(m_playerBase + Game::Offset::CharacterBase::m_skillTime, 0.0f);
    uintptr_t buffCtrl = IL2CPP::Read<uintptr_t>(m_playerBase + Game::Offset::CharacterBase::m_BuffController);
}

void Features::ApplyRemoveDebuff() {
    if (!m_playerBase) return;
    IL2CPP::Write<float>(m_playerBase + Game::Offset::CharacterBase::m_DebuffSpeed, 0.0f);
    IL2CPP::Write<float>(m_playerBase + Game::Offset::CharacterBase::m_DebuffMotion, 0.0f);
}

void Features::ApplyNoClip() {
    if (!m_playerBase) return;
    IL2CPP::Write<bool>(m_playerBase + Game::Offset::CharacterBase::m_targetable, true);
    IL2CPP::Write<bool>(m_playerBase + 0x38, false);
}

void Features::ApplyAll() {
    if (!m_playerBase || !m_playerParam) {
        RefreshAddresses();
        return;
    }

    if (Game::ReadMaxHp_Direct(m_playerParam) <= 0 || Game::ReadMaxHp_Direct(m_playerParam) > 999999999) {
        RefreshAddresses();
        return;
    }

    if (m_bGodMode)       ApplyGodMode();
    if (m_bInfSP)         ApplyInfSP();
    if (m_bSpeedHack)     ApplySpeedHack();
    if (m_bJumpHack)      ApplyJumpHack();
    if (m_bCustomWalk)    ApplyCustomWalk();
    if (m_bCustomRun)     ApplyCustomRun();
    if (m_bCustomDash)    ApplyCustomDash();
    if (m_bNoCooldown)    ApplyNoCooldown();
    if (m_bRemoveDebuff)  ApplyRemoveDebuff();
    if (m_bNoClip)        ApplyNoClip();
}

void Features::ConsoleMenu() {
    system("cls");
    printf("==========================================\n");
    printf("      SAOIF CHEAT MENU | SLA:CHTS STILL ON DEVLOPMENT\n");
    printf("==========================================\n");
    printf("  Status: %s\n\n", m_playerBase ? "IN GAME" : "NO PLAYER");
    printf("  [INS] Hide/show  [R] Refresh  [Q] Quit\n\n");

    printf("  1. God Mode              %s\n", m_bGodMode ? "ON" : "OFF");
    printf("  2. Infinite SP           %s\n", m_bInfSP ? "ON" : "OFF");
    //printf("  3. Speed Hack            %s  (%.1fx)\n", m_bSpeedHack ? "ON" : "OFF", m_fSpeedMult);
    //printf("  4. Jump Hack             %s  (%.1fx)\n", m_bJumpHack ? "ON" : "OFF", m_fJumpMult);
    //printf("  5. Custom Walk           %s  (%.1f)\n", m_bCustomWalk ? "ON" : "OFF", m_fWalkSpeed);
    printf("  6. Custom Run            %s  (%.1f)\n", m_bCustomRun ? "ON" : "OFF", m_fRunSpeed);
    //printf("  7. Custom Dash           %s  (%.1f)\n", m_bCustomDash ? "ON" : "OFF", m_fDashSpeed);
    //printf("  8. No Cooldown           %s\n", m_bNoCooldown ? "ON" : "OFF");
    //printf("  9. Remove Debuffs        %s\n", m_bRemoveDebuff ? "ON" : "OFF");
    //printf("  0. No Clip              %s\n", m_bNoClip ? "ON" : "OFF");

    printf("\n  [+/-] Adjust value   [R] Refresh   [Q] Quit\n");
    printf("==========================================\n");

    if (m_playerParam) {
        int64_t hp  = Game::ReadHp_Direct(m_playerParam);
        int64_t mhp = Game::ReadMaxHp_Direct(m_playerParam);
        float sp    = Game::ReadSp_Direct(m_playerParam);
        int32_t msp = Game::ReadMaxSp_Direct(m_playerParam);
        int32_t lvl = Game::ReadLevel_Direct(m_playerParam);
        printf("\n  HP: %lld/%lld   SP: %.1f/%d   Lv: %d\n", hp, mhp, sp, msp, lvl);

        if (m_playerBase) {
            float walk = IL2CPP::Read<float>(m_playerBase + Game::Offset::CharacterBase::m_walkSpeed);
            float run  = IL2CPP::Read<float>(m_playerBase + Game::Offset::CharacterBase::m_runSpeed);
            float dash = IL2CPP::Read<float>(m_playerBase + Game::Offset::CharacterBase::m_dashSpeed);
            float move = IL2CPP::Read<float>(m_playerBase + Game::Offset::CharacterBase::m_moveSpeed);
            printf("  Walk:%.1f  Run:%.1f  Dash:%.1f  Move:%.1f\n", walk, run, dash, move);
        }
    }

    printf("\n  [Press feature number 1-6 to toggle]");
}

void Features::Toggle(int index) {
    switch (index) {
    case 0: m_bGodMode = !m_bGodMode; break;
    case 1: m_bInfSP = !m_bInfSP; break;
    case 2: m_bSpeedHack = !m_bSpeedHack; m_lastFloatIdx = 2; break;
    case 3: m_bJumpHack = !m_bJumpHack;   m_lastFloatIdx = 3; break;
    case 4: m_bCustomWalk = !m_bCustomWalk; m_lastFloatIdx = 4; break;
    case 5: m_bCustomRun = !m_bCustomRun; m_lastFloatIdx = 5; break;
    case 6: m_bCustomDash = !m_bCustomDash; m_lastFloatIdx = 6; break;
    case 7: m_bNoCooldown = !m_bNoCooldown; break;
    case 8: m_bRemoveDebuff = !m_bRemoveDebuff; break;
    case 9: m_bNoClip = !m_bNoClip; break;
    }
}

void Features::AdjustValue(int delta) {
    float step = 0.1f;
    switch (m_lastFloatIdx) {
    case 2:
        step = 0.1f;
        m_fSpeedMult = max(0.1f, m_fSpeedMult + delta * step);
        break;
    case 3:
        step = 0.1f;
        m_fJumpMult = max(0.1f, m_fJumpMult + delta * step);
        break;
    case 4:
        step = 0.5f;
        m_fWalkSpeed = max(0.1f, m_fWalkSpeed + delta * step);
        break;
    case 5:
        step = 0.5f;
        m_fRunSpeed = max(0.1f, m_fRunSpeed + delta * step);
        break;
    case 6:
        step = 0.5f;
        m_fDashSpeed = max(0.1f, m_fDashSpeed + delta * step);
        break;
    }
}
