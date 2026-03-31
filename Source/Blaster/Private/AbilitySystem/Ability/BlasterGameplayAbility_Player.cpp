// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/BlasterGameplayAbility_Player.h"
#include"Character/BlasterCharacter_Player.h"
#include"Controller/BlasterPlayerController_Player.h"

ABlasterCharacter_Player* UBlasterGameplayAbility_Player::GetPlayerCharacterFromActorInfo()
{
	if (!CachedPlayerCharacter.IsValid())
	{
		CachedPlayerCharacter = Cast<ABlasterCharacter_Player>(CurrentActorInfo->AvatarActor);
	}

	return CachedPlayerCharacter.IsValid() ? CachedPlayerCharacter.Get() : nullptr;
}

