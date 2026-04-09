// Fill out your copyright notice in the Description page of Project Settings.


#include "InvPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Highlightable.h"
#include "InventoryComponent.h"
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

void AInvPlayerController::ToggleInventory()
{
	if (!InventoryComponent.IsValid()) return;
	InventoryComponent->ToggleInventoryMenu();	
}

void AInvPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UEnhancedInputLocalPlayerSubsystem * Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (IsValid(Subsystem))
	{
		Subsystem->AddMappingContext(DefaultIMC, 0);
	}
	
	InventoryComponent = FindComponentByClass<UInventoryComponent>();
	
	CreateHUDWidget();
}

void AInvPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent * EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	
	EnhancedInputComponent->BindAction(PrimaryInteractAction, ETriggerEvent::Started, this, &AInvPlayerController::PrimaryInteract);
	EnhancedInputComponent->BindAction(ToggleInventoryAction, ETriggerEvent::Started, this, &AInvPlayerController::ToggleInventory);

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
		// Gets UHighlightableStaticMesh inherits IHighlightable, overrides Highlight/UnHiglight
		// Unreal is checking if Highlightable interface is implemented via reflection system
		UActorComponent * Highlightable = CurrentActor->FindComponentByInterface(UHighlightable::StaticClass());
		if (IsValid(Highlightable))
		{
			// Execute because the function might be implemented in blueprint/Unreal routes the call safely through reflection
			IHighlightable::Execute_Highlight(Highlightable);	
		}
		
		UItemComponent * ItemComponent = CurrentActor->FindComponentByClass<UItemComponent>();
		if (!IsValid(ItemComponent)) return;
		
		if (IsValid(HUDWidget)) HUDWidget->ShowPickUpMessage(ItemComponent->GetPickUpMessage());
		UE_LOG(InventoryPluginLog, Display, TEXT("CurrentActor: %s"), *CurrentActor->GetName());
		
	}
	
	if (PreviousActor.IsValid())
	{
		
		UActorComponent * UnHighlightable = PreviousActor->FindComponentByInterface(UHighlightable::StaticClass());
		if (IsValid(UnHighlightable))
		{
			IHighlightable::Execute_UnHighlight(UnHighlightable);	
		}
		
		UE_LOG(InventoryPluginLog, Display, TEXT("PreviousActor: %s"),  *PreviousActor->GetName());
	}
	
}
