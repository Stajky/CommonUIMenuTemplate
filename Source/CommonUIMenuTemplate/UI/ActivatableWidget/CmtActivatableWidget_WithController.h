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
	void SetWidgetController(UCmtWidgetController* NewController);

	UFUNCTION(BlueprintCallable)
	UCmtWidgetController* GetWidgetController() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UCmtWidgetController> Controller;

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnSetController();
};
