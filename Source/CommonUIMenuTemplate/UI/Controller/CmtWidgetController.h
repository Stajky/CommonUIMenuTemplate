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
	UFUNCTION()
	virtual void BindDataGenerators();

	//Function to refresh, to get all the data from the data generators
	//It should be used when the Activatable widget is activated to ensure that we have up to data data
	UFUNCTION()
	virtual void RefreshWidgetData();

protected:

	//Function to broadcast data from generators
	UFUNCTION()
	virtual void Broadcast(); 
};
