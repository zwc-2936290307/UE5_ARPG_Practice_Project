// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AncientHUD.generated.h"

/**
 * 
 */
class UAncientOverlay;

UCLASS()
class ANCIENT_API AAncientHUD : public AHUD
{
	GENERATED_BODY()
public:
	FORCEINLINE UAncientOverlay* GetAncientOverlay() const { return AncientOverlay; };
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditDefaultsOnly, Category = Ancient)
	TSubclassOf<UAncientOverlay> AncientOverlayClass;

	UPROPERTY()
	UAncientOverlay* AncientOverlay;
};
