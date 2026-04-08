// Fill out your copyright notice in the Description page of Project Settings.

#include "Ancient/Ancient.h"
#include "Characters/AncientAnimInstance.h"
#include "Characters/AncientCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/kismetMathLibrary.h"

void UAncientAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	AncientCharacter = Cast<AAncientCharacter>(TryGetPawnOwner());
	if (AncientCharacter)
	{
		AncientCharacterMovement = AncientCharacter->GetCharacterMovement();
	}
}

void UAncientAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (AncientCharacterMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(AncientCharacterMovement->Velocity);
		IsFalling = AncientCharacterMovement->IsFalling();
		CharacterState = AncientCharacter->GetCharacterState();
		ActionState = AncientCharacter->GetActionState();
		DeathPose = AncientCharacter->GetDeathPose();
	}
}
