// 

#pragma once

#include "CoreMinimal.h"
#include "CommonPlayerController.h"
#include "CmtPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class COMMONUIMENUTEMPLATE_API ACmtPlayerController : public ACommonPlayerController
{
	GENERATED_BODY()
public:
	ACmtPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~End of AActor interface
};
