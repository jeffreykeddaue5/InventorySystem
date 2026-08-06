// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryBase.h"
#include "SpatialInventory.generated.h"

class UButton;
class UInventoryGrid;
class UWidgetSwitcher;
/**
 * 
 */
UCLASS()
class WIDGETS_API USpatialInventory : public UInventoryBase
{
	GENERATED_BODY()
	
	public:
	virtual void NativeOnInitialized() override;
	
private:
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UWidgetSwitcher> GridSwitcher;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInventoryGrid> GridEquippables;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInventoryGrid> GridConsumables;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInventoryGrid> GridCraftables;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonEquippables;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonConsumables;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonCraftables;
	
	UFUNCTION()
	void ShowEquippables();
	
	UFUNCTION()
	void ShowConsumables();
	
	UFUNCTION()
	void ShowCraftables();
	void DisableButton(UButton* Button);

	void SetActiveGrid(UInventoryGrid* Grid, UButton* Button);
};
