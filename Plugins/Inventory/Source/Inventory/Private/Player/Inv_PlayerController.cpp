#include "Player/Inv_PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InventoryManagement/Components/Inv_InventoryComponent.h"
#include "Items/Components/Inv_ItemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/HUD/Inv_HUDWidget.h"

AInv_PlayerController::AInv_PlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	TraceLength = 500.0;
	ItemTraceChannel = ECC_GameTraceChannel1;
}

void AInv_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TraceForItem();
}

void AInv_PlayerController::ToggleInventory()
{
	if (!InventoryComponent.IsValid()) return;
	InventoryComponent->ToggleInventoryMenu();
	HUDWidget->SetVisibility(InventoryComponent->IsMenuOpen() ? ESlateVisibility::Hidden : ESlateVisibility::HitTestInvisible);
}

void AInv_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	InventoryComponent = FindComponentByClass<UInv_InventoryComponent>();
	CreateHUDWidget();
}

void AInv_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EIC = CastChecked<UEnhancedInputComponent>(InputComponent);
	EIC->BindAction(PrimaryInteractAction, ETriggerEvent::Started, this, &AInv_PlayerController::PrimaryInteract);
	EIC->BindAction(ToggleInventoryAction, ETriggerEvent::Started, this, &AInv_PlayerController::ToggleInventory);
}

void AInv_PlayerController::PrimaryInteract()
{
	if (!ThisActor.IsValid()) return;
	UInv_ItemComponent* ItemComp = ThisActor->FindComponentByClass<UInv_ItemComponent>();
	if (IsValid(ItemComp) && InventoryComponent.IsValid()) InventoryComponent->TryAddItem(ItemComp);
}

void AInv_PlayerController::CreateHUDWidget()
{
	HUDWidget = CreateWidget<UInv_HUDWidget>(this, HUDWidgetClass);
	if (IsValid(HUDWidget)) HUDWidget->AddToViewport();
}

void AInv_PlayerController::TraceForItem()
{
	FVector TraceStart, Forward;
	FVector2D ViewportSize;
	if (!GEngine->GameViewport) return;
	GEngine->GameViewport->GetViewportSize(ViewportSize);
	if (!UGameplayStatics::DeprojectScreenToWorld(this, ViewportSize / 2.f, TraceStart, Forward)) return;

	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceStart + Forward * TraceLength, ItemTraceChannel);

	LastActor = ThisActor;
	ThisActor = Hit.GetActor();

	if (!ThisActor.IsValid())
	{
		if (IsValid(HUDWidget)) HUDWidget->HidePickupMessage();
	}
	else if (ThisActor != LastActor)
	{
		UInv_ItemComponent* ItemComp = ThisActor->FindComponentByClass<UInv_ItemComponent>();
		if (IsValid(ItemComp) && IsValid(HUDWidget)) HUDWidget->ShowPickupMessage(ItemComp->GetPickupMessage());
	}
}