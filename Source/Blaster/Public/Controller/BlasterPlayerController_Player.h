// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BlasterPlayerController_Player.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API ABlasterPlayerController_Player : public APlayerController
{
	GENERATED_BODY()

public:
	void SetHUDHealth(float Health, float MaxHealth);
	void SetHUDScore(float Score);
	void SetHUDDefeats(int32 Defeats);
	void SetHUDWeaponAmmo(int32 Ammo);
	void SetHUDCarriedAmmo(int32 Ammo);
	void SetHUDMatchCountdown(float CountdownTime);
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual float GetServerTime(); //与服务器时钟同步
	virtual void ReceivedPlayer() override; //尽快同步服务器时钟
	void OnMatchStateSet(FName State);
protected:
	virtual void BeginPlay() override;
	void SetHUDTime();
	void PollInit();

	/*
	* 客户端和服务器的时间同步
	*/

	//请求服务器时间，发送请求时传入客户端当前时间
	UFUNCTION(Server, Reliable)
	void ServerRequestServerTime(float TimeOfClientRequest);

	//响应 ServerRequestServerTime 时，向客户端报告当前的服务器时间
	UFUNCTION(Client, Reliable)
	void ClientReportServerTime(float TimeOfClientRequest, float TimeServerReceivedClientRequest);

	float ClientServerDelta = 0.f; //客户端和服务器的时间差

	UPROPERTY(EditAnywhere, Category = "Time")
	float TimeSyncFrequency = 5.f; //每隔多少秒同步一次时间

	float TimeSyncRunningTime = 0.f;

	void CheckTimeSync(float DeltaTime);

private:
	UPROPERTY()
	class ABlasterHUD* BlasterHUD;
	
	UPROPERTY(EditAnywhere)
	float MatchTime = 120.f;

	uint32 CountdownInt = 0;

	UPROPERTY(ReplicatedUsing = OnRep_MatchState)
	FName MatchState;
	
	UFUNCTION()
	void OnRep_MatchState();

	UPROPERTY()
	class UCharacterOverlay* CharacterOverlay;

	bool bInitializeCharacterOverlay = false;

	float HUDHealth;
	bool bInitializeHealth = false;
	float HUDMaxHealth;
	float HUDScore;
	bool bInitializeScore = false;
	int32 HUDDefeats;
	bool bInitializeDefeats = false;
	int32 HUDGrenades;
	bool bInitializeGrenades = false;
	float HUDShield;
	bool bInitializeShield = false;
	float HUDMaxShield;
	float HUDCarriedAmmo;
	bool bInitializeCarriedAmmo = false;
	float HUDWeaponAmmo;
	bool bInitializeWeaponAmmo = false;

};
