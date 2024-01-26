#pragma once

#include "CoreMinimal.h"
#include "PlayerAttributes.generated.h"

USTRUCT(BlueprintType)
struct COMMONUIMENUTEMPLATE_API FPlayerAttributes
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	int32 Level = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	int32 XP = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	float Health = 100.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	float MaxHealth = 100.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	float Mana = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	float MaxMana = 100.0f;
};

