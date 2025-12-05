// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inv_InventoryGrid.h"
#include "Widgets/Inventory/InventoryBase/Inv_InventoryBase.h"
#include "Inv_RPGInventory.generated.h"



class UWidgetSwitcher;
class UButton;
/**
 * 
 */
UCLASS()
class INVENTORY_API UInv_RPGInventory : public UInv_InventoryBase
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override;
	
	
private:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> Switcher;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInv_InventoryGrid> Grid_Equippable; 
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInv_InventoryGrid> Grid_Consumables; 
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInv_InventoryGrid> Grid_Materials; 
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Equippable;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Consumables;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Materials;
	
	
	UFUNCTION()
	void ShowEquippable();
	
	UFUNCTION()
	void ShowConsumables(); 
	
	UFUNCTION()
	void ShowMaterials();
	void DisableButton(UButton* Button);


	void SetActiveGrid(UInv_InventoryGrid* Grid, UButton* Button);
};
