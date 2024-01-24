// 


#include "CmtActivatableWidget_WithController.h"

UCmtActivatableWidget_WithController::UCmtActivatableWidget_WithController(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

void UCmtActivatableWidget_WithController::SetController(UCmtWidgetController* NewController)
{
	Controller = NewController;
	BP_OnSetController();
}

UCmtWidgetController* UCmtActivatableWidget_WithController::GetController() const
{
	return Controller;
}
