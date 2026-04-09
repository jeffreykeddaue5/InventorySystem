// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUDWidget.h"
#include "GameFramework/PlayerController.h"
#include "InvPlayerController.generated.h"

class UInventoryComponent;
class UInputAction;
class UInputMappingContext;
class UHUDWidget;
/**
 * 
 */
UCLASS()
class INVENTORYPLUGIN_API AInvPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	AInvPlayerController();
	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ToggleInventory();
	
protected:
	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	
	void PrimaryInteract();
	void CreateHUDWidget();
	void TraceItem();
	
	TWeakObjectPtr<UInventoryComponent> InventoryComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TObjectPtr<UInputMappingContext> DefaultIMC;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TObjectPtr<UInputAction> PrimaryInteractAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TObjectPtr<UInputAction> ToggleInventoryAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TSubclassOf<UHUDWidget> HUDWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UHUDWidget> HUDWidget;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	double TraceLength;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TEnumAsByte<ECollisionChannel> ItemTraceChannel;
	
	TWeakObjectPtr<AActor> CurrentActor;
	
	TWeakObjectPtr<AActor> PreviousActor;
	
	
	
};
