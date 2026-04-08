// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class USphereComponent;
class UNiagaraComponent;
class UNiagaraSystem;

enum class EItemState : uint8
{
	EIS_Hovering,
	EIS_Equipped
};

UCLASS()
class ANCIENT_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	template<typename T>
	inline T Avg(T a, T b);
protected:
	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	virtual void SpawnPickupSystem();
	virtual void SpawnPickupSound();

	UFUNCTION(BlueprintPure, Category = "Sin Parameters")
	float TransformedSin();

	UFUNCTION(BlueprintPure, Category = "Cos Parameters")
	float TransformedCos();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sin Parameters")
	float Amplitude = 1.f; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sin Parameters")
	float TimeConstant = 5.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ItemMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere = nullptr;

	EItemState ItemState = EItemState::EIS_Hovering;

	UPROPERTY(EditAnywhere)
	UNiagaraComponent* ItemEffect = nullptr;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float RunningTime = 0.f;
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* PickupEffect = nullptr;
	UPROPERTY(EditAnywhere)
	USoundBase* PickupSound = nullptr;
};

template<typename T>
inline T AItem::Avg(T a, T b)
{
	return (a + b) / 2;
}
