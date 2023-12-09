// 

#pragma once

#include "CoreMinimal.h"
#include "CmtActivatableWidget.h"
#include "CmtActivatableWidget_WithController.generated.h"


class UCmtWidgetController;

/**
 * 
 */
UCLASS()
class COMMONUIMENUTEMPLATE_API UCmtActivatableWidget_WithController : public UCmtActivatableWidget
{
	GENERATED_BODY()
public:
	UCmtActivatableWidget_WithController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCmtWidgetController> Controller;
};
