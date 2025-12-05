// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/Inv_GridTypes.h"
#include "Widgets/Inventory/IGridSlots/Inv_GridSlots.h"
#include "Inv_InventoryGrid.generated.h"

/**
 * 
 */
class UCanvasPanel;
class UInv_GridSlots;
UCLASS()
class INVENTORY_API UInv_InventoryGrid : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	EInv_ItemCategory GetItemCategory() const {return ItemCategory; }
	
	virtual void NativeOnInitialized() override;
	
private:
	
	void ConstructGrid(); 
	
	UPROPERTY()
	TArray<TObjectPtr<UInv_GridSlots>> GridSlots;
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TSubclassOf<UInv_GridSlots> GridSlotClass;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel;
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 Rows;
	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 Columns;
	UPROPERTY(EditAnywhere, Category = "Inventory")
	float CellSize;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true" ),  Category = "Inventory")
	EInv_ItemCategory ItemCategory; 
	
	
	
};
