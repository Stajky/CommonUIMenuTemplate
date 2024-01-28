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
	
	UFUNCTION(BlueprintCallable)
	UCmtWidgetController* GetWidgetController() const;

protected:
	/* ~UCommonActivatableWidget */ 
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
	/* ~End of UCommonActivatableWidget */
	
	virtual void SetupWidgetController();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UCmtWidgetController> WidgetController;
	
	bool bIsWidgetControllerSet = false;
};
