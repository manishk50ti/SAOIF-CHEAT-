#include "game.h"

namespace Game {

    fn_get_Instance              GameManager_Instance       = nullptr;
    fn_get_CharacterManager      GameManager_getCharMgr     = nullptr;
    fn_get_ControlPlayerBase     CharMgr_getControlPlayer   = nullptr;
    fn_get_Parameter             PlayerBase_getParameter    = nullptr;
    fn_get_long                  PlayerParameter_getHp      = nullptr;
    fn_set_long                  PlayerParameter_setHp      = nullptr;
    fn_get_long                  PlayerParameter_getMaxHp   = nullptr;
    fn_get_float                 PlayerParameter_getSp      = nullptr;
    fn_set_float                 PlayerParameter_setSp      = nullptr;
    fn_get_int                   PlayerParameter_getMaxSp   = nullptr;
    fn_set_int                   PlayerParameter_setMaxSp   = nullptr;
    fn_get_int                   PlayerParameter_getHpRate  = nullptr;
    fn_set_int                   PlayerParameter_setHpRate  = nullptr;
    fn_get_long                  PlayerBase_GetHp           = nullptr;
    fn_get_long                  PlayerBase_GetMaxHp        = nullptr;
    fn_set_Hp                    PlayerBase_SetHp           = nullptr;
    fn_set_HpRate                PlayerBase_SetHpRate       = nullptr;

    bool Init() {
        if (!IL2CPP::Init()) return false;

        GameManager_Instance         = IL2CPP::GetMethod<fn_get_Instance>(RVA::ManagerUtil_get_GameManager);
        GameManager_getCharMgr       = IL2CPP::GetMethod<fn_get_CharacterManager>(RVA::GameManager_get_CharacterManager);
        CharMgr_getControlPlayer     = IL2CPP::GetMethod<fn_get_ControlPlayerBase>(RVA::CharacterManager_get_ControlPlayerBase);
        PlayerBase_getParameter      = IL2CPP::GetMethod<fn_get_Parameter>(RVA::PlayerBase_get_Parameter);
        PlayerParameter_getHp        = IL2CPP::GetMethod<fn_get_long>(RVA::PlayerParameter_get_Hp);
        PlayerParameter_setHp        = IL2CPP::GetMethod<fn_set_long>(RVA::PlayerParameter_set_Hp);
        PlayerParameter_getMaxHp     = IL2CPP::GetMethod<fn_get_long>(RVA::PlayerParameter_get_MaxHp);
        PlayerParameter_getSp        = IL2CPP::GetMethod<fn_get_float>(RVA::PlayerParameter_get_Sp);
        PlayerParameter_setSp        = IL2CPP::GetMethod<fn_set_float>(RVA::PlayerParameter_set_Sp);
        PlayerParameter_getMaxSp     = IL2CPP::GetMethod<fn_get_int>(RVA::PlayerParameter_get_MaxSp);
        PlayerParameter_setMaxSp     = IL2CPP::GetMethod<fn_set_int>(RVA::PlayerParameter_set_MaxSp);
        PlayerParameter_getHpRate    = IL2CPP::GetMethod<fn_get_int>(RVA::PlayerParameter_get_HpRate);
        PlayerParameter_setHpRate    = IL2CPP::GetMethod<fn_set_int>(RVA::PlayerParameter_set_HpRate);
        PlayerBase_GetHp             = IL2CPP::GetMethod<fn_get_long>(RVA::PlayerBase_GetHp);
        PlayerBase_GetMaxHp          = IL2CPP::GetMethod<fn_get_long>(RVA::PlayerBase_GetMaxHp);
        PlayerBase_SetHp             = IL2CPP::GetMethod<fn_set_Hp>(RVA::PlayerBase_SetHp);
        PlayerBase_SetHpRate         = IL2CPP::GetMethod<fn_set_HpRate>(RVA::PlayerBase_SetHpRate);

        return true;
    }

    uintptr_t GetGameManager() {
        if (!GameManager_Instance) return 0;
        return GameManager_Instance(nullptr);
    }

    uintptr_t GetCharacterManager() {
        uintptr_t gm = GetGameManager();
        if (!gm || !GameManager_getCharMgr) return 0;
        return GameManager_getCharMgr(gm, nullptr);
    }

    uintptr_t GetControlPlayer() {
        uintptr_t cm = GetCharacterManager();
        if (!cm || !CharMgr_getControlPlayer) return 0;
        return CharMgr_getControlPlayer(cm, nullptr);
    }

    uintptr_t GetPlayerParameterDirect(uintptr_t playerBase) {
        if (!playerBase || !PlayerBase_getParameter) return 0;
        return PlayerBase_getParameter(playerBase, nullptr);
    }

    int64_t ReadHp_Direct(uintptr_t paramAddr) {
        if (!paramAddr) return 0;
        return IL2CPP::Read<int64_t>(paramAddr + Offset::PlayerParameter::Hp);
    }

    int64_t ReadMaxHp_Direct(uintptr_t paramAddr) {
        if (!paramAddr) return 0;
        return IL2CPP::Read<int64_t>(paramAddr + Offset::PlayerParameter::MaxHp);
    }

    void WriteHp_Direct(uintptr_t paramAddr, int64_t hp) {
        if (!paramAddr) return;
        IL2CPP::Write<int64_t>(paramAddr + Offset::PlayerParameter::Hp, hp);
    }

    float ReadSp_Direct(uintptr_t paramAddr) {
        if (!paramAddr) return 0;
        return IL2CPP::Read<float>(paramAddr + Offset::PlayerParameter::Sp);
    }

    void WriteSp_Direct(uintptr_t paramAddr, float sp) {
        if (!paramAddr) return;
        IL2CPP::Write<float>(paramAddr + Offset::PlayerParameter::Sp, sp);
    }

    int32_t ReadMaxSp_Direct(uintptr_t paramAddr) {
        if (!paramAddr) return 0;
        return IL2CPP::Read<int32_t>(paramAddr + Offset::PlayerParameter::MaxSp);
    }

    int32_t ReadLevel_Direct(uintptr_t paramAddr) {
        if (!paramAddr) return 0;
        return IL2CPP::Read<int32_t>(paramAddr + Offset::PlayerParameter::Level);
    }

    int32_t ReadHpRate_Direct(uintptr_t paramAddr) {
        if (!paramAddr) return 0;
        return IL2CPP::Read<int32_t>(paramAddr + Offset::PlayerParameter::HpRate);
    }

    void WriteHpRate_Direct(uintptr_t paramAddr, int32_t rate) {
        if (!paramAddr) return;
        IL2CPP::Write<int32_t>(paramAddr + Offset::PlayerParameter::HpRate, rate);
    }
}
