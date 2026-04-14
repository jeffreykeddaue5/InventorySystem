// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridTypes.h"
#include "Blueprint/UserWidget.h"
#include "InventoryGrid.generated.h"

/**
 * 
 */
UCLASS()
class WIDGETS_API UInventoryGrid : public UUserWidget
{
	GENERATED_BODY()

public:
	
	EItemCategory GetItemCategory(EItemCategory Category) const { return ItemCategory; };

private:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category = "Inventory")
	EItemCategory ItemCategory;
};
