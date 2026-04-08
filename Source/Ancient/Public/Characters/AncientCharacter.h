// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Characters/CharacterTypes.h"
#include "Interfaces/PickupInterface.h"
#include "AncientCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;
class AItem;
class UAnimMontage;
class UAncientOverlay;

UCLASS()
class ANCIENT_API AAncientCharacter : public ABaseCharacter, public IPickupInterface
{
	GENERATED_BODY()
public:	
	AAncientCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	/* <IHitInterface> */
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;
	/* </IHitInterface> */

	/* <IPickupInterface> */
	virtual void SetOverlappingItem(AItem* Item) override;
	virtual void AddGold(ATreasure* Gold) override;
	virtual void AddSoul(ASoul* Soul) override;
	/* </IPickupInterface> */
	FORCEINLINE AItem* GetOverlappingItem() const { return OverlappingItem; }
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
	FORCEINLINE EActionState GetActionState() const { return ActionState; }
protected:
	/* <AActor> */
	virtual void BeginPlay() override;
	/* </AActor> */

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void EKeyPressed();
	virtual void Attack() override;
	void Dodge();

	/* Combat */
	void EquipWeapon(AWeapon* Weapon);
	virtual void AttackEnd() override;
	virtual void DodgeEnd() override;
	virtual bool CanAttack() override;
	bool CanDisarm();
	bool CanArm();
	void Disarm();
	void Arm();
	void PlayEquipMontage(const FName& SectionName);
	virtual void Die_Implementation() override;


	UFUNCTION(BlueprintCallable)
	void AttachWeaponToBack();
	UFUNCTION(BlueprintCallable)
	void AttachWeaponToHand();
	UFUNCTION(BlueprintCallable)
	void FinishiEquipping();
	UFUNCTION(BlueprintCallable)
	void HitReactEnd();
private:
	void InitAncientOverlay();
	void UpdateAncientOverlay();
	UPROPERTY()
	UAncientOverlay* AncientOverlay = nullptr;
	/* Character Components */
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm = nullptr;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Hair")
	UGroomComponent* Hair = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Hair")
	UGroomComponent* Eyebrows = nullptr;
	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* EquipMontage = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EActionState ActionState = EActionState::EAS_Unoccupied;
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;
};
