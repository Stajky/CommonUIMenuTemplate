// 

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"


#include "Engine/DataTable.h"
#include "SkipButton.generated.h"

class UInputAction;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSkipButtonPressed);
// DECLARE_DELEGATE(FSkipButtonPressed);
// DECLARE_DELEGATE(FSkipButtonReleased);

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = UI, meta = (Category = "CmtUI", DisableNativeTick))
class COMMONUIMENUTEMPLATE_API USkipButton : public UCommonUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = TabList)
	virtual void SetListeningForInput(bool bShouldListen);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_HeldProgressEvent(float HeldPercent);


protected:
	// UUserWidget interface
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	// End UUserWidget
	
private:
	void UpdateBindings();

	void NativeSkipButtonPressed() const;

	void NativeHeldProgress(float HeldPercent);
	
protected:
	/** Whether to register input immediately upon construction */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SkipButton, meta = (ExposeOnSpawn = "true"))
	bool bAutoListenForInput;

	/** The input action to listen for causing the skip */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SkipButton, meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle InputAction;

	/** The input action to listen for causing the skip */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SkipButton, meta = (EditCondition = "CommonInput.CommonInputSettings.IsEnhancedInputSupportEnabled", EditConditionHides))
	TObjectPtr<UInputAction> EnhancedInputAction;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FSkipButtonPressed OnSkipButtonPressed;
	
private:
	bool bIsListeningForInput = false;

	FUIActionBindingHandle InputActionHandlePressed;
};
