// 


#include "SettingsEditor.h"
#include "CommonInputSubsystem.h"
#include "Components/TextBlock.h"
#include "CommonInputTypeEnum.h"


USettingsEditor::USettingsEditor()
{
	SetIsFocusable(true);
}

void USettingsEditor::SetCurrentAsDefaultOption()
{
}

void USettingsEditor::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (UCommonInputSubsystem* CommonInputSubsystem = UCommonInputSubsystem::Get(GetOwningLocalPlayer()))
	{
		CommonInputSubsystem->OnInputMethodChangedNative.AddUObject(this, &ThisClass::HandleInputMethodChanged);
	}	
}

void USettingsEditor::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	BP_OnHovered();
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
}

void USettingsEditor::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	BP_OnUnhovered();
	Super::NativeOnMouseLeave(InMouseEvent);
}

FReply USettingsEditor::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	const UCommonInputSubsystem* InputSubsystem = GetInputSubsystem();
	if (InputSubsystem && InputSubsystem->GetCurrentInputType() == ECommonInputType::Gamepad)
	{
		if (UWidget* PrimaryFocus = NativeGetPrimaryGamepadFocusWidget())
		{
			TSharedPtr<SWidget> WidgetToFocus = PrimaryFocus->GetCachedWidget();
			if (WidgetToFocus.IsValid())
			{
				return FReply::Handled().SetUserFocus(WidgetToFocus.ToSharedRef(), InFocusEvent.GetCause());
			}
		}
	}
	
	return FReply::Unhandled();
}

void USettingsEditor::NativeOnFocusLost(const FFocusEvent& InFocusEvent)
{
	
}

UWidget* USettingsEditor::NativeGetPrimaryGamepadFocusWidget()
{
	return nullptr;
}

void USettingsEditor::HandleInputMethodChanged(ECommonInputType CurrentInputType)
{
	InputType = CurrentInputType;
}
