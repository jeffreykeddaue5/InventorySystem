// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


class UInventoryBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class ITEMMANAGEMENT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;
	
private:
	void ConstructInventory();
	
	TWeakObjectPtr<APlayerController> OwningController;
	
	UPROPERTY()
	TObjectPtr<UInventoryBase> InventoryMenu;
	
	UPROPERTY(EditAnywhere, Category = "Inventory" )
	TSubclassOf<UInventoryBase> InventoryMenuClass;
	
	
};
