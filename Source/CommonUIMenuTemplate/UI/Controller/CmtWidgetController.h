// 

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CmtWidgetController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class COMMONUIMENUTEMPLATE_API UCmtWidgetController : public UObject
{
	GENERATED_BODY()

public:

	//Function for binding/listening for data generators 
	UFUNCTION(BlueprintCallable)
	virtual void BindData();
	
	UFUNCTION(BlueprintCallable)
	virtual void UnBindData();

	//Function to refresh, to get all the data from the data generators
	//It should be used when the Activatable widget is activated to ensure that we have up to data data
	UFUNCTION(BlueprintCallable)
	virtual void RefreshWidgetData();
	
	virtual void NativeActivateWidgetController();
	virtual void NativeDeactivateWidgetController();

	/* ~UObject */	
	virtual void BeginDestroy() override;
	/* ~End of UObject */
	
protected:
	
	bool LockGuard();
	bool UnlockGuard();
	
protected:
	bool bGuard = false;
};
