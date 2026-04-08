// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Soul.generated.h"

/**
 * 
 */
UCLASS()
class ANCIENT_API ASoul : public AItem
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaTime) override;
	FORCEINLINE int32 GetSoulAmount() const { return SoulAmount; }
	FORCEINLINE void SetSoulAmount(int32 Amount) { SoulAmount = Amount; }
protected:
	virtual void BeginPlay() override;
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
private:
	UPROPERTY(EditAnywhere, Category = "Soul Properties")
	int32 SoulAmount = 1;
	UPROPERTY(EditAnywhere, Category = "Soul Properties")
	float DriftRate = 15.f;
	UPROPERTY(EditAnywhere, Category = "Soul Properties")
	float UPGroundOffset = 100.f;
	double DesiredZ = 0.f;
};
