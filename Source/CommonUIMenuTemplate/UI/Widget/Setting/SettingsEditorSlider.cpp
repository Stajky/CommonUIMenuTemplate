// 


#include "SettingsEditorSlider.h"
#include "../../Slate/Widget/CmtSlider.h"

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
