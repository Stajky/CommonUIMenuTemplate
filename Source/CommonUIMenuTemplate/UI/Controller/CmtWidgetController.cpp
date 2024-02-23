// 


#include "CmtWidgetController.h"

void UCmtWidgetController::BindData()
{
}

void UCmtWidgetController::UnBindData()
{
}

void UCmtWidgetController::RefreshWidgetData()
{
}

void UCmtWidgetController::NativeActivateWidgetController()
{
}

void UCmtWidgetController::NativeDeactivateWidgetController()
{
}

void UCmtWidgetController::BeginDestroy()
{
	UnBindData();
	UObject::BeginDestroy();
}


bool UCmtWidgetController::LockGuard()
{
	//We lock something that is already locked
	if(bGuard)
	{
		return false;
	}
	bGuard = true;
	return true;
}

bool UCmtWidgetController::UnlockGuard()
{
	//We cannot unlock what is already unlocked
	if(!bGuard)
	{
		return false;
	}
	bGuard = false;
	return true;
}
