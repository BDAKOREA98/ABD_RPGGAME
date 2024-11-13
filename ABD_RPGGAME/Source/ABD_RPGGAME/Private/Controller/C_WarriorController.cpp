// Vince Petrelli All Rights Reserved


#include "Controller/C_WarriorController.h"

AC_WarriorController::AC_WarriorController()
{
    HeroTeamID = FGenericTeamId(0);


}

FGenericTeamId AC_WarriorController::GetGenericTeamId() const
{
    return HeroTeamID; 
}
