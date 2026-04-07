// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "InventoryBase.h"
#include "Blueprint/UserWidget.h"


UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	ConstructInventory();
	
}

void UInventoryComponent::ConstructInventory()
{
	OwningController = Cast<APlayerController>(GetOwner());
	checkf(OwningController.IsValid(), TEXT("Inventory Component should have a Player Controller as Owner."))
	if (!OwningController->IsLocalController()) return;
	
	InventoryMenu = CreateWidget<UInventoryBase>(OwningController.Get(), InventoryMenuClass);
	InventoryMenu->AddToViewport();
}

