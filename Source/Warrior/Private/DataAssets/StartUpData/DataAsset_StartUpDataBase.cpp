// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "AbilitySystem/WariorAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"

void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UWariorAbilitySystemComponent *InWarriorACSToGive, int32 ApplyLevel)
{
    check(InWarriorACSToGive);

    GrantAbilities(ActivateOnGivenAbilities, InWarriorACSToGive, ApplyLevel);
    GrantAbilities(ReactedAbilities, InWarriorACSToGive, ApplyLevel);
}
void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UWarriorGameplayAbility>> &InAbilitiesToGive, UWariorAbilitySystemComponent *InWarriorACSToGive, int32 ApplyLevel)
{
    if(InAbilitiesToGive.IsEmpty())
    {
        return;
    }
    for(const TSubclassOf<UWarriorGameplayAbility>& Ability : InAbilitiesToGive)
    {
        if(!Ability) continue;

        FGameplayAbilitySpec AbilitySpec(Ability);
        AbilitySpec.SourceObject = InWarriorACSToGive->GetAvatarActor();
        AbilitySpec.Level = ApplyLevel;

        InWarriorACSToGive->GiveAbility(AbilitySpec);
    }
}