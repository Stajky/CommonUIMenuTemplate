// 


#include "CmtActivatableWidget_WithController.h"

UCmtActivatableWidget_WithController::UCmtActivatableWidget_WithController(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

void UCmtActivatableWidget_WithController::SetWidgetController(UCmtWidgetController* NewController)
{
	Controller = NewController;
	BP_OnSetController();
}

UCmtWidgetController* UCmtActivatableWidget_WithController::GetWidgetController() const
{
	return Controller;
}
