// Fill out your copyright notice in the Description page of Project Settings.


#include "SpatialInventory.h"

#include "InventoryGrid.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

void USpatialInventory::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	ButtonEquippables->OnClicked.AddDynamic(this, &USpatialInventory::ShowEquippables);
	ButtonConsumables->OnClicked.AddDynamic(this, &USpatialInventory::ShowConsumables);
	ButtonCraftables->OnClicked.AddDynamic(this, &USpatialInventory::ShowCraftables);
	
	ShowEquippables();
}

void USpatialInventory::ShowEquippables()
{
	SetActiveGrid(GridEquippables, ButtonEquippables);
}

void USpatialInventory::ShowConsumables()
{
	SetActiveGrid(GridConsumables, ButtonConsumables);
}

void USpatialInventory::ShowCraftables()
{
	SetActiveGrid(GridCraftables, ButtonCraftables);
}

void USpatialInventory::DisableButton(UButton* Button)
{
	ButtonEquippables->SetIsEnabled(true);
	ButtonConsumables->SetIsEnabled(true);
	ButtonCraftables->SetIsEnabled(true);
	Button->SetIsEnabled(false);
}

void USpatialInventory::SetActiveGrid(UInventoryGrid* Grid, UButton* Button)
{
	DisableButton(Button);
	GridSwitcher->SetActiveWidget(Grid);
	
}
