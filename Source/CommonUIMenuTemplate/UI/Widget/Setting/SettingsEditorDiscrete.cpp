// 


#include "SettingsEditorDiscrete.h"
#include "../Button/SwitchButton.h"
#include "CommonButtonBase.h"
#include "Components/Widget.h"


void USettingsEditorDiscrete::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
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
