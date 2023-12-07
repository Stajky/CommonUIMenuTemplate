#pragma once

#include "CoreMinimal.h"
#include "CommonLocalPlayer.h"
#include "CmtLocalPlayer.generated.h"

/**
 * CommonGame LocalPlayer
 *
 * Must be configured in DefaultEngine.ini:
 * [/Script/Engine.Engine]
 * LocalPlayerClassName=/Script/CommonUIMenuTemplate.UCmtLocalPlayer
 */
UCLASS()
class COMMONUIMENUTEMPLATE_API UCmtLocalPlayer : public UCommonLocalPlayer
{
	GENERATED_BODY()
public:
	UCmtLocalPlayer(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

};
