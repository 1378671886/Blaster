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

	virtual float GetServerTime(); //与服务器时钟同步
	virtual void ReceivedPlayer() override; //尽快同步服务器时钟
protected:
	virtual void BeginPlay() override;
	void SetHUDTime();

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

};
