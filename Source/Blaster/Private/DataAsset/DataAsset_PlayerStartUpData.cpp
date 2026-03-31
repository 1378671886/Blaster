// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/DataAsset_PlayerStartUpData.h"
#include "AbilitySystem/BlasterAbilitySystemComponent.h"
#include "AbilitySystem/Ability/BlasterGameplayAbility_Player.h"


void UDataAsset_PlayerStartUpData::GiveToAbilitySystemComponent(UBlasterAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
    Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

    if (!InASCToGive) return;

    AActor* OwnerActor = InASCToGive->GetOwner();
    if (!OwnerActor || !OwnerActor->HasAuthority()) return;

    for (const FBlasterPlayerAbilitySet& AbilitySet : PlayerStartUpAbilitySets)
    {
        if (!AbilitySet.IsValid()) continue;

        FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
        AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
        AbilitySpec.Level = ApplyLevel;
        AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

        InASCToGive->GiveAbility(AbilitySpec);
    }
}
