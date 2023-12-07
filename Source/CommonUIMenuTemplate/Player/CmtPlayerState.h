// 

#pragma once

#include "CoreMinimal.h"
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
};
