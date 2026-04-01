// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class INVENTORYPLUGIN_API UItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UItemComponent();

	FString GetPickUpMessage() const { return PickupMessage; }
	
private:
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	FString PickupMessage;
	
};
