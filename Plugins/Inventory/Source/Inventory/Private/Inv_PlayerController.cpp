#include "Inv_PlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Items/Components/Inv_ItemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/HUD/Inv_HUDWidget.h" 

//#include "D:/UE_5.5/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
//#include "D:/UE_5.5/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"


AInv_PlayerController::AInv_PlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	TraceLength = 500.0;
	ItemTraceChannel = ECollisionChannel::ECC_GameTraceChannel1;
}

void AInv_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	TraceForItem();
}

void AInv_PlayerController::BeginPlay()
{
	Super::BeginPlay();


	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (IsValid(Subsystem))
	{
		Subsystem->AddMappingContext(DefaultMC, 0);
	}
    CreateHubWidget();
}

void AInv_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(PrimaryInteractAction, ETriggerEvent::Started, this, &AInv_PlayerController::PrimaryInteract);
}

void AInv_PlayerController::PrimaryInteract()
{
	UE_LOG(LogTemp, Log, TEXT("Howdy!"))
}

void AInv_PlayerController::CreateHubWidget()
{
	if (!IsLocalController()) return; 
	HUDWidget = CreateWidget<UInv_HUDWidget>(this, HUDWidgetClass);
	if (IsValid(HUDWidget))
	{
		HUDWidget->AddToViewport(); 
	}
}

void AInv_PlayerController::TraceForItem()
{
	if (!IsValid(GEngine) || !IsValid(GEngine->GameViewport)) return; 
	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);
	const FVector2D ViewportCenter = ViewportSize / 2.f; 
	FVector TraceStart;
	FVector Forward;
	
	if (!UGameplayStatics::DeprojectScreenToWorld(this, ViewportCenter, TraceStart, Forward )) return;
	{
		const FVector TraceEnd = TraceStart + Forward * TraceLength ; 
		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd,ItemTraceChannel );
		
		LastActor = ThisActor;
		ThisActor = Hit.GetActor();
		
		if (!ThisActor.IsValid())
		{
			if (IsValid(HUDWidget)) HUDWidget->HidepickupMessage();
		}
		
		if (ThisActor == LastActor) return; 
		
		if (ThisActor.IsValid())
		{
			UInv_ItemComponent* ItemComponent = ThisActor->FindComponentByClass<UInv_ItemComponent>();

			if (!IsValid(ItemComponent)) return;
			
			
			if (IsValid(HUDWidget)) HUDWidget->ShowpickupMessage(ItemComponent->GetPickupMessage()); 
		}
		
	}
		
		if (LastActor.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT ("LAST ACTOR")); 
			
		}
	}
 
