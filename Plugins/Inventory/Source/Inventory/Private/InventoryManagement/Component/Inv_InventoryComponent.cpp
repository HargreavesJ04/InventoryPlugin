// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManagement/Component/Inv_InventoryComponent.h"

#include "Widgets/Inventory/InventoryBase/Inv_InventoryBase.h"


UInv_InventoryComponent::UInv_InventoryComponent()
{
	
	PrimaryComponentTick.bCanEverTick = false;

	
}

void UInv_InventoryComponent::ToggleInventoryMenu()
{
	if (bInventoryEnabled)
	{
		CloseInventoryMenu();
	}
	else
	{
		OpenInventoryMenu();
	}
}


void UInv_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	ConstructInventory();
	
}

void UInv_InventoryComponent::OpenInventoryMenu()
{
	if (!IsValid(InventoryMenu)) return;
	
	InventoryMenu->SetVisibility((ESlateVisibility::Visible)); 
	bInventoryEnabled = true;
	
	if (!OwningController.IsValid()) return;
	
	
	FInputModeGameAndUI InputMode;
	OwningController->SetInputMode(InputMode);
	OwningController->SetShowMouseCursor (true);
}

void UInv_InventoryComponent::CloseInventoryMenu()
{
	if (!IsValid(InventoryMenu)) return;
	InventoryMenu->SetVisibility((ESlateVisibility::Collapsed));
	bInventoryEnabled = false;
	
	if (!OwningController.IsValid()) return;
	FInputModeGameOnly InputMode;
	OwningController->SetInputMode(InputMode);
	OwningController->SetShowMouseCursor (false);
}


void UInv_InventoryComponent::ConstructInventory()
{
	OwningController = Cast<APlayerController>(GetOwner());
	checkf(OwningController.IsValid(), TEXT("Inventory Component needs a player controller as its owner"))
	if (!OwningController->IsLocalController()) return;

	InventoryMenu = CreateWidget<UInv_InventoryBase>(OwningController.Get(), InventoryMenuClass ) ;
	InventoryMenu->AddToViewport(); 
	CloseInventoryMenu();
	
}





