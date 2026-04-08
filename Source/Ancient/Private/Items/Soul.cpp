// Fill out your copyright notice in the Description page of Project Settings.

#include "Ancient/Ancient.h"
#include "Items/Soul.h"
#include "Interfaces/PickupInterface.h"
#include "Kismet/KismetSystemLibrary.h"

void ASoul::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(GetActorLocation().Z > DesiredZ)
	{
		AddActorWorldOffset(FVector(0.f, 0.f, DriftRate * DeltaTime * -1));
	}
}

void ASoul::BeginPlay()
{
	Super::BeginPlay();

	const FVector StartLocation = GetActorLocation();
	TArray<TEnumAsByte<EObjectTypeQuery> > ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery1);
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());
	FHitResult HitResult;
	UKismetSystemLibrary::LineTraceSingleForObjects(this, StartLocation, StartLocation - FVector(0.f, 0.f, 2000.f), ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true);
	DesiredZ = HitResult.Location.Z + UPGroundOffset;
}

void ASoul::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor);
	if (PickupInterface)
	{
		PickupInterface->AddSoul(this);
		SpawnPickupSystem();
		SpawnPickupSound();
		Destroy();
	}
}
