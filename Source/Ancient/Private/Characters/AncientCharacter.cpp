// Fill out your copyright notice in the Description page of Project Settings.

#include "Ancient/Ancient.h"
#include "Characters/AncientCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GroomComponent.h"
#include "Components/AttributeComponent.h"
#include "Items/Item.h"
#include "Items/Weapons/Weapon.h"
#include "Animation/AnimMontage.h"
#include "HUD/AncientHUD.h"
#include "HUD/AncientOverlay.h"
#include "Interfaces/PickupInterface.h"
#include "Items/Soul.h"
#include "Items/Treasure.h"

// Sets default values
AAncientCharacter::AAncientCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 300.0f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(SpringArm);

	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	Hair->SetupAttachment(GetMesh());
	Hair->AttachmentName = TEXT("head");

	Eyebrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyebrows"));
	Eyebrows->SetupAttachment(GetMesh());
	Eyebrows->AttachmentName = TEXT("head");
}

void AAncientCharacter::Tick(float DeltaTime)
{
	if(Attributes && AncientOverlay)
	{
		Attributes->RegenStamina(DeltaTime);
		AncientOverlay->SetStaminaBarPercent(Attributes->GetStaminaPercent());
	}
}

// Called to bind functionality to input
void AAncientCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AAncientCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AAncientCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AAncientCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AAncientCharacter::LookUp);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AAncientCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Equip"), IE_Pressed, this, &AAncientCharacter::EKeyPressed);
	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &AAncientCharacter::Attack);
	PlayerInputComponent->BindAction(TEXT("Dodge"), IE_Pressed, this, &AAncientCharacter::Dodge);
}

void AAncientCharacter::Jump()
{
	if (ActionState != EActionState::EAS_Unoccupied)
		return;
	Super::Jump();
}

float AAncientCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	HandleDamage(DamageAmount);
	if (AncientOverlay && Attributes)
	{
		AncientOverlay->SetHealthBarPercent(Attributes->GetHealthPercent());
	}
	return DamageAmount;
}

void AAncientCharacter::GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter)
{
	Super::GetHit_Implementation(ImpactPoint, Hitter);
	if(Attributes && Attributes->IsAlive())
	{
		ActionState = EActionState::EAS_HitReaction;
	}
}

void AAncientCharacter::SetOverlappingItem(AItem* Item)
{
	OverlappingItem = Item;
}

void AAncientCharacter::AddGold(ATreasure* Gold)
{
	if (Attributes && AncientOverlay && Gold)
	{
		Attributes->AddGold(Gold->GetGoldAmount());
		AncientOverlay->SetGoldText(Attributes->GetGold());
	}
}

void AAncientCharacter::AddSoul(ASoul* Soul)
{
	if(Attributes && AncientOverlay && Soul)
	{
		Attributes->AddSoul(Soul->GetSoulAmount());
		AncientOverlay->SetSoulText(Attributes->GetSoul());
	}
}

// Called when the game starts or when spawned
void AAncientCharacter::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(FName("EngageableTarget"));
	InitAncientOverlay();
}

void AAncientCharacter::MoveForward(float Value)
{
	if (ActionState != EActionState::EAS_Unoccupied) 
		return;
	if (Controller && Value != 0.0f)
	{
		AddMovementInput(FRotationMatrix(FRotator(0.f, GetControlRotation().Yaw, 0.f)).GetUnitAxis(EAxis::X), Value);
	}
}

void AAncientCharacter::MoveRight(float Value)
{
	if (ActionState != EActionState::EAS_Unoccupied)
		return;
	if (Controller && Value != 0.0f)
	{
		AddMovementInput(FRotationMatrix(FRotator(0.f, GetControlRotation().Yaw, 0.f)).GetUnitAxis(EAxis::Y), Value);
	}
}

void AAncientCharacter::Turn(float Value)
{
	if (Controller && Value != 0.0f)
	{
		AddControllerYawInput(Value);
	}
}

void AAncientCharacter::LookUp(float Value)
{
	if (Controller && Value != 0.0f)
	{
		AddControllerPitchInput(Value);
	}
}

