// 


#include "SettingsEditorSlider.h"
#include "../../Slate/Widget/CmtSlider.h"
#include "Components/Image.h"

void USettingsEditorSlider::SetCurrentAsDefaultOption()
{
	DefaultValue = Slider->GetValue();
	UMaterialInstanceDynamic* DynamicMaterial = ProgressImage->GetDynamicMaterial();
	DynamicMaterial->SetScalarParameterValue("DefaultValue",DefaultValue);
	//Normally here we would save to our SettingsSystem, but we use mock data se we just set the visuals  
}

void USettingsEditorSlider::ResetToDefaultOption()
{
	UMaterialInstanceDynamic* DynamicMaterial = ProgressImage->GetDynamicMaterial();
	DynamicMaterial->SetScalarParameterValue("Progress",DefaultValue);
}

void USettingsEditorSlider::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	//Switch Button is de-facto the Focus of the whole setting (we need to so that it reads input)
	//We bind to its focus/unfocus delegates
	Slider->OnFocused().AddUObject(this, &ThisClass::BP_OnFocused);
	Slider->OnUnfocused().AddUObject(this, &ThisClass::BP_OnUnfocused);
}

UWidget* USettingsEditorSlider::NativeGetPrimaryGamepadFocusWidget()
{
	return Slider;
}
