// Fill out your copyright notice in the Description page of Project Settings.


#include "InvPlayerController.h"
#include "InventoryPlugin.h"

void AInvPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(InventoryPluginLog, Log, TEXT("AInvPlayerController::BeginPlay()"));
}
