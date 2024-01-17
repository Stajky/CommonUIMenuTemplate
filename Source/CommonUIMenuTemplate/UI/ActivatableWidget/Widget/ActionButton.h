﻿// 

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"


#include "Engine/DataTable.h"
#include "ActionButton.generated.h"

class UInputAction;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActionButtonPressed);
// DECLARE_DELEGATE(FSkipButtonPressed);
// DECLARE_DELEGATE(FSkipButtonReleased);

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = UI, meta = (Category = "CmtUI", DisableNativeTick))
class COMMONUIMENUTEMPLATE_API UActionButton : public UCommonUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = ActionButton)
	virtual void SetListeningForInput(bool bShouldListen);

protected:
	// UUserWidget interface
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	// End UUserWidget
	
private:
	void UpdateBindings();

	void NativeButtonPressed() const;
	
protected:
	/** Whether to register input immediately upon construction */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ActionButton, meta = (ExposeOnSpawn = "true"))
	bool bAutoListenForInput;

	/** The input action to listen for causing the skip */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ActionButton, meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle InputAction;

	/** The input action to listen for causing the skip */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ActionButton, meta = (EditCondition = "CommonInput.CommonInputSettings.IsEnhancedInputSupportEnabled", EditConditionHides))
	TObjectPtr<UInputAction> EnhancedInputAction;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FActionButtonPressed OnActionPressed;
	
private:
	bool bIsListeningForInput = false;

	FUIActionBindingHandle InputActionHandlePressed;
};