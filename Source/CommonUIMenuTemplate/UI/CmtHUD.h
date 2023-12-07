// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CmtHUD.generated.h"

/**
 * Modular HUD
 */
UCLASS()
class COMMONUIMENUTEMPLATE_API ACmtHUD : public AHUD
{
	GENERATED_BODY()
public:
	ACmtHUD(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	//~UObject interface
	virtual void PreInitializeComponents() override;
	//~End of UObject interface

	//~AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~End of AActor interface
};
