// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ANCIENT_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttributeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void ReceiveDamage(float DamageAmount);
	void RegenStamina(float DeltaTime);
	void UseStamina(float StaminaCost);
	bool IsAlive();
	void AddGold(int32 Amount);
	void AddSoul(int32 Amount);
	FORCEINLINE float GetHealthPercent() const { return Health / MaxHealth; }
	FORCEINLINE float GetStaminaPercent() const { return Stamina / MaxStamina; }
	FORCEINLINE float GetStamina() const { return Stamina; }
	FORCEINLINE float GetDodgeCost() const { return DodgeCost; }
	FORCEINLINE int32 GetGold() const { return Gold; }
	FORCEINLINE int32 GetSoul() const { return Soul; }
private:
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float Health = 0.f;
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float MaxHealth = 0.f;
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float Stamina = 0.f;
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float MaxStamina = 0.f;
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float StaminaRegenRate = 0.f;
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float DodgeCost = 0.f;
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	int32 Gold = 0;
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	int32 Soul = 0;
};
