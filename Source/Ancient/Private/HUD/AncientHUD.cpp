// Fill out your copyright notice in the Description page of Project Settings.

#include "Ancient/Ancient.h"
#include "HUD/AncientHUD.h"
#include "HUD/AncientOverlay.h"

void AAncientHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (World && AncientOverlayClass)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if(PlayerController)
		{
			AncientOverlay = CreateWidget<UAncientOverlay>(PlayerController, AncientOverlayClass);
			if (AncientOverlay)
			{
				AncientOverlay->AddToViewport();
			}
		}
	}
}
