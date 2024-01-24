// 

#pragma once

#include "CoreMinimal.h"
#include "CommonUIMenuTemplate/UI/ActivatableWidget/CmtActivatableWidget_WithController.h"
#include "PlayerOverlay.generated.h"

/**
 * 
 */
UCLASS()
class COMMONUIMENUTEMPLATE_API UPlayerOverlay : public UCmtActivatableWidget_WithController
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
};
