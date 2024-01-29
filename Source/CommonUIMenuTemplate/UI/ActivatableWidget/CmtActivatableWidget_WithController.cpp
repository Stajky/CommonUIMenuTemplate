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
	SetupWidgetController();
	
	//linkup the WidgetControllerActivate with WidgetActivate
	if(WidgetController)
	{
		WidgetController->NativeActivateWidgetController();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("In %s widget controller is not set!. Did You forget to implement SetupWidgetController"), *GetName())
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

void UCmtActivatableWidget_WithController::SetupWidgetController()
{
}


