// Fill out your copyright notice in the Description page of Project Settings.


#include "InvPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InventoryPlugin.h"
#include "Blueprint/UserWidget.h"

void AInvPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UEnhancedInputLocalPlayerSubsystem * Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (IsValid(Subsystem))
	{
		Subsystem->AddMappingContext(DefaultIMC, 0);
	}
	CreateHUDWidget();
}

void AInvPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent * EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	
	EnhancedInputComponent->BindAction(PrimaryInteractAction, ETriggerEvent::Started, this, &AInvPlayerController::PrimaryInteract);
}

void AInvPlayerController::PrimaryInteract()
{
	UE_LOG(InventoryPluginLog, Warning, TEXT("PrimaryInteract"));
}

void AInvPlayerController::CreateHUDWidget()
{
	if (!IsLocalController())
	{
		return;
	}
	HUDWidget = CreateWidget<UHUDWidget>(this, HUDWidgetClass);
	if (IsValid(HUDWidget))
	{
		HUDWidget->AddToViewport();
	}
}
