#pragma once

#include "CoreMinimal.h"
#include "PlayerSpellData.generated.h"

USTRUCT(BlueprintType)
struct COMMONUIMENUTEMPLATE_API FPlayerSpellData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	float Spell1Cooldown = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	float Spell2Cooldown = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	float Spell3Cooldown = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	float Spell4Cooldown = 0.0f;
	
};

