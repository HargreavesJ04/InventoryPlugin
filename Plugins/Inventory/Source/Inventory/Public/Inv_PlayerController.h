
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"


#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InventoryManagement/Component/Inv_InventoryComponent.h"
#include "Widgets/HUD/Inv_HUDWidget.h" 
#include "Inv_PlayerController.generated.h" 
class UInv_InventoryComponent;
/**
 * 
 */

class UInputMappingContext;
class UInputAction;
class UInv_HUDWidget;

UCLASS()
class INVENTORY_API AInv_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AInv_PlayerController();
	virtual void  Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ToggleInventory();
	
protected:

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;
	
	


private:


	void PrimaryInteract();
	void CreateHubWidget(); 
    void TraceForItem(); 

	TWeakObjectPtr<UInv_InventoryComponent> InventoryComponent; 
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TObjectPtr<UInputMappingContext> DefaultMC;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TObjectPtr<UInputAction> PrimaryInteractAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TObjectPtr<UInputAction> ToggleInventorytAction;
	
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TSubclassOf<UInv_HUDWidget> HUDWidgetClass;
	
	UPROPERTY() 
	TObjectPtr<UInv_HUDWidget> HUDWidget; 
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	double TraceLength;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TEnumAsByte<ECollisionChannel> ItemTraceChannel;
	
	TWeakObjectPtr<AActor> ThisActor;
	TWeakObjectPtr<AActor> LastActor;
	
};
