// 

#pragma once

#include "CoreMinimal.h"
#include "SettingsEditor.h"
#include "SettingsEditorSlider.generated.h"

class UCmtSlider;
class UImage;
/**
 * 
 */
UCLASS()
class COMMONUIMENUTEMPLATE_API USettingsEditorSlider : public USettingsEditor
{
	GENERATED_BODY()

public:
	// ~Start of USettingsEditor
	virtual void SetCurrentAsDefaultOption() override;
	virtual void ResetToDefaultOption() override;
	// ~End of USettingsEditor
	
protected:
	// ~Start of UUserWidget
	virtual void NativeOnInitialized() override;
	//~End of UUserWidget
	
	// ~Start of USettingsEditor
	virtual UWidget* NativeGetPrimaryGamepadFocusWidget() override;
	// ~End of USettingsEditor
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float DefaultValue = 1.0f;

private:	// Bound Widgets
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCmtSlider> Slider;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UImage> ProgressImage;
};
