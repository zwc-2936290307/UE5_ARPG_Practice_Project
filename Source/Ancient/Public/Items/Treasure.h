// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Treasure.generated.h"

/**
 * 
 */
UCLASS()
class ANCIENT_API ATreasure : public AItem
{
	GENERATED_BODY()
public:
	FORCEINLINE int32 GetGoldAmount() const { return GoldAmount; }
	FORCEINLINE void SetGoldAmount(int32 Amount) { GoldAmount = Amount; }
protected:
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
private:
	UPROPERTY(EditAnywhere, Category = "Treasure Properties")
	int32 GoldAmount = 0;
};
