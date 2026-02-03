// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "AbilitySystem/WariorAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"

void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UWariorAbilitySystemComponent *InACSToGive, int32 ApplyLevel)
{
    check(InACSToGive);

    GrantAbilities(ActivateOnGivenAbilities, InACSToGive, ApplyLevel);
    GrantAbilities(ReactedAbilities, InACSToGive, ApplyLevel);
}
void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UWarriorGameplayAbility>> &InAbilitiesToGive, UWariorAbilitySystemComponent *InACSToGive, int32 ApplyLevel)
{
    if(InAbilitiesToGive.IsEmpty())
    {
        return;
    }
    for(const TSubclassOf<UWarriorGameplayAbility>& Ability : InAbilitiesToGive)
    {
        if(!Ability) continue;

        FGameplayAbilitySpec AbilitySpec(Ability);
        AbilitySpec.SourceObject = InACSToGive->GetAvatarActor();
        AbilitySpec.Level = ApplyLevel;

        InACSToGive->GiveAbility(AbilitySpec);
    }
}