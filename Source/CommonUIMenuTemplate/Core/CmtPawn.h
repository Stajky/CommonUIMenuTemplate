#pragma once

#include "CoreMinimal.h"
#include "ModularPawn.h"
#include "CmtPawn.generated.h"

/**
 * 
 */
UCLASS()
class COMMONUIMENUTEMPLATE_API ACmtPawn : public AModularPawn
{
	GENERATED_BODY()
	
public:
	ACmtPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
