// 

#pragma once

#include "CoreMinimal.h"
#include "CmtPlayerAttributes.h"
#include "ModularPlayerState.h"
#include "CmtPlayerState.generated.h"


/**
 * 
 */
UCLASS()
class COMMONUIMENUTEMPLATE_API ACmtPlayerState : public AModularPlayerState
{
	GENERATED_BODY()
public:
	ACmtPlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


public:

	//TODO try removing SaveGame to see what it does with save system
	UPROPERTY(VisibleAnywhere, SaveGame)
	FCmtPlayerAttributes PlayerAttributes;
	
};

