// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/BlasterGameplayAbility.h"

#include "BlasterGameplayAbility_Player.generated.h"

class ABlasterCharacter_Player;
class ABlasterController_Player;

/**
 * 
 */
UCLASS()
class BLASTER_API UBlasterGameplayAbility_Player : public UBlasterGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure)
	ABlasterCharacter_Player* GetPlayerCharacterFromActorInfo();

private:
	TWeakObjectPtr<ABlasterCharacter_Player> CachedPlayerCharacter;

};
