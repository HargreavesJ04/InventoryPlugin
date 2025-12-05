// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Utilities/Inv_WidgetUtilities.h"

int32 UInv_WidgetUtilities::GetIndexFromPosition(const FIntPoint& Position, const int32 Columns)
{
	return Position.X + Position.Y * Columns;
}
