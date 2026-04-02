// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Highlightable.generated.h"

UINTERFACE()
class ITEMMANAGEMENT_API UHighlightable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ITEMMANAGEMENT_API IHighlightable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Inventory")
	void Highlight();
	UFUNCTION(BlueprintNativeEvent, Category = "Inventory")
	void UnHighlight();
};
