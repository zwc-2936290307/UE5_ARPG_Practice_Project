// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Characters/CharacterTypes.h"
#include "AncientAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ANCIENT_API UAncientAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	class AAncientCharacter* AncientCharacter = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	class UCharacterMovementComponent* AncientCharacterMovement = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float GroundSpeed = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool IsFalling = false;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	EActionState ActionState = EActionState::EAS_Unoccupied;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	TEnumAsByte<EDeathPose> DeathPose = EDeathPose::EDP_Death1;
};
