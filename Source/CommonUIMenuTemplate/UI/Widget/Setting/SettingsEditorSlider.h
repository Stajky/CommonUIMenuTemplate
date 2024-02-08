// 

#pragma once

#include "CoreMinimal.h"
#include "SettingsEditor.h"
#include "SettingsEditorSlider.generated.h"

class UCmtSlider;
/**
 * 
 */
UCLASS()
class COMMONUIMENUTEMPLATE_API USettingsEditorSlider : public USettingsEditor
{
	GENERATED_BODY()

protected:
	// ~Start of UUserWidget
	virtual void NativeOnInitialized() override;
	//~End of UUserWidget
	
	// ~Start of USettingsEditor
	virtual UWidget* NativeGetPrimaryGamepadFocusWidget() override;
	// ~End of USettingsEditor

private:	// Bound Widgets
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCmtSlider> Slider;
};