void AAncientCharacter::EKeyPressed()
{
	AWeapon* OverLappingWeapon = Cast<AWeapon>(OverlappingItem);
	if(OverLappingWeapon)
	{
		if (EquippedWeapon)
		{
			EquippedWeapon->Destroy();
		}
		EquipWeapon(OverLappingWeapon);
	}
	else
	{
		if (CanDisarm())
		{
			Disarm();
		}
		else if (CanArm())
		{
			Arm();
		}
	}
}

void AAncientCharacter::Attack()
{
	Super::Attack();
	if (CanAttack())
	{
		PlayAttackMontage();
		ActionState = EActionState::EAS_Attacking;
	}
}

void AAncientCharacter::Dodge()
{
	if (ActionState == EActionState::EAS_Unoccupied && Attributes && Attributes->GetStamina() >= Attributes->GetDodgeCost())
	{
		PlayDodgeMontage();
		ActionState = EActionState::EAS_Dodge;
		Attributes->UseStamina(Attributes->GetDodgeCost());
		if(AncientOverlay)
		{
			AncientOverlay->SetStaminaBarPercent(Attributes->GetStaminaPercent());
		}
	}
}

void AAncientCharacter::EquipWeapon(AWeapon* Weapon)
{
	Weapon->Equip(GetMesh(), TEXT("RightHandSocket"), this, this, true);
	CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
	EquippedWeapon = Weapon;
	OverlappingItem = nullptr;
}

void AAncientCharacter::AttackEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
}

void AAncientCharacter::DodgeEnd()
{
	Super::DodgeEnd();

	ActionState = EActionState::EAS_Unoccupied;
}

bool AAncientCharacter::CanAttack()
{
	return ActionState == EActionState::EAS_Unoccupied && CharacterState != ECharacterState::ECS_Unequipped;
}

bool AAncientCharacter::CanDisarm()
{
	return ActionState == EActionState::EAS_Unoccupied && CharacterState != ECharacterState::ECS_Unequipped;
}

bool AAncientCharacter::CanArm()
{
	return ActionState == EActionState::EAS_Unoccupied && CharacterState == ECharacterState::ECS_Unequipped && EquippedWeapon;
}

void AAncientCharacter::Disarm()
{
	PlayEquipMontage(TEXT("UnEquip"));
	CharacterState = ECharacterState::ECS_Unequipped;
	ActionState = EActionState::EAS_EquippingWeapon;
}

void AAncientCharacter::Arm()
{
	PlayEquipMontage(TEXT("Equip"));
	CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
	ActionState = EActionState::EAS_EquippingWeapon;
}

void AAncientCharacter::PlayEquipMontage(const FName& SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && EquipMontage)
	{
		AnimInstance->Montage_Play(EquipMontage);
		AnimInstance->Montage_JumpToSection(SectionName, EquipMontage);
	}
}

void AAncientCharacter::Die_Implementation()
{
	Super::Die_Implementation();

	ActionState = EActionState::EAS_Dead;
	DisableMeshCollision();
}

void AAncientCharacter::AttachWeaponToBack()
{
	if(EquippedWeapon)
	{
		EquippedWeapon->AttachMeshToSocket(GetMesh(), TEXT("SpineSocket"));
	}
}

void AAncientCharacter::AttachWeaponToHand()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->AttachMeshToSocket(GetMesh(), TEXT("RightHandSocket"));
	}
}

void AAncientCharacter::FinishiEquipping()
{
	ActionState = EActionState::EAS_Unoccupied;
}

void AAncientCharacter::HitReactEnd()
{
	ActionState = EActionState::EAS_Unoccupied; 
}

void AAncientCharacter::InitAncientOverlay()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		AAncientHUD* AncientHUD = Cast<AAncientHUD>(PlayerController->GetHUD());
		if (AncientHUD)
		{
			AncientOverlay = AncientHUD->GetAncientOverlay();
			if (AncientOverlay && Attributes)
			{
				UpdateAncientOverlay();
			}
		}
	}
}

void AAncientCharacter::UpdateAncientOverlay()
{
	if (AncientOverlay && Attributes)
	{
		AncientOverlay->SetHealthBarPercent(Attributes->GetHealthPercent());
		AncientOverlay->SetStaminaBarPercent(1.f);
		AncientOverlay->SetGoldText(Attributes->GetGold());
		AncientOverlay->SetSoulText(Attributes->GetSoul());
	}
}
