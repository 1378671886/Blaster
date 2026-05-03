// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Projectile.generated.h"

UCLASS()
class BLASTER_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();
	virtual void Destroyed() override;

	/*
	* 与服务器端倒带一起使用
	*/
	bool bUseServerSideRewind = false;
	FVector_NetQuantize TraceStart;
	FVector_NetQuantize100 InitialVelocity;

	UPROPERTY(EditAnywhere)
	float InitialSpeed = 15000;

	//用于蓝图覆盖范围伤害
	UPROPERTY(EditAnywhere)
	float Damage = 20.f;

	//只对于射弹武器的爆头伤害
	UPROPERTY(EditAnywhere)
	float HeadShotDamage = 40.f;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* ImpactNiagara;

	UPROPERTY(EditAnywhere)
	class USoundCue* ImpactSound;

private:
	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* Tracer;

	UPROPERTY()
	class UNiagaraComponent* TracerComponent;

	

public:	
	virtual void Tick(float DeltaTime) override;

};
