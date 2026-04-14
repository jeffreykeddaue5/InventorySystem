// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryBase.h"
#include "SpatialInventory.generated.h"

class UInventoryGrid;
class UWidgetSwitcher;
/**
 * 
 */
UCLASS()
class WIDGETS_API USpatialInventory : public UInventoryBase
{
	GENERATED_BODY()
	
private:
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UWidgetSwitcher> WidgetSwitcher;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInventoryGrid> GridEquippables;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInventoryGrid> GridConsumables;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInventoryGrid> GridCraftables;
	
};
