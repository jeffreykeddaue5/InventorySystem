// Fill out your copyright notice in the Description page of Project Settings.


#include "InvPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InventoryPlugin.h"
#include "ItemComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


AInvPlayerController::AInvPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	TraceLength = 500.0;
	ItemTraceChannel = ECC_GameTraceChannel1;
}

void AInvPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	TraceItem();
}

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

void AInvPlayerController::TraceItem()
{
	if (!IsValid(GEngine) || !IsValid(GEngine->GameViewport)) return; 
	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);
	const FVector2D ViewportCenter = ViewportSize / 2.f;
	
	FVector TraceStart;
	FVector Forward;
	
	if (!UGameplayStatics::DeprojectScreenToWorld(this, ViewportCenter, TraceStart, Forward)) return;
	
	const FVector TraceEnd = TraceStart + Forward * TraceLength;
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ItemTraceChannel);
	
	PreviousActor = CurrentActor;
	CurrentActor = HitResult.GetActor();
	
	if (!CurrentActor.IsValid())
	{
		if (IsValid(HUDWidget)) HUDWidget->HidePickUpMessage();	
	}
	
	if (CurrentActor == PreviousActor) return;
	
	if (CurrentActor.IsValid())
	{
		UItemComponent * ItemComponent = CurrentActor->FindComponentByClass<UItemComponent>();
		if (!IsValid(ItemComponent)) return;
		
		if (IsValid(HUDWidget)) HUDWidget->ShowPickUpMessage(ItemComponent->GetPickUpMessage());
		UE_LOG(InventoryPluginLog, Display, TEXT("CurrentActor: %s"), *CurrentActor->GetName());
	}
	
	if (PreviousActor.IsValid())
	{
		UE_LOG(InventoryPluginLog, Display, TEXT("PreviousActor: %s"),  *PreviousActor->GetName());
	}
	
}
