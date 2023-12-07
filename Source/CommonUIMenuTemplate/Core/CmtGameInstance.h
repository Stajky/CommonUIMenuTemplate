#pragma once

#include "CoreMinimal.h"
#include "CommonGameInstance.h"
#include "CmtGameInstance.generated.h"

/**
 * CommonGame Game Instance
 *
 * Must be configured in DefaultEngine.ini:
 *
 * [/Script/EngineSettings.GameMapsSettings]
 * GameInstanceClass=/Script/CommonUIMenuTemplate.CmtGameInstance
 */
UCLASS()
class COMMONUIMENUTEMPLATE_API UCmtGameInstance : public UCommonGameInstance
{
	GENERATED_BODY()
public:
	UCmtGameInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
