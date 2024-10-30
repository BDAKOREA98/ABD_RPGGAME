// Vince Petrelli All Rights Reserved


#include "Animation/Hero/C_WarriorLinkedLayer.h"
#include "Animation/Hero/C_WarriorHeroAnimInstance.h"
UC_WarriorHeroAnimInstance* UC_WarriorLinkedLayer::GetHeroAnimInstance() const
{
    return  Cast< UC_WarriorHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
