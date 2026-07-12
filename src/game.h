#pragma once
#include "il2cp.h"

namespace Game {

    namespace RVA {
        constexpr uintptr_t ManagerUtil_get_GameManager     = 0xCC4300;
        constexpr uintptr_t GameManager_get_CharacterManager = 0x613EF0;
        constexpr uintptr_t CharacterManager_get_ControlPlayerBase    = 0x6465D0;
        constexpr uintptr_t CharacterManager_get_PlayerCharacterBase  = 0x4C2860;
        constexpr uintptr_t PlayerBase_GetHp         = 0x84BA00;
        constexpr uintptr_t PlayerBase_GetMaxHp      = 0x84BB10;
        constexpr uintptr_t PlayerBase_SetHp         = 0x84E2F0;
        constexpr uintptr_t PlayerBase_SetHpRate     = 0x84E1F0;
        constexpr uintptr_t PlayerBase_get_Parameter = 0x6E18D0;
        constexpr uintptr_t PlayerParameter_get_Hp    = 0x4BAF40;
        constexpr uintptr_t PlayerParameter_set_Hp    = 0x5B4650;
        constexpr uintptr_t PlayerParameter_get_MaxHp = 0x4AA290;
        constexpr uintptr_t PlayerParameter_set_MaxHp = 0x54FF60;
        constexpr uintptr_t PlayerParameter_get_Sp    = 0x631E10;
        constexpr uintptr_t PlayerParameter_set_Sp    = 0x6A3580;
        constexpr uintptr_t PlayerParameter_get_MaxSp = 0x4D4C10;
        constexpr uintptr_t PlayerParameter_set_MaxSp = 0x4D4C20;
        constexpr uintptr_t PlayerParameter_get_HpRate= 0x5405E0;
        constexpr uintptr_t PlayerParameter_set_HpRate= 0x5407A0;
        constexpr uintptr_t MobParameter_get_Hp    = 0x4AA290;
        constexpr uintptr_t MobParameter_set_Hp    = 0x54FF60;
        constexpr uintptr_t MobParameter_get_MaxHp = 0x4AA320;
    }

    namespace Offset {

        namespace GameManager {
            constexpr uintptr_t m_characterManager  = 0x88;
        }

        namespace CharacterManager {
            constexpr uintptr_t m_ControlPlayer     = 0xA8;
            constexpr uintptr_t m_PlayerCharacter   = 0xB0;
        }

        namespace CharacterBase {
            constexpr uintptr_t m_BuffController    = 0xC8;
            constexpr uintptr_t m_walkSpeed         = 0x1F4;
            constexpr uintptr_t m_runSpeed          = 0x1F8;
            constexpr uintptr_t m_dashSpeed         = 0x1FC;
            constexpr uintptr_t m_moveSpeed         = 0x1E4;
            constexpr uintptr_t m_stepSpeed         = 0x200;
            constexpr uintptr_t m_DebuffSpeed       = 0x20C;
            constexpr uintptr_t m_DebuffMotion      = 0x210;
            constexpr uintptr_t isGrounded          = 0x89;
            constexpr uintptr_t m_targetable        = 0x108;
            constexpr uintptr_t m_skillTime         = 0x130;
        }

        namespace PlayerBase {
            constexpr uintptr_t m_Parameter         = 0x270;
            constexpr uintptr_t JumpHeight          = 0x2AC;
            constexpr uintptr_t IsJumping           = 0x2B4;
            constexpr uintptr_t Looking             = 0x288;
        }

        namespace PlayerParameter {
            constexpr uintptr_t Hp                  = 0x40;
            constexpr uintptr_t MaxHp               = 0x30;
            constexpr uintptr_t Sp                  = 0x48;
            constexpr uintptr_t MaxSp               = 0x38;
            constexpr uintptr_t HpRate              = 0x70;
            constexpr uintptr_t Level               = 0x28;
        }

        namespace Mob {
            constexpr uintptr_t m_Parameter         = 0x2A0;
        }

        namespace MobParameter {
            constexpr uintptr_t Hp                  = 0x30;
            constexpr uintptr_t MaxHp               = 0x28;
        }
    }

    using fn_get_Instance               = uintptr_t(*)(IL2CPP::MethodInfo*);
    using fn_get_CharacterManager       = uintptr_t(*)(uintptr_t gameMgr, IL2CPP::MethodInfo*);
    using fn_get_ControlPlayerBase      = uintptr_t(*)(uintptr_t charMgr, IL2CPP::MethodInfo*);
    using fn_get_Parameter              = uintptr_t(*)(uintptr_t playerBase, IL2CPP::MethodInfo*);
    using fn_get_long                   = int64_t(*)(uintptr_t obj, IL2CPP::MethodInfo*);
    using fn_set_long                   = void(*)(uintptr_t obj, int64_t val, IL2CPP::MethodInfo*);
    using fn_get_float                  = float(*)(uintptr_t obj, IL2CPP::MethodInfo*);
    using fn_set_float                  = void(*)(uintptr_t obj, float val, IL2CPP::MethodInfo*);
    using fn_get_int                    = int32_t(*)(uintptr_t obj, IL2CPP::MethodInfo*);
    using fn_set_int                    = void(*)(uintptr_t obj, int32_t val, IL2CPP::MethodInfo*);
    using fn_set_Hp                     = void(*)(uintptr_t playerBase, int64_t hp, IL2CPP::MethodInfo*);
    using fn_set_HpRate                 = void(*)(uintptr_t playerBase, int32_t rate, IL2CPP::MethodInfo*);

    extern fn_get_Instance              GameManager_Instance;
    extern fn_get_CharacterManager      GameManager_getCharMgr;
    extern fn_get_ControlPlayerBase     CharMgr_getControlPlayer;
    extern fn_get_Parameter             PlayerBase_getParameter;
    extern fn_get_long                  PlayerParameter_getHp;
    extern fn_set_long                  PlayerParameter_setHp;
    extern fn_get_long                  PlayerParameter_getMaxHp;
    extern fn_get_float                 PlayerParameter_getSp;
    extern fn_set_float                 PlayerParameter_setSp;
    extern fn_get_int                   PlayerParameter_getMaxSp;
    extern fn_set_int                   PlayerParameter_setMaxSp;
    extern fn_get_int                   PlayerParameter_getHpRate;
    extern fn_set_int                   PlayerParameter_setHpRate;
    extern fn_get_long                  PlayerBase_GetHp;
    extern fn_get_long                  PlayerBase_GetMaxHp;
    extern fn_set_Hp                    PlayerBase_SetHp;
    extern fn_set_HpRate                PlayerBase_SetHpRate;

    bool Init();

    uintptr_t GetGameManager();
    uintptr_t GetCharacterManager();
    uintptr_t GetControlPlayer();
    uintptr_t GetPlayerParameterDirect(uintptr_t playerBase);

    int64_t ReadHp_Direct(uintptr_t paramAddr);
    int64_t ReadMaxHp_Direct(uintptr_t paramAddr);
    void WriteHp_Direct(uintptr_t paramAddr, int64_t hp);
    float ReadSp_Direct(uintptr_t paramAddr);
    void WriteSp_Direct(uintptr_t paramAddr, float sp);
    int32_t ReadMaxSp_Direct(uintptr_t paramAddr);
    int32_t ReadLevel_Direct(uintptr_t paramAddr);
    int32_t ReadHpRate_Direct(uintptr_t paramAddr);
    void WriteHpRate_Direct(uintptr_t paramAddr, int32_t rate);
}
