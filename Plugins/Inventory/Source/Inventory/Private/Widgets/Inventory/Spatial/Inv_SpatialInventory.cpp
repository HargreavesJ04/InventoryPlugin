#include "Widgets/Inventory/Spatial/Inv_SpatialInventory.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Widgets/Inventory/Spatial/Inv_InventoryGrid.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Items/Inv_InventoryItem.h"
#include "Widgets/ItemDescription/Inv_ItemDescription.h"
#include "InventoryManagement/Utils/Inv_InventoryStatics.h"

void UInv_SpatialInventory::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Button_Equippables->OnClicked.AddDynamic(this, &ThisClass::ShowEquippables);
	Button_Consumables->OnClicked.AddDynamic(this, &ThisClass::ShowConsumables);
	Button_Craftables->OnClicked.AddDynamic(this, &ThisClass::ShowCraftables);

	Grid_Equippables->SetOwningCanvas(CanvasPanel);
	Grid_Consumables->SetOwningCanvas(CanvasPanel);
	Grid_Craftables->SetOwningCanvas(CanvasPanel);
	ShowEquippables();
}

FReply UInv_SpatialInventory::NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (ActiveGrid.IsValid()) ActiveGrid->DropItem();
	return FReply::Handled();
}

void UInv_SpatialInventory::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (IsValid(ItemDescription)) SetItemDescriptionSizeAndPosition(ItemDescription, CanvasPanel);
}

void UInv_SpatialInventory::SetItemDescriptionSizeAndPosition(UInv_ItemDescription* Description, UCanvasPanel* Canvas) const
{
	UCanvasPanelSlot* ItemDescriptionCPS = UWidgetLayoutLibrary::SlotAsCanvasSlot(Description);
	if (!IsValid(ItemDescriptionCPS)) return;
	ItemDescriptionCPS->SetSize(Description->GetBoxSize());
	ItemDescriptionCPS->SetPosition(UWidgetLayoutLibrary::GetMousePositionOnViewport(GetOwningPlayer()));
}

FInv_SlotAvailabilityResult UInv_SpatialInventory::HasRoomForItem(UInv_ItemComponent* ItemComponent) const
{
	switch (UInv_InventoryStatics::GetItemCategoryFromItemComp(ItemComponent))
	{
		case EInv_ItemCategory::Equippable: return Grid_Equippables->HasRoomForItem(ItemComponent);
		case EInv_ItemCategory::Consumable: return Grid_Consumables->HasRoomForItem(ItemComponent);
		case EInv_ItemCategory::Craftable: return Grid_Craftables->HasRoomForItem(ItemComponent);
		default: return FInv_SlotAvailabilityResult();
	}
}

void UInv_SpatialInventory::OnItemHovered(UInv_InventoryItem* Item)
{
	UInv_ItemDescription* DescriptionWidget = GetItemDescription();
	DescriptionWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
	Item->GetItemManifest().AssimilateInventoryFragments(DescriptionWidget);
}

void UInv_SpatialInventory::OnItemUnHovered()
{
	if (IsValid(ItemDescription)) ItemDescription->SetVisibility(ESlateVisibility::Collapsed);
}

bool UInv_SpatialInventory::HasHoverItem() const { return ActiveGrid.IsValid() && ActiveGrid->HasHoverItem(); }
UInv_HoverItem* UInv_SpatialInventory::GetHoverItem() const { return ActiveGrid.IsValid() ? ActiveGrid->GetHoverItem() : nullptr; }
float UInv_SpatialInventory::GetTileSize() const { return Grid_Equippables->GetTileSize(); }

UInv_ItemDescription* UInv_SpatialInventory::GetItemDescription()
{
	if (!IsValid(ItemDescription))
	{
		ItemDescription = CreateWidget<UInv_ItemDescription>(GetOwningPlayer(), ItemDescriptionClass);
		CanvasPanel->AddChild(ItemDescription);
	}
	return ItemDescription;
}

void UInv_SpatialInventory::ShowEquippables() { SetActiveGrid(Grid_Equippables, Button_Equippables); }
void UInv_SpatialInventory::ShowConsumables() { SetActiveGrid(Grid_Consumables, Button_Consumables); }
void UInv_SpatialInventory::ShowCraftables() { SetActiveGrid(Grid_Craftables, Button_Craftables); }

void UInv_SpatialInventory::DisableButton(UButton* Button)
{
	Button_Equippables->SetIsEnabled(true);
	Button_Consumables->SetIsEnabled(true);
	Button_Craftables->SetIsEnabled(true);
	Button->SetIsEnabled(false);
}

void UInv_SpatialInventory::SetActiveGrid(UInv_InventoryGrid* Grid, UButton* Button)
{
	if (ActiveGrid.IsValid()) ActiveGrid->OnHide();
	ActiveGrid = Grid;
	if (ActiveGrid.IsValid()) ActiveGrid->ShowCursor();
	DisableButton(Button);
	Switcher->SetActiveWidget(Grid);
}