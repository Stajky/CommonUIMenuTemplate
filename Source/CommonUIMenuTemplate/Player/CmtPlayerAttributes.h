#pragma once

#include "CoreMinimal.h"
#include "CmtPlayerAttributes.generated.h"

USTRUCT(BlueprintType)
struct COMMONUIMENUTEMPLATE_API FCmtPlayerAttributes
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	int32 Level = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	int32 XP = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	float Health = 100;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	float MaxHealth = 100;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	float Mana = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	float MaxMana = 100;
};

