#pragma once

#include "CoreMinimal.h"
#include "ModularGameState.h"
#include "CmtGameState.generated.h"

/**
 * 
 */
UCLASS()
class COMMONUIMENUTEMPLATE_API ACmtGameState : public AModularGameStateBase
{
	GENERATED_BODY()
public:
	ACmtGameState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
};


