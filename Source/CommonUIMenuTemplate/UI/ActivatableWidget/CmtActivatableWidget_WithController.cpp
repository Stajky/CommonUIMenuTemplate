// 


#include "CmtActivatableWidget_WithController.h"
#include "CommonUIMenuTemplate/UI/Controller/CmtWidgetController.h"

UCmtActivatableWidget_WithController::UCmtActivatableWidget_WithController(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

UCmtWidgetController* UCmtActivatableWidget_WithController::GetWidgetController() const
{
	return WidgetController;
}

void UCmtActivatableWidget_WithController::NativeOnActivated()
{
	Super::NativeOnActivated();

	SetupWidgetController();
	
	//linkup the WidgetControllerActivate with WidgetActivate
	//This will fail be null the first time its called since activate happens automatically when we push to stack,
	//This means that we need to handle this case with OnControllerSet logic
	if(WidgetController)
	{
		WidgetController->NativeActivateWidgetController();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("In %s widget controller is not set!. Did You forget to implement SetupWidgetController"), *GetName())
	}
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

void UCmtActivatableWidget_WithController::SetupWidgetController()
{
}


