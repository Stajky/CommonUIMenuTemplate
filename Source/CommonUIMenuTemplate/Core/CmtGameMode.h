#pragma once

#include "CoreMinimal.h"
#include "ModularGameMode.h"
#include "CmtGameMode.generated.h"

/**
 * Modular Game Mode
 */
UCLASS()
class COMMONUIMENUTEMPLATE_API ACmtGameMode : public AModularGameModeBase
{
	GENERATED_BODY()
public:
	ACmtGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~AGameModeBase interface
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void InitGameState() override;
	//~End of AGameModeBase interface
};
