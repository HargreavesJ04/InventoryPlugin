// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Inventory/RPG/Inv_InventoryGrid.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Widgets/Inventory/IGridSlots/Inv_GridSlots.h"
#include "Widgets/Utilities/Inv_WidgetUtilities.h"


void UInv_InventoryGrid::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	ConstructGrid();
}

void UInv_InventoryGrid::ConstructGrid()
{
	GridSlots.Reserve(Rows * Columns);
	
	for (int32 j = 0; j < Rows; j++)
	{
		for (int32 i = 0; i < Columns; i++)
		{
			UInv_GridSlots* GridSlot = CreateWidget<UInv_GridSlots>(this, GridSlotClass); 
			CanvasPanel->AddChildToCanvas(GridSlot);
			
			
			const FIntPoint TilePosition(i, j);
			GridSlot->SetTileIndex(UInv_WidgetUtilities::GetIndexFromPosition(FIntPoint(i, j), Columns));
			
			UCanvasPanelSlot* GridCPS = UWidgetLayoutLibrary::SlotAsCanvasSlot(GridSlot);
			GridCPS->SetSize(FVector2D(CellSize));
			GridCPS->SetPosition(FVector2D(TilePosition * CellSize));
			
			GridSlots.Add(GridSlot);
			
			
		}
	}
}
