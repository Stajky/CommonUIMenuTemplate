// 

#pragma once

#include "CoreMinimal.h"
#include "SettingsEditor.h"
#include "SettingsEditorDiscrete.generated.h"

class UWidget;
class USwitchButton;
class UCommonButtonBase;



/**
 * 
 */
UCLASS()
class COMMONUIMENUTEMPLATE_API USettingsEditorDiscrete : public USettingsEditor
{
	GENERATED_BODY()

protected:
	// ~Start of UUserWidget
	virtual void NativeOnInitialized() override;
	//~End of UUserWidget

	// ~Start of USettingsEditor
	virtual UWidget* NativeGetPrimaryGamepadFocusWidget() override;
	// ~End of USettingsEditor

	void HandleOptionDecrease();
	void HandleOptionIncrease();
	
private:	// Bound Widgets
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<USwitchButton> SwitchButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCommonButtonBase> Button_Decrease;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCommonButtonBase> Button_Increase;
	
};
