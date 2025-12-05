// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Inv_WidgetUtilities.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY_API UInv_WidgetUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	static int32 GetIndexFromPosition(const FIntPoint& Position, const int32 Columns);
};
