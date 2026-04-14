#pragma once

#include "GridTypes.generated.h"

UENUM(BlueprintType)
enum class EItemCategory : uint8
{
	Equippable,
	Consumable,
	Craftable,
	None
};