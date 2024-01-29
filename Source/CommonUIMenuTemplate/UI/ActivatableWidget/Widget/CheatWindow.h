// 

#pragma once

#include "CoreMinimal.h"
#include "CommonUIMenuTemplate/UI/ActivatableWidget/CmtActivatableWidget_WithController.h"
#include "CheatWindow.generated.h"

/**
 * 
 */
UCLASS()
class COMMONUIMENUTEMPLATE_API UCheatWindow : public UCmtActivatableWidget_WithController
{
	GENERATED_BODY()
public:
	/* ~UCmtActivatableWidget_WithController */
	virtual void SetupWidgetController() override;
	/* ~End of UCmtActivatableWidget_WithController */
};
