// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Public/Widgets/Inventory/RPG/Inv_RPGInventory.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

void UInv_RPGInventory::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	Button_Equippable->OnClicked.AddDynamic(this, &ThisClass::UInv_RPGInventory::ShowEquippable); 
	Button_Consumables->OnClicked.AddDynamic(this, &ThisClass::UInv_RPGInventory::ShowConsumables);
	Button_Materials->OnClicked.AddDynamic(this, &ThisClass::UInv_RPGInventory::ShowMaterials);
	
	ShowConsumables(); 
}

void UInv_RPGInventory::ShowEquippable()
{
	SetActiveGrid(Grid_Equippable, Button_Equippable);
}

void UInv_RPGInventory::ShowConsumables()
{
	SetActiveGrid(Grid_Consumables, Button_Consumables);
}

void UInv_RPGInventory::ShowMaterials()
{
	SetActiveGrid(Grid_Materials, Button_Materials);
}

void UInv_RPGInventory::DisableButton(UButton* Button)
{
	Button_Equippable->SetIsEnabled(true);
	Button_Consumables->SetIsEnabled(true);
	Button_Materials->SetIsEnabled(true);
	Button->SetIsEnabled(false);
}

void UInv_RPGInventory::SetActiveGrid(UInv_InventoryGrid* Grid, UButton* Button)
{
	DisableButton(Button);
	
	Switcher->SetActiveWidget(Grid);
}
