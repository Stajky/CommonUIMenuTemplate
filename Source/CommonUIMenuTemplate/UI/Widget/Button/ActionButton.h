// 

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Engine/DataTable.h"
#include "ActionButton.generated.h"

class UInputAction;
class UCommonActionWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSimpleDynamicDelegate);

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

	/* ~Start of UUserWidget */
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	/* ~End of UUserWidget */

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Hovered"))
	void BP_OnHovered();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Unhovered"))
	void BP_OnUnhovered();
	
protected:
	// UUserWidget interface
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	// End UUserWidget
	
private:
	void UpdateBindings();

	void RefreshInputActionIconValue();

	void NativeButtonPressed() const;
	
protected:
	/** Whether to register input immediately upon construction */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ActionButton, meta = (ExposeOnSpawn = "true"))
	bool bAutoListenForInput;

	/** The input action to listen for causing the skip */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ActionButton, meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle InputAction;

	/** The input action to listen for causing the skip */
	UPROPERTY(EditAnywhere,  BlueprintReadWrite, Category = ActionButton, meta = (EditCondition = "CommonInput.CommonInputSettings.IsEnhancedInputSupportEnabled", EditConditionHides))
	TObjectPtr<UInputAction> EnhancedInputAction;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FSimpleDynamicDelegate OnActionPressed;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, OptionalWidget = true))
	UCommonActionWidget* InputActionIcon;

private:
	bool bIsListeningForInput = false;

	FUIActionBindingHandle InputActionHandlePressed;
};
