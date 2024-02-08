// 


#include "SettingsEditorDiscrete.h"
#include "../Button/SwitchButton.h"
#include "CommonButtonBase.h"
#include "Components/Widget.h"


void USettingsEditorDiscrete::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	//Switch Button is de-facto the Focus of the whole setting (we need to so that it reads input)
	//We bind to its focus/unfocus delegates
	SwitchButton->OnFocusLost().AddUObject(this, &ThisClass::BP_OnUnfocused);
	SwitchButton->OnFocusReceived().AddUObject(this, &ThisClass::BP_OnFocused);
	
	Button_Decrease->OnClicked().AddUObject(this, &ThisClass::HandleOptionDecrease);
	Button_Increase->OnClicked().AddUObject(this, &ThisClass::HandleOptionIncrease);
}


UWidget* USettingsEditorDiscrete::NativeGetPrimaryGamepadFocusWidget()
{
	return SwitchButton;
}

void USettingsEditorDiscrete::HandleOptionDecrease()
{
	SwitchButton->ShiftTextLeft();
}

void USettingsEditorDiscrete::HandleOptionIncrease()
{
	SwitchButton->ShiftTextRight();
}
