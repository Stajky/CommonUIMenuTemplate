// 


#include "CmtActivatableWidget_WithController.h"
#include "CommonUIMenuTemplate/UI/Controller/CmtWidgetController.h"

UCmtActivatableWidget_WithController::UCmtActivatableWidget_WithController(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

void UCmtActivatableWidget_WithController::SetWidgetController(UCmtWidgetController* NewController)
{
	WidgetController = NewController;
	//Call Native Activate since 
	if(WidgetController)
	{
		WidgetController->NativeActivateWidgetController();
	}
	BP_OnSetController();
}

UCmtWidgetController* UCmtActivatableWidget_WithController::GetWidgetController() const
{
	return WidgetController;
}

void UCmtActivatableWidget_WithController::NativeOnActivated()
{
	//linkup the WidgetControllerActivate with WidgetActivate
	//This will fail be null the first time its called since activate happens automatically when we push to stack,
	//This means that we need to handle this case with OnControllerSet logic
	if(WidgetController)
	{
		WidgetController->NativeActivateWidgetController();
	}
	
	Super::NativeOnActivated();
}

void UCmtActivatableWidget_WithController::NativeOnDeactivated()
{
	//linkup the WidgetControllerDeactivate with WidgetDeactivate
	if(WidgetController)
	{
		WidgetController->NativeDeactivateWidgetController();
	}
	
	Super::NativeOnDeactivated();
}
