// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/DataAsset_StartUpDataBase.h"
#include "AbilitySystem/BlasterAbilitySystemComponent.h"
#include "AbilitySystem/Ability/BlasterGameplayAbility.h"

void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UBlasterAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	check(InASCToGive);

	AActor* OwnerActor = InASCToGive->GetOwner();
	if (!OwnerActor || !OwnerActor->HasAuthority()) return;

	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);
}

void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UBlasterGameplayAbility>>& InAbilitiesToGive, UBlasterAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty()) return;

	for (const TSubclassOf<UBlasterGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;

		InASCToGive->GiveAbility(AbilitySpec);
	}
}
